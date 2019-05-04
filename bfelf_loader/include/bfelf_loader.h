/*
 * Copyright (C) 2019 Assured Information Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file bfelf_loader.h
 *
 * Motivation:
 *
 * We need a way to load an ELF executable as shellcode from both the Linux and
 * Windows kernels as well as UEFI. At the time of writing, there wasn't a
 * header-only library designed to load ELF executables that doesn't have
 * dependencies on an OS. The goal of this ELF loader is to provide such
 * support with the following features:
 * - Capable of loading ELF executables in any C/C++ environment
 * - Header-only
 * - Well tested and statically/dynamically analyzed.
 *
 * There are some limitations:
 * - The ELF exectuable must be compiled as a static PIE. Note that this does
 *   not mean or support the use of GCC's "-static-pie" option. This option
 *   is a GCC/Linux specific thing designed to add libgcc functionality to the
 *   resulting executable which performs the relocations itself. This code
 *   relies on OS level stuff that we do not/can not use. Instead, this library
 *   assumes that the ELF executable was compiled using a freestanding
 *   environment, and as such, this ELF loader provides the logic to perform
 *   the needed relocations prior to execution. For this reason, we assume that
 *   linking is handled manually by the user and the following flags were
 *   used at a minimum:
 *   GCC/Clang: -fpie
 *   LD: --no-dynamic-linker -nostdlib -pie -static
 *
 * - R_xxx_RELATIVE is the only relocation type that is currently supported.
 *   This relocation type is simple and doesn't require symbol information.
 *   Instead, it simply needs the load offset for the position independent
 *   executable.
 *
 * - Memory allocation (or mapping) must be provided. In other ELF loader
 *   implementations, you pass the ELF file to it, and boom... you have a
 *   working ELF executable. This is not the case with this library as RWE
 *   memory is needed (you can always mprotect back to RW later). How this
 *   memory is allocated or mapped depends on the OS. So, this library breaks
 *   the load option into two steps. The first step initializes an internal ELF
 *   structure with information about the ELF file. The user then allocates
 *   the needed memory with RWE (or RW and then you manually mprotect RE as
 *   needed). The second and final step loads the ELF file into the allocated
 *   memory and then performs the needed relocations.
 *
 * - Since this is C code, there really is no way to validate that the user
 *   isn't using the APIs properly. This includes dumb things like allocating
 *   the wrong sized memory, passing invalid pointers, etc... To handle this
 *   issue, we test the hell out of the code including 100% unit test coverage,
 *   static/dynamic analysis, etc...
 *
 * - There are some limitations on what types of ELF files this loader will
 *   except. These limitation include:
 *   - We only support a single RE and a single RW PT_LOAD segment. If there are
 *     more, or if the segments are labeled RWE, we do not support that.
 *   - We only support a single RELA section. REL sections are not supported.
 *     Furthermore, the only relocation type that we support is R_xxx_RELATIVE.
 *   - We do not support the legacy init, fini, ctors and dtors sections.
 */

#ifndef BFELF_LOADER_H
#define BFELF_LOADER_H

#include "bfelf_loader_private.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @struct bfelf_file_t
 *
 * The bfelf_file_t structure is used to store information about the ELF file
 * that is useful/needed by the user of these APIs, as well as store internal
 * private state that should not be used by the user. That "public" fields in
 * this structure are as follows. All other fields should be ignored as they
 * are subject to change.
 *
 * @var bfelf_file_t::size
 *      the size of the ELF exectuable (filled by bfelf_file_init)
 * @var bfelf_file_t::entry
 *      the _start function for the ELF exectuable (filled by bfelf_file_load)
 * @var bfelf_file_t::rx_addr
 *      the address of the RE program segment (filled by bfelf_file_load)
 * @var bfelf_file_t::rx_size
 *      the size of the RE program segment (filled by bfelf_file_load)
 * @var bfelf_file_t::rw_addr
 *      the address of the RW program segment (filled by bfelf_file_load)
 * @var bfelf_file_t::rw_size
 *      the size of the RW program segment (filled by bfelf_file_load)
 * @var bfelf_file_t::rw_size
 *      the size of the RW program segment (filled by bfelf_file_load)
 * @var bfelf_file_t::init_array_addr
 *      the address of the init array section (filled by bfelf_file_load)
 * @var bfelf_file_t::init_array_size
 *      the size of the init array section (filled by bfelf_file_load)
 * @var bfelf_file_t::fini_array_addr
 *      the address of the fini array section (filled by bfelf_file_load)
 * @var bfelf_file_t::fini_array_size
 *      the size of the fini array section (filled by bfelf_file_load)
 * @var bfelf_file_t::eh_frame_addr
 *      the address of the eh_frame section (filled by bfelf_file_load)
 * @var bfelf_file_t::eh_frame_size
 *      the size of the eh_frame section (filled by bfelf_file_load)
 */

/**
 * Initialize an ELF file
 *
 * This function initializes an ELF file structure given the file's contents
 * in memory. The resulting structure will be used by the bfelf_file_load and
 * as a result, this function must be execute prior to executing the
 * bfelf_file_load() function.
 *
 * After executing this function, the bfelf_file structure will have the total
 * size of the memory needed by the executable stored. Therefore, the proper
 * way to use this API is the following:
 *
 * @code
 * struct bfelf_file_t ef;
 * bfelf_file_init(file, filesz, &ef);
 * uint8_t *exec = (uint8_t *)malloc(ef.size);
 * bfelf_file_load(exec, nullptr, &ef);
 * @endcode
 *
 * It should ne noted that after this function is executed, the only field
 * that is valid from the bfelf_file_t structure is the "size" field. All
 * other fields are only valid after executing bfelf_file_load.
 *
 * @expects file != nullptr
 * @expects filesz != nullptr
 * @expects ef != nullptr
 * @ensures
 *
 * @param file a character buffer containing the contents of the ELF file to
 *     be loaded.
 * @param filesz the size of the character buffer
 * @param ef a pointer to the bfelf_file_t structure which stores information
 *     about the ELF file being loaded.
 * @return ELF_SUCCESS on success, negative on error
 */
static inline status_t
bfelf_file_init(const uint8_t *file, uint64_t filesz, struct bfelf_file_t *ef);

/**
 * Load an ELF file
 *
 * This function loads the ELF file that was previously initialized using the
 * bfelf_file_init function. The main purpose of the bfelf_file_init function
 * is to make sure the ELF file is valid, to store some private internal state
 * and then populate the "size" field so that the user of these APIs knows
 * how much RWE memory to allocate. The ELF file itself cannot be directly
 * executed and instead must be loaded into memory based on instructions
 * provided by the ELF file's program headers. This API forces the user to
 * allocate this memory for the APIs as allocating RWE memory is platform
 * specific. Once this memory is allocated, this function can be called which
 * will actually load the ELF file into memory so that it can be executed.
 *
 * Besides providing the bfelf_file_t that was initialied using the
 * bfelf_file_init() function, this function takes two additional parameters.
 * The first, "exec" is the address to the RWE memory that must be allocated
 * by the user. The total size of this memory is provided by the ef.size
 * field after executing bfelf_file_init(). The "virt" parameter is needed
 * because in the ELF file needs to be relocated and the address that the ELF
 * file is being relocated too might not be the same address as "exec". If you
 * are using the ELF loader for shellcode, "exec" and "virt" are the same, and
 * you can pass the pointer you allocated for "exec" to "virt" or you can simply
 * pass a nullptr and the APIs will set "virt" to "exec" for you. If however
 * you are using the ELF loader in a custom kernel or hypervisor, and the
 * executable will be executing with a virtual address (i.e. its own pages
 * tables) that is different from the virtual address that is being used to
 * initialize the executables memory, you must set "virt" to the starting
 * address of the executable as the executable would see it. This ensures that
 * all of the relocations are performed using the memory space the executable
 * expects to see, and not the one that was used to load the executable.
 *
 * Also not that the "exec" buffer needs to be allocated with RWE privileges.
 * You could also allocate the "exec" buffer using RW privileges and then
 * use the ef.rx_addr and ef.rx_size to mark the RE segment as RE once you are
 * done loading the ELF file (and before you attempt to execute it). Either
 * will work and just depends on your use case.
 *
 * @code
 * struct bfelf_file_t ef;
 * bfelf_file_init(file, filesz, &ef);
 * uint8_t *exec = (uint8_t *)malloc(ef.size);
 * bfelf_file_load(exec, nullptr, &ef);
 * @endcode
 *
 * @expects exec != nullptr
 * @expects ef != nullptr
 * @ensures
 *
 * @param exec a buffer of memory the size of "ef.size" with RWE privileges.
 * @param virt the virtual address the executable will be relocated to.
 * @param ef the ELF file structure to initialize.
 * @return ELF_SUCCESS on success, negative on error
 */
static inline status_t
bfelf_file_load(uint8_t *exec, uint8_t *virt, struct bfelf_file_t *ef);

#ifdef __cplusplus
}
#endif

#endif
