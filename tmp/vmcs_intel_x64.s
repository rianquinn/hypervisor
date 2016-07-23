	.file	"vmcs_intel_x64.cpp"
	.section	.rodata
	.type	_ZNSt3__1L19piecewise_constructE, @object
	.size	_ZNSt3__1L19piecewise_constructE, 1
_ZNSt3__1L19piecewise_constructE:
	.zero	1
	.type	_ZNSt3__1L13allocator_argE, @object
	.size	_ZNSt3__1L13allocator_argE, 1
_ZNSt3__1L13allocator_argE:
	.zero	1
	.type	_ZNSt3__112_GLOBAL__N_1L6ignoreE, @object
	.size	_ZNSt3__112_GLOBAL__N_1L6ignoreE, 1
_ZNSt3__112_GLOBAL__N_1L6ignoreE:
	.zero	1
	.section	.text._ZNSt3__111char_traitsIcE6lengthEPKc,"axG",@progbits,_ZNSt3__111char_traitsIcE6lengthEPKc,comdat
	.weak	_ZNSt3__111char_traitsIcE6lengthEPKc
	.type	_ZNSt3__111char_traitsIcE6lengthEPKc, @function
_ZNSt3__111char_traitsIcE6lengthEPKc:
.LFB1180:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1180:
	.size	_ZNSt3__111char_traitsIcE6lengthEPKc, .-_ZNSt3__111char_traitsIcE6lengthEPKc
	.section	.text._ZNSt3__111char_traitsIcE11eq_int_typeEii,"axG",@progbits,_ZNSt3__111char_traitsIcE11eq_int_typeEii,comdat
	.weak	_ZNSt3__111char_traitsIcE11eq_int_typeEii
	.type	_ZNSt3__111char_traitsIcE11eq_int_typeEii, @function
_ZNSt3__111char_traitsIcE11eq_int_typeEii:
.LFB1188:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	sete	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1188:
	.size	_ZNSt3__111char_traitsIcE11eq_int_typeEii, .-_ZNSt3__111char_traitsIcE11eq_int_typeEii
	.section	.text._ZNSt3__111char_traitsIcE3eofEv,"axG",@progbits,_ZNSt3__111char_traitsIcE3eofEv,comdat
	.weak	_ZNSt3__111char_traitsIcE3eofEv
	.type	_ZNSt3__111char_traitsIcE3eofEv, @function
_ZNSt3__111char_traitsIcE3eofEv:
.LFB1189:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$-1, %eax
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1189:
	.size	_ZNSt3__111char_traitsIcE3eofEv, .-_ZNSt3__111char_traitsIcE3eofEv
	.section	.text._ZN18commit_or_rollbackC2EONSt3__18functionIFvvEEE,"axG",@progbits,_ZN18commit_or_rollbackC5EONSt3__18functionIFvvEEE,comdat
	.align 2
	.weak	_ZN18commit_or_rollbackC2EONSt3__18functionIFvvEEE
	.type	_ZN18commit_or_rollbackC2EONSt3__18functionIFvvEEE, @function
_ZN18commit_or_rollbackC2EONSt3__18functionIFvvEEE:
.LFB2694:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movb	$0, (%rax)
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	addq	$16, %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSt3__18functionIFvvEEC1EOS2_@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2694:
	.size	_ZN18commit_or_rollbackC2EONSt3__18functionIFvvEEE, .-_ZN18commit_or_rollbackC2EONSt3__18functionIFvvEEE
	.weak	_ZN18commit_or_rollbackC1EONSt3__18functionIFvvEEE
	.set	_ZN18commit_or_rollbackC1EONSt3__18functionIFvvEEE,_ZN18commit_or_rollbackC2EONSt3__18functionIFvvEEE
	.section	.text._ZN18commit_or_rollbackD2Ev,"axG",@progbits,_ZN18commit_or_rollbackD5Ev,comdat
	.align 2
	.weak	_ZN18commit_or_rollbackD2Ev
	.type	_ZN18commit_or_rollbackD2Ev, @function
_ZN18commit_or_rollbackD2Ev:
.LFB2697:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2697
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L10
	movq	-8(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	_ZNKSt3__18functionIFvvEEclEv@PLT
.L10:
	movq	-8(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	_ZNSt3__18functionIFvvEED1Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2697:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN18commit_or_rollbackD2Ev,"aG",@progbits,_ZN18commit_or_rollbackD5Ev,comdat
.LLSDA2697:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2697-.LLSDACSB2697
.LLSDACSB2697:
.LLSDACSE2697:
	.section	.text._ZN18commit_or_rollbackD2Ev,"axG",@progbits,_ZN18commit_or_rollbackD5Ev,comdat
	.size	_ZN18commit_or_rollbackD2Ev, .-_ZN18commit_or_rollbackD2Ev
	.weak	_ZN18commit_or_rollbackD1Ev
	.set	_ZN18commit_or_rollbackD1Ev,_ZN18commit_or_rollbackD2Ev
	.section	.text._ZN18commit_or_rollback6commitEv,"axG",@progbits,_ZN18commit_or_rollback6commitEv,comdat
	.align 2
	.weak	_ZN18commit_or_rollback6commitEv
	.type	_ZN18commit_or_rollback6commitEv, @function
_ZN18commit_or_rollback6commitEv:
.LFB2699:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movb	$1, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2699:
	.size	_ZN18commit_or_rollback6commitEv, .-_ZN18commit_or_rollback6commitEv
	.section	.text._ZN14intrinsics_x64C2Ev,"axG",@progbits,_ZN14intrinsics_x64C5Ev,comdat
	.align 2
	.weak	_ZN14intrinsics_x64C2Ev
	.type	_ZN14intrinsics_x64C2Ev, @function
_ZN14intrinsics_x64C2Ev:
.LFB2701:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTV14intrinsics_x64@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2701:
	.size	_ZN14intrinsics_x64C2Ev, .-_ZN14intrinsics_x64C2Ev
	.weak	_ZN14intrinsics_x64C1Ev
	.set	_ZN14intrinsics_x64C1Ev,_ZN14intrinsics_x64C2Ev
	.section	.text._ZN14intrinsics_x64D2Ev,"axG",@progbits,_ZN14intrinsics_x64D5Ev,comdat
	.align 2
	.weak	_ZN14intrinsics_x64D2Ev
	.type	_ZN14intrinsics_x64D2Ev, @function
_ZN14intrinsics_x64D2Ev:
.LFB2704:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTV14intrinsics_x64@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2704:
	.size	_ZN14intrinsics_x64D2Ev, .-_ZN14intrinsics_x64D2Ev
	.weak	_ZN14intrinsics_x64D1Ev
	.set	_ZN14intrinsics_x64D1Ev,_ZN14intrinsics_x64D2Ev
	.section	.text._ZN14intrinsics_x64D0Ev,"axG",@progbits,_ZN14intrinsics_x64D5Ev,comdat
	.align 2
	.weak	_ZN14intrinsics_x64D0Ev
	.type	_ZN14intrinsics_x64D0Ev, @function
_ZN14intrinsics_x64D0Ev:
.LFB2706:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN14intrinsics_x64D1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2706:
	.size	_ZN14intrinsics_x64D0Ev, .-_ZN14intrinsics_x64D0Ev
	.section	.text._ZNK14intrinsics_x644haltEv,"axG",@progbits,_ZNK14intrinsics_x644haltEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x644haltEv
	.type	_ZNK14intrinsics_x644haltEv, @function
_ZNK14intrinsics_x644haltEv:
.LFB2707:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2707
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__halt@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2707:
	.section	.gcc_except_table._ZNK14intrinsics_x644haltEv,"aG",@progbits,_ZNK14intrinsics_x644haltEv,comdat
.LLSDA2707:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2707-.LLSDACSB2707
.LLSDACSB2707:
.LLSDACSE2707:
	.section	.text._ZNK14intrinsics_x644haltEv,"axG",@progbits,_ZNK14intrinsics_x644haltEv,comdat
	.size	_ZNK14intrinsics_x644haltEv, .-_ZNK14intrinsics_x644haltEv
	.section	.text._ZNK14intrinsics_x644stopEv,"axG",@progbits,_ZNK14intrinsics_x644stopEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x644stopEv
	.type	_ZNK14intrinsics_x644stopEv, @function
_ZNK14intrinsics_x644stopEv:
.LFB2708:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2708
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__stop@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2708:
	.section	.gcc_except_table._ZNK14intrinsics_x644stopEv,"aG",@progbits,_ZNK14intrinsics_x644stopEv,comdat
.LLSDA2708:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2708-.LLSDACSB2708
.LLSDACSB2708:
.LLSDACSE2708:
	.section	.text._ZNK14intrinsics_x644stopEv,"axG",@progbits,_ZNK14intrinsics_x644stopEv,comdat
	.size	_ZNK14intrinsics_x644stopEv, .-_ZNK14intrinsics_x644stopEv
	.section	.text._ZNK14intrinsics_x644invdEv,"axG",@progbits,_ZNK14intrinsics_x644invdEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x644invdEv
	.type	_ZNK14intrinsics_x644invdEv, @function
_ZNK14intrinsics_x644invdEv:
.LFB2709:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2709
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__invd@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2709:
	.section	.gcc_except_table._ZNK14intrinsics_x644invdEv,"aG",@progbits,_ZNK14intrinsics_x644invdEv,comdat
.LLSDA2709:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2709-.LLSDACSB2709
.LLSDACSB2709:
.LLSDACSE2709:
	.section	.text._ZNK14intrinsics_x644invdEv,"axG",@progbits,_ZNK14intrinsics_x644invdEv,comdat
	.size	_ZNK14intrinsics_x644invdEv, .-_ZNK14intrinsics_x644invdEv
	.section	.text._ZNK14intrinsics_x646wbinvdEv,"axG",@progbits,_ZNK14intrinsics_x646wbinvdEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x646wbinvdEv
	.type	_ZNK14intrinsics_x646wbinvdEv, @function
_ZNK14intrinsics_x646wbinvdEv:
.LFB2710:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2710
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__wbinvd@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2710:
	.section	.gcc_except_table._ZNK14intrinsics_x646wbinvdEv,"aG",@progbits,_ZNK14intrinsics_x646wbinvdEv,comdat
.LLSDA2710:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2710-.LLSDACSB2710
.LLSDACSB2710:
.LLSDACSE2710:
	.section	.text._ZNK14intrinsics_x646wbinvdEv,"axG",@progbits,_ZNK14intrinsics_x646wbinvdEv,comdat
	.size	_ZNK14intrinsics_x646wbinvdEv, .-_ZNK14intrinsics_x646wbinvdEv
	.section	.text._ZNK14intrinsics_x649cpuid_eaxEj,"axG",@progbits,_ZNK14intrinsics_x649cpuid_eaxEj,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649cpuid_eaxEj
	.type	_ZNK14intrinsics_x649cpuid_eaxEj, @function
_ZNK14intrinsics_x649cpuid_eaxEj:
.LFB2711:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2711
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__cpuid_eax@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2711:
	.section	.gcc_except_table._ZNK14intrinsics_x649cpuid_eaxEj,"aG",@progbits,_ZNK14intrinsics_x649cpuid_eaxEj,comdat
.LLSDA2711:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2711-.LLSDACSB2711
.LLSDACSB2711:
.LLSDACSE2711:
	.section	.text._ZNK14intrinsics_x649cpuid_eaxEj,"axG",@progbits,_ZNK14intrinsics_x649cpuid_eaxEj,comdat
	.size	_ZNK14intrinsics_x649cpuid_eaxEj, .-_ZNK14intrinsics_x649cpuid_eaxEj
	.section	.text._ZNK14intrinsics_x649cpuid_ebxEj,"axG",@progbits,_ZNK14intrinsics_x649cpuid_ebxEj,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649cpuid_ebxEj
	.type	_ZNK14intrinsics_x649cpuid_ebxEj, @function
_ZNK14intrinsics_x649cpuid_ebxEj:
.LFB2712:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2712
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__cpuid_ebx@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2712:
	.section	.gcc_except_table._ZNK14intrinsics_x649cpuid_ebxEj,"aG",@progbits,_ZNK14intrinsics_x649cpuid_ebxEj,comdat
.LLSDA2712:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2712-.LLSDACSB2712
.LLSDACSB2712:
.LLSDACSE2712:
	.section	.text._ZNK14intrinsics_x649cpuid_ebxEj,"axG",@progbits,_ZNK14intrinsics_x649cpuid_ebxEj,comdat
	.size	_ZNK14intrinsics_x649cpuid_ebxEj, .-_ZNK14intrinsics_x649cpuid_ebxEj
	.section	.text._ZNK14intrinsics_x649cpuid_ecxEj,"axG",@progbits,_ZNK14intrinsics_x649cpuid_ecxEj,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649cpuid_ecxEj
	.type	_ZNK14intrinsics_x649cpuid_ecxEj, @function
_ZNK14intrinsics_x649cpuid_ecxEj:
.LFB2713:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2713
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__cpuid_ecx@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2713:
	.section	.gcc_except_table._ZNK14intrinsics_x649cpuid_ecxEj,"aG",@progbits,_ZNK14intrinsics_x649cpuid_ecxEj,comdat
.LLSDA2713:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2713-.LLSDACSB2713
.LLSDACSB2713:
.LLSDACSE2713:
	.section	.text._ZNK14intrinsics_x649cpuid_ecxEj,"axG",@progbits,_ZNK14intrinsics_x649cpuid_ecxEj,comdat
	.size	_ZNK14intrinsics_x649cpuid_ecxEj, .-_ZNK14intrinsics_x649cpuid_ecxEj
	.section	.text._ZNK14intrinsics_x649cpuid_edxEj,"axG",@progbits,_ZNK14intrinsics_x649cpuid_edxEj,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649cpuid_edxEj
	.type	_ZNK14intrinsics_x649cpuid_edxEj, @function
_ZNK14intrinsics_x649cpuid_edxEj:
.LFB2714:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2714
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__cpuid_edx@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2714:
	.section	.gcc_except_table._ZNK14intrinsics_x649cpuid_edxEj,"aG",@progbits,_ZNK14intrinsics_x649cpuid_edxEj,comdat
.LLSDA2714:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2714-.LLSDACSB2714
.LLSDACSB2714:
.LLSDACSE2714:
	.section	.text._ZNK14intrinsics_x649cpuid_edxEj,"axG",@progbits,_ZNK14intrinsics_x649cpuid_edxEj,comdat
	.size	_ZNK14intrinsics_x649cpuid_edxEj, .-_ZNK14intrinsics_x649cpuid_edxEj
	.section	.text._ZNK14intrinsics_x645cpuidEPmS0_S0_S0_,"axG",@progbits,_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_,comdat
	.align 2
	.weak	_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_
	.type	_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_, @function
_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_:
.LFB2715:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2715
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rsi
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__cpuid@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2715:
	.section	.gcc_except_table._ZNK14intrinsics_x645cpuidEPmS0_S0_S0_,"aG",@progbits,_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_,comdat
.LLSDA2715:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2715-.LLSDACSB2715
.LLSDACSB2715:
.LLSDACSE2715:
	.section	.text._ZNK14intrinsics_x645cpuidEPmS0_S0_S0_,"axG",@progbits,_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_,comdat
	.size	_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_, .-_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_
	.section	.text._ZNK14intrinsics_x6411read_rflagsEv,"axG",@progbits,_ZNK14intrinsics_x6411read_rflagsEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x6411read_rflagsEv
	.type	_ZNK14intrinsics_x6411read_rflagsEv, @function
_ZNK14intrinsics_x6411read_rflagsEv:
.LFB2716:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2716
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_rflags@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2716:
	.section	.gcc_except_table._ZNK14intrinsics_x6411read_rflagsEv,"aG",@progbits,_ZNK14intrinsics_x6411read_rflagsEv,comdat
.LLSDA2716:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2716-.LLSDACSB2716
.LLSDACSB2716:
.LLSDACSE2716:
	.section	.text._ZNK14intrinsics_x6411read_rflagsEv,"axG",@progbits,_ZNK14intrinsics_x6411read_rflagsEv,comdat
	.size	_ZNK14intrinsics_x6411read_rflagsEv, .-_ZNK14intrinsics_x6411read_rflagsEv
	.section	.text._ZNK14intrinsics_x648read_msrEj,"axG",@progbits,_ZNK14intrinsics_x648read_msrEj,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_msrEj
	.type	_ZNK14intrinsics_x648read_msrEj, @function
_ZNK14intrinsics_x648read_msrEj:
.LFB2717:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2717
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__read_msr@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2717:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_msrEj,"aG",@progbits,_ZNK14intrinsics_x648read_msrEj,comdat
.LLSDA2717:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2717-.LLSDACSB2717
.LLSDACSB2717:
.LLSDACSE2717:
	.section	.text._ZNK14intrinsics_x648read_msrEj,"axG",@progbits,_ZNK14intrinsics_x648read_msrEj,comdat
	.size	_ZNK14intrinsics_x648read_msrEj, .-_ZNK14intrinsics_x648read_msrEj
	.section	.text._ZNK14intrinsics_x649write_msrEjm,"axG",@progbits,_ZNK14intrinsics_x649write_msrEjm,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649write_msrEjm
	.type	_ZNK14intrinsics_x649write_msrEjm, @function
_ZNK14intrinsics_x649write_msrEjm:
.LFB2718:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2718
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movl	-12(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	__write_msr@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2718:
	.section	.gcc_except_table._ZNK14intrinsics_x649write_msrEjm,"aG",@progbits,_ZNK14intrinsics_x649write_msrEjm,comdat
.LLSDA2718:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2718-.LLSDACSB2718
.LLSDACSB2718:
.LLSDACSE2718:
	.section	.text._ZNK14intrinsics_x649write_msrEjm,"axG",@progbits,_ZNK14intrinsics_x649write_msrEjm,comdat
	.size	_ZNK14intrinsics_x649write_msrEjm, .-_ZNK14intrinsics_x649write_msrEjm
	.section	.text._ZNK14intrinsics_x648read_ripEv,"axG",@progbits,_ZNK14intrinsics_x648read_ripEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_ripEv
	.type	_ZNK14intrinsics_x648read_ripEv, @function
_ZNK14intrinsics_x648read_ripEv:
.LFB2719:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2719
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_rip@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2719:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_ripEv,"aG",@progbits,_ZNK14intrinsics_x648read_ripEv,comdat
.LLSDA2719:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2719-.LLSDACSB2719
.LLSDACSB2719:
.LLSDACSE2719:
	.section	.text._ZNK14intrinsics_x648read_ripEv,"axG",@progbits,_ZNK14intrinsics_x648read_ripEv,comdat
	.size	_ZNK14intrinsics_x648read_ripEv, .-_ZNK14intrinsics_x648read_ripEv
	.section	.text._ZNK14intrinsics_x648read_cr0Ev,"axG",@progbits,_ZNK14intrinsics_x648read_cr0Ev,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_cr0Ev
	.type	_ZNK14intrinsics_x648read_cr0Ev, @function
_ZNK14intrinsics_x648read_cr0Ev:
.LFB2720:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2720
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_cr0@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2720:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_cr0Ev,"aG",@progbits,_ZNK14intrinsics_x648read_cr0Ev,comdat
.LLSDA2720:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2720-.LLSDACSB2720
.LLSDACSB2720:
.LLSDACSE2720:
	.section	.text._ZNK14intrinsics_x648read_cr0Ev,"axG",@progbits,_ZNK14intrinsics_x648read_cr0Ev,comdat
	.size	_ZNK14intrinsics_x648read_cr0Ev, .-_ZNK14intrinsics_x648read_cr0Ev
	.section	.text._ZNK14intrinsics_x649write_cr0Em,"axG",@progbits,_ZNK14intrinsics_x649write_cr0Em,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649write_cr0Em
	.type	_ZNK14intrinsics_x649write_cr0Em, @function
_ZNK14intrinsics_x649write_cr0Em:
.LFB2721:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2721
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__write_cr0@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2721:
	.section	.gcc_except_table._ZNK14intrinsics_x649write_cr0Em,"aG",@progbits,_ZNK14intrinsics_x649write_cr0Em,comdat
.LLSDA2721:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2721-.LLSDACSB2721
.LLSDACSB2721:
.LLSDACSE2721:
	.section	.text._ZNK14intrinsics_x649write_cr0Em,"axG",@progbits,_ZNK14intrinsics_x649write_cr0Em,comdat
	.size	_ZNK14intrinsics_x649write_cr0Em, .-_ZNK14intrinsics_x649write_cr0Em
	.section	.text._ZNK14intrinsics_x648read_cr3Ev,"axG",@progbits,_ZNK14intrinsics_x648read_cr3Ev,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_cr3Ev
	.type	_ZNK14intrinsics_x648read_cr3Ev, @function
_ZNK14intrinsics_x648read_cr3Ev:
.LFB2722:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2722
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_cr3@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2722:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_cr3Ev,"aG",@progbits,_ZNK14intrinsics_x648read_cr3Ev,comdat
.LLSDA2722:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2722-.LLSDACSB2722
.LLSDACSB2722:
.LLSDACSE2722:
	.section	.text._ZNK14intrinsics_x648read_cr3Ev,"axG",@progbits,_ZNK14intrinsics_x648read_cr3Ev,comdat
	.size	_ZNK14intrinsics_x648read_cr3Ev, .-_ZNK14intrinsics_x648read_cr3Ev
	.section	.text._ZNK14intrinsics_x649write_cr3Em,"axG",@progbits,_ZNK14intrinsics_x649write_cr3Em,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649write_cr3Em
	.type	_ZNK14intrinsics_x649write_cr3Em, @function
_ZNK14intrinsics_x649write_cr3Em:
.LFB2723:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2723
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__write_cr3@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2723:
	.section	.gcc_except_table._ZNK14intrinsics_x649write_cr3Em,"aG",@progbits,_ZNK14intrinsics_x649write_cr3Em,comdat
.LLSDA2723:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2723-.LLSDACSB2723
.LLSDACSB2723:
.LLSDACSE2723:
	.section	.text._ZNK14intrinsics_x649write_cr3Em,"axG",@progbits,_ZNK14intrinsics_x649write_cr3Em,comdat
	.size	_ZNK14intrinsics_x649write_cr3Em, .-_ZNK14intrinsics_x649write_cr3Em
	.section	.text._ZNK14intrinsics_x648read_cr4Ev,"axG",@progbits,_ZNK14intrinsics_x648read_cr4Ev,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_cr4Ev
	.type	_ZNK14intrinsics_x648read_cr4Ev, @function
_ZNK14intrinsics_x648read_cr4Ev:
.LFB2724:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2724
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_cr4@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2724:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_cr4Ev,"aG",@progbits,_ZNK14intrinsics_x648read_cr4Ev,comdat
.LLSDA2724:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2724-.LLSDACSB2724
.LLSDACSB2724:
.LLSDACSE2724:
	.section	.text._ZNK14intrinsics_x648read_cr4Ev,"axG",@progbits,_ZNK14intrinsics_x648read_cr4Ev,comdat
	.size	_ZNK14intrinsics_x648read_cr4Ev, .-_ZNK14intrinsics_x648read_cr4Ev
	.section	.text._ZNK14intrinsics_x649write_cr4Em,"axG",@progbits,_ZNK14intrinsics_x649write_cr4Em,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649write_cr4Em
	.type	_ZNK14intrinsics_x649write_cr4Em, @function
_ZNK14intrinsics_x649write_cr4Em:
.LFB2725:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2725
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__write_cr4@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2725:
	.section	.gcc_except_table._ZNK14intrinsics_x649write_cr4Em,"aG",@progbits,_ZNK14intrinsics_x649write_cr4Em,comdat
.LLSDA2725:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2725-.LLSDACSB2725
.LLSDACSB2725:
.LLSDACSE2725:
	.section	.text._ZNK14intrinsics_x649write_cr4Em,"axG",@progbits,_ZNK14intrinsics_x649write_cr4Em,comdat
	.size	_ZNK14intrinsics_x649write_cr4Em, .-_ZNK14intrinsics_x649write_cr4Em
	.section	.text._ZNK14intrinsics_x649read_xcr0Ev,"axG",@progbits,_ZNK14intrinsics_x649read_xcr0Ev,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649read_xcr0Ev
	.type	_ZNK14intrinsics_x649read_xcr0Ev, @function
_ZNK14intrinsics_x649read_xcr0Ev:
.LFB2726:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2726
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_xcr0@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2726:
	.section	.gcc_except_table._ZNK14intrinsics_x649read_xcr0Ev,"aG",@progbits,_ZNK14intrinsics_x649read_xcr0Ev,comdat
.LLSDA2726:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2726-.LLSDACSB2726
.LLSDACSB2726:
.LLSDACSE2726:
	.section	.text._ZNK14intrinsics_x649read_xcr0Ev,"axG",@progbits,_ZNK14intrinsics_x649read_xcr0Ev,comdat
	.size	_ZNK14intrinsics_x649read_xcr0Ev, .-_ZNK14intrinsics_x649read_xcr0Ev
	.section	.text._ZNK14intrinsics_x6410write_xcr0Em,"axG",@progbits,_ZNK14intrinsics_x6410write_xcr0Em,comdat
	.align 2
	.weak	_ZNK14intrinsics_x6410write_xcr0Em
	.type	_ZNK14intrinsics_x6410write_xcr0Em, @function
_ZNK14intrinsics_x6410write_xcr0Em:
.LFB2727:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2727
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__write_xcr0@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2727:
	.section	.gcc_except_table._ZNK14intrinsics_x6410write_xcr0Em,"aG",@progbits,_ZNK14intrinsics_x6410write_xcr0Em,comdat
.LLSDA2727:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2727-.LLSDACSB2727
.LLSDACSB2727:
.LLSDACSE2727:
	.section	.text._ZNK14intrinsics_x6410write_xcr0Em,"axG",@progbits,_ZNK14intrinsics_x6410write_xcr0Em,comdat
	.size	_ZNK14intrinsics_x6410write_xcr0Em, .-_ZNK14intrinsics_x6410write_xcr0Em
	.section	.text._ZNK14intrinsics_x648read_dr7Ev,"axG",@progbits,_ZNK14intrinsics_x648read_dr7Ev,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_dr7Ev
	.type	_ZNK14intrinsics_x648read_dr7Ev, @function
_ZNK14intrinsics_x648read_dr7Ev:
.LFB2728:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2728
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_dr7@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2728:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_dr7Ev,"aG",@progbits,_ZNK14intrinsics_x648read_dr7Ev,comdat
.LLSDA2728:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2728-.LLSDACSB2728
.LLSDACSB2728:
.LLSDACSE2728:
	.section	.text._ZNK14intrinsics_x648read_dr7Ev,"axG",@progbits,_ZNK14intrinsics_x648read_dr7Ev,comdat
	.size	_ZNK14intrinsics_x648read_dr7Ev, .-_ZNK14intrinsics_x648read_dr7Ev
	.section	.text._ZNK14intrinsics_x649write_dr7Em,"axG",@progbits,_ZNK14intrinsics_x649write_dr7Em,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649write_dr7Em
	.type	_ZNK14intrinsics_x649write_dr7Em, @function
_ZNK14intrinsics_x649write_dr7Em:
.LFB2729:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2729
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__write_dr7@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2729:
	.section	.gcc_except_table._ZNK14intrinsics_x649write_dr7Em,"aG",@progbits,_ZNK14intrinsics_x649write_dr7Em,comdat
.LLSDA2729:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2729-.LLSDACSB2729
.LLSDACSB2729:
.LLSDACSE2729:
	.section	.text._ZNK14intrinsics_x649write_dr7Em,"axG",@progbits,_ZNK14intrinsics_x649write_dr7Em,comdat
	.size	_ZNK14intrinsics_x649write_dr7Em, .-_ZNK14intrinsics_x649write_dr7Em
	.section	.text._ZNK14intrinsics_x647read_esEv,"axG",@progbits,_ZNK14intrinsics_x647read_esEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x647read_esEv
	.type	_ZNK14intrinsics_x647read_esEv, @function
_ZNK14intrinsics_x647read_esEv:
.LFB2730:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2730
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_es@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2730:
	.section	.gcc_except_table._ZNK14intrinsics_x647read_esEv,"aG",@progbits,_ZNK14intrinsics_x647read_esEv,comdat
.LLSDA2730:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2730-.LLSDACSB2730
.LLSDACSB2730:
.LLSDACSE2730:
	.section	.text._ZNK14intrinsics_x647read_esEv,"axG",@progbits,_ZNK14intrinsics_x647read_esEv,comdat
	.size	_ZNK14intrinsics_x647read_esEv, .-_ZNK14intrinsics_x647read_esEv
	.section	.text._ZNK14intrinsics_x648write_esEt,"axG",@progbits,_ZNK14intrinsics_x648write_esEt,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648write_esEt
	.type	_ZNK14intrinsics_x648write_esEt, @function
_ZNK14intrinsics_x648write_esEt:
.LFB2731:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2731
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__write_es@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2731:
	.section	.gcc_except_table._ZNK14intrinsics_x648write_esEt,"aG",@progbits,_ZNK14intrinsics_x648write_esEt,comdat
.LLSDA2731:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2731-.LLSDACSB2731
.LLSDACSB2731:
.LLSDACSE2731:
	.section	.text._ZNK14intrinsics_x648write_esEt,"axG",@progbits,_ZNK14intrinsics_x648write_esEt,comdat
	.size	_ZNK14intrinsics_x648write_esEt, .-_ZNK14intrinsics_x648write_esEt
	.section	.text._ZNK14intrinsics_x647read_csEv,"axG",@progbits,_ZNK14intrinsics_x647read_csEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x647read_csEv
	.type	_ZNK14intrinsics_x647read_csEv, @function
_ZNK14intrinsics_x647read_csEv:
.LFB2732:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2732
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_cs@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2732:
	.section	.gcc_except_table._ZNK14intrinsics_x647read_csEv,"aG",@progbits,_ZNK14intrinsics_x647read_csEv,comdat
.LLSDA2732:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2732-.LLSDACSB2732
.LLSDACSB2732:
.LLSDACSE2732:
	.section	.text._ZNK14intrinsics_x647read_csEv,"axG",@progbits,_ZNK14intrinsics_x647read_csEv,comdat
	.size	_ZNK14intrinsics_x647read_csEv, .-_ZNK14intrinsics_x647read_csEv
	.section	.text._ZNK14intrinsics_x648write_csEt,"axG",@progbits,_ZNK14intrinsics_x648write_csEt,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648write_csEt
	.type	_ZNK14intrinsics_x648write_csEt, @function
_ZNK14intrinsics_x648write_csEt:
.LFB2733:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2733
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__write_cs@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2733:
	.section	.gcc_except_table._ZNK14intrinsics_x648write_csEt,"aG",@progbits,_ZNK14intrinsics_x648write_csEt,comdat
.LLSDA2733:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2733-.LLSDACSB2733
.LLSDACSB2733:
.LLSDACSE2733:
	.section	.text._ZNK14intrinsics_x648write_csEt,"axG",@progbits,_ZNK14intrinsics_x648write_csEt,comdat
	.size	_ZNK14intrinsics_x648write_csEt, .-_ZNK14intrinsics_x648write_csEt
	.section	.text._ZNK14intrinsics_x647read_ssEv,"axG",@progbits,_ZNK14intrinsics_x647read_ssEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x647read_ssEv
	.type	_ZNK14intrinsics_x647read_ssEv, @function
_ZNK14intrinsics_x647read_ssEv:
.LFB2734:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2734
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_ss@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2734:
	.section	.gcc_except_table._ZNK14intrinsics_x647read_ssEv,"aG",@progbits,_ZNK14intrinsics_x647read_ssEv,comdat
.LLSDA2734:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2734-.LLSDACSB2734
.LLSDACSB2734:
.LLSDACSE2734:
	.section	.text._ZNK14intrinsics_x647read_ssEv,"axG",@progbits,_ZNK14intrinsics_x647read_ssEv,comdat
	.size	_ZNK14intrinsics_x647read_ssEv, .-_ZNK14intrinsics_x647read_ssEv
	.section	.text._ZNK14intrinsics_x648write_ssEt,"axG",@progbits,_ZNK14intrinsics_x648write_ssEt,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648write_ssEt
	.type	_ZNK14intrinsics_x648write_ssEt, @function
_ZNK14intrinsics_x648write_ssEt:
.LFB2735:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2735
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__write_ss@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2735:
	.section	.gcc_except_table._ZNK14intrinsics_x648write_ssEt,"aG",@progbits,_ZNK14intrinsics_x648write_ssEt,comdat
.LLSDA2735:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2735-.LLSDACSB2735
.LLSDACSB2735:
.LLSDACSE2735:
	.section	.text._ZNK14intrinsics_x648write_ssEt,"axG",@progbits,_ZNK14intrinsics_x648write_ssEt,comdat
	.size	_ZNK14intrinsics_x648write_ssEt, .-_ZNK14intrinsics_x648write_ssEt
	.section	.text._ZNK14intrinsics_x647read_dsEv,"axG",@progbits,_ZNK14intrinsics_x647read_dsEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x647read_dsEv
	.type	_ZNK14intrinsics_x647read_dsEv, @function
_ZNK14intrinsics_x647read_dsEv:
.LFB2736:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2736
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_ds@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2736:
	.section	.gcc_except_table._ZNK14intrinsics_x647read_dsEv,"aG",@progbits,_ZNK14intrinsics_x647read_dsEv,comdat
.LLSDA2736:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2736-.LLSDACSB2736
.LLSDACSB2736:
.LLSDACSE2736:
	.section	.text._ZNK14intrinsics_x647read_dsEv,"axG",@progbits,_ZNK14intrinsics_x647read_dsEv,comdat
	.size	_ZNK14intrinsics_x647read_dsEv, .-_ZNK14intrinsics_x647read_dsEv
	.section	.text._ZNK14intrinsics_x648write_dsEt,"axG",@progbits,_ZNK14intrinsics_x648write_dsEt,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648write_dsEt
	.type	_ZNK14intrinsics_x648write_dsEt, @function
_ZNK14intrinsics_x648write_dsEt:
.LFB2737:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2737
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__write_ds@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2737:
	.section	.gcc_except_table._ZNK14intrinsics_x648write_dsEt,"aG",@progbits,_ZNK14intrinsics_x648write_dsEt,comdat
.LLSDA2737:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2737-.LLSDACSB2737
.LLSDACSB2737:
.LLSDACSE2737:
	.section	.text._ZNK14intrinsics_x648write_dsEt,"axG",@progbits,_ZNK14intrinsics_x648write_dsEt,comdat
	.size	_ZNK14intrinsics_x648write_dsEt, .-_ZNK14intrinsics_x648write_dsEt
	.section	.text._ZNK14intrinsics_x647read_fsEv,"axG",@progbits,_ZNK14intrinsics_x647read_fsEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x647read_fsEv
	.type	_ZNK14intrinsics_x647read_fsEv, @function
_ZNK14intrinsics_x647read_fsEv:
.LFB2738:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2738
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_fs@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2738:
	.section	.gcc_except_table._ZNK14intrinsics_x647read_fsEv,"aG",@progbits,_ZNK14intrinsics_x647read_fsEv,comdat
.LLSDA2738:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2738-.LLSDACSB2738
.LLSDACSB2738:
.LLSDACSE2738:
	.section	.text._ZNK14intrinsics_x647read_fsEv,"axG",@progbits,_ZNK14intrinsics_x647read_fsEv,comdat
	.size	_ZNK14intrinsics_x647read_fsEv, .-_ZNK14intrinsics_x647read_fsEv
	.section	.text._ZNK14intrinsics_x648write_fsEt,"axG",@progbits,_ZNK14intrinsics_x648write_fsEt,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648write_fsEt
	.type	_ZNK14intrinsics_x648write_fsEt, @function
_ZNK14intrinsics_x648write_fsEt:
.LFB2739:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2739
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__write_fs@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2739:
	.section	.gcc_except_table._ZNK14intrinsics_x648write_fsEt,"aG",@progbits,_ZNK14intrinsics_x648write_fsEt,comdat
.LLSDA2739:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2739-.LLSDACSB2739
.LLSDACSB2739:
.LLSDACSE2739:
	.section	.text._ZNK14intrinsics_x648write_fsEt,"axG",@progbits,_ZNK14intrinsics_x648write_fsEt,comdat
	.size	_ZNK14intrinsics_x648write_fsEt, .-_ZNK14intrinsics_x648write_fsEt
	.section	.text._ZNK14intrinsics_x647read_gsEv,"axG",@progbits,_ZNK14intrinsics_x647read_gsEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x647read_gsEv
	.type	_ZNK14intrinsics_x647read_gsEv, @function
_ZNK14intrinsics_x647read_gsEv:
.LFB2740:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2740
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_gs@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2740:
	.section	.gcc_except_table._ZNK14intrinsics_x647read_gsEv,"aG",@progbits,_ZNK14intrinsics_x647read_gsEv,comdat
.LLSDA2740:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2740-.LLSDACSB2740
.LLSDACSB2740:
.LLSDACSE2740:
	.section	.text._ZNK14intrinsics_x647read_gsEv,"axG",@progbits,_ZNK14intrinsics_x647read_gsEv,comdat
	.size	_ZNK14intrinsics_x647read_gsEv, .-_ZNK14intrinsics_x647read_gsEv
	.section	.text._ZNK14intrinsics_x648write_gsEt,"axG",@progbits,_ZNK14intrinsics_x648write_gsEt,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648write_gsEt
	.type	_ZNK14intrinsics_x648write_gsEt, @function
_ZNK14intrinsics_x648write_gsEt:
.LFB2741:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2741
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__write_gs@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2741:
	.section	.gcc_except_table._ZNK14intrinsics_x648write_gsEt,"aG",@progbits,_ZNK14intrinsics_x648write_gsEt,comdat
.LLSDA2741:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2741-.LLSDACSB2741
.LLSDACSB2741:
.LLSDACSE2741:
	.section	.text._ZNK14intrinsics_x648write_gsEt,"axG",@progbits,_ZNK14intrinsics_x648write_gsEt,comdat
	.size	_ZNK14intrinsics_x648write_gsEt, .-_ZNK14intrinsics_x648write_gsEt
	.section	.text._ZNK14intrinsics_x647read_trEv,"axG",@progbits,_ZNK14intrinsics_x647read_trEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x647read_trEv
	.type	_ZNK14intrinsics_x647read_trEv, @function
_ZNK14intrinsics_x647read_trEv:
.LFB2742:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2742
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_tr@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2742:
	.section	.gcc_except_table._ZNK14intrinsics_x647read_trEv,"aG",@progbits,_ZNK14intrinsics_x647read_trEv,comdat
.LLSDA2742:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2742-.LLSDACSB2742
.LLSDACSB2742:
.LLSDACSE2742:
	.section	.text._ZNK14intrinsics_x647read_trEv,"axG",@progbits,_ZNK14intrinsics_x647read_trEv,comdat
	.size	_ZNK14intrinsics_x647read_trEv, .-_ZNK14intrinsics_x647read_trEv
	.section	.text._ZNK14intrinsics_x648write_trEt,"axG",@progbits,_ZNK14intrinsics_x648write_trEt,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648write_trEt
	.type	_ZNK14intrinsics_x648write_trEt, @function
_ZNK14intrinsics_x648write_trEt:
.LFB2743:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2743
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__write_tr@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2743:
	.section	.gcc_except_table._ZNK14intrinsics_x648write_trEt,"aG",@progbits,_ZNK14intrinsics_x648write_trEt,comdat
.LLSDA2743:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2743-.LLSDACSB2743
.LLSDACSB2743:
.LLSDACSE2743:
	.section	.text._ZNK14intrinsics_x648write_trEt,"axG",@progbits,_ZNK14intrinsics_x648write_trEt,comdat
	.size	_ZNK14intrinsics_x648write_trEt, .-_ZNK14intrinsics_x648write_trEt
	.section	.text._ZNK14intrinsics_x649read_ldtrEv,"axG",@progbits,_ZNK14intrinsics_x649read_ldtrEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649read_ldtrEv
	.type	_ZNK14intrinsics_x649read_ldtrEv, @function
_ZNK14intrinsics_x649read_ldtrEv:
.LFB2744:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2744
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_ldtr@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2744:
	.section	.gcc_except_table._ZNK14intrinsics_x649read_ldtrEv,"aG",@progbits,_ZNK14intrinsics_x649read_ldtrEv,comdat
.LLSDA2744:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2744-.LLSDACSB2744
.LLSDACSB2744:
.LLSDACSE2744:
	.section	.text._ZNK14intrinsics_x649read_ldtrEv,"axG",@progbits,_ZNK14intrinsics_x649read_ldtrEv,comdat
	.size	_ZNK14intrinsics_x649read_ldtrEv, .-_ZNK14intrinsics_x649read_ldtrEv
	.section	.text._ZNK14intrinsics_x6410write_ldtrEt,"axG",@progbits,_ZNK14intrinsics_x6410write_ldtrEt,comdat
	.align 2
	.weak	_ZNK14intrinsics_x6410write_ldtrEt
	.type	_ZNK14intrinsics_x6410write_ldtrEt, @function
_ZNK14intrinsics_x6410write_ldtrEt:
.LFB2745:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2745
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__write_ldtr@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2745:
	.section	.gcc_except_table._ZNK14intrinsics_x6410write_ldtrEt,"aG",@progbits,_ZNK14intrinsics_x6410write_ldtrEt,comdat
.LLSDA2745:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2745-.LLSDACSB2745
.LLSDACSB2745:
.LLSDACSE2745:
	.section	.text._ZNK14intrinsics_x6410write_ldtrEt,"axG",@progbits,_ZNK14intrinsics_x6410write_ldtrEt,comdat
	.size	_ZNK14intrinsics_x6410write_ldtrEt, .-_ZNK14intrinsics_x6410write_ldtrEt
	.section	.text._ZNK14intrinsics_x648read_rspEv,"axG",@progbits,_ZNK14intrinsics_x648read_rspEv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_rspEv
	.type	_ZNK14intrinsics_x648read_rspEv, @function
_ZNK14intrinsics_x648read_rspEv:
.LFB2746:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2746
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__read_rsp@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2746:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_rspEv,"aG",@progbits,_ZNK14intrinsics_x648read_rspEv,comdat
.LLSDA2746:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2746-.LLSDACSB2746
.LLSDACSB2746:
.LLSDACSE2746:
	.section	.text._ZNK14intrinsics_x648read_rspEv,"axG",@progbits,_ZNK14intrinsics_x648read_rspEv,comdat
	.size	_ZNK14intrinsics_x648read_rspEv, .-_ZNK14intrinsics_x648read_rspEv
	.section	.text._ZNK14intrinsics_x648read_gdtEPv,"axG",@progbits,_ZNK14intrinsics_x648read_gdtEPv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_gdtEPv
	.type	_ZNK14intrinsics_x648read_gdtEPv, @function
_ZNK14intrinsics_x648read_gdtEPv:
.LFB2747:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2747
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__read_gdt@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2747:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_gdtEPv,"aG",@progbits,_ZNK14intrinsics_x648read_gdtEPv,comdat
.LLSDA2747:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2747-.LLSDACSB2747
.LLSDACSB2747:
.LLSDACSE2747:
	.section	.text._ZNK14intrinsics_x648read_gdtEPv,"axG",@progbits,_ZNK14intrinsics_x648read_gdtEPv,comdat
	.size	_ZNK14intrinsics_x648read_gdtEPv, .-_ZNK14intrinsics_x648read_gdtEPv
	.section	.text._ZNK14intrinsics_x649write_gdtEPv,"axG",@progbits,_ZNK14intrinsics_x649write_gdtEPv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649write_gdtEPv
	.type	_ZNK14intrinsics_x649write_gdtEPv, @function
_ZNK14intrinsics_x649write_gdtEPv:
.LFB2748:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2748
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__write_gdt@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2748:
	.section	.gcc_except_table._ZNK14intrinsics_x649write_gdtEPv,"aG",@progbits,_ZNK14intrinsics_x649write_gdtEPv,comdat
.LLSDA2748:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2748-.LLSDACSB2748
.LLSDACSB2748:
.LLSDACSE2748:
	.section	.text._ZNK14intrinsics_x649write_gdtEPv,"axG",@progbits,_ZNK14intrinsics_x649write_gdtEPv,comdat
	.size	_ZNK14intrinsics_x649write_gdtEPv, .-_ZNK14intrinsics_x649write_gdtEPv
	.section	.text._ZNK14intrinsics_x648read_idtEPv,"axG",@progbits,_ZNK14intrinsics_x648read_idtEPv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x648read_idtEPv
	.type	_ZNK14intrinsics_x648read_idtEPv, @function
_ZNK14intrinsics_x648read_idtEPv:
.LFB2749:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2749
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__read_idt@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2749:
	.section	.gcc_except_table._ZNK14intrinsics_x648read_idtEPv,"aG",@progbits,_ZNK14intrinsics_x648read_idtEPv,comdat
.LLSDA2749:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2749-.LLSDACSB2749
.LLSDACSB2749:
.LLSDACSE2749:
	.section	.text._ZNK14intrinsics_x648read_idtEPv,"axG",@progbits,_ZNK14intrinsics_x648read_idtEPv,comdat
	.size	_ZNK14intrinsics_x648read_idtEPv, .-_ZNK14intrinsics_x648read_idtEPv
	.section	.text._ZNK14intrinsics_x649write_idtEPv,"axG",@progbits,_ZNK14intrinsics_x649write_idtEPv,comdat
	.align 2
	.weak	_ZNK14intrinsics_x649write_idtEPv
	.type	_ZNK14intrinsics_x649write_idtEPv, @function
_ZNK14intrinsics_x649write_idtEPv:
.LFB2750:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2750
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__write_idt@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2750:
	.section	.gcc_except_table._ZNK14intrinsics_x649write_idtEPv,"aG",@progbits,_ZNK14intrinsics_x649write_idtEPv,comdat
.LLSDA2750:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2750-.LLSDACSB2750
.LLSDACSB2750:
.LLSDACSE2750:
	.section	.text._ZNK14intrinsics_x649write_idtEPv,"axG",@progbits,_ZNK14intrinsics_x649write_idtEPv,comdat
	.size	_ZNK14intrinsics_x649write_idtEPv, .-_ZNK14intrinsics_x649write_idtEPv
	.section	.text._ZNK14intrinsics_x6414write_portio_8Eth,"axG",@progbits,_ZNK14intrinsics_x6414write_portio_8Eth,comdat
	.align 2
	.weak	_ZNK14intrinsics_x6414write_portio_8Eth
	.type	_ZNK14intrinsics_x6414write_portio_8Eth, @function
_ZNK14intrinsics_x6414write_portio_8Eth:
.LFB2751:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2751
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %ecx
	movl	%edx, %eax
	movw	%cx, -12(%rbp)
	movb	%al, -16(%rbp)
	movzbl	-16(%rbp), %edx
	movzwl	-12(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	__outb@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2751:
	.section	.gcc_except_table._ZNK14intrinsics_x6414write_portio_8Eth,"aG",@progbits,_ZNK14intrinsics_x6414write_portio_8Eth,comdat
.LLSDA2751:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2751-.LLSDACSB2751
.LLSDACSB2751:
.LLSDACSE2751:
	.section	.text._ZNK14intrinsics_x6414write_portio_8Eth,"axG",@progbits,_ZNK14intrinsics_x6414write_portio_8Eth,comdat
	.size	_ZNK14intrinsics_x6414write_portio_8Eth, .-_ZNK14intrinsics_x6414write_portio_8Eth
	.section	.text._ZNK14intrinsics_x6415write_portio_16Ett,"axG",@progbits,_ZNK14intrinsics_x6415write_portio_16Ett,comdat
	.align 2
	.weak	_ZNK14intrinsics_x6415write_portio_16Ett
	.type	_ZNK14intrinsics_x6415write_portio_16Ett, @function
_ZNK14intrinsics_x6415write_portio_16Ett:
.LFB2752:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2752
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %ecx
	movl	%edx, %eax
	movw	%cx, -12(%rbp)
	movw	%ax, -16(%rbp)
	movzwl	-16(%rbp), %edx
	movzwl	-12(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	__outw@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2752:
	.section	.gcc_except_table._ZNK14intrinsics_x6415write_portio_16Ett,"aG",@progbits,_ZNK14intrinsics_x6415write_portio_16Ett,comdat
.LLSDA2752:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2752-.LLSDACSB2752
.LLSDACSB2752:
.LLSDACSE2752:
	.section	.text._ZNK14intrinsics_x6415write_portio_16Ett,"axG",@progbits,_ZNK14intrinsics_x6415write_portio_16Ett,comdat
	.size	_ZNK14intrinsics_x6415write_portio_16Ett, .-_ZNK14intrinsics_x6415write_portio_16Ett
	.section	.text._ZNK14intrinsics_x6413read_portio_8Et,"axG",@progbits,_ZNK14intrinsics_x6413read_portio_8Et,comdat
	.align 2
	.weak	_ZNK14intrinsics_x6413read_portio_8Et
	.type	_ZNK14intrinsics_x6413read_portio_8Et, @function
_ZNK14intrinsics_x6413read_portio_8Et:
.LFB2753:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2753
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__inb@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2753:
	.section	.gcc_except_table._ZNK14intrinsics_x6413read_portio_8Et,"aG",@progbits,_ZNK14intrinsics_x6413read_portio_8Et,comdat
.LLSDA2753:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2753-.LLSDACSB2753
.LLSDACSB2753:
.LLSDACSE2753:
	.section	.text._ZNK14intrinsics_x6413read_portio_8Et,"axG",@progbits,_ZNK14intrinsics_x6413read_portio_8Et,comdat
	.size	_ZNK14intrinsics_x6413read_portio_8Et, .-_ZNK14intrinsics_x6413read_portio_8Et
	.section	.text._ZNK14intrinsics_x6414read_portio_16Et,"axG",@progbits,_ZNK14intrinsics_x6414read_portio_16Et,comdat
	.align 2
	.weak	_ZNK14intrinsics_x6414read_portio_16Et
	.type	_ZNK14intrinsics_x6414read_portio_16Et, @function
_ZNK14intrinsics_x6414read_portio_16Et:
.LFB2754:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2754
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movw	%ax, -12(%rbp)
	movzwl	-12(%rbp), %eax
	movl	%eax, %edi
	call	__inw@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2754:
	.section	.gcc_except_table._ZNK14intrinsics_x6414read_portio_16Et,"aG",@progbits,_ZNK14intrinsics_x6414read_portio_16Et,comdat
.LLSDA2754:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2754-.LLSDACSB2754
.LLSDACSB2754:
.LLSDACSE2754:
	.section	.text._ZNK14intrinsics_x6414read_portio_16Et,"axG",@progbits,_ZNK14intrinsics_x6414read_portio_16Et,comdat
	.size	_ZNK14intrinsics_x6414read_portio_16Et, .-_ZNK14intrinsics_x6414read_portio_16Et
	.section	.text._ZN13gdt_reg_x64_tC2Ev,"axG",@progbits,_ZN13gdt_reg_x64_tC5Ev,comdat
	.align 2
	.weak	_ZN13gdt_reg_x64_tC2Ev
	.type	_ZN13gdt_reg_x64_tC2Ev, @function
_ZN13gdt_reg_x64_tC2Ev:
.LFB2756:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movw	$0, (%rax)
	movq	-8(%rbp), %rax
	movq	$0, 2(%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2756:
	.size	_ZN13gdt_reg_x64_tC2Ev, .-_ZN13gdt_reg_x64_tC2Ev
	.weak	_ZN13gdt_reg_x64_tC1Ev
	.set	_ZN13gdt_reg_x64_tC1Ev,_ZN13gdt_reg_x64_tC2Ev
	.section	.text._ZN7gdt_x64D2Ev,"axG",@progbits,_ZN7gdt_x64D5Ev,comdat
	.align 2
	.weak	_ZN7gdt_x64D2Ev
	.type	_ZN7gdt_x64D2Ev, @function
_ZN7gdt_x64D2Ev:
.LFB2759:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTV7gdt_x64@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$24, %rax
	movq	%rax, %rdi
	call	_ZNSt3__110shared_ptrImED1Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2759:
	.size	_ZN7gdt_x64D2Ev, .-_ZN7gdt_x64D2Ev
	.weak	_ZN7gdt_x64D1Ev
	.set	_ZN7gdt_x64D1Ev,_ZN7gdt_x64D2Ev
	.section	.text._ZN7gdt_x64D0Ev,"axG",@progbits,_ZN7gdt_x64D5Ev,comdat
	.align 2
	.weak	_ZN7gdt_x64D0Ev
	.type	_ZN7gdt_x64D0Ev, @function
_ZN7gdt_x64D0Ev:
.LFB2761:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7gdt_x64D1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$40, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2761:
	.size	_ZN7gdt_x64D0Ev, .-_ZN7gdt_x64D0Ev
	.section	.text._ZN13idt_reg_x64_tC2Ev,"axG",@progbits,_ZN13idt_reg_x64_tC5Ev,comdat
	.align 2
	.weak	_ZN13idt_reg_x64_tC2Ev
	.type	_ZN13idt_reg_x64_tC2Ev, @function
_ZN13idt_reg_x64_tC2Ev:
.LFB2763:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movw	$0, (%rax)
	movq	-8(%rbp), %rax
	movq	$0, 2(%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2763:
	.size	_ZN13idt_reg_x64_tC2Ev, .-_ZN13idt_reg_x64_tC2Ev
	.weak	_ZN13idt_reg_x64_tC1Ev
	.set	_ZN13idt_reg_x64_tC1Ev,_ZN13idt_reg_x64_tC2Ev
	.section	.text._ZN20intrinsics_intel_x64C2Ev,"axG",@progbits,_ZN20intrinsics_intel_x64C5Ev,comdat
	.align 2
	.weak	_ZN20intrinsics_intel_x64C2Ev
	.type	_ZN20intrinsics_intel_x64C2Ev, @function
_ZN20intrinsics_intel_x64C2Ev:
.LFB2824:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN14intrinsics_x64C2Ev@PLT
	movq	_ZTV20intrinsics_intel_x64@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2824:
	.size	_ZN20intrinsics_intel_x64C2Ev, .-_ZN20intrinsics_intel_x64C2Ev
	.weak	_ZN20intrinsics_intel_x64C1Ev
	.set	_ZN20intrinsics_intel_x64C1Ev,_ZN20intrinsics_intel_x64C2Ev
	.section	.text._ZN20intrinsics_intel_x64D2Ev,"axG",@progbits,_ZN20intrinsics_intel_x64D5Ev,comdat
	.align 2
	.weak	_ZN20intrinsics_intel_x64D2Ev
	.type	_ZN20intrinsics_intel_x64D2Ev, @function
_ZN20intrinsics_intel_x64D2Ev:
.LFB2827:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTV20intrinsics_intel_x64@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN14intrinsics_x64D2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2827:
	.size	_ZN20intrinsics_intel_x64D2Ev, .-_ZN20intrinsics_intel_x64D2Ev
	.weak	_ZN20intrinsics_intel_x64D1Ev
	.set	_ZN20intrinsics_intel_x64D1Ev,_ZN20intrinsics_intel_x64D2Ev
	.section	.text._ZN20intrinsics_intel_x64D0Ev,"axG",@progbits,_ZN20intrinsics_intel_x64D5Ev,comdat
	.align 2
	.weak	_ZN20intrinsics_intel_x64D0Ev
	.type	_ZN20intrinsics_intel_x64D0Ev, @function
_ZN20intrinsics_intel_x64D0Ev:
.LFB2829:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN20intrinsics_intel_x64D1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2829:
	.size	_ZN20intrinsics_intel_x64D0Ev, .-_ZN20intrinsics_intel_x64D0Ev
	.section	.text._ZNK20intrinsics_intel_x645vmxonEPv,"axG",@progbits,_ZNK20intrinsics_intel_x645vmxonEPv,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x645vmxonEPv
	.type	_ZNK20intrinsics_intel_x645vmxonEPv, @function
_ZNK20intrinsics_intel_x645vmxonEPv:
.LFB2830:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2830
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__vmxon@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2830:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x645vmxonEPv,"aG",@progbits,_ZNK20intrinsics_intel_x645vmxonEPv,comdat
.LLSDA2830:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2830-.LLSDACSB2830
.LLSDACSB2830:
.LLSDACSE2830:
	.section	.text._ZNK20intrinsics_intel_x645vmxonEPv,"axG",@progbits,_ZNK20intrinsics_intel_x645vmxonEPv,comdat
	.size	_ZNK20intrinsics_intel_x645vmxonEPv, .-_ZNK20intrinsics_intel_x645vmxonEPv
	.section	.text._ZNK20intrinsics_intel_x646vmxoffEv,"axG",@progbits,_ZNK20intrinsics_intel_x646vmxoffEv,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x646vmxoffEv
	.type	_ZNK20intrinsics_intel_x646vmxoffEv, @function
_ZNK20intrinsics_intel_x646vmxoffEv:
.LFB2831:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2831
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__vmxoff@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2831:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x646vmxoffEv,"aG",@progbits,_ZNK20intrinsics_intel_x646vmxoffEv,comdat
.LLSDA2831:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2831-.LLSDACSB2831
.LLSDACSB2831:
.LLSDACSE2831:
	.section	.text._ZNK20intrinsics_intel_x646vmxoffEv,"axG",@progbits,_ZNK20intrinsics_intel_x646vmxoffEv,comdat
	.size	_ZNK20intrinsics_intel_x646vmxoffEv, .-_ZNK20intrinsics_intel_x646vmxoffEv
	.section	.text._ZNK20intrinsics_intel_x646vmcallEm,"axG",@progbits,_ZNK20intrinsics_intel_x646vmcallEm,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x646vmcallEm
	.type	_ZNK20intrinsics_intel_x646vmcallEm, @function
_ZNK20intrinsics_intel_x646vmcallEm:
.LFB2832:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2832
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__vmcall@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2832:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x646vmcallEm,"aG",@progbits,_ZNK20intrinsics_intel_x646vmcallEm,comdat
.LLSDA2832:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2832-.LLSDACSB2832
.LLSDACSB2832:
.LLSDACSE2832:
	.section	.text._ZNK20intrinsics_intel_x646vmcallEm,"axG",@progbits,_ZNK20intrinsics_intel_x646vmcallEm,comdat
	.size	_ZNK20intrinsics_intel_x646vmcallEm, .-_ZNK20intrinsics_intel_x646vmcallEm
	.section	.text._ZNK20intrinsics_intel_x647vmclearEPv,"axG",@progbits,_ZNK20intrinsics_intel_x647vmclearEPv,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x647vmclearEPv
	.type	_ZNK20intrinsics_intel_x647vmclearEPv, @function
_ZNK20intrinsics_intel_x647vmclearEPv:
.LFB2833:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2833
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__vmclear@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2833:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x647vmclearEPv,"aG",@progbits,_ZNK20intrinsics_intel_x647vmclearEPv,comdat
.LLSDA2833:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2833-.LLSDACSB2833
.LLSDACSB2833:
.LLSDACSE2833:
	.section	.text._ZNK20intrinsics_intel_x647vmclearEPv,"axG",@progbits,_ZNK20intrinsics_intel_x647vmclearEPv,comdat
	.size	_ZNK20intrinsics_intel_x647vmclearEPv, .-_ZNK20intrinsics_intel_x647vmclearEPv
	.section	.text._ZNK20intrinsics_intel_x647vmptrldEPv,"axG",@progbits,_ZNK20intrinsics_intel_x647vmptrldEPv,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x647vmptrldEPv
	.type	_ZNK20intrinsics_intel_x647vmptrldEPv, @function
_ZNK20intrinsics_intel_x647vmptrldEPv:
.LFB2834:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2834
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__vmptrld@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2834:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x647vmptrldEPv,"aG",@progbits,_ZNK20intrinsics_intel_x647vmptrldEPv,comdat
.LLSDA2834:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2834-.LLSDACSB2834
.LLSDACSB2834:
.LLSDACSE2834:
	.section	.text._ZNK20intrinsics_intel_x647vmptrldEPv,"axG",@progbits,_ZNK20intrinsics_intel_x647vmptrldEPv,comdat
	.size	_ZNK20intrinsics_intel_x647vmptrldEPv, .-_ZNK20intrinsics_intel_x647vmptrldEPv
	.section	.text._ZNK20intrinsics_intel_x647vmptrstEPv,"axG",@progbits,_ZNK20intrinsics_intel_x647vmptrstEPv,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x647vmptrstEPv
	.type	_ZNK20intrinsics_intel_x647vmptrstEPv, @function
_ZNK20intrinsics_intel_x647vmptrstEPv:
.LFB2835:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2835
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	__vmptrst@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2835:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x647vmptrstEPv,"aG",@progbits,_ZNK20intrinsics_intel_x647vmptrstEPv,comdat
.LLSDA2835:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2835-.LLSDACSB2835
.LLSDACSB2835:
.LLSDACSE2835:
	.section	.text._ZNK20intrinsics_intel_x647vmptrstEPv,"axG",@progbits,_ZNK20intrinsics_intel_x647vmptrstEPv,comdat
	.size	_ZNK20intrinsics_intel_x647vmptrstEPv, .-_ZNK20intrinsics_intel_x647vmptrstEPv
	.section	.text._ZNK20intrinsics_intel_x647vmwriteEmm,"axG",@progbits,_ZNK20intrinsics_intel_x647vmwriteEmm,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x647vmwriteEmm
	.type	_ZNK20intrinsics_intel_x647vmwriteEmm, @function
_ZNK20intrinsics_intel_x647vmwriteEmm:
.LFB2836:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2836
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	__vmwrite@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2836:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x647vmwriteEmm,"aG",@progbits,_ZNK20intrinsics_intel_x647vmwriteEmm,comdat
.LLSDA2836:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2836-.LLSDACSB2836
.LLSDACSB2836:
.LLSDACSE2836:
	.section	.text._ZNK20intrinsics_intel_x647vmwriteEmm,"axG",@progbits,_ZNK20intrinsics_intel_x647vmwriteEmm,comdat
	.size	_ZNK20intrinsics_intel_x647vmwriteEmm, .-_ZNK20intrinsics_intel_x647vmwriteEmm
	.section	.text._ZNK20intrinsics_intel_x646vmreadEmPm,"axG",@progbits,_ZNK20intrinsics_intel_x646vmreadEmPm,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x646vmreadEmPm
	.type	_ZNK20intrinsics_intel_x646vmreadEmPm, @function
_ZNK20intrinsics_intel_x646vmreadEmPm:
.LFB2837:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2837
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	__vmread@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2837:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x646vmreadEmPm,"aG",@progbits,_ZNK20intrinsics_intel_x646vmreadEmPm,comdat
.LLSDA2837:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2837-.LLSDACSB2837
.LLSDACSB2837:
.LLSDACSE2837:
	.section	.text._ZNK20intrinsics_intel_x646vmreadEmPm,"axG",@progbits,_ZNK20intrinsics_intel_x646vmreadEmPm,comdat
	.size	_ZNK20intrinsics_intel_x646vmreadEmPm, .-_ZNK20intrinsics_intel_x646vmreadEmPm
	.section	.text._ZNK20intrinsics_intel_x648vmlaunchEv,"axG",@progbits,_ZNK20intrinsics_intel_x648vmlaunchEv,comdat
	.align 2
	.weak	_ZNK20intrinsics_intel_x648vmlaunchEv
	.type	_ZNK20intrinsics_intel_x648vmlaunchEv, @function
_ZNK20intrinsics_intel_x648vmlaunchEv:
.LFB2838:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2838
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__vmlaunch@PLT
	testq	%rax, %rax
	setne	%al
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2838:
	.section	.gcc_except_table._ZNK20intrinsics_intel_x648vmlaunchEv,"aG",@progbits,_ZNK20intrinsics_intel_x648vmlaunchEv,comdat
.LLSDA2838:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2838-.LLSDACSB2838
.LLSDACSB2838:
.LLSDACSE2838:
	.section	.text._ZNK20intrinsics_intel_x648vmlaunchEv,"axG",@progbits,_ZNK20intrinsics_intel_x648vmlaunchEv,comdat
	.size	_ZNK20intrinsics_intel_x648vmlaunchEv, .-_ZNK20intrinsics_intel_x648vmlaunchEv
	.section	.text._ZN14vmcs_intel_x64D2Ev,"axG",@progbits,_ZN14vmcs_intel_x64D5Ev,comdat
	.align 2
	.weak	_ZN14vmcs_intel_x64D2Ev
	.type	_ZN14vmcs_intel_x64D2Ev, @function
_ZN14vmcs_intel_x64D2Ev:
.LFB2840:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%rdi, -200(%rbp)
	movq	_ZTV14vmcs_intel_x64@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-200(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-200(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	$0, (%rax)
	cmpq	$0, -64(%rbp)
	je	.L117
	movq	-88(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	$0, -8(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L117
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdaPv@PLT
.L117:
	movq	-200(%rbp), %rax
	addq	$32, %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	$0, -176(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -152(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	-176(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -152(%rbp)
	je	.L124
	movq	-184(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-152(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
.L124:
	movq	-200(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED1Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2840:
	.size	_ZN14vmcs_intel_x64D2Ev, .-_ZN14vmcs_intel_x64D2Ev
	.weak	_ZN14vmcs_intel_x64D1Ev
	.set	_ZN14vmcs_intel_x64D1Ev,_ZN14vmcs_intel_x64D2Ev
	.section	.text._ZN14vmcs_intel_x64D0Ev,"axG",@progbits,_ZN14vmcs_intel_x64D5Ev,comdat
	.align 2
	.weak	_ZN14vmcs_intel_x64D0Ev
	.type	_ZN14vmcs_intel_x64D0Ev, @function
_ZN14vmcs_intel_x64D0Ev:
.LFB2842:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN14vmcs_intel_x64D1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$48, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2842:
	.size	_ZN14vmcs_intel_x64D0Ev, .-_ZN14vmcs_intel_x64D0Ev
	.section	.text._ZN3bfn17general_exceptionC2Ev,"axG",@progbits,_ZN3bfn17general_exceptionC5Ev,comdat
	.align 2
	.weak	_ZN3bfn17general_exceptionC2Ev
	.type	_ZN3bfn17general_exceptionC2Ev, @function
_ZN3bfn17general_exceptionC2Ev:
.LFB2844:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	_ZTVSt9exception@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	_ZTVN3bfn17general_exceptionE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2844:
	.size	_ZN3bfn17general_exceptionC2Ev, .-_ZN3bfn17general_exceptionC2Ev
	.weak	_ZN3bfn17general_exceptionC1Ev
	.set	_ZN3bfn17general_exceptionC1Ev,_ZN3bfn17general_exceptionC2Ev
	.section	.text._ZN3bfn17general_exceptionD2Ev,"axG",@progbits,_ZN3bfn17general_exceptionD5Ev,comdat
	.align 2
	.weak	_ZN3bfn17general_exceptionD2Ev
	.type	_ZN3bfn17general_exceptionD2Ev, @function
_ZN3bfn17general_exceptionD2Ev:
.LFB2847:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTVN3bfn17general_exceptionE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt9exceptionD2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2847:
	.size	_ZN3bfn17general_exceptionD2Ev, .-_ZN3bfn17general_exceptionD2Ev
	.weak	_ZN3bfn17general_exceptionD1Ev
	.set	_ZN3bfn17general_exceptionD1Ev,_ZN3bfn17general_exceptionD2Ev
	.section	.text._ZN3bfn17general_exceptionD0Ev,"axG",@progbits,_ZN3bfn17general_exceptionD5Ev,comdat
	.align 2
	.weak	_ZN3bfn17general_exceptionD0Ev
	.type	_ZN3bfn17general_exceptionD0Ev, @function
_ZN3bfn17general_exceptionD0Ev:
.LFB2849:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2849:
	.size	_ZN3bfn17general_exceptionD0Ev, .-_ZN3bfn17general_exceptionD0Ev
	.section	.text._ZNK3bfn17general_exception4whatEv,"axG",@progbits,_ZNK3bfn17general_exception4whatEv,comdat
	.align 2
	.weak	_ZNK3bfn17general_exception4whatEv
	.type	_ZNK3bfn17general_exception4whatEv, @function
_ZNK3bfn17general_exception4whatEv:
.LFB2850:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2850:
	.size	_ZNK3bfn17general_exception4whatEv, .-_ZNK3bfn17general_exception4whatEv
	.section	.rodata
.LC0:
	.string	"general exception"
	.section	.text._ZNK3bfn17general_exception5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,"axG",@progbits,_ZNK3bfn17general_exception5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,comdat
	.align 2
	.weak	_ZNK3bfn17general_exception5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.type	_ZNK3bfn17general_exception5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, @function
_ZNK3bfn17general_exception5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE:
.LFB2851:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2851:
	.size	_ZNK3bfn17general_exception5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, .-_ZNK3bfn17general_exception5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.section	.text._ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,"axG",@progbits,_ZN3bfn18vmcs_failure_errorC5ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,comdat
	.align 2
	.weak	_ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m
	.type	_ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m, @function
_ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m:
.LFB2887:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2887
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionC2Ev@PLT
	movq	_ZTVN3bfn18vmcs_failure_errorE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB0:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_@PLT
.LEHE0:
	movq	-24(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB1:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_@PLT
.LEHE1:
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 56(%rax)
	jmp	.L141
.L140:
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L138
.L139:
	movq	%rax, %rbx
.L138:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD2Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
.L141:
	addq	$40, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2887:
	.section	.gcc_except_table._ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,"aG",@progbits,_ZN3bfn18vmcs_failure_errorC5ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,comdat
.LLSDA2887:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2887-.LLSDACSB2887
.LLSDACSB2887:
	.uleb128 .LEHB0-.LFB2887
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L139-.LFB2887
	.uleb128 0
	.uleb128 .LEHB1-.LFB2887
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L140-.LFB2887
	.uleb128 0
	.uleb128 .LEHB2-.LFB2887
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE2887:
	.section	.text._ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,"axG",@progbits,_ZN3bfn18vmcs_failure_errorC5ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,comdat
	.size	_ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m, .-_ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m
	.weak	_ZN3bfn18vmcs_failure_errorC1ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m
	.set	_ZN3bfn18vmcs_failure_errorC1ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,_ZN3bfn18vmcs_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m
	.section	.rodata
.LC1:
	.string	"vmcs failure:"
.LC2:
	.string	"    - mesg: "
.LC3:
	.string	"    - func: "
.LC4:
	.string	"    - line: "
	.section	.text._ZNK3bfn18vmcs_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,"axG",@progbits,_ZNK3bfn18vmcs_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,comdat
	.align 2
	.weak	_ZNK3bfn18vmcs_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.type	_ZNK3bfn18vmcs_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, @function
_ZNK3bfn18vmcs_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE:
.LFB2889:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-80(%rbp), %rax
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	-72(%rbp), %rax
	leaq	8(%rax), %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -32(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE@PLT
	movq	-72(%rbp), %rax
	leaq	32(%rax), %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -48(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -40(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE@PLT
	movq	-72(%rbp), %rax
	movq	56(%rax), %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -64(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEm@PLT
	movq	-80(%rbp), %rax
	addq	$72, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2889:
	.size	_ZNK3bfn18vmcs_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, .-_ZNK3bfn18vmcs_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.section	.text._ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,"axG",@progbits,_ZN3bfn23vmcs_read_failure_errorC5EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,comdat
	.align 2
	.weak	_ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm
	.type	_ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm, @function
_ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm:
.LFB2891:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2891
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionC2Ev@PLT
	movq	_ZTVN3bfn23vmcs_read_failure_errorE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB3:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_@PLT
.LEHE3:
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 40(%rax)
	jmp	.L150
.L149:
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD2Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB4:
	call	_Unwind_Resume@PLT
.LEHE4:
.L150:
	addq	$40, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2891:
	.section	.gcc_except_table._ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,"aG",@progbits,_ZN3bfn23vmcs_read_failure_errorC5EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,comdat
.LLSDA2891:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2891-.LLSDACSB2891
.LLSDACSB2891:
	.uleb128 .LEHB3-.LFB2891
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L149-.LFB2891
	.uleb128 0
	.uleb128 .LEHB4-.LFB2891
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSE2891:
	.section	.text._ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,"axG",@progbits,_ZN3bfn23vmcs_read_failure_errorC5EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,comdat
	.size	_ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm, .-_ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm
	.weak	_ZN3bfn23vmcs_read_failure_errorC1EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm
	.set	_ZN3bfn23vmcs_read_failure_errorC1EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,_ZN3bfn23vmcs_read_failure_errorC2EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm
	.section	.rodata
.LC5:
	.string	"vmcs read failure:"
.LC6:
	.string	"    - field: "
	.section	.text._ZNK3bfn23vmcs_read_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,"axG",@progbits,_ZNK3bfn23vmcs_read_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,comdat
	.align 2
	.weak	_ZNK3bfn23vmcs_read_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.type	_ZNK3bfn23vmcs_read_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, @function
_ZNK3bfn23vmcs_read_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE:
.LFB2893:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-80(%rbp), %rax
	leaq	.LC5(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	-72(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -32(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	-72(%rbp), %rax
	leaq	16(%rax), %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -48(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -40(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE@PLT
	movq	-72(%rbp), %rax
	movq	40(%rax), %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -64(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEm@PLT
	movq	-80(%rbp), %rax
	addq	$72, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2893:
	.size	_ZNK3bfn23vmcs_read_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, .-_ZNK3bfn23vmcs_read_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.section	.text._ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,"axG",@progbits,_ZN3bfn24vmcs_write_failure_errorC5EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,comdat
	.align 2
	.weak	_ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm
	.type	_ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm, @function
_ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm:
.LFB2895:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2895
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionC2Ev@PLT
	movq	_ZTVN3bfn24vmcs_write_failure_errorE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-24(%rbp), %rax
	leaq	24(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB5:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_@PLT
.LEHE5:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, 48(%rax)
	jmp	.L159
.L158:
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD2Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB6:
	call	_Unwind_Resume@PLT
.LEHE6:
.L159:
	addq	$56, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2895:
	.section	.gcc_except_table._ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,"aG",@progbits,_ZN3bfn24vmcs_write_failure_errorC5EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,comdat
.LLSDA2895:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2895-.LLSDACSB2895
.LLSDACSB2895:
	.uleb128 .LEHB5-.LFB2895
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L158-.LFB2895
	.uleb128 0
	.uleb128 .LEHB6-.LFB2895
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE2895:
	.section	.text._ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,"axG",@progbits,_ZN3bfn24vmcs_write_failure_errorC5EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,comdat
	.size	_ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm, .-_ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm
	.weak	_ZN3bfn24vmcs_write_failure_errorC1EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm
	.set	_ZN3bfn24vmcs_write_failure_errorC1EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm,_ZN3bfn24vmcs_write_failure_errorC2EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm
	.section	.rodata
.LC7:
	.string	"vmcs write failure:"
.LC8:
	.string	"    - value: "
	.section	.text._ZNK3bfn24vmcs_write_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,"axG",@progbits,_ZNK3bfn24vmcs_write_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,comdat
	.align 2
	.weak	_ZNK3bfn24vmcs_write_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.type	_ZNK3bfn24vmcs_write_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, @function
_ZNK3bfn24vmcs_write_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE:
.LFB2897:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	-96(%rbp), %rax
	leaq	.LC7(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	-88(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -32(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	-88(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -48(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -40(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC8(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	-88(%rbp), %rax
	leaq	24(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -64(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE@PLT
	movq	-88(%rbp), %rax
	movq	48(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -80(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -72(%rbp)
	movq	-80(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEm@PLT
	movq	-96(%rbp), %rax
	addq	$88, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2897:
	.size	_ZNK3bfn24vmcs_write_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, .-_ZNK3bfn24vmcs_write_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.section	.text._ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,"axG",@progbits,_ZN3bfn25vmcs_launch_failure_errorC5ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,comdat
	.align 2
	.weak	_ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m
	.type	_ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m, @function
_ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m:
.LFB2899:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2899
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionC2Ev@PLT
	movq	_ZTVN3bfn25vmcs_launch_failure_errorE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB7:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_@PLT
.LEHE7:
	movq	-24(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB8:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_@PLT
.LEHE8:
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 56(%rax)
	jmp	.L171
.L170:
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L168
.L169:
	movq	%rax, %rbx
.L168:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD2Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB9:
	call	_Unwind_Resume@PLT
.LEHE9:
.L171:
	addq	$40, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2899:
	.section	.gcc_except_table._ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,"aG",@progbits,_ZN3bfn25vmcs_launch_failure_errorC5ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,comdat
.LLSDA2899:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2899-.LLSDACSB2899
.LLSDACSB2899:
	.uleb128 .LEHB7-.LFB2899
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L169-.LFB2899
	.uleb128 0
	.uleb128 .LEHB8-.LFB2899
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L170-.LFB2899
	.uleb128 0
	.uleb128 .LEHB9-.LFB2899
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
.LLSDACSE2899:
	.section	.text._ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,"axG",@progbits,_ZN3bfn25vmcs_launch_failure_errorC5ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,comdat
	.size	_ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m, .-_ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m
	.weak	_ZN3bfn25vmcs_launch_failure_errorC1ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m
	.set	_ZN3bfn25vmcs_launch_failure_errorC1ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m,_ZN3bfn25vmcs_launch_failure_errorC2ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m
	.section	.rodata
.LC9:
	.string	"vmcs launch failure:"
	.section	.text._ZNK3bfn25vmcs_launch_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,"axG",@progbits,_ZNK3bfn25vmcs_launch_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE,comdat
	.align 2
	.weak	_ZNK3bfn25vmcs_launch_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.type	_ZNK3bfn25vmcs_launch_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, @function
_ZNK3bfn25vmcs_launch_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE:
.LFB2901:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-80(%rbp), %rax
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	-72(%rbp), %rax
	leaq	8(%rax), %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -32(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE@PLT
	movq	-72(%rbp), %rax
	leaq	32(%rax), %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -48(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -40(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE@PLT
	movq	-72(%rbp), %rax
	movq	56(%rax), %rbx
	movq	-80(%rbp), %rax
	movq	%rax, -64(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEm@PLT
	movq	-80(%rbp), %rax
	addq	$72, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2901:
	.size	_ZNK3bfn25vmcs_launch_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE, .-_ZNK3bfn25vmcs_launch_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.text
	.align 2
	.globl	_ZN14vmcs_intel_x64C2ERKNSt3__110shared_ptrI20intrinsics_intel_x64EE
	.type	_ZN14vmcs_intel_x64C2ERKNSt3__110shared_ptrI20intrinsics_intel_x64EE, @function
_ZN14vmcs_intel_x64C2ERKNSt3__110shared_ptrI20intrinsics_intel_x64EE:
.LFB3279:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3279
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$504, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -504(%rbp)
	movq	%rsi, -512(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	movq	%rcx, -24(%rbp)
	xorl	%ecx, %ecx
	movq	_ZTV14vmcs_intel_x64@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-504(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-504(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -368(%rbp)
	movq	-512(%rbp), %rax
	movq	%rax, -360(%rbp)
	movq	-360(%rbp), %rax
	movq	(%rax), %rdx
	movq	-368(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-360(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-368(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-368(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L178
	movq	-368(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	_ZNSt3__119__shared_weak_count12__add_sharedEv@PLT
.L178:
	movq	-504(%rbp), %rax
	addq	$32, %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	$0, -472(%rbp)
	leaq	-472(%rbp), %rax
	movq	(%rax), %rax
	movq	-392(%rbp), %rdx
	movq	%rdx, -384(%rbp)
	movq	%rax, -464(%rbp)
	movq	-384(%rbp), %rax
	movq	%rax, -376(%rbp)
	leaq	-464(%rbp), %rax
	movq	(%rax), %rdx
	movq	-384(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-504(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	%rax, -424(%rbp)
	movq	$0, -488(%rbp)
	leaq	-488(%rbp), %rax
	movq	(%rax), %rax
	movq	-424(%rbp), %rdx
	movq	%rdx, -416(%rbp)
	movq	%rax, -480(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -408(%rbp)
	leaq	-480(%rbp), %rax
	movq	(%rax), %rdx
	movq	-416(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-504(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	%rax, -440(%rbp)
	movq	-440(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	setne	%al
	xorl	$1, %eax
	testb	%al, %al
	je	.L212
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
.LEHB10:
	call	_ZNSt3__110shared_ptrI20intrinsics_intel_x64E11make_sharedIJEEES2_DpOT_@PLT
.LEHE10:
	movq	-504(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -352(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	%rax, -336(%rbp)
	movq	-336(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-336(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-336(%rbp), %rax
	movq	$0, (%rax)
	movq	-336(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-352(%rbp), %rax
	movq	%rax, -328(%rbp)
	movq	-328(%rbp), %rax
	leaq	-48(%rbp), %rdx
	movq	%rdx, -320(%rbp)
	movq	%rax, -312(%rbp)
	movq	-320(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -456(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	(%rax), %rdx
	movq	-320(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-456(%rbp), %rax
	movq	(%rax), %rdx
	movq	-312(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-328(%rbp), %rax
	addq	$8, %rax
	leaq	-48(%rbp), %rdx
	addq	$8, %rdx
	movq	%rdx, -288(%rbp)
	movq	%rax, -280(%rbp)
	movq	-288(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -456(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	(%rax), %rdx
	movq	-288(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-456(%rbp), %rax
	movq	(%rax), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED1Ev@PLT
	jmp	.L212
.L211:
	movq	%rax, %rbx
	movq	-504(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	movq	%rax, -232(%rbp)
	movq	-232(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -224(%rbp)
	movq	-248(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	$0, (%rax)
	cmpq	$0, -224(%rbp)
	je	.L200
	movq	-248(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	$0, -168(%rbp)
	cmpq	$0, -176(%rbp)
	je	.L200
	movq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdaPv@PLT
.L200:
	movq	-504(%rbp), %rax
	addq	$32, %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	$0, -144(%rbp)
	movq	-152(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -120(%rbp)
	movq	-152(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	-144(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -120(%rbp)
	je	.L207
	movq	-152(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
.L207:
	movq	-504(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB11:
	call	_Unwind_Resume@PLT
.LEHE11:
.L212:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-24(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L210
	call	__stack_chk_fail@PLT
.L210:
	addq	$504, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3279:
	.section	.gcc_except_table,"a",@progbits
.LLSDA3279:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3279-.LLSDACSB3279
.LLSDACSB3279:
	.uleb128 .LEHB10-.LFB3279
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L211-.LFB3279
	.uleb128 0
	.uleb128 .LEHB11-.LFB3279
	.uleb128 .LEHE11-.LEHB11
	.uleb128 0
	.uleb128 0
.LLSDACSE3279:
	.text
	.size	_ZN14vmcs_intel_x64C2ERKNSt3__110shared_ptrI20intrinsics_intel_x64EE, .-_ZN14vmcs_intel_x64C2ERKNSt3__110shared_ptrI20intrinsics_intel_x64EE
	.globl	_ZN14vmcs_intel_x64C1ERKNSt3__110shared_ptrI20intrinsics_intel_x64EE
	.set	_ZN14vmcs_intel_x64C1ERKNSt3__110shared_ptrI20intrinsics_intel_x64EE,_ZN14vmcs_intel_x64C2ERKNSt3__110shared_ptrI20intrinsics_intel_x64EE
	.align 2
	.type	_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_ENKUlvE_clEv, @function
_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_ENKUlvE_clEv:
.LFB3282:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	addq	$40, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	addq	$56, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, %rdi
	call	*%rax
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3282:
	.size	_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_ENKUlvE_clEv, .-_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_ENKUlvE_clEv
	.section	.rodata
.LC10:
	.string	"failed to clear vmcs"
.LC11:
	.string	"failed to load vmcs"
	.text
	.align 2
	.globl	_ZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_
	.type	_ZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_, @function
_ZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_:
.LFB3281:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3281
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x70,0x6
	.cfi_escape 0x10,0xc,0x2,0x76,0x78
	pushq	%rbx
	subq	$536, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x68
	movq	%rdi, -536(%rbp)
	movq	%rsi, -544(%rbp)
	movq	%rdx, -552(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rbx
	movq	%rbx, -40(%rbp)
	xorl	%ebx, %ebx
	movq	-536(%rbp), %rcx
	leaq	-160(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB12:
	call	_ZNSt3__18functionIFvvEEC1IZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES9_EUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableISB_XaantsrNS_7is_sameISB_S2_EE5valuesrNS_11__invokableIRSB_JEEE5valueEEE5valuentsrSF_5valueEvE4typeE
.LEHE12:
	leaq	-160(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackC1EONSt3__18functionIFvvEEE@PLT
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__18functionIFvvEED1Ev@PLT
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$32, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
.LEHB13:
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$48, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
.LEHE13:
	movq	-536(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -520(%rbp)
	movq	-520(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$424, %rdx
	movq	(%rdx), %rdx
	movq	-536(%rbp), %rcx
	addq	$24, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	*%rdx
	xorl	$1, %eax
	testb	%al, %al
	je	.L216
	movl	$64, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	leaq	_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_E8__func__(%rip), %rax
	movq	%rax, -512(%rbp)
	leaq	-288(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__121__basic_string_commonILb1EEC2Ev@PLT
	leaq	-288(%rbp), %rax
	movq	%rax, -504(%rbp)
	movq	-504(%rbp), %rax
	movq	%rax, -496(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, -488(%rbp)
	movq	-496(%rbp), %rax
	movq	$0, (%rax)
	movq	-496(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-496(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-512(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__111char_traitsIcE6lengthEPKc@PLT
	movq	%rax, %rdx
	movq	-512(%rbp), %rcx
	leaq	-288(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB14:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm@PLT
.LEHE14:
	leaq	.LC10(%rip), %rax
	movq	%rax, -480(%rbp)
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__121__basic_string_commonILb1EEC2Ev@PLT
	leaq	-320(%rbp), %rax
	movq	%rax, -472(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, -464(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, -456(%rbp)
	movq	-464(%rbp), %rax
	movq	$0, (%rax)
	movq	-464(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-464(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-480(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__111char_traitsIcE6lengthEPKc@PLT
	movq	%rax, %rdx
	movq	-480(%rbp), %rcx
	leaq	-320(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB15:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm@PLT
.LEHE15:
	leaq	-288(%rbp), %rdx
	leaq	-320(%rbp), %rax
	movl	$54, %ecx
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB16:
	call	_ZN3bfn18vmcs_failure_errorC1ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m@PLT
.LEHE16:
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	leaq	-288(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	_ZN3bfn18vmcs_failure_errorD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdx
	movq	_ZTIN3bfn18vmcs_failure_errorE@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB17:
	call	__cxa_throw@PLT
.LEHE17:
.L216:
	movq	-536(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$432, %rdx
	movq	(%rdx), %rdx
	movq	-536(%rbp), %rcx
	addq	$24, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	*%rdx
	xorl	$1, %eax
	testb	%al, %al
	je	.L218
	movl	$64, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	leaq	_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_E8__func__(%rip), %rax
	movq	%rax, -440(%rbp)
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__121__basic_string_commonILb1EEC2Ev@PLT
	leaq	-224(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	%rax, -424(%rbp)
	movq	-424(%rbp), %rax
	movq	%rax, -416(%rbp)
	movq	-424(%rbp), %rax
	movq	$0, (%rax)
	movq	-424(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-424(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__111char_traitsIcE6lengthEPKc@PLT
	movq	%rax, %rdx
	movq	-440(%rbp), %rcx
	leaq	-224(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB18:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm@PLT
.LEHE18:
	leaq	.LC11(%rip), %rax
	movq	%rax, -408(%rbp)
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__121__basic_string_commonILb1EEC2Ev@PLT
	leaq	-256(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movq	%rax, -384(%rbp)
	movq	-392(%rbp), %rax
	movq	$0, (%rax)
	movq	-392(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-392(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-408(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__111char_traitsIcE6lengthEPKc@PLT
	movq	%rax, %rdx
	movq	-408(%rbp), %rcx
	leaq	-256(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB19:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm@PLT
.LEHE19:
	leaq	-224(%rbp), %rdx
	leaq	-256(%rbp), %rax
	movl	$57, %ecx
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB20:
	call	_ZN3bfn18vmcs_failure_errorC1ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m@PLT
.LEHE20:
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	_ZN3bfn18vmcs_failure_errorD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdx
	movq	_ZTIN3bfn18vmcs_failure_errorE@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB21:
	call	__cxa_throw@PLT
.L218:
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$96, %rax
	movq	(%rax), %rax
	movq	-552(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$104, %rax
	movq	(%rax), %rax
	movq	-552(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$112, %rax
	movq	(%rax), %rax
	movq	-552(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$120, %rax
	movq	(%rax), %rax
	movq	-552(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$64, %rax
	movq	(%rax), %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$72, %rax
	movq	(%rax), %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$80, %rax
	movq	(%rax), %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$88, %rax
	movq	(%rax), %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	subq	$-128, %rax
	movq	(%rax), %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$136, %rax
	movq	(%rax), %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$144, %rax
	movq	(%rax), %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$152, %rax
	movq	(%rax), %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$160, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$168, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$176, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$184, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$192, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -376(%rbp)
	movq	-376(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$464, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	xorl	$1, %eax
	testb	%al, %al
	je	.L220
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$224, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$232, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$240, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$248, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$256, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$264, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$272, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-544(%rbp), %rax
	movq	%rax, -368(%rbp)
	movq	-368(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$384, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	-552(%rbp), %rax
	movq	%rax, -360(%rbp)
	movq	-360(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$384, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$1408, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$1400, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$1392, %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
.LEHE21:
	movl	$64, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	leaq	_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_E8__func__(%rip), %rax
	movq	%rax, -352(%rbp)
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__121__basic_string_commonILb1EEC2Ev@PLT
	leaq	-160(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	%rax, -336(%rbp)
	movq	-336(%rbp), %rax
	movq	%rax, -328(%rbp)
	movq	-336(%rbp), %rax
	movq	$0, (%rax)
	movq	-336(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-336(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-352(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__111char_traitsIcE6lengthEPKc@PLT
	movq	%rax, %rdx
	movq	-352(%rbp), %rcx
	leaq	-160(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB22:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm@PLT
.LEHE22:
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	addq	$280, %rax
	movq	(%rax), %rax
	leaq	-192(%rbp), %rdx
	movq	-536(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
.LEHB23:
	call	*%rax
.LEHE23:
	leaq	-160(%rbp), %rdx
	leaq	-192(%rbp), %rax
	movl	$98, %ecx
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB24:
	call	_ZN3bfn25vmcs_launch_failure_errorC1ERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_m@PLT
.LEHE24:
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	_ZN3bfn25vmcs_launch_failure_errorD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdx
	movq	_ZTIN3bfn25vmcs_launch_failure_errorE@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB25:
	call	__cxa_throw@PLT
.LEHE25:
.L220:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollback6commitEv@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackD1Ev@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-40(%rbp), %rbx
	xorq	(%rax), %rbx
	je	.L233
	jmp	.L244
.L237:
	movq	%rax, %r12
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L224
.L236:
	movq	%rax, %r12
.L224:
	leaq	-288(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L225
.L235:
	movq	%rax, %r12
.L225:
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rbx
	jmp	.L226
.L240:
	movq	%rax, %r12
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L228
.L239:
	movq	%rax, %r12
.L228:
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L229
.L238:
	movq	%rax, %r12
.L229:
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rbx
	jmp	.L226
.L243:
	movq	%rax, %r12
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L231
.L242:
	movq	%rax, %r12
.L231:
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L232
.L241:
	movq	%rax, %r12
.L232:
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rbx
	jmp	.L226
.L234:
	movq	%rax, %rbx
.L226:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackD1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB26:
	call	_Unwind_Resume@PLT
.LEHE26:
.L244:
	call	__stack_chk_fail@PLT
.L233:
	addq	$536, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3281:
	.section	.gcc_except_table
.LLSDA3281:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3281-.LLSDACSB3281
.LLSDACSB3281:
	.uleb128 .LEHB12-.LFB3281
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB13-.LFB3281
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L234-.LFB3281
	.uleb128 0
	.uleb128 .LEHB14-.LFB3281
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L235-.LFB3281
	.uleb128 0
	.uleb128 .LEHB15-.LFB3281
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L236-.LFB3281
	.uleb128 0
	.uleb128 .LEHB16-.LFB3281
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L237-.LFB3281
	.uleb128 0
	.uleb128 .LEHB17-.LFB3281
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L234-.LFB3281
	.uleb128 0
	.uleb128 .LEHB18-.LFB3281
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L238-.LFB3281
	.uleb128 0
	.uleb128 .LEHB19-.LFB3281
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L239-.LFB3281
	.uleb128 0
	.uleb128 .LEHB20-.LFB3281
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L240-.LFB3281
	.uleb128 0
	.uleb128 .LEHB21-.LFB3281
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L234-.LFB3281
	.uleb128 0
	.uleb128 .LEHB22-.LFB3281
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L241-.LFB3281
	.uleb128 0
	.uleb128 .LEHB23-.LFB3281
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L242-.LFB3281
	.uleb128 0
	.uleb128 .LEHB24-.LFB3281
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L243-.LFB3281
	.uleb128 0
	.uleb128 .LEHB25-.LFB3281
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L234-.LFB3281
	.uleb128 0
	.uleb128 .LEHB26-.LFB3281
	.uleb128 .LEHE26-.LEHB26
	.uleb128 0
	.uleb128 0
.LLSDACSE3281:
	.text
	.size	_ZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_, .-_ZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_
	.section	.rodata
.LC12:
	.string	"\033[1;31m"
.LC13:
	.string	"FATAL ERROR"
.LC14:
	.string	"\033[0m"
.LC15:
	.string	": "
	.align 8
.LC16:
	.string	"promote failed. unable to rollback state"
	.text
	.align 2
	.type	_ZZN14vmcs_intel_x647promoteEvENKUlvE_clEv, @function
_ZZN14vmcs_intel_x647promoteEvENKUlvE_clEv:
.LFB3300:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	leaq	.LC12(%rip), %rsi
	movq	_ZNSt3__14cerrE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC13(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC16(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rax, -16(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	call	abort@PLT
	.cfi_endproc
.LFE3300:
	.size	_ZZN14vmcs_intel_x647promoteEvENKUlvE_clEv, .-_ZZN14vmcs_intel_x647promoteEvENKUlvE_clEv
	.align 2
	.globl	_ZN14vmcs_intel_x647promoteEv
	.type	_ZN14vmcs_intel_x647promoteEv, @function
_ZN14vmcs_intel_x647promoteEv:
.LFB3299:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3299
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x70,0x6
	.cfi_escape 0x10,0xc,0x2,0x76,0x78
	pushq	%rbx
	subq	$552, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x68
	movq	%rdi, -568(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	movq	%rcx, -40(%rbp)
	xorl	%ecx, %ecx
	leaq	-160(%rbp), %rax
	subq	$8, %rsp
	pushq	%rdx
	movl	$0, %esi
	movq	%rax, %rdi
.LEHB27:
	call	_ZNSt3__18functionIFvvEEC1IZN14vmcs_intel_x647promoteEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
.LEHE27:
	addq	$16, %rsp
	leaq	-160(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackC1EONSt3__18functionIFvvEEE@PLT
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__18functionIFvvEED1Ev@PLT
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$10242, %esi
	movq	%rdx, %rdi
.LEHB28:
	call	*%rax
	movq	%rax, -560(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$10244, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -552(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$10246, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -544(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$10248, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -536(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$18474, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -528(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26660, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -520(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26662, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -512(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26638, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -504(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26640, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -496(%rbp)
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN13gdt_reg_x64_tC1Ev@PLT
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26646, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -254(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$18448, %esi
	movq	%rdx, %rdi
	call	*%rax
	movw	%ax, -256(%rbp)
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN13idt_reg_x64_tC1Ev@PLT
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26648, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -238(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$18450, %esi
	movq	%rdx, %rdi
	call	*%rax
	movw	%ax, -240(%rbp)
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -472(%rbp)
	movq	-472(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	subq	$-128, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26624, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -464(%rbp)
	movq	-464(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$144, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26626, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -456(%rbp)
	movq	-456(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$160, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26628, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$192, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$26650, %esi
	movq	%rdx, %rdi
	call	*%rax
.LEHE28:
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$344, %rdx
	movq	(%rdx), %rdx
	leaq	-256(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	*%rdx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$360, %rdx
	movq	(%rdx), %rdx
	leaq	-240(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	*%rdx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -440(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	(%rax), %rax
	leaq	-224(%rbp), %rdx
	movq	%rdx, -424(%rbp)
	movq	-440(%rbp), %rdx
	movq	%rdx, -416(%rbp)
	movq	%rax, -408(%rbp)
	movq	-424(%rbp), %rax
	movq	-408(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-416(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-424(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-424(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L255
	movq	-424(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	_ZNSt3__119__shared_weak_count12__add_sharedEv@PLT
.L255:
	leaq	-224(%rbp), %rdx
	leaq	-208(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB29:
	call	_ZN7gdt_x64C1ERKNSt3__110shared_ptrI14intrinsics_x64EE@PLT
.LEHE29:
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110shared_ptrI14intrinsics_x64ED1Ev@PLT
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$2062, %esi
	movq	%rdx, %rdi
.LEHB30:
	call	*%rax
	shrq	$3, %rax
	movq	%rax, -488(%rbp)
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$18466, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -480(%rbp)
	movq	-480(%rbp), %rax
	andq	$-3, %rax
	movq	%rax, %rdx
	movq	-488(%rbp), %rax
	movzwl	%ax, %ecx
	leaq	-208(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	_ZN7gdt_x6417set_access_rightsEtm@PLT
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -384(%rbp)
	movq	-384(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$208, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$2048, %esi
	movq	%rdx, %rdi
	call	*%rax
	movzwl	%ax, %eax
	movl	%eax, %esi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -376(%rbp)
	movq	-376(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$224, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$2050, %esi
	movq	%rdx, %rdi
	call	*%rax
	movzwl	%ax, %eax
	movl	%eax, %esi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -368(%rbp)
	movq	-368(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$240, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$2052, %esi
	movq	%rdx, %rdi
	call	*%rax
	movzwl	%ax, %eax
	movl	%eax, %esi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -360(%rbp)
	movq	-360(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$256, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$2054, %esi
	movq	%rdx, %rdi
	call	*%rax
	movzwl	%ax, %eax
	movl	%eax, %esi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -352(%rbp)
	movq	-352(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$272, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$2056, %esi
	movq	%rdx, %rdi
	call	*%rax
	movzwl	%ax, %eax
	movl	%eax, %esi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$288, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$2058, %esi
	movq	%rdx, %rdi
	call	*%rax
	movzwl	%ax, %eax
	movl	%eax, %esi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -336(%rbp)
	movq	-336(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	movq	(%rbx), %rax
	addq	$304, %rax
	movq	(%rax), %r12
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$2062, %esi
	movq	%rdx, %rdi
	call	*%rax
	movzwl	%ax, %eax
	movl	%eax, %esi
	movq	%rbx, %rdi
	call	*%r12
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-560(%rbp), %rdx
	movl	$473, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-552(%rbp), %rdx
	movl	$631, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -280(%rbp)
	movq	-280(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-544(%rbp), %rdx
	movl	$-1073741696, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-536(%rbp), %rdx
	movl	$911, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-528(%rbp), %rdx
	movl	$372, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-520(%rbp), %rdx
	movl	$373, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-512(%rbp), %rdx
	movl	$374, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-504(%rbp), %rdx
	movl	$-1073741568, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -328(%rbp)
	movq	-328(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rcx
	movq	-496(%rbp), %rdx
	movl	$-1073741567, %esi
	movq	%rax, %rdi
	call	*%rcx
	movq	-568(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rdx
	movl	$27656, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, %rdi
	call	promote_vmcs_to_root@PLT
.LEHE30:
	leaq	-208(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7gdt_x64D1Ev@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackD1Ev@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-40(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L275
	jmp	.L279
.L277:
	movq	%rax, %rbx
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110shared_ptrI14intrinsics_x64ED1Ev@PLT
	jmp	.L273
.L278:
	movq	%rax, %rbx
	leaq	-208(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7gdt_x64D1Ev@PLT
	jmp	.L273
.L276:
	movq	%rax, %rbx
.L273:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackD1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB31:
	call	_Unwind_Resume@PLT
.LEHE31:
.L279:
	call	__stack_chk_fail@PLT
.L275:
	leaq	-24(%rbp), %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3299:
	.section	.gcc_except_table
.LLSDA3299:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3299-.LLSDACSB3299
.LLSDACSB3299:
	.uleb128 .LEHB27-.LFB3299
	.uleb128 .LEHE27-.LEHB27
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB28-.LFB3299
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L276-.LFB3299
	.uleb128 0
	.uleb128 .LEHB29-.LFB3299
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L277-.LFB3299
	.uleb128 0
	.uleb128 .LEHB30-.LFB3299
	.uleb128 .LEHE30-.LEHB30
	.uleb128 .L278-.LFB3299
	.uleb128 0
	.uleb128 .LEHB31-.LFB3299
	.uleb128 .LEHE31-.LEHB31
	.uleb128 0
	.uleb128 0
.LLSDACSE3299:
	.text
	.size	_ZN14vmcs_intel_x647promoteEv, .-_ZN14vmcs_intel_x647promoteEv
	.align 2
	.type	_ZZN14vmcs_intel_x6418create_vmcs_regionEvENKUlvE_clEv, @function
_ZZN14vmcs_intel_x6418create_vmcs_regionEvENKUlvE_clEv:
.LFB3308:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	addq	$40, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, %rdi
	call	*%rax
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3308:
	.size	_ZZN14vmcs_intel_x6418create_vmcs_regionEvENKUlvE_clEv, .-_ZZN14vmcs_intel_x6418create_vmcs_regionEvENKUlvE_clEv
	.section	.rodata
.LC17:
	.string	"m_vmcs_region_phys == nullptr"
	.text
	.align 2
	.globl	_ZN14vmcs_intel_x6418create_vmcs_regionEv
	.type	_ZN14vmcs_intel_x6418create_vmcs_regionEv, @function
_ZN14vmcs_intel_x6418create_vmcs_regionEv:
.LFB3307:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3307
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x70,0x6
	.cfi_escape 0x10,0xc,0x2,0x76,0x78
	pushq	%rbx
	subq	$504, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x68
	movq	%rdi, -520(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	movq	%rcx, -40(%rbp)
	xorl	%ecx, %ecx
	movq	-520(%rbp), %rcx
	leaq	-160(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB32:
	call	_ZNSt3__18functionIFvvEEC1IZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
.LEHE32:
	leaq	-160(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackC1EONSt3__18functionIFvvEEE@PLT
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__18functionIFvvEED1Ev@PLT
	call	_ZN14memory_manager8instanceEv@PLT
	movq	(%rax), %rdx
	addq	$32, %rdx
	movq	(%rdx), %rcx
	movl	$4096, %edx
	movl	$4096, %esi
	movq	%rax, %rdi
.LEHB33:
	call	*%rcx
	movq	%rax, -480(%rbp)
	movq	-480(%rbp), %rax
	movq	%rax, -504(%rbp)
	leaq	-504(%rbp), %rax
	movq	(%rax), %rax
	leaq	-512(%rbp), %rdx
	movq	%rdx, -192(%rbp)
	movq	%rax, -496(%rbp)
	leaq	-496(%rbp), %rax
	movq	(%rax), %rax
	movq	-192(%rbp), %rdx
	movq	%rdx, -184(%rbp)
	movq	%rax, -488(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -176(%rbp)
	leaq	-488(%rbp), %rax
	movq	(%rax), %rdx
	movq	-184(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-520(%rbp), %rax
	addq	$32, %rax
	movq	%rax, -384(%rbp)
	leaq	-512(%rbp), %rax
	movq	%rax, -376(%rbp)
	movq	-376(%rbp), %rax
	movq	%rax, -368(%rbp)
	movq	-368(%rbp), %rax
	movq	%rax, -360(%rbp)
	movq	-360(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -352(%rbp)
	movq	-376(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	%rax, -336(%rbp)
	movq	-336(%rbp), %rax
	movq	$0, (%rax)
	movq	-352(%rbp), %rax
	movq	-384(%rbp), %rdx
	movq	%rdx, -328(%rbp)
	movq	%rax, -320(%rbp)
	movq	-328(%rbp), %rax
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -296(%rbp)
	movq	-328(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	%rax, -280(%rbp)
	movq	-280(%rbp), %rax
	movq	-320(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -296(%rbp)
	je	.L294
	movq	-328(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
.L294:
	movq	-384(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	movq	%rax, -232(%rbp)
	leaq	-512(%rbp), %rax
	movq	%rax, -224(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -200(%rbp)
	leaq	-512(%rbp), %rax
	movq	%rax, -472(%rbp)
	movq	$0, -464(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, -456(%rbp)
	movq	-456(%rbp), %rax
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -440(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	%rax, -424(%rbp)
	movq	-424(%rbp), %rax
	movq	-464(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -440(%rbp)
	je	.L308
	movq	-472(%rbp), %rax
	movq	%rax, -416(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -408(%rbp)
	movq	-408(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
.L308:
	call	_ZN14memory_manager8instanceEv@PLT
	movq	(%rax), %rdx
	addq	$48, %rdx
	movq	(%rdx), %rdx
	movq	-480(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	*%rdx
.LEHE33:
	movq	%rax, %rdx
	movq	-520(%rbp), %rax
	movq	%rdx, 24(%rax)
	movq	-520(%rbp), %rax
	movq	24(%rax), %rax
	testq	%rax, %rax
	jne	.L311
	movl	$16, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	leaq	.LC17(%rip), %rsi
	movq	%rbx, %rdi
.LEHB34:
	call	_ZNSt11logic_errorC1EPKc@PLT
.LEHE34:
	movq	_ZNSt11logic_errorD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdx
	movq	_ZTISt11logic_error@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB35:
	call	__cxa_throw@PLT
.LEHE35:
.L311:
	movq	-520(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$96, %rdx
	movq	(%rdx), %rdx
	movl	$1152, %esi
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-480(%rbp), %rax
	movl	%edx, (%rax)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollback6commitEv@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackD1Ev@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-40(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L315
	jmp	.L318
.L317:
	movq	%rax, %r12
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rbx
	jmp	.L314
.L316:
	movq	%rax, %rbx
.L314:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackD1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB36:
	call	_Unwind_Resume@PLT
.LEHE36:
.L318:
	call	__stack_chk_fail@PLT
.L315:
	addq	$504, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3307:
	.section	.gcc_except_table
.LLSDA3307:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3307-.LLSDACSB3307
.LLSDACSB3307:
	.uleb128 .LEHB32-.LFB3307
	.uleb128 .LEHE32-.LEHB32
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB33-.LFB3307
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L316-.LFB3307
	.uleb128 0
	.uleb128 .LEHB34-.LFB3307
	.uleb128 .LEHE34-.LEHB34
	.uleb128 .L317-.LFB3307
	.uleb128 0
	.uleb128 .LEHB35-.LFB3307
	.uleb128 .LEHE35-.LEHB35
	.uleb128 .L316-.LFB3307
	.uleb128 0
	.uleb128 .LEHB36-.LFB3307
	.uleb128 .LEHE36-.LEHB36
	.uleb128 0
	.uleb128 0
.LLSDACSE3307:
	.text
	.size	_ZN14vmcs_intel_x6418create_vmcs_regionEv, .-_ZN14vmcs_intel_x6418create_vmcs_regionEv
	.align 2
	.globl	_ZN14vmcs_intel_x6419release_vmcs_regionEv
	.type	_ZN14vmcs_intel_x6419release_vmcs_regionEv, @function
_ZN14vmcs_intel_x6419release_vmcs_regionEv:
.LFB3310:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	24(%rax), %rax
	testq	%rax, %rax
	je	.L328
	movq	-104(%rbp), %rax
	addq	$32, %rax
	movq	%rax, -88(%rbp)
	movq	$0, -80(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	-80(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -56(%rbp)
	je	.L325
	movq	-88(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
.L325:
	movq	-104(%rbp), %rax
	movq	$0, 24(%rax)
.L328:
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3310:
	.size	_ZN14vmcs_intel_x6419release_vmcs_regionEv, .-_ZN14vmcs_intel_x6419release_vmcs_regionEv
	.align 2
	.type	_ZZN14vmcs_intel_x6425create_exit_handler_stackEvENKUlvE_clEv, @function
_ZZN14vmcs_intel_x6425create_exit_handler_stackEvENKUlvE_clEv:
.LFB3312:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	addq	$56, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, %rdi
	call	*%rax
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3312:
	.size	_ZZN14vmcs_intel_x6425create_exit_handler_stackEvENKUlvE_clEv, .-_ZZN14vmcs_intel_x6425create_exit_handler_stackEvENKUlvE_clEv
	.align 2
	.globl	_ZN14vmcs_intel_x6425create_exit_handler_stackEv
	.type	_ZN14vmcs_intel_x6425create_exit_handler_stackEv, @function
_ZN14vmcs_intel_x6425create_exit_handler_stackEv:
.LFB3311:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3311
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x70,0x6
	.cfi_escape 0x10,0xc,0x2,0x76,0x78
	pushq	%rbx
	subq	$536, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x68
	movq	%rdi, -552(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -40(%rbp)
	xorl	%esi, %esi
	movq	-552(%rbp), %rcx
	leaq	-160(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB37:
	call	_ZNSt3__18functionIFvvEEC1IZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
.LEHE37:
	leaq	-160(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackC1EONSt3__18functionIFvvEEE@PLT
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__18functionIFvvEED1Ev@PLT
	movq	$32768, -496(%rbp)
	movl	$0, %r12d
	movq	-496(%rbp), %rbx
	movq	%rbx, %rdi
.LEHB38:
	call	_Znam@PLT
.LEHE38:
	movq	%rax, %rcx
	movq	%rcx, %rdx
	leaq	-1(%rbx), %rax
.L332:
	testq	%rax, %rax
	js	.L331
	movb	$0, (%rdx)
	addq	$1, %rdx
	subq	$1, %rax
	jmp	.L332
.L331:
	leaq	-528(%rbp), %rax
	movq	%rax, -488(%rbp)
	movq	%rcx, -480(%rbp)
	movl	%r12d, -544(%rbp)
	movq	-488(%rbp), %rax
	movq	%rax, -472(%rbp)
	movq	-480(%rbp), %rax
	movq	%rax, -512(%rbp)
	leaq	-512(%rbp), %rax
	movq	(%rax), %rax
	movq	-472(%rbp), %rdx
	movq	%rdx, -464(%rbp)
	movq	%rax, -504(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, -456(%rbp)
	leaq	-504(%rbp), %rax
	movq	(%rax), %rdx
	movq	-464(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-552(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -360(%rbp)
	leaq	-528(%rbp), %rax
	movq	%rax, -352(%rbp)
	movq	-352(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	%rax, -336(%rbp)
	movq	-336(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -328(%rbp)
	movq	-352(%rbp), %rax
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rax
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rax
	movq	$0, (%rax)
	movq	-328(%rbp), %rax
	movq	-360(%rbp), %rdx
	movq	%rdx, -304(%rbp)
	movq	%rax, -296(%rbp)
	movq	-304(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	%rax, -280(%rbp)
	movq	-280(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -272(%rbp)
	movq	-304(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rax
	movq	-296(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -272(%rbp)
	je	.L345
	movq	-304(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	movq	%rax, -232(%rbp)
	movq	-272(%rbp), %rax
	movq	%rax, -224(%rbp)
	movq	$0, -216(%rbp)
	cmpq	$0, -224(%rbp)
	je	.L345
	movq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdaPv@PLT
.L345:
	movq	-360(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -200(%rbp)
	leaq	-528(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -168(%rbp)
	leaq	-528(%rbp), %rax
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	%rax, -440(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -424(%rbp)
	movq	-448(%rbp), %rax
	movq	%rax, -416(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -408(%rbp)
	movq	-408(%rbp), %rax
	movq	$0, (%rax)
	cmpq	$0, -424(%rbp)
	je	.L359
	movq	-448(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movq	%rax, -384(%rbp)
	movq	-424(%rbp), %rax
	movq	%rax, -376(%rbp)
	movq	$0, -368(%rbp)
	cmpq	$0, -376(%rbp)
	je	.L359
	movq	-376(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdaPv@PLT
.L359:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollback6commitEv@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackD1Ev@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-40(%rbp), %rsi
	xorq	(%rax), %rsi
	je	.L363
	jmp	.L365
.L364:
	movq	%rax, %rbx
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN18commit_or_rollbackD1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB39:
	call	_Unwind_Resume@PLT
.LEHE39:
.L365:
	call	__stack_chk_fail@PLT
.L363:
	addq	$536, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3311:
	.section	.gcc_except_table
.LLSDA3311:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3311-.LLSDACSB3311
.LLSDACSB3311:
	.uleb128 .LEHB37-.LFB3311
	.uleb128 .LEHE37-.LEHB37
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB38-.LFB3311
	.uleb128 .LEHE38-.LEHB38
	.uleb128 .L364-.LFB3311
	.uleb128 0
	.uleb128 .LEHB39-.LFB3311
	.uleb128 .LEHE39-.LEHB39
	.uleb128 0
	.uleb128 0
.LLSDACSE3311:
	.text
	.size	_ZN14vmcs_intel_x6425create_exit_handler_stackEv, .-_ZN14vmcs_intel_x6425create_exit_handler_stackEv
	.align 2
	.globl	_ZN14vmcs_intel_x6426release_exit_handler_stackEv
	.type	_ZN14vmcs_intel_x6426release_exit_handler_stackEv, @function
_ZN14vmcs_intel_x6426release_exit_handler_stackEv:
.LFB3314:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -104(%rbp)
	movq	-104(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	$0, (%rax)
	cmpq	$0, -64(%rbp)
	je	.L374
	movq	-88(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	$0, -8(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L374
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdaPv@PLT
.L374:
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3314:
	.size	_ZN14vmcs_intel_x6426release_exit_handler_stackEv, .-_ZN14vmcs_intel_x6426release_exit_handler_stackEv
	.align 2
	.globl	_ZN14vmcs_intel_x6425write_16bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6425write_16bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6425write_16bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3315:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3315:
	.size	_ZN14vmcs_intel_x6425write_16bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6425write_16bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6425write_64bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6425write_64bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6425write_64bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3316:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3316:
	.size	_ZN14vmcs_intel_x6425write_64bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6425write_64bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6425write_32bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6425write_32bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6425write_32bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3317:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	-88(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$96, %rdx
	movq	(%rdx), %rdx
	movl	$1165, %esi
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, -80(%rbp)
	movq	-88(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$96, %rdx
	movq	(%rdx), %rdx
	movl	$1166, %esi
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, -72(%rbp)
	movq	-88(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$96, %rdx
	movq	(%rdx), %rdx
	movl	$1167, %esi
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, -64(%rbp)
	movq	-88(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$96, %rdx
	movq	(%rdx), %rdx
	movl	$1168, %esi
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, -56(%rbp)
	movq	-80(%rbp), %rax
	movl	%eax, %eax
	movq	%rax, -48(%rbp)
	movq	-80(%rbp), %rax
	shrq	$32, %rax
	movq	%rax, -40(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rdx
	andq	-40(%rbp), %rdx
	movq	-88(%rbp), %rcx
	movl	$16384, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-72(%rbp), %rax
	movl	%eax, %eax
	movq	%rax, -48(%rbp)
	movq	-72(%rbp), %rax
	shrq	$32, %rax
	movq	%rax, -40(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rdx
	andq	-40(%rbp), %rdx
	movq	-88(%rbp), %rcx
	movl	$16386, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-64(%rbp), %rax
	movl	%eax, %eax
	movq	%rax, -48(%rbp)
	movq	-64(%rbp), %rax
	shrq	$32, %rax
	movq	%rax, -40(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rdx
	andq	-40(%rbp), %rdx
	movq	-88(%rbp), %rcx
	movl	$16396, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-56(%rbp), %rax
	movl	%eax, %eax
	movq	%rax, -48(%rbp)
	movq	-56(%rbp), %rax
	shrq	$32, %rax
	movq	%rax, -40(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rdx
	andq	-40(%rbp), %rdx
	movq	-88(%rbp), %rcx
	movl	$16402, %esi
	movq	%rcx, %rdi
	call	*%rax
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3317:
	.size	_ZN14vmcs_intel_x6425write_32bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6425write_32bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6427write_natural_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6427write_natural_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6427write_natural_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3318:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3318:
	.size	_ZN14vmcs_intel_x6427write_natural_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6427write_natural_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6423write_16bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6423write_16bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6423write_16bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3319:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$16, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$2048, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$24, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$2050, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$32, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$2052, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$40, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$2054, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$48, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$2056, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$56, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$2058, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$64, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$2062, %esi
	movq	%rax, %rdi
	call	*%rbx
	nop
	addq	$88, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3319:
	.size	_ZN14vmcs_intel_x6423write_16bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6423write_16bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6423write_64bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6423write_64bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6423write_64bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3320:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-56(%rbp), %rcx
	movq	$-1, %rdx
	movl	$10240, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-64(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$312, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movl	$10242, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-64(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$320, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movl	$10244, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-64(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$328, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movl	$10246, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-64(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$336, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movl	$10248, %esi
	movq	%rax, %rdi
	call	*%rbx
	nop
	addq	$56, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3320:
	.size	_ZN14vmcs_intel_x6423write_64bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6423write_64bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6423write_32bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6423write_32bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6423write_32bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3321:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$168, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -168(%rbp)
	movq	%rsi, -176(%rbp)
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$144, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18432, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$152, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18434, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$160, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18436, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$168, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18438, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$176, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18440, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$184, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18442, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$192, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18446, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	subq	$-128, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-168(%rbp), %rax
	movl	$18448, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$136, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-168(%rbp), %rax
	movl	$18450, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$200, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18452, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$208, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18454, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$216, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18456, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$224, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18458, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$232, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18460, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$240, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18462, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-168(%rbp), %rcx
	movl	$65536, %edx
	movl	$18464, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$248, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movl	%eax, %edx
	movq	-168(%rbp), %rax
	movl	$18466, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-168(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-176(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$344, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	movl	$18474, %esi
	movq	%rax, %rdi
	call	*%rbx
	nop
	addq	$168, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3321:
	.size	_ZN14vmcs_intel_x6423write_32bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6423write_32bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6425write_natural_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6425write_natural_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6425write_natural_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3322:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movq	%rsi, -160(%rbp)
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$72, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26624, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$80, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26626, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$88, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26628, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$256, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26630, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$264, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26632, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$272, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26634, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$280, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26636, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$368, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26638, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$376, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26640, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$304, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26644, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$112, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26646, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$120, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26648, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$96, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26650, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$104, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26656, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$352, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26660, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-160(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$360, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-152(%rbp), %rax
	movl	$26662, %esi
	movq	%rax, %rdi
	call	*%rbx
	nop
	addq	$152, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3322:
	.size	_ZN14vmcs_intel_x6425write_natural_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6425write_natural_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6422write_16bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6422write_16bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6422write_16bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3323:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$16, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$3072, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$24, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$3074, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$32, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$3076, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$40, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$3078, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$48, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$3080, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$56, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$3082, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-96(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$64, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movzwl	%ax, %edx
	movq	-88(%rbp), %rax
	movl	$3084, %esi
	movq	%rax, %rdi
	call	*%rbx
	nop
	addq	$88, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3323:
	.size	_ZN14vmcs_intel_x6422write_16bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6422write_16bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6422write_64bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6422write_64bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6422write_64bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3324:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-64(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$320, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movl	$11264, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-64(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$328, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movl	$11266, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-64(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$336, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movl	$11268, %esi
	movq	%rax, %rdi
	call	*%rbx
	nop
	addq	$56, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3324:
	.size	_ZN14vmcs_intel_x6422write_64bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6422write_64bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6422write_32bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6422write_32bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6422write_32bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3325:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$344, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movl	$19456, %esi
	movq	%rax, %rdi
	call	*%rbx
	nop
	addq	$40, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3325:
	.size	_ZN14vmcs_intel_x6422write_32bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6422write_32bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6424write_natural_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.type	_ZN14vmcs_intel_x6424write_natural_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, @function
_ZN14vmcs_intel_x6424write_natural_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE:
.LFB3326:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -136(%rbp)
	movq	%rsi, -144(%rbp)
	movq	-136(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -128(%rbp)
	addq	$32768, -128(%rbp)
	subq	$16, -128(%rbp)
	andq	$-16, -128(%rbp)
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$72, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27648, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$80, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27650, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$88, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27652, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$368, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27654, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$376, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27656, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$304, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27658, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$112, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27660, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$120, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27662, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$352, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27664, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rbx
	movq	-144(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$360, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movl	$27666, %esi
	movq	%rax, %rdi
	call	*%rbx
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movl	$27668, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	exit_handler_entry@GOTPCREL(%rip), %rdx
	movq	-136(%rbp), %rcx
	movl	$27670, %esi
	movq	%rcx, %rdi
	call	*%rax
	nop
	addq	$136, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3326:
	.size	_ZN14vmcs_intel_x6424write_natural_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE, .-_ZN14vmcs_intel_x6424write_natural_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.align 2
	.globl	_ZN14vmcs_intel_x6431pin_based_vm_execution_controlsEv
	.type	_ZN14vmcs_intel_x6431pin_based_vm_execution_controlsEv, @function
_ZN14vmcs_intel_x6431pin_based_vm_execution_controlsEv:
.LFB3327:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -8(%rbp)
	xorl	%esi, %esi
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-24(%rbp), %rdx
	movl	$16384, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$216, %rax
	movq	(%rax), %rax
	leaq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movl	$1165, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movl	$16384, %esi
	movq	%rcx, %rdi
	call	*%rax
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L460
	call	__stack_chk_fail@PLT
.L460:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3327:
	.size	_ZN14vmcs_intel_x6431pin_based_vm_execution_controlsEv, .-_ZN14vmcs_intel_x6431pin_based_vm_execution_controlsEv
	.align 2
	.globl	_ZN14vmcs_intel_x6445primary_processor_based_vm_execution_controlsEv
	.type	_ZN14vmcs_intel_x6445primary_processor_based_vm_execution_controlsEv, @function
_ZN14vmcs_intel_x6445primary_processor_based_vm_execution_controlsEv:
.LFB3328:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -8(%rbp)
	xorl	%esi, %esi
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-24(%rbp), %rdx
	movl	$16386, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movl	$2147483648, %eax
	orq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$216, %rax
	movq	(%rax), %rax
	leaq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movl	$1166, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movl	$16386, %esi
	movq	%rcx, %rdi
	call	*%rax
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L462
	call	__stack_chk_fail@PLT
.L462:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3328:
	.size	_ZN14vmcs_intel_x6445primary_processor_based_vm_execution_controlsEv, .-_ZN14vmcs_intel_x6445primary_processor_based_vm_execution_controlsEv
	.section	.rodata
.LC18:
	.string	"hello world"
	.text
	.align 2
	.globl	_ZN14vmcs_intel_x6447secondary_processor_based_vm_execution_controlsEv
	.type	_ZN14vmcs_intel_x6447secondary_processor_based_vm_execution_controlsEv, @function
_ZN14vmcs_intel_x6447secondary_processor_based_vm_execution_controlsEv:
.LFB3329:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3329
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	movq	%rcx, -24(%rbp)
	xorl	%ecx, %ecx
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-40(%rbp), %rdx
	movl	$16414, %esi
	movq	%rdx, %rdi
.LEHB40:
	call	*%rax
.LEHE40:
	movq	%rax, -32(%rbp)
	movl	$16, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	leaq	.LC18(%rip), %rsi
	movq	%rbx, %rdi
.LEHB41:
	call	_ZNSt11logic_errorC1EPKc@PLT
.LEHE41:
	movq	_ZNSt11logic_errorD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdx
	movq	_ZTISt11logic_error@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB42:
	call	__cxa_throw@PLT
.L466:
	movq	%rax, %r12
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE42:
	.cfi_endproc
.LFE3329:
	.section	.gcc_except_table
.LLSDA3329:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3329-.LLSDACSB3329
.LLSDACSB3329:
	.uleb128 .LEHB40-.LFB3329
	.uleb128 .LEHE40-.LEHB40
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB41-.LFB3329
	.uleb128 .LEHE41-.LEHB41
	.uleb128 .L466-.LFB3329
	.uleb128 0
	.uleb128 .LEHB42-.LFB3329
	.uleb128 .LEHE42-.LEHB42
	.uleb128 0
	.uleb128 0
.LLSDACSE3329:
	.text
	.size	_ZN14vmcs_intel_x6447secondary_processor_based_vm_execution_controlsEv, .-_ZN14vmcs_intel_x6447secondary_processor_based_vm_execution_controlsEv
	.align 2
	.globl	_ZN14vmcs_intel_x6416vm_exit_controlsEv
	.type	_ZN14vmcs_intel_x6416vm_exit_controlsEv, @function
_ZN14vmcs_intel_x6416vm_exit_controlsEv:
.LFB3330:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -8(%rbp)
	xorl	%esi, %esi
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-24(%rbp), %rdx
	movl	$16396, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orq	$4, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orb	$2, %ah
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orb	$16, %ah
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orq	$262144, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orq	$524288, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orq	$1048576, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orq	$2097152, %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$216, %rax
	movq	(%rax), %rax
	leaq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movl	$1167, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movl	$16396, %esi
	movq	%rcx, %rdi
	call	*%rax
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L468
	call	__stack_chk_fail@PLT
.L468:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3330:
	.size	_ZN14vmcs_intel_x6416vm_exit_controlsEv, .-_ZN14vmcs_intel_x6416vm_exit_controlsEv
	.align 2
	.globl	_ZN14vmcs_intel_x6417vm_entry_controlsEv
	.type	_ZN14vmcs_intel_x6417vm_entry_controlsEv, @function
_ZN14vmcs_intel_x6417vm_entry_controlsEv:
.LFB3331:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -8(%rbp)
	xorl	%esi, %esi
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$200, %rax
	movq	(%rax), %rax
	movq	-24(%rbp), %rdx
	movl	$16402, %esi
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orq	$4, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orb	$2, %ah
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orb	$32, %ah
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orb	$64, %ah
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	orb	$128, %ah
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$216, %rax
	movq	(%rax), %rax
	leaq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movl	$1168, %esi
	movq	%rcx, %rdi
	call	*%rax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$208, %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movl	$16402, %esi
	movq	%rcx, %rdi
	call	*%rax
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L470
	call	__stack_chk_fail@PLT
.L470:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3331:
	.size	_ZN14vmcs_intel_x6417vm_entry_controlsEv, .-_ZN14vmcs_intel_x6417vm_entry_controlsEv
	.align 2
	.globl	_ZNK14vmcs_intel_x646vmreadEm
	.type	_ZNK14vmcs_intel_x646vmreadEm, @function
_ZNK14vmcs_intel_x646vmreadEm:
.LFB3332:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3332
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$96, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rbx
	movq	%rbx, -24(%rbp)
	xorl	%ebx, %ebx
	movq	$0, -96(%rbp)
	movq	-104(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$456, %rdx
	movq	(%rdx), %rcx
	leaq	-96(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movq	%rax, %rdi
	call	*%rcx
	xorl	$1, %eax
	testb	%al, %al
	je	.L473
	movl	$48, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	leaq	_ZZNK14vmcs_intel_x646vmreadEmE8__func__(%rip), %rax
	movq	%rax, -80(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__121__basic_string_commonILb1EEC2Ev@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rax
	movq	$0, (%rax)
	movq	-64(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-64(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__111char_traitsIcE6lengthEPKc@PLT
	movq	%rax, %rdx
	movq	-80(%rbp), %rcx
	leaq	-48(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB43:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm@PLT
.LEHE43:
	leaq	-48(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	$584, %ecx
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB44:
	call	_ZN3bfn23vmcs_read_failure_errorC1EmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm@PLT
.LEHE44:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	_ZN3bfn23vmcs_read_failure_errorD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdx
	movq	_ZTIN3bfn23vmcs_read_failure_errorE@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB45:
	call	__cxa_throw@PLT
.L473:
	movq	-96(%rbp), %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-24(%rbp), %rcx
	xorq	(%rdx), %rcx
	je	.L477
	jmp	.L480
.L479:
	movq	%rax, %r12
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L476
.L478:
	movq	%rax, %r12
.L476:
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE45:
.L480:
	call	__stack_chk_fail@PLT
.L477:
	addq	$96, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3332:
	.section	.gcc_except_table
.LLSDA3332:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3332-.LLSDACSB3332
.LLSDACSB3332:
	.uleb128 .LEHB43-.LFB3332
	.uleb128 .LEHE43-.LEHB43
	.uleb128 .L478-.LFB3332
	.uleb128 0
	.uleb128 .LEHB44-.LFB3332
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L479-.LFB3332
	.uleb128 0
	.uleb128 .LEHB45-.LFB3332
	.uleb128 .LEHE45-.LEHB45
	.uleb128 0
	.uleb128 0
.LLSDACSE3332:
	.text
	.size	_ZNK14vmcs_intel_x646vmreadEm, .-_ZNK14vmcs_intel_x646vmreadEm
	.align 2
	.globl	_ZN14vmcs_intel_x647vmwriteEmm
	.type	_ZN14vmcs_intel_x647vmwriteEmm, @function
_ZN14vmcs_intel_x647vmwriteEmm:
.LFB3336:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3336
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$112, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rbx
	movq	%rbx, -24(%rbp)
	xorl	%ebx, %ebx
	movq	-104(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$448, %rdx
	movq	(%rdx), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movq	%rax, %rdi
	call	*%rcx
	xorl	$1, %eax
	testb	%al, %al
	je	.L489
	movl	$56, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	leaq	_ZZN14vmcs_intel_x647vmwriteEmmE8__func__(%rip), %rax
	movq	%rax, -80(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__121__basic_string_commonILb1EEC2Ev@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rax
	movq	$0, (%rax)
	movq	-64(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-64(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__111char_traitsIcE6lengthEPKc@PLT
	movq	%rax, %rdx
	movq	-80(%rbp), %rcx
	leaq	-48(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB46:
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm@PLT
.LEHE46:
	leaq	-48(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	$593, %r8d
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB47:
	call	_ZN3bfn24vmcs_write_failure_errorC1EmmRKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm@PLT
.LEHE47:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	_ZN3bfn24vmcs_write_failure_errorD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdx
	movq	_ZTIN3bfn24vmcs_write_failure_errorE@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB48:
	call	__cxa_throw@PLT
.L488:
	movq	%rax, %r12
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	jmp	.L485
.L487:
	movq	%rax, %r12
.L485:
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE48:
.L489:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-24(%rbp), %rbx
	xorq	(%rax), %rbx
	je	.L486
	call	__stack_chk_fail@PLT
.L486:
	addq	$112, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3336:
	.section	.gcc_except_table
.LLSDA3336:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3336-.LLSDACSB3336
.LLSDACSB3336:
	.uleb128 .LEHB46-.LFB3336
	.uleb128 .LEHE46-.LEHB46
	.uleb128 .L487-.LFB3336
	.uleb128 0
	.uleb128 .LEHB47-.LFB3336
	.uleb128 .LEHE47-.LEHB47
	.uleb128 .L488-.LFB3336
	.uleb128 0
	.uleb128 .LEHB48-.LFB3336
	.uleb128 .LEHE48-.LEHB48
	.uleb128 0
	.uleb128 0
.LLSDACSE3336:
	.text
	.size	_ZN14vmcs_intel_x647vmwriteEmm, .-_ZN14vmcs_intel_x647vmwriteEmm
	.section	.rodata
.LC19:
	.string	"\033[1;32m"
.LC20:
	.string	"DEBUG"
	.align 8
.LC21:
	.string	"vmcs ctrl field mis-configured for msr allowed 0: "
.LC22:
	.string	"    - allowed0: "
.LC23:
	.string	"    - old ctrl: "
.LC24:
	.string	"    - new ctrl: "
	.align 8
.LC25:
	.string	"vmcs ctrl field mis-configured for msr allowed 1: "
.LC26:
	.string	"    - allowed1: "
	.text
	.align 2
	.globl	_ZN14vmcs_intel_x6418filter_unsupportedEmRm
	.type	_ZN14vmcs_intel_x6418filter_unsupportedEmRm, @function
_ZN14vmcs_intel_x6418filter_unsupportedEmRm:
.LFB3340:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$200, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -184(%rbp)
	movq	%rsi, -192(%rbp)
	movq	%rdx, -200(%rbp)
	movq	-184(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	addq	$96, %rdx
	movq	(%rdx), %rdx
	movq	-192(%rbp), %rcx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movl	%eax, %eax
	movq	%rax, -168(%rbp)
	movq	-176(%rbp), %rax
	shrq	$32, %rax
	movq	%rax, -160(%rbp)
	movq	-200(%rbp), %rax
	movq	(%rax), %rax
	andq	-168(%rbp), %rax
	cmpq	-168(%rbp), %rax
	je	.L492
	movq	-192(%rbp), %rbx
	leaq	.LC19(%rip), %rsi
	movq	_ZNSt3__14coutE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC20(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC21(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	%rax, -96(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -88(%rbp)
	movq	-96(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	movq	-168(%rbp), %rbx
	leaq	.LC19(%rip), %rsi
	movq	_ZNSt3__14coutE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC20(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC22(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	%rax, -112(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -104(%rbp)
	movq	-112(%rbp), %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	movq	-200(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	leaq	.LC19(%rip), %rsi
	movq	_ZNSt3__14coutE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC20(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC23(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	%rax, -128(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -120(%rbp)
	movq	-128(%rbp), %rdx
	movq	-120(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	movq	-200(%rbp), %rax
	movq	(%rax), %rax
	orq	-168(%rbp), %rax
	movq	%rax, %rdx
	movq	-200(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-200(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	leaq	.LC19(%rip), %rsi
	movq	_ZNSt3__14coutE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC20(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC24(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	%rax, -144(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -136(%rbp)
	movq	-144(%rbp), %rdx
	movq	-136(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
.L492:
	movq	-200(%rbp), %rax
	movq	(%rax), %rax
	movq	-160(%rbp), %rdx
	notq	%rdx
	andq	%rdx, %rax
	testq	%rax, %rax
	je	.L502
	movq	-192(%rbp), %rbx
	leaq	.LC19(%rip), %rsi
	movq	_ZNSt3__14coutE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC20(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC25(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	%rax, -32(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	movq	-160(%rbp), %rbx
	leaq	.LC19(%rip), %rsi
	movq	_ZNSt3__14coutE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC20(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC26(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	%rax, -48(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -40(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	movq	-200(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	leaq	.LC19(%rip), %rsi
	movq	_ZNSt3__14coutE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC20(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC23(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	%rax, -64(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	movq	-200(%rbp), %rax
	movq	(%rax), %rax
	andq	-160(%rbp), %rax
	movq	%rax, %rdx
	movq	-200(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-200(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rbx
	leaq	.LC19(%rip), %rsi
	movq	_ZNSt3__14coutE@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC20(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	leaq	.LC24(%rip), %rsi
	movq	%rax, %rdi
	call	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc@PLT
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPKv@PLT
	movq	%rax, -80(%rbp)
	leaq	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rax
	movq	%rax, -72(%rbp)
	movq	-80(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
.L502:
	nop
	addq	$200, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3340:
	.size	_ZN14vmcs_intel_x6418filter_unsupportedEmRm, .-_ZN14vmcs_intel_x6418filter_unsupportedEmRm
	.section	.text._ZNSt3__121__basic_string_commonILb1EEC2Ev,"axG",@progbits,_ZNSt3__121__basic_string_commonILb1EEC5Ev,comdat
	.align 2
	.weak	_ZNSt3__121__basic_string_commonILb1EEC2Ev
	.type	_ZNSt3__121__basic_string_commonILb1EEC2Ev, @function
_ZNSt3__121__basic_string_commonILb1EEC2Ev:
.LFB3344:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3344:
	.size	_ZNSt3__121__basic_string_commonILb1EEC2Ev, .-_ZNSt3__121__basic_string_commonILb1EEC2Ev
	.weak	_ZNSt3__121__basic_string_commonILb1EEC1Ev
	.set	_ZNSt3__121__basic_string_commonILb1EEC1Ev,_ZNSt3__121__basic_string_commonILb1EEC2Ev
	.section	.text._ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev,"axG",@progbits,_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC5Ev,comdat
	.align 2
	.weak	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev
	.type	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev, @function
_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev:
.LFB3402:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3402:
	.size	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev, .-_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev
	.weak	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC1Ev
	.set	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC1Ev,_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev
	.section	.text._ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev,"axG",@progbits,_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC5Ev,comdat
	.align 2
	.weak	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev
	.type	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev, @function
_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev:
.LFB3405:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3405:
	.size	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev, .-_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev
	.weak	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC1Ev
	.set	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC1Ev,_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev
	.section	.text._ZNSt3__18functionIFvvEEC2EOS2_,"axG",@progbits,_ZNSt3__18functionIFvvEEC5EOS2_,comdat
	.align 2
	.weak	_ZNSt3__18functionIFvvEEC2EOS2_
	.type	_ZNSt3__18functionIFvvEEC2EOS2_, @function
_ZNSt3__18functionIFvvEEC2EOS2_:
.LFB3407:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3407
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev@PLT
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	jne	.L507
	movq	-8(%rbp), %rax
	movq	$0, 32(%rax)
	jmp	.L510
.L507:
	movq	-16(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-16(%rbp), %rax
	cmpq	%rax, %rdx
	jne	.L509
	movq	-8(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 32(%rax)
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	movq	(%rax), %rax
	addq	$24, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	32(%rdx), %rcx
	movq	-16(%rbp), %rdx
	movq	32(%rdx), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	jmp	.L510
.L509:
	movq	-16(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 32(%rax)
	movq	-16(%rbp), %rax
	movq	$0, 32(%rax)
.L510:
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3407:
	.section	.gcc_except_table
.LLSDA3407:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3407-.LLSDACSB3407
.LLSDACSB3407:
.LLSDACSE3407:
	.section	.text._ZNSt3__18functionIFvvEEC2EOS2_,"axG",@progbits,_ZNSt3__18functionIFvvEEC5EOS2_,comdat
	.size	_ZNSt3__18functionIFvvEEC2EOS2_, .-_ZNSt3__18functionIFvvEEC2EOS2_
	.weak	_ZNSt3__18functionIFvvEEC1EOS2_
	.set	_ZNSt3__18functionIFvvEEC1EOS2_,_ZNSt3__18functionIFvvEEC2EOS2_
	.section	.text._ZNSt3__18functionIFvvEED2Ev,"axG",@progbits,_ZNSt3__18functionIFvvEED5Ev,comdat
	.align 2
	.weak	_ZNSt3__18functionIFvvEED2Ev
	.type	_ZNSt3__18functionIFvvEED2Ev, @function
_ZNSt3__18functionIFvvEED2Ev:
.LFB3410:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-8(%rbp), %rax
	cmpq	%rax, %rdx
	jne	.L512
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	(%rax), %rax
	addq	$32, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	32(%rdx), %rdx
	movq	%rdx, %rdi
	call	*%rax
	jmp	.L514
.L512:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	je	.L514
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	(%rax), %rax
	addq	$40, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	32(%rdx), %rdx
	movq	%rdx, %rdi
	call	*%rax
.L514:
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3410:
	.size	_ZNSt3__18functionIFvvEED2Ev, .-_ZNSt3__18functionIFvvEED2Ev
	.weak	_ZNSt3__18functionIFvvEED1Ev
	.set	_ZNSt3__18functionIFvvEED1Ev,_ZNSt3__18functionIFvvEED2Ev
	.section	.text._ZNSt3__117bad_function_callC2Ev,"axG",@progbits,_ZNSt3__117bad_function_callC5Ev,comdat
	.align 2
	.weak	_ZNSt3__117bad_function_callC2Ev
	.type	_ZNSt3__117bad_function_callC2Ev, @function
_ZNSt3__117bad_function_callC2Ev:
.LFB3414:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	_ZTVSt9exception@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	_ZTVNSt3__117bad_function_callE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3414:
	.size	_ZNSt3__117bad_function_callC2Ev, .-_ZNSt3__117bad_function_callC2Ev
	.weak	_ZNSt3__117bad_function_callC1Ev
	.set	_ZNSt3__117bad_function_callC1Ev,_ZNSt3__117bad_function_callC2Ev
	.section	.text._ZNSt3__117bad_function_callD2Ev,"axG",@progbits,_ZNSt3__117bad_function_callD5Ev,comdat
	.align 2
	.weak	_ZNSt3__117bad_function_callD2Ev
	.type	_ZNSt3__117bad_function_callD2Ev, @function
_ZNSt3__117bad_function_callD2Ev:
.LFB3417:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTVNSt3__117bad_function_callE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt9exceptionD2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3417:
	.size	_ZNSt3__117bad_function_callD2Ev, .-_ZNSt3__117bad_function_callD2Ev
	.weak	_ZNSt3__117bad_function_callD1Ev
	.set	_ZNSt3__117bad_function_callD1Ev,_ZNSt3__117bad_function_callD2Ev
	.section	.text._ZNSt3__117bad_function_callD0Ev,"axG",@progbits,_ZNSt3__117bad_function_callD5Ev,comdat
	.align 2
	.weak	_ZNSt3__117bad_function_callD0Ev
	.type	_ZNSt3__117bad_function_callD0Ev, @function
_ZNSt3__117bad_function_callD0Ev:
.LFB3419:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__117bad_function_callD1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3419:
	.size	_ZNSt3__117bad_function_callD0Ev, .-_ZNSt3__117bad_function_callD0Ev
	.section	.text._ZNKSt3__18functionIFvvEEclEv,"axG",@progbits,_ZNKSt3__18functionIFvvEEclEv,comdat
	.align 2
	.weak	_ZNKSt3__18functionIFvvEEclEv
	.type	_ZNKSt3__18functionIFvvEEclEv, @function
_ZNKSt3__18functionIFvvEEclEv:
.LFB3412:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	jne	.L519
	movl	$8, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	movq	$0, (%rbx)
	movq	%rbx, %rdi
	call	_ZNSt3__117bad_function_callC1Ev@PLT
	movq	_ZNSt3__117bad_function_callD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdx
	movq	_ZTINSt3__117bad_function_callE@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	__cxa_throw@PLT
.L519:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	(%rax), %rax
	addq	$48, %rax
	movq	(%rax), %rax
	movq	-24(%rbp), %rdx
	movq	32(%rdx), %rdx
	movq	%rdx, %rdi
	call	*%rax
	addq	$24, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3412:
	.size	_ZNKSt3__18functionIFvvEEclEv, .-_ZNKSt3__18functionIFvvEEclEv
	.section	.text._ZNSt3__110shared_ptrImED2Ev,"axG",@progbits,_ZNSt3__110shared_ptrImED5Ev,comdat
	.align 2
	.weak	_ZNSt3__110shared_ptrImED2Ev
	.type	_ZNSt3__110shared_ptrImED2Ev, @function
_ZNSt3__110shared_ptrImED2Ev:
.LFB3424:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L523
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	_ZNSt3__119__shared_weak_count16__release_sharedEv@PLT
.L523:
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3424:
	.size	_ZNSt3__110shared_ptrImED2Ev, .-_ZNSt3__110shared_ptrImED2Ev
	.weak	_ZNSt3__110shared_ptrImED1Ev
	.set	_ZNSt3__110shared_ptrImED1Ev,_ZNSt3__110shared_ptrImED2Ev
	.section	.text._ZNSt3__110shared_ptrI20intrinsics_intel_x64ED2Ev,"axG",@progbits,_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED5Ev,comdat
	.align 2
	.weak	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED2Ev
	.type	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED2Ev, @function
_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED2Ev:
.LFB3427:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L526
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	_ZNSt3__119__shared_weak_count16__release_sharedEv@PLT
.L526:
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3427:
	.size	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED2Ev, .-_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED2Ev
	.weak	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED1Ev
	.set	_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED1Ev,_ZNSt3__110shared_ptrI20intrinsics_intel_x64ED2Ev
	.section	.text._ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc,"axG",@progbits,_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc,comdat
	.weak	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	.type	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc, @function
_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc:
.LFB3435:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__111char_traitsIcE6lengthEPKc@PLT
	movq	%rax, %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3435:
	.size	_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc, .-_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	.section	.text._ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE,"axG",@progbits,_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE,comdat
	.weak	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE
	.type	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE, @function
_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE:
.LFB3436:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%rdi, -200(%rbp)
	movq	%rsi, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L533
	movq	-80(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	jmp	.L541
.L533:
	movq	-80(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	sarl	%eax
	cltq
.L541:
	movq	-208(%rbp), %rdx
	movq	%rdx, -192(%rbp)
	movq	-192(%rbp), %rdx
	movq	%rdx, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	%rdx, -176(%rbp)
	movq	-176(%rbp), %rdx
	movq	%rdx, -168(%rbp)
	movq	-168(%rbp), %rdx
	movq	%rdx, -160(%rbp)
	movq	-160(%rbp), %rdx
	movzbl	(%rdx), %edx
	movzbl	%dl, %edx
	andl	$1, %edx
	testl	%edx, %edx
	setne	%dl
	testb	%dl, %dl
	je	.L545
	movq	-184(%rbp), %rdx
	movq	%rdx, -152(%rbp)
	movq	-152(%rbp), %rdx
	movq	%rdx, -144(%rbp)
	movq	-144(%rbp), %rdx
	movq	%rdx, -136(%rbp)
	movq	-136(%rbp), %rdx
	movq	16(%rdx), %rdx
	jmp	.L555
.L545:
	movq	-184(%rbp), %rdx
	movq	%rdx, -128(%rbp)
	movq	-128(%rbp), %rdx
	movq	%rdx, -120(%rbp)
	movq	-120(%rbp), %rdx
	movq	%rdx, -112(%rbp)
	movq	-112(%rbp), %rdx
	addq	$1, %rdx
	movq	%rdx, -104(%rbp)
	movq	-104(%rbp), %rdx
	movq	%rdx, -96(%rbp)
	movq	-96(%rbp), %rdx
.L555:
	movq	%rdx, -88(%rbp)
	movq	-88(%rbp), %rsi
	movq	-200(%rbp), %rcx
	movq	%rax, %rdx
	movq	%rcx, %rdi
	call	_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3436:
	.size	_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE, .-_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE
	.section	.text._ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_,"axG",@progbits,_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_,comdat
	.weak	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_
	.hidden	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_
	.type	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_, @function
_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_:
.LFB3437:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3437
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	movq	%rcx, -24(%rbp)
	xorl	%ecx, %ecx
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	subq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -40(%rbp)
	movb	$10, -50(%rbp)
	movsbl	-50(%rbp), %ebx
	movq	-40(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB49:
	call	_ZNKSt3__18ios_base6getlocEv@PLT
.LEHE49:
	leaq	-48(%rbp), %rax
	movq	_ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB50:
	call	_ZNKSt3__16locale9use_facetERNS0_2idE@PLT
	movq	%rax, -32(%rbp)
	movb	%bl, -49(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addq	$56, %rax
	movq	(%rax), %rax
	movsbl	-49(%rbp), %ecx
	movq	-32(%rbp), %rdx
	movl	%ecx, %esi
	movq	%rdx, %rdi
	call	*%rax
.LEHE50:
	movl	%eax, %ebx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__16localeD1Ev@PLT
	movsbl	%bl, %edx
	movq	-72(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
.LEHB51:
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE3putEc@PLT
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE5flushEv@PLT
	movq	-72(%rbp), %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-24(%rbp), %rcx
	xorq	(%rdx), %rcx
	je	.L565
	jmp	.L567
.L566:
	movq	%rax, %rbx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__16localeD1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE51:
.L567:
	call	__stack_chk_fail@PLT
.L565:
	addq	$72, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3437:
	.section	.gcc_except_table
.LLSDA3437:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3437-.LLSDACSB3437
.LLSDACSB3437:
	.uleb128 .LEHB49-.LFB3437
	.uleb128 .LEHE49-.LEHB49
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB50-.LFB3437
	.uleb128 .LEHE50-.LEHB50
	.uleb128 .L566-.LFB3437
	.uleb128 0
	.uleb128 .LEHB51-.LFB3437
	.uleb128 .LEHE51-.LEHB51
	.uleb128 0
	.uleb128 0
.LLSDACSE3437:
	.section	.text._ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_,"axG",@progbits,_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_,comdat
	.size	_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_, .-_ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_
	.text
	.align 2
	.type	_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES9_EUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableISB_XaantsrNS_7is_sameISB_S2_EE5valuesrNS_11__invokableIRSB_JEEE5valueEEE5valuentsrSF_5valueEvE4typeE, @function
_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES9_EUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableISB_XaantsrNS_7is_sameISB_S2_EE5valuesrNS_11__invokableIRSB_JEEE5valueEEE5valuentsrSF_5valueEvE4typeE:
.LFB3459:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	subq	$256, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movq	%rdi, -280(%rbp)
	movq	%rsi, -288(%rbp)
	movq	%rdx, -296(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	%rdi, -56(%rbp)
	xorl	%edi, %edi
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev@PLT
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev@PLT
	movq	-280(%rbp), %rax
	movq	$0, 32(%rax)
	movl	$1, %eax
	testb	%al, %al
	je	.L588
	movq	-280(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, 32(%rax)
	leaq	-288(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	32(%rax), %rax
	movq	$16, -248(%rbp)
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	testq	%rax, %rax
	je	.L588
	movq	%rax, -232(%rbp)
	movq	%rdx, -224(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-216(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE(%rip), %rdx
	movq	-232(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-224(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	leaq	-80(%rbp), %rdx
	movq	%rdx, -168(%rbp)
	movzbl	-301(%rbp), %ecx
	movb	%cl, -263(%rbp)
	movzbl	-300(%rbp), %esi
	movb	%sil, -264(%rbp)
	movzbl	-299(%rbp), %ecx
	movb	%cl, -265(%rbp)
	movzbl	-298(%rbp), %esi
	movb	%sil, -266(%rbp)
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rdx, -144(%rbp)
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rdx
	movq	-144(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-80(%rbp), %rax
	movq	%rax, %rdx
	movq	-232(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -120(%rbp)
	movzbl	-297(%rbp), %eax
	movb	%al, -261(%rbp)
	movq	%rdx, -256(%rbp)
	movb	%r15b, -262(%rbp)
	leaq	-256(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rdx, -112(%rbp)
	movb	%r14b, -257(%rbp)
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movb	%r13b, -258(%rbp)
	movb	%r12b, -259(%rbp)
	movb	%bl, -260(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -104(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rdx
	movq	-112(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L588:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-56(%rbp), %rbx
	xorq	(%rax), %rbx
	je	.L587
	call	__stack_chk_fail@PLT
.L587:
	addq	$256, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3459:
	.size	_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES9_EUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableISB_XaantsrNS_7is_sameISB_S2_EE5valuesrNS_11__invokableIRSB_JEEE5valueEEE5valuentsrSF_5valueEvE4typeE, .-_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES9_EUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableISB_XaantsrNS_7is_sameISB_S2_EE5valuesrNS_11__invokableIRSB_JEEE5valueEEE5valuentsrSF_5valueEvE4typeE
	.set	_ZNSt3__18functionIFvvEEC1IZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES9_EUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableISB_XaantsrNS_7is_sameISB_S2_EE5valuesrNS_11__invokableIRSB_JEEE5valueEEE5valuentsrSF_5valueEvE4typeE,_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES9_EUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableISB_XaantsrNS_7is_sameISB_S2_EE5valuesrNS_11__invokableIRSB_JEEE5valueEEE5valuentsrSF_5valueEvE4typeE
	.align 2
	.type	_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x647promoteEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE, @function
_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x647promoteEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE:
.LFB3471:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$264, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -280(%rbp)
	movq	%rsi, -288(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	%rdi, -56(%rbp)
	xorl	%edi, %edi
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev@PLT
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev@PLT
	movq	-280(%rbp), %rax
	movq	$0, 32(%rax)
	movl	$1, %eax
	testb	%al, %al
	je	.L609
	movq	-280(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, 32(%rax)
	leaq	16(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	32(%rax), %rax
	movq	$16, -248(%rbp)
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	testq	%rax, %rax
	je	.L609
	movq	%rax, -232(%rbp)
	movq	%rdx, -224(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-216(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-232(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-224(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	leaq	-80(%rbp), %rdx
	movq	%rdx, -168(%rbp)
	movzbl	-293(%rbp), %ecx
	movb	%cl, -263(%rbp)
	movzbl	-292(%rbp), %esi
	movb	%sil, -264(%rbp)
	movzbl	-291(%rbp), %ecx
	movb	%cl, -265(%rbp)
	movzbl	-290(%rbp), %esi
	movb	%sil, -266(%rbp)
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rdx, -144(%rbp)
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rdx
	movq	-144(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-80(%rbp), %rax
	movq	%rax, %rdx
	movq	-232(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -120(%rbp)
	movzbl	-289(%rbp), %eax
	movb	%al, -261(%rbp)
	movq	%rdx, -256(%rbp)
	movb	%r15b, -262(%rbp)
	leaq	-256(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rdx, -112(%rbp)
	movb	%r14b, -257(%rbp)
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movb	%r13b, -258(%rbp)
	movb	%r12b, -259(%rbp)
	movb	%bl, -260(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -96(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -88(%rbp)
.L609:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-56(%rbp), %rbx
	xorq	(%rax), %rbx
	je	.L608
	call	__stack_chk_fail@PLT
.L608:
	addq	$264, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3471:
	.size	_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x647promoteEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE, .-_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x647promoteEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
	.set	_ZNSt3__18functionIFvvEEC1IZN14vmcs_intel_x647promoteEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE,_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x647promoteEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
	.section	.text._ZNSt3__110shared_ptrI14intrinsics_x64ED2Ev,"axG",@progbits,_ZNSt3__110shared_ptrI14intrinsics_x64ED5Ev,comdat
	.align 2
	.weak	_ZNSt3__110shared_ptrI14intrinsics_x64ED2Ev
	.type	_ZNSt3__110shared_ptrI14intrinsics_x64ED2Ev, @function
_ZNSt3__110shared_ptrI14intrinsics_x64ED2Ev:
.LFB3475:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L612
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	_ZNSt3__119__shared_weak_count16__release_sharedEv@PLT
.L612:
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3475:
	.size	_ZNSt3__110shared_ptrI14intrinsics_x64ED2Ev, .-_ZNSt3__110shared_ptrI14intrinsics_x64ED2Ev
	.weak	_ZNSt3__110shared_ptrI14intrinsics_x64ED1Ev
	.set	_ZNSt3__110shared_ptrI14intrinsics_x64ED1Ev,_ZNSt3__110shared_ptrI14intrinsics_x64ED2Ev
	.text
	.align 2
	.type	_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE, @function
_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE:
.LFB3482:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	subq	$256, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movq	%rdi, -280(%rbp)
	movq	%rsi, -288(%rbp)
	movq	%rdx, -296(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	%rdi, -56(%rbp)
	xorl	%edi, %edi
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev@PLT
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev@PLT
	movq	-280(%rbp), %rax
	movq	$0, 32(%rax)
	movl	$1, %eax
	testb	%al, %al
	je	.L633
	movq	-280(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, 32(%rax)
	leaq	-288(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	32(%rax), %rax
	movq	$16, -248(%rbp)
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	testq	%rax, %rax
	je	.L633
	movq	%rax, -232(%rbp)
	movq	%rdx, -224(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-216(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-232(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-224(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	leaq	-80(%rbp), %rdx
	movq	%rdx, -168(%rbp)
	movzbl	-301(%rbp), %ecx
	movb	%cl, -263(%rbp)
	movzbl	-300(%rbp), %esi
	movb	%sil, -264(%rbp)
	movzbl	-299(%rbp), %ecx
	movb	%cl, -265(%rbp)
	movzbl	-298(%rbp), %esi
	movb	%sil, -266(%rbp)
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rdx, -144(%rbp)
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rdx
	movq	-144(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-80(%rbp), %rax
	movq	%rax, %rdx
	movq	-232(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -120(%rbp)
	movzbl	-297(%rbp), %eax
	movb	%al, -261(%rbp)
	movq	%rdx, -256(%rbp)
	movb	%r15b, -262(%rbp)
	leaq	-256(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rdx, -112(%rbp)
	movb	%r14b, -257(%rbp)
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movb	%r13b, -258(%rbp)
	movb	%r12b, -259(%rbp)
	movb	%bl, -260(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -104(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rdx
	movq	-112(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L633:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-56(%rbp), %rbx
	xorq	(%rax), %rbx
	je	.L632
	call	__stack_chk_fail@PLT
.L632:
	addq	$256, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3482:
	.size	_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE, .-_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
	.set	_ZNSt3__18functionIFvvEEC1IZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE,_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
	.align 2
	.type	_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE, @function
_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE:
.LFB3493:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	subq	$256, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movq	%rdi, -280(%rbp)
	movq	%rsi, -288(%rbp)
	movq	%rdx, -296(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	%rdi, -56(%rbp)
	xorl	%edi, %edi
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function34__maybe_derive_from_unary_functionIFvvEEC2Ev@PLT
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function35__maybe_derive_from_binary_functionIFvvEEC2Ev@PLT
	movq	-280(%rbp), %rax
	movq	$0, 32(%rax)
	movl	$1, %eax
	testb	%al, %al
	je	.L654
	movq	-280(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, 32(%rax)
	leaq	-288(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	32(%rax), %rax
	movq	$16, -248(%rbp)
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	testq	%rax, %rax
	je	.L654
	movq	%rax, -232(%rbp)
	movq	%rdx, -224(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-216(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-232(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-224(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	leaq	-80(%rbp), %rdx
	movq	%rdx, -168(%rbp)
	movzbl	-301(%rbp), %ecx
	movb	%cl, -263(%rbp)
	movzbl	-300(%rbp), %esi
	movb	%sil, -264(%rbp)
	movzbl	-299(%rbp), %ecx
	movb	%cl, -265(%rbp)
	movzbl	-298(%rbp), %esi
	movb	%sil, -266(%rbp)
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rdx, -144(%rbp)
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rdx
	movq	-144(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-80(%rbp), %rax
	movq	%rax, %rdx
	movq	-232(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -120(%rbp)
	movzbl	-297(%rbp), %eax
	movb	%al, -261(%rbp)
	movq	%rdx, -256(%rbp)
	movb	%r15b, -262(%rbp)
	leaq	-256(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rdx, -112(%rbp)
	movb	%r14b, -257(%rbp)
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movb	%r13b, -258(%rbp)
	movb	%r12b, -259(%rbp)
	movb	%bl, -260(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -104(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rdx
	movq	-112(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L654:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-56(%rbp), %rbx
	xorq	(%rax), %rbx
	je	.L653
	call	__stack_chk_fail@PLT
.L653:
	addq	$256, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3493:
	.size	_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE, .-_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
	.set	_ZNSt3__18functionIFvvEEC1IZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE,_ZNSt3__18functionIFvvEEC2IZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EET_PNS_9enable_ifIXaasrNS2_10__callableIS6_XaantsrNS_7is_sameIS6_S2_EE5valuesrNS_11__invokableIRS6_JEEE5valueEEE5valuentsrSA_5valueEvE4typeE
	.section	.text._ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m,"axG",@progbits,_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m,comdat
	.weak	_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.type	_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m, @function
_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m:
.LFB3534:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3534
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$176, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movq	%rdi, -184(%rbp)
	movq	%rsi, -192(%rbp)
	movq	%rdx, -200(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	movq	%rcx, -40(%rbp)
	xorl	%ecx, %ecx
	movq	-184(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB52:
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_@PLT
.LEHE52:
	movzbl	-64(%rbp), %eax
	testb	%al, %al
	je	.L657
	movq	-184(%rbp), %rax
	movq	(%rax), %rax
	subq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movl	144(%rax), %ebx
	call	_ZNSt3__111char_traitsIcE3eofEv@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	_ZNSt3__111char_traitsIcE11eq_int_typeEii@PLT
	testb	%al, %al
	je	.L658
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movb	$32, -170(%rbp)
	movsbl	-170(%rbp), %ebx
	movq	-128(%rbp), %rdx
	leaq	-144(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB53:
	call	_ZNKSt3__18ios_base6getlocEv@PLT
.LEHE53:
	leaq	-144(%rbp), %rax
	movq	_ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB54:
	call	_ZNKSt3__16locale9use_facetERNS0_2idE@PLT
	movq	%rax, -120(%rbp)
	movb	%bl, -169(%rbp)
	movq	-120(%rbp), %rax
	movq	(%rax), %rax
	addq	$56, %rax
	movq	(%rax), %rax
	movsbl	-169(%rbp), %ecx
	movq	-120(%rbp), %rdx
	movl	%ecx, %esi
	movq	%rdx, %rdi
	call	*%rax
.LEHE54:
	movl	%eax, %ebx
	leaq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__16localeD1Ev@PLT
	movsbl	%bl, %edx
	movq	-136(%rbp), %rax
	movl	%edx, 144(%rax)
	jmp	.L658
.L680:
	movq	%rax, %rbx
	leaq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__16localeD1Ev@PLT
	jmp	.L663
.L658:
	movq	-136(%rbp), %rax
	movl	144(%rax), %eax
	movsbl	%al, %r13d
	movq	-184(%rbp), %rax
	movq	(%rax), %rax
	subq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	leaq	(%rdx,%rax), %r14
	movq	-192(%rbp), %rdx
	movq	-200(%rbp), %rax
	leaq	(%rdx,%rax), %r12
	movq	-184(%rbp), %rax
	movq	(%rax), %rax
	subq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movl	8(%rax), %eax
	andl	$176, %eax
	cmpl	$32, %eax
	jne	.L666
	movq	-192(%rbp), %rdx
	movq	-200(%rbp), %rax
	leaq	(%rdx,%rax), %rbx
	jmp	.L667
.L666:
	movq	-192(%rbp), %rbx
.L667:
	movq	-184(%rbp), %rax
	movq	%rax, -104(%rbp)
	leaq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC2Ev@PLT
	movq	-104(%rbp), %rax
	movq	(%rax), %rax
	subq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-104(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, -144(%rbp)
	movq	-192(%rbp), %rsi
	movq	-144(%rbp), %rax
	movl	%r13d, %r9d
	movq	%r14, %r8
	movq	%r12, %rcx
	movq	%rbx, %rdx
	movq	%rax, %rdi
.LEHB55:
	call	_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	testq	%rax, %rax
	sete	%al
	testb	%al, %al
	je	.L657
	movq	-184(%rbp), %rax
	movq	(%rax), %rax
	subq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -80(%rbp)
	movl	$5, -168(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -72(%rbp)
	movl	-168(%rbp), %eax
	movl	%eax, -164(%rbp)
	movq	-72(%rbp), %rax
	movl	32(%rax), %eax
	orl	-164(%rbp), %eax
	movl	%eax, %edx
	movq	-72(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZNSt3__18ios_base5clearEj@PLT
.LEHE55:
.L657:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev@PLT
.L674:
	movq	-184(%rbp), %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-40(%rbp), %rcx
	xorq	(%rdx), %rcx
	je	.L676
	jmp	.L681
.L678:
	movq	%rax, %rbx
.L663:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev@PLT
	movq	%rbx, %rax
	jmp	.L673
.L677:
.L673:
	movq	%rax, %rdi
	call	__cxa_begin_catch@PLT
	movq	-184(%rbp), %rax
	movq	(%rax), %rax
	subq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
.LEHB56:
	call	_ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv@PLT
.LEHE56:
.LEHB57:
	call	__cxa_end_catch@PLT
.LEHE57:
	jmp	.L674
.L679:
	movq	%rax, %rbx
	call	__cxa_end_catch@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB58:
	call	_Unwind_Resume@PLT
.LEHE58:
.L681:
	call	__stack_chk_fail@PLT
.L676:
	addq	$176, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3534:
	.section	.gcc_except_table
	.align 4
.LLSDA3534:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT3534-.LLSDATTD3534
.LLSDATTD3534:
	.byte	0x1
	.uleb128 .LLSDACSE3534-.LLSDACSB3534
.LLSDACSB3534:
	.uleb128 .LEHB52-.LFB3534
	.uleb128 .LEHE52-.LEHB52
	.uleb128 .L677-.LFB3534
	.uleb128 0x1
	.uleb128 .LEHB53-.LFB3534
	.uleb128 .LEHE53-.LEHB53
	.uleb128 .L678-.LFB3534
	.uleb128 0x3
	.uleb128 .LEHB54-.LFB3534
	.uleb128 .LEHE54-.LEHB54
	.uleb128 .L680-.LFB3534
	.uleb128 0x3
	.uleb128 .LEHB55-.LFB3534
	.uleb128 .LEHE55-.LEHB55
	.uleb128 .L678-.LFB3534
	.uleb128 0x3
	.uleb128 .LEHB56-.LFB3534
	.uleb128 .LEHE56-.LEHB56
	.uleb128 .L679-.LFB3534
	.uleb128 0
	.uleb128 .LEHB57-.LFB3534
	.uleb128 .LEHE57-.LEHB57
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB58-.LFB3534
	.uleb128 .LEHE58-.LEHB58
	.uleb128 0
	.uleb128 0
.LLSDACSE3534:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align 4
	.long	0

.LLSDATT3534:
	.section	.text._ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m,"axG",@progbits,_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m,comdat
	.size	_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m, .-_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.section	.text._ZNSt3__110shared_ptrI20intrinsics_intel_x64E11make_sharedIJEEES2_DpOT_,"axG",@progbits,_ZNSt3__110shared_ptrI20intrinsics_intel_x64E11make_sharedIJEEES2_DpOT_,comdat
	.align 2
	.weak	_ZNSt3__110shared_ptrI20intrinsics_intel_x64E11make_sharedIJEEES2_DpOT_
	.type	_ZNSt3__110shared_ptrI20intrinsics_intel_x64E11make_sharedIJEEES2_DpOT_, @function
_ZNSt3__110shared_ptrI20intrinsics_intel_x64E11make_sharedIJEEES2_DpOT_:
.LFB3553:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x68,0x6
	.cfi_escape 0x10,0xd,0x2,0x76,0x78
	.cfi_escape 0x10,0xc,0x2,0x76,0x70
	pushq	%rbx
	subq	$512, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x60
	movq	%rdi, -536(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -40(%rbp)
	xorl	%esi, %esi
	movq	$1, -480(%rbp)
	leaq	-524(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-480(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	$1, -504(%rbp)
	movq	$0, -496(%rbp)
	movq	-504(%rbp), %rax
	salq	$5, %rax
	movq	%rax, -488(%rbp)
	movq	-488(%rbp), %rax
	movq	%rax, %rdi
	call	_Znwm@PLT
	movq	%rax, -440(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	leaq	-64(%rbp), %rdx
	movq	%rdx, -424(%rbp)
	movq	-440(%rbp), %rdx
	movq	%rdx, -520(%rbp)
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	leaq	-96(%rbp), %rax
	leaq	-520(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	-424(%rbp), %rcx
	movq	%rcx, -416(%rbp)
	movq	%rdx, -512(%rbp)
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	leaq	-512(%rbp), %rax
	movq	(%rax), %rdx
	movq	-416(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-80(%rbp), %rax
	movq	-416(%rbp), %rcx
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, 8(%rcx)
	movq	%rdx, 16(%rcx)
	movb	%r13b, -523(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, -456(%rbp)
	movq	-456(%rbp), %rax
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	(%rax), %rax
	movq	$32, -472(%rbp)
	movq	%rax, -464(%rbp)
	movq	-464(%rbp), %rax
	testq	%rax, %rax
	je	.L698
	movq	%rax, -408(%rbp)
	movzbl	-523(%rbp), %eax
	movb	%al, -522(%rbp)
	movq	-408(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	$0, -392(%rbp)
	movq	-400(%rbp), %rax
	movq	%rax, -384(%rbp)
	movq	-392(%rbp), %rax
	movq	%rax, -376(%rbp)
	movq	_ZTVNSt3__114__shared_countE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-384(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-384(%rbp), %rax
	movq	-376(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	_ZTVNSt3__119__shared_weak_countE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-400(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-400(%rbp), %rax
	movq	-392(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	_ZTVNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-408(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-408(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -368(%rbp)
	movb	%r12b, -521(%rbp)
	movq	-368(%rbp), %rax
	movq	%rax, -360(%rbp)
	movb	%bl, -112(%rbp)
	movq	-360(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN20intrinsics_intel_x64C1Ev@PLT
.L698:
	movq	-536(%rbp), %rax
	movq	$0, (%rax)
	movq	-536(%rbp), %rax
	movq	$0, 8(%rax)
	leaq	-64(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	%rax, -280(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, %rdx
	movq	-536(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-64(%rbp), %rax
	movq	%rax, -336(%rbp)
	movq	-336(%rbp), %rax
	movq	%rax, -328(%rbp)
	movq	-328(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -320(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rax
	movq	$0, (%rax)
	movq	-320(%rbp), %rdx
	movq	-536(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-536(%rbp), %rax
	movq	(%rax), %rax
	movq	-536(%rbp), %rdx
	movq	%rdx, -352(%rbp)
	movq	%rax, -344(%rbp)
	nop
	leaq	-64(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	$0, -248(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	movq	%rax, -232(%rbp)
	movq	-232(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -224(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	-248(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -224(%rbp)
	je	.L719
	movq	-256(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -184(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-184(%rbp), %rax
	movq	8(%rax), %rax
	movq	-184(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, -168(%rbp)
	movq	-176(%rbp), %rdx
	movq	%rdx, -160(%rbp)
	movq	%rax, -152(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-152(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
.L719:
	nop
	movq	-536(%rbp), %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-40(%rbp), %rsi
	xorq	(%rdx), %rsi
	je	.L718
	call	__stack_chk_fail@PLT
.L718:
	addq	$512, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3553:
	.size	_ZNSt3__110shared_ptrI20intrinsics_intel_x64E11make_sharedIJEEES2_DpOT_, .-_ZNSt3__110shared_ptrI20intrinsics_intel_x64E11make_sharedIJEEES2_DpOT_
	.section	.text._ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC2Ev,"axG",@progbits,_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC5Ev,comdat
	.align 2
	.weak	_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC2Ev
	.type	_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC2Ev, @function
_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC2Ev:
.LFB3830:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3830:
	.size	_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC2Ev, .-_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC2Ev
	.weak	_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC1Ev
	.set	_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC1Ev,_ZNSt3__18iteratorINS_19output_iterator_tagEvvvvEC2Ev
	.section	.text._ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_,"axG",@progbits,_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_,comdat
	.weak	_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.hidden	_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.type	_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_, @function
_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_:
.LFB3835:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3835
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x70,0x6
	.cfi_escape 0x10,0xc,0x2,0x76,0x78
	pushq	%rbx
	subq	$360, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x68
	movq	%rdi, -352(%rbp)
	movq	%rsi, -344(%rbp)
	movq	%rdx, -360(%rbp)
	movq	%rcx, -368(%rbp)
	movq	%r8, -376(%rbp)
	movl	%r9d, %eax
	movb	%al, -380(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	movq	%rcx, -40(%rbp)
	xorl	%ecx, %ecx
	movq	-352(%rbp), %rax
	testq	%rax, %rax
	jne	.L722
	movq	-352(%rbp), %rbx
	jmp	.L723
.L722:
	movq	-368(%rbp), %rdx
	movq	-344(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -320(%rbp)
	movq	-376(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -328(%rbp)
	movq	-328(%rbp), %rax
	cmpq	-320(%rbp), %rax
	jle	.L725
	movq	-320(%rbp), %rax
	subq	%rax, -328(%rbp)
	jmp	.L726
.L725:
	movq	$0, -328(%rbp)
.L726:
	movq	-360(%rbp), %rdx
	movq	-344(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -312(%rbp)
	cmpq	$0, -312(%rbp)
	jle	.L727
	movq	-352(%rbp), %rax
	movq	%rax, -296(%rbp)
	movq	-344(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -280(%rbp)
	movq	-296(%rbp), %rax
	movq	(%rax), %rax
	addq	$96, %rax
	movq	(%rax), %rax
	movq	-280(%rbp), %rdx
	movq	-288(%rbp), %rsi
	movq	-296(%rbp), %rcx
	movq	%rcx, %rdi
.LEHB59:
	call	*%rax
	cmpq	-312(%rbp), %rax
	setne	%al
	testb	%al, %al
	je	.L727
	movq	$0, -352(%rbp)
	movq	-352(%rbp), %rbx
	jmp	.L723
.L727:
	cmpq	$0, -328(%rbp)
	jle	.L729
	movsbl	-380(%rbp), %eax
	movq	-328(%rbp), %rdx
	movq	%rdx, -272(%rbp)
	movb	%al, -329(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__121__basic_string_commonILb1EEC2Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-256(%rbp), %rax
	movq	$0, (%rax)
	movq	-256(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-256(%rbp), %rax
	movq	$0, 16(%rax)
	movsbl	-329(%rbp), %edx
	movq	-272(%rbp), %rcx
	leaq	-64(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEmc@PLT
.LEHE59:
	leaq	-64(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L733
	movq	-216(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	16(%rax), %rax
	jmp	.L743
.L733:
	movq	-216(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
.L743:
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	-352(%rbp), %rdx
	movq	%rdx, -240(%rbp)
	movq	%rax, -232(%rbp)
	movq	-328(%rbp), %rax
	movq	%rax, -224(%rbp)
	movq	-240(%rbp), %rax
	movq	(%rax), %rax
	addq	$96, %rax
	movq	(%rax), %rax
	movq	-224(%rbp), %rdx
	movq	-232(%rbp), %rsi
	movq	-240(%rbp), %rcx
	movq	%rcx, %rdi
.LEHB60:
	call	*%rax
.LEHE60:
	cmpq	-328(%rbp), %rax
	setne	%al
	testb	%al, %al
	je	.L747
	movq	$0, -352(%rbp)
	movq	-352(%rbp), %rbx
	movl	$0, %r12d
	jmp	.L748
.L747:
	movl	$1, %r12d
.L748:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	cmpl	$1, %r12d
	jne	.L723
	nop
.L729:
	movq	-368(%rbp), %rdx
	movq	-360(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -312(%rbp)
	cmpq	$0, -312(%rbp)
	jle	.L751
	movq	-352(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-360(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-112(%rbp), %rax
	movq	(%rax), %rax
	addq	$96, %rax
	movq	(%rax), %rax
	movq	-96(%rbp), %rdx
	movq	-104(%rbp), %rsi
	movq	-112(%rbp), %rcx
	movq	%rcx, %rdi
.LEHB61:
	call	*%rax
	cmpq	-312(%rbp), %rax
	setne	%al
	testb	%al, %al
	je	.L751
	movq	$0, -352(%rbp)
	movq	-352(%rbp), %rbx
	jmp	.L723
.L751:
	movq	-376(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	$0, -80(%rbp)
	movq	-88(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -72(%rbp)
	movq	-88(%rbp), %rax
	movq	-80(%rbp), %rdx
	movq	%rdx, 24(%rax)
	movq	-352(%rbp), %rbx
.L723:
	movq	%rbx, %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-40(%rbp), %rbx
	xorq	(%rdx), %rbx
	je	.L755
	jmp	.L757
.L756:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE61:
.L757:
	call	__stack_chk_fail@PLT
.L755:
	addq	$360, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3835:
	.section	.gcc_except_table
.LLSDA3835:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3835-.LLSDACSB3835
.LLSDACSB3835:
	.uleb128 .LEHB59-.LFB3835
	.uleb128 .LEHE59-.LEHB59
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB60-.LFB3835
	.uleb128 .LEHE60-.LEHB60
	.uleb128 .L756-.LFB3835
	.uleb128 0
	.uleb128 .LEHB61-.LFB3835
	.uleb128 .LEHE61-.LEHB61
	.uleb128 0
	.uleb128 0
.LLSDACSE3835:
	.section	.text._ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_,"axG",@progbits,_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_,comdat
	.size	_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_, .-_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.section	.text._ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED2Ev,"axG",@progbits,_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED5Ev,comdat
	.align 2
	.weak	_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED2Ev
	.type	_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED2Ev, @function
_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED2Ev:
.LFB3871:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN20intrinsics_intel_x64D1Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3871:
	.size	_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED2Ev, .-_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED2Ev
	.weak	_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED1Ev
	.set	_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED1Ev,_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED2Ev
	.section	.text._ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED2Ev,"axG",@progbits,_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED5Ev,comdat
	.align 2
	.weak	_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED2Ev
	.type	_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED2Ev, @function
_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED2Ev:
.LFB3873:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__128__libcpp_compressed_pair_impINS_9allocatorI20intrinsics_intel_x64EES2_Lj1EED2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3873:
	.size	_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED2Ev, .-_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED2Ev
	.weak	_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED1Ev
	.set	_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED1Ev,_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED2Ev
	.weak	_ZTVNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE
	.section	.data.rel.ro._ZTVNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE,"awG",@progbits,_ZTVNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE,comdat
	.align 8
	.type	_ZTVNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE, @object
	.size	_ZTVNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE, 56
_ZTVNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE:
	.quad	0
	.quad	_ZTINSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE
	.quad	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED1Ev
	.quad	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED0Ev
	.quad	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE16__on_zero_sharedEv
	.quad	_ZNKSt3__119__shared_weak_count13__get_deleterERKSt9type_info
	.quad	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE21__on_zero_shared_weakEv
	.section	.text._ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED2Ev,"axG",@progbits,_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED5Ev,comdat
	.align 2
	.weak	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED2Ev
	.type	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED2Ev, @function
_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED2Ev:
.LFB4159:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTVNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$24, %rax
	movq	%rax, %rdi
	call	_ZNSt3__117__compressed_pairINS_9allocatorI20intrinsics_intel_x64EES2_ED1Ev@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__119__shared_weak_countD2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4159:
	.size	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED2Ev, .-_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED2Ev
	.weak	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED1Ev
	.set	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED1Ev,_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED2Ev
	.section	.text._ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED0Ev,"axG",@progbits,_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED5Ev,comdat
	.align 2
	.weak	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED0Ev
	.type	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED0Ev, @function
_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED0Ev:
.LFB4161:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4161:
	.size	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED0Ev, .-_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEED0Ev
	.section	.data.rel.ro.local,"aw",@progbits
	.align 8
	.type	_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 88
_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.quad	0
	.quad	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv
	.text
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev:
.LFB4163:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4163:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev
	.set	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev,_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev:
.LFB4165:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4165:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev
	.section	.data.rel.ro.local
	.align 8
	.type	_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 88
_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.quad	0
	.quad	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv
	.text
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev:
.LFB4167:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4167:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev
	.set	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev,_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev:
.LFB4169:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4169:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev
	.section	.data.rel.ro.local
	.align 8
	.type	_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 88
_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.quad	0
	.quad	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv
	.text
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev:
.LFB4171:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4171:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev
	.set	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev,_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED2Ev
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev:
.LFB4173:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4173:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEED0Ev
	.section	.data.rel.ro.local
	.align 8
	.type	_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE, @object
	.size	_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE, 88
_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE:
	.quad	0
	.quad	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED1Ev
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED0Ev
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEv
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEPNS0_6__baseISB_EE
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7destroyEv
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE18destroy_deallocateEv
	.quad	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEclEv
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE6targetERKSt9type_info
	.quad	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE11target_typeEv
	.text
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED2Ev, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED2Ev:
.LFB4175:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE(%rip), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4175:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED2Ev, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED2Ev
	.set	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED1Ev,_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED2Ev
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED0Ev, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED0Ev:
.LFB4177:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4177:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED0Ev, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEED0Ev
	.weak	_ZTVNSt3__110__function6__baseIFvvEEE
	.section	.data.rel.ro._ZTVNSt3__110__function6__baseIFvvEEE,"awG",@progbits,_ZTVNSt3__110__function6__baseIFvvEEE,comdat
	.align 8
	.type	_ZTVNSt3__110__function6__baseIFvvEEE, @object
	.size	_ZTVNSt3__110__function6__baseIFvvEEE, 88
_ZTVNSt3__110__function6__baseIFvvEEE:
	.quad	0
	.quad	_ZTINSt3__110__function6__baseIFvvEEE
	.quad	0
	.quad	0
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.weak	_ZTV14vmcs_intel_x64
	.section	.data.rel.ro._ZTV14vmcs_intel_x64,"awG",@progbits,_ZTV14vmcs_intel_x64,comdat
	.align 8
	.type	_ZTV14vmcs_intel_x64, @object
	.size	_ZTV14vmcs_intel_x64, 3040
_ZTV14vmcs_intel_x64:
	.quad	0
	.quad	_ZTI14vmcs_intel_x64
	.quad	_ZN14vmcs_intel_x64D1Ev
	.quad	_ZN14vmcs_intel_x64D0Ev
	.quad	_ZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_
	.quad	_ZN14vmcs_intel_x647promoteEv
	.quad	_ZN14vmcs_intel_x6418create_vmcs_regionEv
	.quad	_ZN14vmcs_intel_x6419release_vmcs_regionEv
	.quad	_ZN14vmcs_intel_x6425create_exit_handler_stackEv
	.quad	_ZN14vmcs_intel_x6426release_exit_handler_stackEv
	.quad	_ZN14vmcs_intel_x6425write_16bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6425write_64bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6425write_32bit_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6427write_natural_control_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6423write_16bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6423write_64bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6423write_32bit_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6425write_natural_guest_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6422write_16bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6422write_64bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6422write_32bit_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6424write_natural_host_stateERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEE
	.quad	_ZN14vmcs_intel_x6431pin_based_vm_execution_controlsEv
	.quad	_ZN14vmcs_intel_x6445primary_processor_based_vm_execution_controlsEv
	.quad	_ZN14vmcs_intel_x6447secondary_processor_based_vm_execution_controlsEv
	.quad	_ZN14vmcs_intel_x6416vm_exit_controlsEv
	.quad	_ZN14vmcs_intel_x6417vm_entry_controlsEv
	.quad	_ZNK14vmcs_intel_x646vmreadEm
	.quad	_ZN14vmcs_intel_x647vmwriteEmm
	.quad	_ZN14vmcs_intel_x6418filter_unsupportedEmRm
	.quad	_ZN14vmcs_intel_x649dump_vmcsEv
	.quad	_ZN14vmcs_intel_x6424print_execution_controlsEv
	.quad	_ZN14vmcs_intel_x6437print_pin_based_vm_execution_controlsEv
	.quad	_ZN14vmcs_intel_x6451print_primary_processor_based_vm_execution_controlsEv
	.quad	_ZN14vmcs_intel_x6453print_secondary_processor_based_vm_execution_controlsEv
	.quad	_ZN14vmcs_intel_x6428print_vm_exit_control_fieldsEv
	.quad	_ZN14vmcs_intel_x6429print_vm_entry_control_fieldsEv
	.quad	_ZN14vmcs_intel_x6424get_vm_instruction_errorEv
	.quad	_ZNK14vmcs_intel_x6412get_pin_ctlsEv
	.quad	_ZNK14vmcs_intel_x6413get_proc_ctlsEv
	.quad	_ZNK14vmcs_intel_x6414get_proc2_ctlsEv
	.quad	_ZNK14vmcs_intel_x6413get_exit_ctlsEv
	.quad	_ZNK14vmcs_intel_x6414get_entry_ctlsEv
	.quad	_ZN14vmcs_intel_x6420is_address_canonicalEm
	.quad	_ZN14vmcs_intel_x6423is_linear_address_validEm
	.quad	_ZN14vmcs_intel_x6425is_physical_address_validEm
	.quad	_ZN14vmcs_intel_x6412is_cs_usableEv
	.quad	_ZN14vmcs_intel_x6412is_ss_usableEv
	.quad	_ZN14vmcs_intel_x6412is_ds_usableEv
	.quad	_ZN14vmcs_intel_x6412is_es_usableEv
	.quad	_ZN14vmcs_intel_x6412is_gs_usableEv
	.quad	_ZN14vmcs_intel_x6412is_fs_usableEv
	.quad	_ZN14vmcs_intel_x6412is_tr_usableEv
	.quad	_ZN14vmcs_intel_x6414is_ldtr_usableEv
	.quad	_ZNK14vmcs_intel_x6416is_enabled_v8086Ev
	.quad	_ZNK14vmcs_intel_x6437is_enabled_external_interrupt_exitingEv
	.quad	_ZNK14vmcs_intel_x6422is_enabled_nmi_exitingEv
	.quad	_ZNK14vmcs_intel_x6423is_enabled_virtual_nmisEv
	.quad	_ZNK14vmcs_intel_x6431is_enabled_vmx_preemption_timerEv
	.quad	_ZNK14vmcs_intel_x6428is_enabled_posted_interruptsEv
	.quad	_ZNK14vmcs_intel_x6435is_enabled_interrupt_window_exitingEv
	.quad	_ZNK14vmcs_intel_x6425is_enabled_tsc_offsettingEv
	.quad	_ZNK14vmcs_intel_x6422is_enabled_hlt_exitingEv
	.quad	_ZNK14vmcs_intel_x6425is_enabled_invlpg_exitingEv
	.quad	_ZNK14vmcs_intel_x6424is_enabled_mwait_exitingEv
	.quad	_ZNK14vmcs_intel_x6424is_enabled_rdpmc_exitingEv
	.quad	_ZNK14vmcs_intel_x6424is_enabled_rdtsc_exitingEv
	.quad	_ZNK14vmcs_intel_x6427is_enabled_cr3_load_exitingEv
	.quad	_ZNK14vmcs_intel_x6428is_enabled_cr3_store_exitingEv
	.quad	_ZNK14vmcs_intel_x6427is_enabled_cr8_load_exitingEv
	.quad	_ZNK14vmcs_intel_x6428is_enabled_cr8_store_exitingEv
	.quad	_ZNK14vmcs_intel_x6421is_enabled_tpr_shadowEv
	.quad	_ZNK14vmcs_intel_x6429is_enabled_nmi_window_exitingEv
	.quad	_ZNK14vmcs_intel_x6425is_enabled_mov_dr_exitingEv
	.quad	_ZNK14vmcs_intel_x6435is_enabled_unconditional_io_exitingEv
	.quad	_ZNK14vmcs_intel_x6421is_enabled_io_bitmapsEv
	.quad	_ZNK14vmcs_intel_x6428is_enabled_monitor_trap_flagEv
	.quad	_ZNK14vmcs_intel_x6422is_enabled_msr_bitmapsEv
	.quad	_ZNK14vmcs_intel_x6426is_enabled_monitor_exitingEv
	.quad	_ZNK14vmcs_intel_x6424is_enabled_pause_exitingEv
	.quad	_ZNK14vmcs_intel_x6429is_enabled_secondary_controlsEv
	.quad	_ZNK14vmcs_intel_x6427is_enabled_virtualized_apicEv
	.quad	_ZNK14vmcs_intel_x6414is_enabled_eptEv
	.quad	_ZNK14vmcs_intel_x6435is_enabled_descriptor_table_exitingEv
	.quad	_ZNK14vmcs_intel_x6417is_enabled_rdtscpEv
	.quad	_ZNK14vmcs_intel_x6422is_enabled_x2apic_modeEv
	.quad	_ZNK14vmcs_intel_x6415is_enabled_vpidEv
	.quad	_ZNK14vmcs_intel_x6425is_enabled_wbinvd_exitingEv
	.quad	_ZNK14vmcs_intel_x6430is_enabled_unrestricted_guestsEv
	.quad	_ZNK14vmcs_intel_x6439is_enabled_apic_register_virtualizationEv
	.quad	_ZNK14vmcs_intel_x6437is_enabled_virtual_interrupt_deliveryEv
	.quad	_ZNK14vmcs_intel_x6429is_enabled_pause_loop_exitingEv
	.quad	_ZNK14vmcs_intel_x6425is_enabled_rdrand_exitingEv
	.quad	_ZNK14vmcs_intel_x6418is_enabled_invpcidEv
	.quad	_ZNK14vmcs_intel_x6423is_enabled_vm_functionsEv
	.quad	_ZNK14vmcs_intel_x6425is_enabled_vmcs_shadowingEv
	.quad	_ZNK14vmcs_intel_x6425is_enabled_rdseed_exitingEv
	.quad	_ZNK14vmcs_intel_x6427is_enabled_ept_violation_veEv
	.quad	_ZNK14vmcs_intel_x6425is_enabled_xsave_xrestoreEv
	.quad	_ZNK14vmcs_intel_x6438is_enabled_save_debug_controls_on_exitEv
	.quad	_ZNK14vmcs_intel_x6434is_enabled_host_address_space_sizeEv
	.quad	_ZNK14vmcs_intel_x6445is_enabled_load_ia32_perf_global_ctrl_on_exitEv
	.quad	_ZNK14vmcs_intel_x6432is_enabled_ack_interrupt_on_exitEv
	.quad	_ZNK14vmcs_intel_x6432is_enabled_save_ia32_pat_on_exitEv
	.quad	_ZNK14vmcs_intel_x6432is_enabled_load_ia32_pat_on_exitEv
	.quad	_ZNK14vmcs_intel_x6433is_enabled_save_ia32_efer_on_exitEv
	.quad	_ZNK14vmcs_intel_x6433is_enabled_load_ia32_efer_on_exitEv
	.quad	_ZNK14vmcs_intel_x6444is_enabled_save_vmx_preemption_timer_on_exitEv
	.quad	_ZNK14vmcs_intel_x6439is_enabled_load_debug_controls_on_entryEv
	.quad	_ZNK14vmcs_intel_x6428is_enabled_ia_32e_mode_guestEv
	.quad	_ZNK14vmcs_intel_x6423is_enabled_entry_to_smmEv
	.quad	_ZNK14vmcs_intel_x6444is_enabled_deactivate_dual_monitor_treatmentEv
	.quad	_ZNK14vmcs_intel_x6446is_enabled_load_ia32_perf_global_ctrl_on_entryEv
	.quad	_ZNK14vmcs_intel_x6433is_enabled_load_ia32_pat_on_entryEv
	.quad	_ZNK14vmcs_intel_x6434is_enabled_load_ia32_efer_on_entryEv
	.quad	_ZNK14vmcs_intel_x6439is_supported_external_interrupt_exitingEv
	.quad	_ZNK14vmcs_intel_x6424is_supported_nmi_exitingEv
	.quad	_ZNK14vmcs_intel_x6425is_supported_virtual_nmisEv
	.quad	_ZNK14vmcs_intel_x6433is_supported_vmx_preemption_timerEv
	.quad	_ZNK14vmcs_intel_x6430is_supported_posted_interruptsEv
	.quad	_ZNK14vmcs_intel_x6437is_supported_interrupt_window_exitingEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_tsc_offsettingEv
	.quad	_ZNK14vmcs_intel_x6424is_supported_hlt_exitingEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_invlpg_exitingEv
	.quad	_ZNK14vmcs_intel_x6426is_supported_mwait_exitingEv
	.quad	_ZNK14vmcs_intel_x6426is_supported_rdpmc_exitingEv
	.quad	_ZNK14vmcs_intel_x6426is_supported_rdtsc_exitingEv
	.quad	_ZNK14vmcs_intel_x6429is_supported_cr3_load_exitingEv
	.quad	_ZNK14vmcs_intel_x6430is_supported_cr3_store_exitingEv
	.quad	_ZNK14vmcs_intel_x6429is_supported_cr8_load_exitingEv
	.quad	_ZNK14vmcs_intel_x6430is_supported_cr8_store_exitingEv
	.quad	_ZNK14vmcs_intel_x6423is_supported_tpr_shadowEv
	.quad	_ZNK14vmcs_intel_x6431is_supported_nmi_window_exitingEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_mov_dr_exitingEv
	.quad	_ZNK14vmcs_intel_x6437is_supported_unconditional_io_exitingEv
	.quad	_ZNK14vmcs_intel_x6423is_supported_io_bitmapsEv
	.quad	_ZNK14vmcs_intel_x6430is_supported_monitor_trap_flagEv
	.quad	_ZNK14vmcs_intel_x6424is_supported_msr_bitmapsEv
	.quad	_ZNK14vmcs_intel_x6428is_supported_monitor_exitingEv
	.quad	_ZNK14vmcs_intel_x6426is_supported_pause_exitingEv
	.quad	_ZNK14vmcs_intel_x6431is_supported_secondary_controlsEv
	.quad	_ZNK14vmcs_intel_x6429is_supported_virtualized_apicEv
	.quad	_ZNK14vmcs_intel_x6416is_supported_eptEv
	.quad	_ZNK14vmcs_intel_x6437is_supported_descriptor_table_exitingEv
	.quad	_ZNK14vmcs_intel_x6419is_supported_rdtscpEv
	.quad	_ZNK14vmcs_intel_x6424is_supported_x2apic_modeEv
	.quad	_ZNK14vmcs_intel_x6417is_supported_vpidEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_wbinvd_exitingEv
	.quad	_ZNK14vmcs_intel_x6432is_supported_unrestricted_guestsEv
	.quad	_ZNK14vmcs_intel_x6441is_supported_apic_register_virtualizationEv
	.quad	_ZNK14vmcs_intel_x6439is_supported_virtual_interrupt_deliveryEv
	.quad	_ZNK14vmcs_intel_x6431is_supported_pause_loop_exitingEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_rdrand_exitingEv
	.quad	_ZNK14vmcs_intel_x6420is_supported_invpcidEv
	.quad	_ZNK14vmcs_intel_x6425is_supported_vm_functionsEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_vmcs_shadowingEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_rdseed_exitingEv
	.quad	_ZNK14vmcs_intel_x6429is_supported_ept_violation_veEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_xsave_xrestoreEv
	.quad	_ZNK14vmcs_intel_x6440is_supported_save_debug_controls_on_exitEv
	.quad	_ZNK14vmcs_intel_x6436is_supported_host_address_space_sizeEv
	.quad	_ZNK14vmcs_intel_x6447is_supported_load_ia32_perf_global_ctrl_on_exitEv
	.quad	_ZNK14vmcs_intel_x6434is_supported_ack_interrupt_on_exitEv
	.quad	_ZNK14vmcs_intel_x6434is_supported_save_ia32_pat_on_exitEv
	.quad	_ZNK14vmcs_intel_x6434is_supported_load_ia32_pat_on_exitEv
	.quad	_ZNK14vmcs_intel_x6435is_supported_save_ia32_efer_on_exitEv
	.quad	_ZNK14vmcs_intel_x6435is_supported_load_ia32_efer_on_exitEv
	.quad	_ZNK14vmcs_intel_x6446is_supported_save_vmx_preemption_timer_on_exitEv
	.quad	_ZNK14vmcs_intel_x6441is_supported_load_debug_controls_on_entryEv
	.quad	_ZNK14vmcs_intel_x6430is_supported_ia_32e_mode_guestEv
	.quad	_ZNK14vmcs_intel_x6425is_supported_entry_to_smmEv
	.quad	_ZNK14vmcs_intel_x6446is_supported_deactivate_dual_monitor_treatmentEv
	.quad	_ZNK14vmcs_intel_x6448is_supported_load_ia32_perf_global_ctrl_on_entryEv
	.quad	_ZNK14vmcs_intel_x6435is_supported_load_ia32_pat_on_entryEv
	.quad	_ZNK14vmcs_intel_x6436is_supported_load_ia32_efer_on_entryEv
	.quad	_ZNK14vmcs_intel_x6427is_supported_eptp_switchingEv
	.quad	_ZN14vmcs_intel_x6421check_vmcs_host_stateEv
	.quad	_ZN14vmcs_intel_x6422check_vmcs_guest_stateEv
	.quad	_ZN14vmcs_intel_x6424check_vmcs_control_stateEv
	.quad	_ZN14vmcs_intel_x6437check_host_control_registers_and_msrsEv
	.quad	_ZN14vmcs_intel_x6435check_host_cr0_for_unsupported_bitsEv
	.quad	_ZN14vmcs_intel_x6435check_host_cr4_for_unsupported_bitsEv
	.quad	_ZN14vmcs_intel_x6435check_host_cr3_for_unsupported_bitsEv
	.quad	_ZN14vmcs_intel_x6446check_host_ia32_sysenter_esp_canonical_addressEv
	.quad	_ZN14vmcs_intel_x6446check_host_ia32_sysenter_eip_canonical_addressEv
	.quad	_ZN14vmcs_intel_x6444check_host_verify_load_ia32_perf_global_ctrlEv
	.quad	_ZN14vmcs_intel_x6431check_host_verify_load_ia32_patEv
	.quad	_ZN14vmcs_intel_x6432check_host_verify_load_ia32_eferEv
	.quad	_ZN14vmcs_intel_x6449check_host_segment_and_descriptor_table_registersEv
	.quad	_ZN14vmcs_intel_x6440check_host_es_selector_rpl_ti_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6440check_host_cs_selector_rpl_ti_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6440check_host_ss_selector_rpl_ti_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6440check_host_ds_selector_rpl_ti_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6440check_host_fs_selector_rpl_ti_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6440check_host_gs_selector_rpl_ti_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6440check_host_tr_selector_rpl_ti_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6428check_host_cs_not_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6428check_host_tr_not_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6428check_host_ss_not_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6436check_host_fs_canonical_base_addressEv
	.quad	_ZN14vmcs_intel_x6436check_host_gs_canonical_base_addressEv
	.quad	_ZN14vmcs_intel_x6438check_host_gdtr_canonical_base_addressEv
	.quad	_ZN14vmcs_intel_x6438check_host_idtr_canonical_base_addressEv
	.quad	_ZN14vmcs_intel_x6436check_host_tr_canonical_base_addressEv
	.quad	_ZN14vmcs_intel_x6447check_host_checks_related_to_address_space_sizeEv
	.quad	_ZN14vmcs_intel_x6432check_host_if_outside_ia32e_modeEv
	.quad	_ZN14vmcs_intel_x6446check_host_vmcs_host_address_space_size_is_setEv
	.quad	_ZN14vmcs_intel_x6438check_host_host_address_space_disabledEv
	.quad	_ZN14vmcs_intel_x6437check_host_host_address_space_enabledEv
	.quad	_ZN14vmcs_intel_x6458checks_on_guest_control_registers_debug_registers_and_msrsEv
	.quad	_ZN14vmcs_intel_x6436check_guest_cr0_for_unsupported_bitsEv
	.quad	_ZN14vmcs_intel_x6437check_guest_cr0_verify_paging_enabledEv
	.quad	_ZN14vmcs_intel_x6436check_guest_cr4_for_unsupported_bitsEv
	.quad	_ZN14vmcs_intel_x6447check_guest_load_debug_controls_verify_reservedEv
	.quad	_ZN14vmcs_intel_x6438check_guest_verify_ia_32e_mode_enabledEv
	.quad	_ZN14vmcs_intel_x6439check_guest_verify_ia_32e_mode_disabledEv
	.quad	_ZN14vmcs_intel_x6436check_guest_cr3_for_unsupported_bitsEv
	.quad	_ZN14vmcs_intel_x6442check_guest_load_debug_controls_verify_dr7Ev
	.quad	_ZN14vmcs_intel_x6447check_guest_ia32_sysenter_esp_canonical_addressEv
	.quad	_ZN14vmcs_intel_x6447check_guest_ia32_sysenter_eip_canonical_addressEv
	.quad	_ZN14vmcs_intel_x6445check_guest_verify_load_ia32_perf_global_ctrlEv
	.quad	_ZN14vmcs_intel_x6432check_guest_verify_load_ia32_patEv
	.quad	_ZN14vmcs_intel_x6433check_guest_verify_load_ia32_eferEv
	.quad	_ZN14vmcs_intel_x6433checks_on_guest_segment_registersEv
	.quad	_ZN14vmcs_intel_x6430check_guest_tr_ti_bit_equals_0Ev
	.quad	_ZN14vmcs_intel_x6432check_guest_ldtr_ti_bit_equals_0Ev
	.quad	_ZN14vmcs_intel_x6438check_guest_ss_and_cs_rpl_are_the_sameEv
	.quad	_ZN14vmcs_intel_x6430check_guest_cs_base_is_shiftedEv
	.quad	_ZN14vmcs_intel_x6430check_guest_ss_base_is_shiftedEv
	.quad	_ZN14vmcs_intel_x6430check_guest_ds_base_is_shiftedEv
	.quad	_ZN14vmcs_intel_x6430check_guest_es_base_is_shiftedEv
	.quad	_ZN14vmcs_intel_x6430check_guest_fs_base_is_shiftedEv
	.quad	_ZN14vmcs_intel_x6430check_guest_gs_base_is_shiftedEv
	.quad	_ZN14vmcs_intel_x6432check_guest_tr_base_is_canonicalEv
	.quad	_ZN14vmcs_intel_x6432check_guest_fs_base_is_canonicalEv
	.quad	_ZN14vmcs_intel_x6432check_guest_gs_base_is_canonicalEv
	.quad	_ZN14vmcs_intel_x6434check_guest_ldtr_base_is_canonicalEv
	.quad	_ZN14vmcs_intel_x6433check_guest_cs_base_upper_dword_0Ev
	.quad	_ZN14vmcs_intel_x6433check_guest_ss_base_upper_dword_0Ev
	.quad	_ZN14vmcs_intel_x6433check_guest_ds_base_upper_dword_0Ev
	.quad	_ZN14vmcs_intel_x6433check_guest_es_base_upper_dword_0Ev
	.quad	_ZN14vmcs_intel_x6420check_guest_cs_limitEv
	.quad	_ZN14vmcs_intel_x6420check_guest_ss_limitEv
	.quad	_ZN14vmcs_intel_x6420check_guest_ds_limitEv
	.quad	_ZN14vmcs_intel_x6420check_guest_es_limitEv
	.quad	_ZN14vmcs_intel_x6420check_guest_gs_limitEv
	.quad	_ZN14vmcs_intel_x6420check_guest_fs_limitEv
	.quad	_ZN14vmcs_intel_x6434check_guest_v8086_cs_access_rightsEv
	.quad	_ZN14vmcs_intel_x6434check_guest_v8086_ss_access_rightsEv
	.quad	_ZN14vmcs_intel_x6434check_guest_v8086_ds_access_rightsEv
	.quad	_ZN14vmcs_intel_x6434check_guest_v8086_es_access_rightsEv
	.quad	_ZN14vmcs_intel_x6434check_guest_v8086_fs_access_rightsEv
	.quad	_ZN14vmcs_intel_x6434check_guest_v8086_gs_access_rightsEv
	.quad	_ZN14vmcs_intel_x6433check_guest_cs_access_rights_typeEv
	.quad	_ZN14vmcs_intel_x6433check_guest_ss_access_rights_typeEv
	.quad	_ZN14vmcs_intel_x6433check_guest_ds_access_rights_typeEv
	.quad	_ZN14vmcs_intel_x6433check_guest_es_access_rights_typeEv
	.quad	_ZN14vmcs_intel_x6433check_guest_fs_access_rights_typeEv
	.quad	_ZN14vmcs_intel_x6433check_guest_gs_access_rights_typeEv
	.quad	_ZN14vmcs_intel_x6441check_guest_cs_is_not_a_system_descriptorEv
	.quad	_ZN14vmcs_intel_x6441check_guest_ss_is_not_a_system_descriptorEv
	.quad	_ZN14vmcs_intel_x6441check_guest_ds_is_not_a_system_descriptorEv
	.quad	_ZN14vmcs_intel_x6441check_guest_es_is_not_a_system_descriptorEv
	.quad	_ZN14vmcs_intel_x6441check_guest_fs_is_not_a_system_descriptorEv
	.quad	_ZN14vmcs_intel_x6441check_guest_gs_is_not_a_system_descriptorEv
	.quad	_ZN14vmcs_intel_x6431check_guest_cs_type_not_equal_3Ev
	.quad	_ZN14vmcs_intel_x6436check_guest_cs_dpl_adheres_to_ss_dplEv
	.quad	_ZN14vmcs_intel_x6433check_guest_ss_dpl_must_equal_rplEv
	.quad	_ZN14vmcs_intel_x6434check_guest_ss_dpl_must_equal_zeroEv
	.quad	_ZN14vmcs_intel_x6418check_guest_ds_dplEv
	.quad	_ZN14vmcs_intel_x6418check_guest_es_dplEv
	.quad	_ZN14vmcs_intel_x6418check_guest_fs_dplEv
	.quad	_ZN14vmcs_intel_x6418check_guest_gs_dplEv
	.quad	_ZN14vmcs_intel_x6430check_guest_cs_must_be_presentEv
	.quad	_ZN14vmcs_intel_x6440check_guest_ss_must_be_present_if_usableEv
	.quad	_ZN14vmcs_intel_x6440check_guest_ds_must_be_present_if_usableEv
	.quad	_ZN14vmcs_intel_x6440check_guest_es_must_be_present_if_usableEv
	.quad	_ZN14vmcs_intel_x6440check_guest_fs_must_be_present_if_usableEv
	.quad	_ZN14vmcs_intel_x6440check_guest_gs_must_be_present_if_usableEv
	.quad	_ZN14vmcs_intel_x6447check_guest_cs_access_rights_reserved_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6447check_guest_ss_access_rights_reserved_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6447check_guest_ds_access_rights_reserved_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6447check_guest_es_access_rights_reserved_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6447check_guest_fs_access_rights_reserved_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6447check_guest_gs_access_rights_reserved_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6441check_guest_cs_db_must_be_0_if_l_equals_1Ev
	.quad	_ZN14vmcs_intel_x6426check_guest_cs_granularityEv
	.quad	_ZN14vmcs_intel_x6426check_guest_ss_granularityEv
	.quad	_ZN14vmcs_intel_x6426check_guest_ds_granularityEv
	.quad	_ZN14vmcs_intel_x6426check_guest_es_granularityEv
	.quad	_ZN14vmcs_intel_x6426check_guest_fs_granularityEv
	.quad	_ZN14vmcs_intel_x6426check_guest_gs_granularityEv
	.quad	_ZN14vmcs_intel_x6453check_guest_cs_access_rights_remaining_reserved_bit_0Ev
	.quad	_ZN14vmcs_intel_x6453check_guest_ss_access_rights_remaining_reserved_bit_0Ev
	.quad	_ZN14vmcs_intel_x6453check_guest_ds_access_rights_remaining_reserved_bit_0Ev
	.quad	_ZN14vmcs_intel_x6453check_guest_es_access_rights_remaining_reserved_bit_0Ev
	.quad	_ZN14vmcs_intel_x6453check_guest_fs_access_rights_remaining_reserved_bit_0Ev
	.quad	_ZN14vmcs_intel_x6453check_guest_gs_access_rights_remaining_reserved_bit_0Ev
	.quad	_ZN14vmcs_intel_x6430check_guest_tr_type_must_be_11Ev
	.quad	_ZN14vmcs_intel_x6442check_guest_tr_must_be_a_system_descriptorEv
	.quad	_ZN14vmcs_intel_x6430check_guest_tr_must_be_presentEv
	.quad	_ZN14vmcs_intel_x6447check_guest_tr_access_rights_reserved_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6426check_guest_tr_granularityEv
	.quad	_ZN14vmcs_intel_x6429check_guest_tr_must_be_usableEv
	.quad	_ZN14vmcs_intel_x6453check_guest_tr_access_rights_remaining_reserved_bit_0Ev
	.quad	_ZN14vmcs_intel_x6431check_guest_ldtr_type_must_be_2Ev
	.quad	_ZN14vmcs_intel_x6444check_guest_ldtr_must_be_a_system_descriptorEv
	.quad	_ZN14vmcs_intel_x6432check_guest_ldtr_must_be_presentEv
	.quad	_ZN14vmcs_intel_x6449check_guest_ldtr_access_rights_reserved_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6428check_guest_ldtr_granularityEv
	.quad	_ZN14vmcs_intel_x6455check_guest_ldtr_access_rights_remaining_reserved_bit_0Ev
	.quad	_ZN14vmcs_intel_x6442checks_on_guest_descriptor_table_registersEv
	.quad	_ZN14vmcs_intel_x6439check_guest_gdtr_base_must_be_canonicalEv
	.quad	_ZN14vmcs_intel_x6439check_guest_idtr_base_must_be_canonicalEv
	.quad	_ZN14vmcs_intel_x6436check_guest_gdtr_limit_reserved_bitsEv
	.quad	_ZN14vmcs_intel_x6436check_guest_idtr_limit_reserved_bitsEv
	.quad	_ZN14vmcs_intel_x6430checks_on_guest_rip_and_rflagsEv
	.quad	_ZN14vmcs_intel_x6426check_guest_rip_upper_bitsEv
	.quad	_ZN14vmcs_intel_x6426check_guest_rip_valid_addrEv
	.quad	_ZN14vmcs_intel_x6432check_guest_rflags_reserved_bitsEv
	.quad	_ZN14vmcs_intel_x6425check_guest_rflags_vm_bitEv
	.quad	_ZN14vmcs_intel_x6434check_guest_rflag_interrupt_enableEv
	.quad	_ZN14vmcs_intel_x6434checks_on_guest_non_register_stateEv
	.quad	_ZN14vmcs_intel_x6432check_guest_valid_activity_stateEv
	.quad	_ZN14vmcs_intel_x6449check_guest_activity_state_not_hlt_when_dpl_not_0Ev
	.quad	_ZN14vmcs_intel_x6454check_guest_must_be_active_if_injecting_blocking_stateEv
	.quad	_ZN14vmcs_intel_x6432check_guest_hlt_valid_interruptsEv
	.quad	_ZN14vmcs_intel_x6437check_guest_shutdown_valid_interruptsEv
	.quad	_ZN14vmcs_intel_x6433check_guest_sipi_valid_interruptsEv
	.quad	_ZN14vmcs_intel_x6440check_guest_valid_activity_state_and_smmEv
	.quad	_ZN14vmcs_intel_x6443check_guest_interruptability_state_reservedEv
	.quad	_ZN14vmcs_intel_x6445check_guest_interruptability_state_sti_mov_ssEv
	.quad	_ZN14vmcs_intel_x6438check_guest_interruptability_state_stiEv
	.quad	_ZN14vmcs_intel_x6453check_guest_interruptability_state_external_interruptEv
	.quad	_ZN14vmcs_intel_x6438check_guest_interruptability_state_nmiEv
	.quad	_ZN14vmcs_intel_x6439check_guest_interruptability_not_in_smmEv
	.quad	_ZN14vmcs_intel_x6441check_guest_interruptability_entry_to_smmEv
	.quad	_ZN14vmcs_intel_x6446check_guest_interruptability_state_sti_and_nmiEv
	.quad	_ZN14vmcs_intel_x6446check_guest_interruptability_state_virtual_nmiEv
	.quad	_ZN14vmcs_intel_x6445check_guest_pending_debug_exceptions_reservedEv
	.quad	_ZN14vmcs_intel_x6444check_guest_pending_debug_exceptions_dbg_ctlEv
	.quad	_ZN14vmcs_intel_x6439check_guest_vmcs_link_pointer_bits_11_0Ev
	.quad	_ZN14vmcs_intel_x6440check_guest_vmcs_link_pointer_valid_addrEv
	.quad	_ZN14vmcs_intel_x6440check_guest_vmcs_link_pointer_first_wordEv
	.quad	_ZN14vmcs_intel_x6440check_guest_vmcs_link_pointer_not_in_smmEv
	.quad	_ZN14vmcs_intel_x6436check_guest_vmcs_link_pointer_in_smmEv
	.quad	_ZN14vmcs_intel_x6437checks_on_vm_execution_control_fieldsEv
	.quad	_ZN14vmcs_intel_x6450check_control_pin_based_ctls_reserved_properly_setEv
	.quad	_ZN14vmcs_intel_x6451check_control_proc_based_ctls_reserved_properly_setEv
	.quad	_ZN14vmcs_intel_x6452check_control_proc_based_ctls2_reserved_properly_setEv
	.quad	_ZN14vmcs_intel_x6435check_control_cr3_count_less_then_4Ev
	.quad	_ZN14vmcs_intel_x6436check_control_io_bitmap_address_bitsEv
	.quad	_ZN14vmcs_intel_x6437check_control_msr_bitmap_address_bitsEv
	.quad	_ZN14vmcs_intel_x6441check_control_tpr_shadow_and_virtual_apicEv
	.quad	_ZN14vmcs_intel_x6441check_control_nmi_exiting_and_virtual_nmiEv
	.quad	_ZN14vmcs_intel_x6440check_control_virtual_nmi_and_nmi_windowEv
	.quad	_ZN14vmcs_intel_x6439check_control_virtual_apic_address_bitsEv
	.quad	_ZN14vmcs_intel_x6449check_control_x2apic_mode_and_virtual_apic_accessEv
	.quad	_ZN14vmcs_intel_x6454check_control_virtual_interrupt_and_external_interruptEv
	.quad	_ZN14vmcs_intel_x6445check_control_process_posted_interrupt_checksEv
	.quad	_ZN14vmcs_intel_x6425check_control_vpid_checksEv
	.quad	_ZN14vmcs_intel_x6431check_control_enable_ept_checksEv
	.quad	_ZN14vmcs_intel_x6433check_control_unrestricted_guestsEv
	.quad	_ZN14vmcs_intel_x6433check_control_enable_vm_functionsEv
	.quad	_ZN14vmcs_intel_x6435check_control_enable_vmcs_shadowingEv
	.quad	_ZN14vmcs_intel_x6441check_control_enable_ept_violation_checksEv
	.quad	_ZN14vmcs_intel_x6432checks_on_vm_exit_control_fieldsEv
	.quad	_ZN14vmcs_intel_x6448check_control_vm_exit_ctls_reserved_properly_setEv
	.quad	_ZN14vmcs_intel_x6458check_control_activate_and_save_premeption_timer_must_be_0Ev
	.quad	_ZN14vmcs_intel_x6436check_control_exit_msr_store_addressEv
	.quad	_ZN14vmcs_intel_x6435check_control_exit_msr_load_addressEv
	.quad	_ZN14vmcs_intel_x6433checks_on_vm_entry_control_fieldsEv
	.quad	_ZN14vmcs_intel_x6449check_control_vm_entry_ctls_reserved_properly_setEv
	.quad	_ZN14vmcs_intel_x6448check_control_event_injection_type_vector_checksEv
	.quad	_ZN14vmcs_intel_x6448check_control_event_injection_delivery_ec_checksEv
	.quad	_ZN14vmcs_intel_x6450check_control_event_injection_reserved_bits_checksEv
	.quad	_ZN14vmcs_intel_x6439check_control_event_injection_ec_checksEv
	.quad	_ZN14vmcs_intel_x6449check_control_event_injection_instr_length_checksEv
	.quad	_ZN14vmcs_intel_x6436check_control_entry_msr_load_addressEv
	.quad	_ZN14vmcs_intel_x649check_patEm
	.weak	_ZTVN3bfn25vmcs_launch_failure_errorE
	.section	.data.rel.ro._ZTVN3bfn25vmcs_launch_failure_errorE,"awG",@progbits,_ZTVN3bfn25vmcs_launch_failure_errorE,comdat
	.align 8
	.type	_ZTVN3bfn25vmcs_launch_failure_errorE, @object
	.size	_ZTVN3bfn25vmcs_launch_failure_errorE, 48
_ZTVN3bfn25vmcs_launch_failure_errorE:
	.quad	0
	.quad	_ZTIN3bfn25vmcs_launch_failure_errorE
	.quad	_ZN3bfn25vmcs_launch_failure_errorD1Ev
	.quad	_ZN3bfn25vmcs_launch_failure_errorD0Ev
	.quad	_ZNK3bfn17general_exception4whatEv
	.quad	_ZNK3bfn25vmcs_launch_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.section	.text._ZN3bfn25vmcs_launch_failure_errorD2Ev,"axG",@progbits,_ZN3bfn25vmcs_launch_failure_errorD5Ev,comdat
	.align 2
	.weak	_ZN3bfn25vmcs_launch_failure_errorD2Ev
	.type	_ZN3bfn25vmcs_launch_failure_errorD2Ev, @function
_ZN3bfn25vmcs_launch_failure_errorD2Ev:
.LFB4195:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTVN3bfn25vmcs_launch_failure_errorE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4195:
	.size	_ZN3bfn25vmcs_launch_failure_errorD2Ev, .-_ZN3bfn25vmcs_launch_failure_errorD2Ev
	.weak	_ZN3bfn25vmcs_launch_failure_errorD1Ev
	.set	_ZN3bfn25vmcs_launch_failure_errorD1Ev,_ZN3bfn25vmcs_launch_failure_errorD2Ev
	.section	.text._ZN3bfn25vmcs_launch_failure_errorD0Ev,"axG",@progbits,_ZN3bfn25vmcs_launch_failure_errorD5Ev,comdat
	.align 2
	.weak	_ZN3bfn25vmcs_launch_failure_errorD0Ev
	.type	_ZN3bfn25vmcs_launch_failure_errorD0Ev, @function
_ZN3bfn25vmcs_launch_failure_errorD0Ev:
.LFB4197:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn25vmcs_launch_failure_errorD1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$64, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4197:
	.size	_ZN3bfn25vmcs_launch_failure_errorD0Ev, .-_ZN3bfn25vmcs_launch_failure_errorD0Ev
	.weak	_ZTVN3bfn24vmcs_write_failure_errorE
	.section	.data.rel.ro._ZTVN3bfn24vmcs_write_failure_errorE,"awG",@progbits,_ZTVN3bfn24vmcs_write_failure_errorE,comdat
	.align 8
	.type	_ZTVN3bfn24vmcs_write_failure_errorE, @object
	.size	_ZTVN3bfn24vmcs_write_failure_errorE, 48
_ZTVN3bfn24vmcs_write_failure_errorE:
	.quad	0
	.quad	_ZTIN3bfn24vmcs_write_failure_errorE
	.quad	_ZN3bfn24vmcs_write_failure_errorD1Ev
	.quad	_ZN3bfn24vmcs_write_failure_errorD0Ev
	.quad	_ZNK3bfn17general_exception4whatEv
	.quad	_ZNK3bfn24vmcs_write_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.section	.text._ZN3bfn24vmcs_write_failure_errorD2Ev,"axG",@progbits,_ZN3bfn24vmcs_write_failure_errorD5Ev,comdat
	.align 2
	.weak	_ZN3bfn24vmcs_write_failure_errorD2Ev
	.type	_ZN3bfn24vmcs_write_failure_errorD2Ev, @function
_ZN3bfn24vmcs_write_failure_errorD2Ev:
.LFB4199:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTVN3bfn24vmcs_write_failure_errorE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$24, %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4199:
	.size	_ZN3bfn24vmcs_write_failure_errorD2Ev, .-_ZN3bfn24vmcs_write_failure_errorD2Ev
	.weak	_ZN3bfn24vmcs_write_failure_errorD1Ev
	.set	_ZN3bfn24vmcs_write_failure_errorD1Ev,_ZN3bfn24vmcs_write_failure_errorD2Ev
	.section	.text._ZN3bfn24vmcs_write_failure_errorD0Ev,"axG",@progbits,_ZN3bfn24vmcs_write_failure_errorD5Ev,comdat
	.align 2
	.weak	_ZN3bfn24vmcs_write_failure_errorD0Ev
	.type	_ZN3bfn24vmcs_write_failure_errorD0Ev, @function
_ZN3bfn24vmcs_write_failure_errorD0Ev:
.LFB4201:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn24vmcs_write_failure_errorD1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$56, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4201:
	.size	_ZN3bfn24vmcs_write_failure_errorD0Ev, .-_ZN3bfn24vmcs_write_failure_errorD0Ev
	.weak	_ZTVN3bfn23vmcs_read_failure_errorE
	.section	.data.rel.ro._ZTVN3bfn23vmcs_read_failure_errorE,"awG",@progbits,_ZTVN3bfn23vmcs_read_failure_errorE,comdat
	.align 8
	.type	_ZTVN3bfn23vmcs_read_failure_errorE, @object
	.size	_ZTVN3bfn23vmcs_read_failure_errorE, 48
_ZTVN3bfn23vmcs_read_failure_errorE:
	.quad	0
	.quad	_ZTIN3bfn23vmcs_read_failure_errorE
	.quad	_ZN3bfn23vmcs_read_failure_errorD1Ev
	.quad	_ZN3bfn23vmcs_read_failure_errorD0Ev
	.quad	_ZNK3bfn17general_exception4whatEv
	.quad	_ZNK3bfn23vmcs_read_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.section	.text._ZN3bfn23vmcs_read_failure_errorD2Ev,"axG",@progbits,_ZN3bfn23vmcs_read_failure_errorD5Ev,comdat
	.align 2
	.weak	_ZN3bfn23vmcs_read_failure_errorD2Ev
	.type	_ZN3bfn23vmcs_read_failure_errorD2Ev, @function
_ZN3bfn23vmcs_read_failure_errorD2Ev:
.LFB4203:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTVN3bfn23vmcs_read_failure_errorE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4203:
	.size	_ZN3bfn23vmcs_read_failure_errorD2Ev, .-_ZN3bfn23vmcs_read_failure_errorD2Ev
	.weak	_ZN3bfn23vmcs_read_failure_errorD1Ev
	.set	_ZN3bfn23vmcs_read_failure_errorD1Ev,_ZN3bfn23vmcs_read_failure_errorD2Ev
	.section	.text._ZN3bfn23vmcs_read_failure_errorD0Ev,"axG",@progbits,_ZN3bfn23vmcs_read_failure_errorD5Ev,comdat
	.align 2
	.weak	_ZN3bfn23vmcs_read_failure_errorD0Ev
	.type	_ZN3bfn23vmcs_read_failure_errorD0Ev, @function
_ZN3bfn23vmcs_read_failure_errorD0Ev:
.LFB4205:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn23vmcs_read_failure_errorD1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$48, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4205:
	.size	_ZN3bfn23vmcs_read_failure_errorD0Ev, .-_ZN3bfn23vmcs_read_failure_errorD0Ev
	.weak	_ZTVN3bfn18vmcs_failure_errorE
	.section	.data.rel.ro._ZTVN3bfn18vmcs_failure_errorE,"awG",@progbits,_ZTVN3bfn18vmcs_failure_errorE,comdat
	.align 8
	.type	_ZTVN3bfn18vmcs_failure_errorE, @object
	.size	_ZTVN3bfn18vmcs_failure_errorE, 48
_ZTVN3bfn18vmcs_failure_errorE:
	.quad	0
	.quad	_ZTIN3bfn18vmcs_failure_errorE
	.quad	_ZN3bfn18vmcs_failure_errorD1Ev
	.quad	_ZN3bfn18vmcs_failure_errorD0Ev
	.quad	_ZNK3bfn17general_exception4whatEv
	.quad	_ZNK3bfn18vmcs_failure_error5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.section	.text._ZN3bfn18vmcs_failure_errorD2Ev,"axG",@progbits,_ZN3bfn18vmcs_failure_errorD5Ev,comdat
	.align 2
	.weak	_ZN3bfn18vmcs_failure_errorD2Ev
	.type	_ZN3bfn18vmcs_failure_errorD2Ev, @function
_ZN3bfn18vmcs_failure_errorD2Ev:
.LFB4207:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	_ZTVN3bfn18vmcs_failure_errorE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn17general_exceptionD2Ev@PLT
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4207:
	.size	_ZN3bfn18vmcs_failure_errorD2Ev, .-_ZN3bfn18vmcs_failure_errorD2Ev
	.weak	_ZN3bfn18vmcs_failure_errorD1Ev
	.set	_ZN3bfn18vmcs_failure_errorD1Ev,_ZN3bfn18vmcs_failure_errorD2Ev
	.section	.text._ZN3bfn18vmcs_failure_errorD0Ev,"axG",@progbits,_ZN3bfn18vmcs_failure_errorD5Ev,comdat
	.align 2
	.weak	_ZN3bfn18vmcs_failure_errorD0Ev
	.type	_ZN3bfn18vmcs_failure_errorD0Ev, @function
_ZN3bfn18vmcs_failure_errorD0Ev:
.LFB4209:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN3bfn18vmcs_failure_errorD1Ev@PLT
	movq	-8(%rbp), %rax
	movl	$64, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4209:
	.size	_ZN3bfn18vmcs_failure_errorD0Ev, .-_ZN3bfn18vmcs_failure_errorD0Ev
	.weak	_ZTVN3bfn17general_exceptionE
	.section	.data.rel.ro._ZTVN3bfn17general_exceptionE,"awG",@progbits,_ZTVN3bfn17general_exceptionE,comdat
	.align 8
	.type	_ZTVN3bfn17general_exceptionE, @object
	.size	_ZTVN3bfn17general_exceptionE, 48
_ZTVN3bfn17general_exceptionE:
	.quad	0
	.quad	_ZTIN3bfn17general_exceptionE
	.quad	_ZN3bfn17general_exceptionD1Ev
	.quad	_ZN3bfn17general_exceptionD0Ev
	.quad	_ZNK3bfn17general_exception4whatEv
	.quad	_ZNK3bfn17general_exception5printERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE
	.weak	_ZTV20intrinsics_intel_x64
	.section	.data.rel.ro._ZTV20intrinsics_intel_x64,"awG",@progbits,_ZTV20intrinsics_intel_x64,comdat
	.align 8
	.type	_ZTV20intrinsics_intel_x64, @object
	.size	_ZTV20intrinsics_intel_x64, 488
_ZTV20intrinsics_intel_x64:
	.quad	0
	.quad	_ZTI20intrinsics_intel_x64
	.quad	_ZN20intrinsics_intel_x64D1Ev
	.quad	_ZN20intrinsics_intel_x64D0Ev
	.quad	_ZNK14intrinsics_x644haltEv
	.quad	_ZNK14intrinsics_x644stopEv
	.quad	_ZNK14intrinsics_x644invdEv
	.quad	_ZNK14intrinsics_x646wbinvdEv
	.quad	_ZNK14intrinsics_x649cpuid_eaxEj
	.quad	_ZNK14intrinsics_x649cpuid_ebxEj
	.quad	_ZNK14intrinsics_x649cpuid_ecxEj
	.quad	_ZNK14intrinsics_x649cpuid_edxEj
	.quad	_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_
	.quad	_ZNK14intrinsics_x6411read_rflagsEv
	.quad	_ZNK14intrinsics_x648read_msrEj
	.quad	_ZNK14intrinsics_x649write_msrEjm
	.quad	_ZNK14intrinsics_x648read_ripEv
	.quad	_ZNK14intrinsics_x648read_cr0Ev
	.quad	_ZNK14intrinsics_x649write_cr0Em
	.quad	_ZNK14intrinsics_x648read_cr3Ev
	.quad	_ZNK14intrinsics_x649write_cr3Em
	.quad	_ZNK14intrinsics_x648read_cr4Ev
	.quad	_ZNK14intrinsics_x649write_cr4Em
	.quad	_ZNK14intrinsics_x649read_xcr0Ev
	.quad	_ZNK14intrinsics_x6410write_xcr0Em
	.quad	_ZNK14intrinsics_x648read_dr7Ev
	.quad	_ZNK14intrinsics_x649write_dr7Em
	.quad	_ZNK14intrinsics_x647read_esEv
	.quad	_ZNK14intrinsics_x648write_esEt
	.quad	_ZNK14intrinsics_x647read_csEv
	.quad	_ZNK14intrinsics_x648write_csEt
	.quad	_ZNK14intrinsics_x647read_ssEv
	.quad	_ZNK14intrinsics_x648write_ssEt
	.quad	_ZNK14intrinsics_x647read_dsEv
	.quad	_ZNK14intrinsics_x648write_dsEt
	.quad	_ZNK14intrinsics_x647read_fsEv
	.quad	_ZNK14intrinsics_x648write_fsEt
	.quad	_ZNK14intrinsics_x647read_gsEv
	.quad	_ZNK14intrinsics_x648write_gsEt
	.quad	_ZNK14intrinsics_x647read_trEv
	.quad	_ZNK14intrinsics_x648write_trEt
	.quad	_ZNK14intrinsics_x649read_ldtrEv
	.quad	_ZNK14intrinsics_x6410write_ldtrEt
	.quad	_ZNK14intrinsics_x648read_rspEv
	.quad	_ZNK14intrinsics_x648read_gdtEPv
	.quad	_ZNK14intrinsics_x649write_gdtEPv
	.quad	_ZNK14intrinsics_x648read_idtEPv
	.quad	_ZNK14intrinsics_x649write_idtEPv
	.quad	_ZNK14intrinsics_x6414write_portio_8Eth
	.quad	_ZNK14intrinsics_x6415write_portio_16Ett
	.quad	_ZNK14intrinsics_x6413read_portio_8Et
	.quad	_ZNK14intrinsics_x6414read_portio_16Et
	.quad	_ZNK20intrinsics_intel_x645vmxonEPv
	.quad	_ZNK20intrinsics_intel_x646vmxoffEv
	.quad	_ZNK20intrinsics_intel_x646vmcallEm
	.quad	_ZNK20intrinsics_intel_x647vmclearEPv
	.quad	_ZNK20intrinsics_intel_x647vmptrldEPv
	.quad	_ZNK20intrinsics_intel_x647vmptrstEPv
	.quad	_ZNK20intrinsics_intel_x647vmwriteEmm
	.quad	_ZNK20intrinsics_intel_x646vmreadEmPm
	.quad	_ZNK20intrinsics_intel_x648vmlaunchEv
	.weak	_ZTV14intrinsics_x64
	.section	.data.rel.ro._ZTV14intrinsics_x64,"awG",@progbits,_ZTV14intrinsics_x64,comdat
	.align 8
	.type	_ZTV14intrinsics_x64, @object
	.size	_ZTV14intrinsics_x64, 416
_ZTV14intrinsics_x64:
	.quad	0
	.quad	_ZTI14intrinsics_x64
	.quad	_ZN14intrinsics_x64D1Ev
	.quad	_ZN14intrinsics_x64D0Ev
	.quad	_ZNK14intrinsics_x644haltEv
	.quad	_ZNK14intrinsics_x644stopEv
	.quad	_ZNK14intrinsics_x644invdEv
	.quad	_ZNK14intrinsics_x646wbinvdEv
	.quad	_ZNK14intrinsics_x649cpuid_eaxEj
	.quad	_ZNK14intrinsics_x649cpuid_ebxEj
	.quad	_ZNK14intrinsics_x649cpuid_ecxEj
	.quad	_ZNK14intrinsics_x649cpuid_edxEj
	.quad	_ZNK14intrinsics_x645cpuidEPmS0_S0_S0_
	.quad	_ZNK14intrinsics_x6411read_rflagsEv
	.quad	_ZNK14intrinsics_x648read_msrEj
	.quad	_ZNK14intrinsics_x649write_msrEjm
	.quad	_ZNK14intrinsics_x648read_ripEv
	.quad	_ZNK14intrinsics_x648read_cr0Ev
	.quad	_ZNK14intrinsics_x649write_cr0Em
	.quad	_ZNK14intrinsics_x648read_cr3Ev
	.quad	_ZNK14intrinsics_x649write_cr3Em
	.quad	_ZNK14intrinsics_x648read_cr4Ev
	.quad	_ZNK14intrinsics_x649write_cr4Em
	.quad	_ZNK14intrinsics_x649read_xcr0Ev
	.quad	_ZNK14intrinsics_x6410write_xcr0Em
	.quad	_ZNK14intrinsics_x648read_dr7Ev
	.quad	_ZNK14intrinsics_x649write_dr7Em
	.quad	_ZNK14intrinsics_x647read_esEv
	.quad	_ZNK14intrinsics_x648write_esEt
	.quad	_ZNK14intrinsics_x647read_csEv
	.quad	_ZNK14intrinsics_x648write_csEt
	.quad	_ZNK14intrinsics_x647read_ssEv
	.quad	_ZNK14intrinsics_x648write_ssEt
	.quad	_ZNK14intrinsics_x647read_dsEv
	.quad	_ZNK14intrinsics_x648write_dsEt
	.quad	_ZNK14intrinsics_x647read_fsEv
	.quad	_ZNK14intrinsics_x648write_fsEt
	.quad	_ZNK14intrinsics_x647read_gsEv
	.quad	_ZNK14intrinsics_x648write_gsEt
	.quad	_ZNK14intrinsics_x647read_trEv
	.quad	_ZNK14intrinsics_x648write_trEt
	.quad	_ZNK14intrinsics_x649read_ldtrEv
	.quad	_ZNK14intrinsics_x6410write_ldtrEt
	.quad	_ZNK14intrinsics_x648read_rspEv
	.quad	_ZNK14intrinsics_x648read_gdtEPv
	.quad	_ZNK14intrinsics_x649write_gdtEPv
	.quad	_ZNK14intrinsics_x648read_idtEPv
	.quad	_ZNK14intrinsics_x649write_idtEPv
	.quad	_ZNK14intrinsics_x6414write_portio_8Eth
	.quad	_ZNK14intrinsics_x6415write_portio_16Ett
	.quad	_ZNK14intrinsics_x6413read_portio_8Et
	.quad	_ZNK14intrinsics_x6414read_portio_16Et
	.weak	_ZTVNSt3__117bad_function_callE
	.section	.data.rel.ro._ZTVNSt3__117bad_function_callE,"awG",@progbits,_ZTVNSt3__117bad_function_callE,comdat
	.align 8
	.type	_ZTVNSt3__117bad_function_callE, @object
	.size	_ZTVNSt3__117bad_function_callE, 40
_ZTVNSt3__117bad_function_callE:
	.quad	0
	.quad	_ZTINSt3__117bad_function_callE
	.quad	_ZNSt3__117bad_function_callD1Ev
	.quad	_ZNSt3__117bad_function_callD0Ev
	.quad	_ZNKSt9exception4whatEv
	.weak	_ZTINSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE
	.section	.data.rel.ro._ZTINSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE,"awG",@progbits,_ZTINSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE,comdat
	.align 8
	.type	_ZTINSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE, @object
	.size	_ZTINSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE, 24
_ZTINSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE
	.quad	_ZTINSt3__119__shared_weak_countE
	.weak	_ZTSNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE
	.section	.rodata._ZTSNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE,"aG",@progbits,_ZTSNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE,comdat
	.align 16
	.type	_ZTSNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE, @object
	.size	_ZTSNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE, 74
_ZTSNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE:
	.string	"NSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEEE"
	.section	.rodata
	.align 16
	.type	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 107
_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.string	"*NSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE"
	.section	.data.rel.ro,"aw",@progbits
	.align 8
	.type	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 24
_ZTINSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE
	.quad	_ZTINSt3__110__function6__baseIFvvEEE
	.section	.rodata
	.align 16
	.type	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 100
_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.string	"*NSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE"
	.section	.data.rel.ro
	.align 8
	.type	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 24
_ZTINSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE
	.quad	_ZTINSt3__110__function6__baseIFvvEEE
	.section	.rodata
	.align 16
	.type	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 88
_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.string	"*NSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE"
	.section	.data.rel.ro
	.align 8
	.type	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE, @object
	.size	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE, 24
_ZTINSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE
	.quad	_ZTINSt3__110__function6__baseIFvvEEE
	.section	.rodata
	.align 16
	.type	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE, @object
	.size	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE, 131
_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE:
	.string	"*NSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE"
	.section	.data.rel.ro
	.align 8
	.type	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE, @object
	.size	_ZTINSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE, 24
_ZTINSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE
	.quad	_ZTINSt3__110__function6__baseIFvvEEE
	.weak	_ZTINSt3__110__function6__baseIFvvEEE
	.section	.data.rel.ro._ZTINSt3__110__function6__baseIFvvEEE,"awG",@progbits,_ZTINSt3__110__function6__baseIFvvEEE,comdat
	.align 8
	.type	_ZTINSt3__110__function6__baseIFvvEEE, @object
	.size	_ZTINSt3__110__function6__baseIFvvEEE, 16
_ZTINSt3__110__function6__baseIFvvEEE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSNSt3__110__function6__baseIFvvEEE
	.weak	_ZTSNSt3__110__function6__baseIFvvEEE
	.section	.rodata._ZTSNSt3__110__function6__baseIFvvEEE,"aG",@progbits,_ZTSNSt3__110__function6__baseIFvvEEE,comdat
	.align 16
	.type	_ZTSNSt3__110__function6__baseIFvvEEE, @object
	.size	_ZTSNSt3__110__function6__baseIFvvEEE, 34
_ZTSNSt3__110__function6__baseIFvvEEE:
	.string	"NSt3__110__function6__baseIFvvEEE"
	.weak	_ZTIN3bfn25vmcs_launch_failure_errorE
	.section	.data.rel.ro._ZTIN3bfn25vmcs_launch_failure_errorE,"awG",@progbits,_ZTIN3bfn25vmcs_launch_failure_errorE,comdat
	.align 8
	.type	_ZTIN3bfn25vmcs_launch_failure_errorE, @object
	.size	_ZTIN3bfn25vmcs_launch_failure_errorE, 24
_ZTIN3bfn25vmcs_launch_failure_errorE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN3bfn25vmcs_launch_failure_errorE
	.quad	_ZTIN3bfn17general_exceptionE
	.weak	_ZTSN3bfn25vmcs_launch_failure_errorE
	.section	.rodata._ZTSN3bfn25vmcs_launch_failure_errorE,"aG",@progbits,_ZTSN3bfn25vmcs_launch_failure_errorE,comdat
	.align 16
	.type	_ZTSN3bfn25vmcs_launch_failure_errorE, @object
	.size	_ZTSN3bfn25vmcs_launch_failure_errorE, 34
_ZTSN3bfn25vmcs_launch_failure_errorE:
	.string	"N3bfn25vmcs_launch_failure_errorE"
	.weak	_ZTIN3bfn24vmcs_write_failure_errorE
	.section	.data.rel.ro._ZTIN3bfn24vmcs_write_failure_errorE,"awG",@progbits,_ZTIN3bfn24vmcs_write_failure_errorE,comdat
	.align 8
	.type	_ZTIN3bfn24vmcs_write_failure_errorE, @object
	.size	_ZTIN3bfn24vmcs_write_failure_errorE, 24
_ZTIN3bfn24vmcs_write_failure_errorE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN3bfn24vmcs_write_failure_errorE
	.quad	_ZTIN3bfn17general_exceptionE
	.weak	_ZTSN3bfn24vmcs_write_failure_errorE
	.section	.rodata._ZTSN3bfn24vmcs_write_failure_errorE,"aG",@progbits,_ZTSN3bfn24vmcs_write_failure_errorE,comdat
	.align 16
	.type	_ZTSN3bfn24vmcs_write_failure_errorE, @object
	.size	_ZTSN3bfn24vmcs_write_failure_errorE, 33
_ZTSN3bfn24vmcs_write_failure_errorE:
	.string	"N3bfn24vmcs_write_failure_errorE"
	.weak	_ZTIN3bfn23vmcs_read_failure_errorE
	.section	.data.rel.ro._ZTIN3bfn23vmcs_read_failure_errorE,"awG",@progbits,_ZTIN3bfn23vmcs_read_failure_errorE,comdat
	.align 8
	.type	_ZTIN3bfn23vmcs_read_failure_errorE, @object
	.size	_ZTIN3bfn23vmcs_read_failure_errorE, 24
_ZTIN3bfn23vmcs_read_failure_errorE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN3bfn23vmcs_read_failure_errorE
	.quad	_ZTIN3bfn17general_exceptionE
	.weak	_ZTSN3bfn23vmcs_read_failure_errorE
	.section	.rodata._ZTSN3bfn23vmcs_read_failure_errorE,"aG",@progbits,_ZTSN3bfn23vmcs_read_failure_errorE,comdat
	.align 16
	.type	_ZTSN3bfn23vmcs_read_failure_errorE, @object
	.size	_ZTSN3bfn23vmcs_read_failure_errorE, 32
_ZTSN3bfn23vmcs_read_failure_errorE:
	.string	"N3bfn23vmcs_read_failure_errorE"
	.weak	_ZTIN3bfn18vmcs_failure_errorE
	.section	.data.rel.ro._ZTIN3bfn18vmcs_failure_errorE,"awG",@progbits,_ZTIN3bfn18vmcs_failure_errorE,comdat
	.align 8
	.type	_ZTIN3bfn18vmcs_failure_errorE, @object
	.size	_ZTIN3bfn18vmcs_failure_errorE, 24
_ZTIN3bfn18vmcs_failure_errorE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN3bfn18vmcs_failure_errorE
	.quad	_ZTIN3bfn17general_exceptionE
	.weak	_ZTSN3bfn18vmcs_failure_errorE
	.section	.rodata._ZTSN3bfn18vmcs_failure_errorE,"aG",@progbits,_ZTSN3bfn18vmcs_failure_errorE,comdat
	.align 16
	.type	_ZTSN3bfn18vmcs_failure_errorE, @object
	.size	_ZTSN3bfn18vmcs_failure_errorE, 27
_ZTSN3bfn18vmcs_failure_errorE:
	.string	"N3bfn18vmcs_failure_errorE"
	.weak	_ZTIN3bfn17general_exceptionE
	.section	.data.rel.ro._ZTIN3bfn17general_exceptionE,"awG",@progbits,_ZTIN3bfn17general_exceptionE,comdat
	.align 8
	.type	_ZTIN3bfn17general_exceptionE, @object
	.size	_ZTIN3bfn17general_exceptionE, 24
_ZTIN3bfn17general_exceptionE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN3bfn17general_exceptionE
	.quad	_ZTISt9exception
	.weak	_ZTSN3bfn17general_exceptionE
	.section	.rodata._ZTSN3bfn17general_exceptionE,"aG",@progbits,_ZTSN3bfn17general_exceptionE,comdat
	.align 16
	.type	_ZTSN3bfn17general_exceptionE, @object
	.size	_ZTSN3bfn17general_exceptionE, 26
_ZTSN3bfn17general_exceptionE:
	.string	"N3bfn17general_exceptionE"
	.weak	_ZTI14vmcs_intel_x64
	.section	.data.rel.ro._ZTI14vmcs_intel_x64,"awG",@progbits,_ZTI14vmcs_intel_x64,comdat
	.align 8
	.type	_ZTI14vmcs_intel_x64, @object
	.size	_ZTI14vmcs_intel_x64, 16
_ZTI14vmcs_intel_x64:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS14vmcs_intel_x64
	.weak	_ZTS14vmcs_intel_x64
	.section	.rodata._ZTS14vmcs_intel_x64,"aG",@progbits,_ZTS14vmcs_intel_x64,comdat
	.align 16
	.type	_ZTS14vmcs_intel_x64, @object
	.size	_ZTS14vmcs_intel_x64, 17
_ZTS14vmcs_intel_x64:
	.string	"14vmcs_intel_x64"
	.weak	_ZTI20intrinsics_intel_x64
	.section	.data.rel.ro._ZTI20intrinsics_intel_x64,"awG",@progbits,_ZTI20intrinsics_intel_x64,comdat
	.align 8
	.type	_ZTI20intrinsics_intel_x64, @object
	.size	_ZTI20intrinsics_intel_x64, 24
_ZTI20intrinsics_intel_x64:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS20intrinsics_intel_x64
	.quad	_ZTI14intrinsics_x64
	.weak	_ZTS20intrinsics_intel_x64
	.section	.rodata._ZTS20intrinsics_intel_x64,"aG",@progbits,_ZTS20intrinsics_intel_x64,comdat
	.align 16
	.type	_ZTS20intrinsics_intel_x64, @object
	.size	_ZTS20intrinsics_intel_x64, 23
_ZTS20intrinsics_intel_x64:
	.string	"20intrinsics_intel_x64"
	.weak	_ZTI14intrinsics_x64
	.section	.data.rel.ro._ZTI14intrinsics_x64,"awG",@progbits,_ZTI14intrinsics_x64,comdat
	.align 8
	.type	_ZTI14intrinsics_x64, @object
	.size	_ZTI14intrinsics_x64, 16
_ZTI14intrinsics_x64:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS14intrinsics_x64
	.weak	_ZTS14intrinsics_x64
	.section	.rodata._ZTS14intrinsics_x64,"aG",@progbits,_ZTS14intrinsics_x64,comdat
	.align 16
	.type	_ZTS14intrinsics_x64, @object
	.size	_ZTS14intrinsics_x64, 17
_ZTS14intrinsics_x64:
	.string	"14intrinsics_x64"
	.weak	_ZTINSt3__117bad_function_callE
	.section	.data.rel.ro._ZTINSt3__117bad_function_callE,"awG",@progbits,_ZTINSt3__117bad_function_callE,comdat
	.align 8
	.type	_ZTINSt3__117bad_function_callE, @object
	.size	_ZTINSt3__117bad_function_callE, 24
_ZTINSt3__117bad_function_callE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt3__117bad_function_callE
	.quad	_ZTISt9exception
	.weak	_ZTSNSt3__117bad_function_callE
	.section	.rodata._ZTSNSt3__117bad_function_callE,"aG",@progbits,_ZTSNSt3__117bad_function_callE,comdat
	.align 16
	.type	_ZTSNSt3__117bad_function_callE, @object
	.size	_ZTSNSt3__117bad_function_callE, 28
_ZTSNSt3__117bad_function_callE:
	.string	"NSt3__117bad_function_callE"
	.section	.text._ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE16__on_zero_sharedEv,"axG",@progbits,_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE16__on_zero_sharedEv,comdat
	.align 2
	.weak	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE16__on_zero_sharedEv
	.type	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE16__on_zero_sharedEv, @function
_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE16__on_zero_sharedEv:
.LFB4238:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4238:
	.size	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE16__on_zero_sharedEv, .-_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE16__on_zero_sharedEv
	.section	.text._ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE21__on_zero_shared_weakEv,"axG",@progbits,_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE21__on_zero_shared_weakEv,comdat
	.align 2
	.weak	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE21__on_zero_shared_weakEv
	.type	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE21__on_zero_shared_weakEv, @function
_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE21__on_zero_shared_weakEv:
.LFB4239:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -104(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdx
	movq	%rdx, -8(%rbp)
	xorl	%edx, %edx
	movq	-104(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-104(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	$1, -80(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L788
	call	__stack_chk_fail@PLT
.L788:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4239:
	.size	_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE21__on_zero_shared_weakEv, .-_ZNSt3__120__shared_ptr_emplaceI20intrinsics_intel_x64NS_9allocatorIS1_EEE21__on_zero_shared_weakEv
	.text
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv:
.LFB4240:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	subq	$736, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movq	%rdi, -776(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	%rdi, -56(%rbp)
	xorl	%edi, %edi
	movq	-776(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -648(%rbp)
	movq	-648(%rbp), %rax
	movq	%rax, -640(%rbp)
	movq	-640(%rbp), %rax
	movq	%rax, -656(%rbp)
	movq	$1, -664(%rbp)
	leaq	-766(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-664(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	$1, -688(%rbp)
	movq	$0, -680(%rbp)
	movq	-688(%rbp), %rax
	salq	$4, %rax
	movq	%rax, -672(%rbp)
	movq	-672(%rbp), %rax
	movq	%rax, %rdi
	call	_Znwm@PLT
	movq	%rax, -584(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -576(%rbp)
	movq	-576(%rbp), %rax
	leaq	-80(%rbp), %rdx
	movq	%rdx, -568(%rbp)
	movq	-584(%rbp), %rdx
	movq	%rdx, -704(%rbp)
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	leaq	-112(%rbp), %rdx
	leaq	-704(%rbp), %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rcx
	movq	%rcx, -560(%rbp)
	movq	%rax, -696(%rbp)
	movq	(%rdx), %rax
	movq	8(%rdx), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	leaq	-696(%rbp), %rax
	movq	(%rax), %rdx
	movq	-560(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-96(%rbp), %rax
	movq	-560(%rbp), %rcx
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, 8(%rcx)
	movq	%rdx, 16(%rcx)
	movq	-776(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -600(%rbp)
	movq	-600(%rbp), %rax
	movq	%rax, -592(%rbp)
	movq	-592(%rbp), %rcx
	leaq	-765(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rax, -616(%rbp)
	movq	-616(%rbp), %rax
	movq	%rax, -608(%rbp)
	movq	-608(%rbp), %rax
	movq	(%rax), %rax
	movq	$16, -632(%rbp)
	movq	%rax, -624(%rbp)
	movq	-624(%rbp), %rax
	testq	%rax, %rax
	je	.L824
	movq	%rax, -552(%rbp)
	movq	%rcx, -544(%rbp)
	movq	%rdx, -536(%rbp)
	movq	-552(%rbp), %rax
	movq	%rax, -528(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-528(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-552(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-536(%rbp), %rax
	movq	%rax, -520(%rbp)
	movq	-520(%rbp), %rax
	movq	%rax, -512(%rbp)
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
	movq	-504(%rbp), %rax
	movq	%rax, -496(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, -488(%rbp)
	movq	-488(%rbp), %rax
	leaq	-128(%rbp), %rdx
	movq	%rdx, -480(%rbp)
	movzbl	-783(%rbp), %esi
	movb	%sil, -761(%rbp)
	movzbl	-782(%rbp), %esi
	movb	%sil, -762(%rbp)
	movzbl	-781(%rbp), %edi
	movb	%dil, -763(%rbp)
	movzbl	-780(%rbp), %esi
	movb	%sil, -764(%rbp)
	movq	%rax, -472(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, -464(%rbp)
	movq	-464(%rbp), %rax
	movq	-480(%rbp), %rdx
	movq	%rdx, -456(%rbp)
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	%rax, -440(%rbp)
	movq	-440(%rbp), %rdx
	movq	-456(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movq	-544(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	%rax, -424(%rbp)
	movq	-424(%rbp), %rax
	movq	%rax, -416(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -408(%rbp)
	movzbl	-779(%rbp), %eax
	movb	%al, -757(%rbp)
	movzbl	-778(%rbp), %eax
	movb	%al, -758(%rbp)
	movzbl	-777(%rbp), %eax
	movb	%al, -759(%rbp)
	movb	%r15b, -760(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movq	-408(%rbp), %rdx
	movq	%rdx, -384(%rbp)
	movq	%rax, -376(%rbp)
	movq	-376(%rbp), %rax
	movq	%rax, -368(%rbp)
	movq	-368(%rbp), %rdx
	movq	-384(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, %rdx
	movq	-552(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -360(%rbp)
	movb	%r14b, -756(%rbp)
	movq	%rdx, -736(%rbp)
	movq	%rcx, -752(%rbp)
	leaq	-752(%rbp), %rax
	leaq	-736(%rbp), %rdx
	movq	-360(%rbp), %rcx
	movq	%rcx, -352(%rbp)
	movb	%r13b, -753(%rbp)
	movq	(%rdx), %rdx
	movq	%rdx, -128(%rbp)
	movq	(%rax), %rax
	movq	%rax, -720(%rbp)
	movb	%r12b, -754(%rbp)
	movb	%bl, -755(%rbp)
	leaq	-720(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -336(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -328(%rbp)
	movq	-328(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rdx
	movq	-352(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L824:
	leaq	-80(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -152(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	$0, (%rax)
	movq	-152(%rbp), %rax
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, -312(%rbp)
	movq	$0, -304(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -280(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	-304(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -280(%rbp)
	je	.L837
	movq	-312(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -240(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -232(%rbp)
	movq	-240(%rbp), %rax
	movq	8(%rax), %rax
	movq	-240(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, -224(%rbp)
	movq	-232(%rbp), %rdx
	movq	%rdx, -216(%rbp)
	movq	%rax, -208(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
.L837:
	movq	%rbx, %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-56(%rbp), %rbx
	xorq	(%rdx), %rbx
	je	.L838
	call	__stack_chk_fail@PLT
.L838:
	addq	$736, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4240:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE:
.LFB4241:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$392, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -408(%rbp)
	movq	%rsi, -416(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -56(%rbp)
	xorl	%esi, %esi
	movq	-408(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rcx
	movq	-408(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rdx
	movq	-416(%rbp), %rax
	movq	$16, -328(%rbp)
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rax
	testq	%rax, %rax
	je	.L864
	movq	%rax, -280(%rbp)
	movq	%rcx, -272(%rbp)
	movq	%rdx, -264(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-256(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-264(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	movq	%rax, -232(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -224(%rbp)
	movzbl	-419(%rbp), %eax
	movb	%al, -393(%rbp)
	movzbl	-418(%rbp), %eax
	movb	%al, -394(%rbp)
	movzbl	-417(%rbp), %eax
	movb	%al, -395(%rbp)
	movb	%r15b, -396(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	-224(%rbp), %rdx
	movq	%rdx, -200(%rbp)
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	-200(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, %rcx
	movq	-272(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -152(%rbp)
	movb	%r14b, -389(%rbp)
	movb	%r13b, -390(%rbp)
	movb	%r12b, -391(%rbp)
	movb	%bl, -392(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rdx, -128(%rbp)
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, %rdx
	movq	-280(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -104(%rbp)
	movb	%r11b, -388(%rbp)
	movq	%rdx, -368(%rbp)
	movq	%rcx, -384(%rbp)
	leaq	-384(%rbp), %rax
	leaq	-368(%rbp), %rdx
	movq	-104(%rbp), %rcx
	movq	%rcx, -96(%rbp)
	movb	%r10b, -385(%rbp)
	movq	(%rdx), %rdx
	movq	%rdx, -336(%rbp)
	movq	(%rax), %rax
	movq	%rax, -352(%rbp)
	movb	%r9b, -386(%rbp)
	movb	%r8b, -387(%rbp)
	leaq	-352(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rdx
	movq	-96(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L864:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-56(%rbp), %rdi
	xorq	(%rax), %rdi
	je	.L863
	call	__stack_chk_fail@PLT
.L863:
	addq	$392, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4241:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv:
.LFB4242:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4242:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv:
.LFB4243:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdx
	movq	%rdx, -8(%rbp)
	xorl	%edx, %edx
	movq	-72(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	$1, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L869
	call	__stack_chk_fail@PLT
.L869:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4243:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv:
.LFB4244:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EEEvDpOT_
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4244:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info:
.LFB4245:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	leaq	_ZTSZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_(%rip), %rax
	cmpq	%rax, %rdx
	sete	%al
	testb	%al, %al
	je	.L876
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	jmp	.L879
.L876:
	movl	$0, %eax
.L879:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4245:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv:
.LFB4246:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	leaq	_ZTIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_(%rip), %rax
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4246:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv:
.LFB4247:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	subq	$736, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movq	%rdi, -776(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	%rdi, -56(%rbp)
	xorl	%edi, %edi
	movq	-776(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -648(%rbp)
	movq	-648(%rbp), %rax
	movq	%rax, -640(%rbp)
	movq	-640(%rbp), %rax
	movq	%rax, -656(%rbp)
	movq	$1, -664(%rbp)
	leaq	-766(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-664(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	$1, -688(%rbp)
	movq	$0, -680(%rbp)
	movq	-688(%rbp), %rax
	salq	$4, %rax
	movq	%rax, -672(%rbp)
	movq	-672(%rbp), %rax
	movq	%rax, %rdi
	call	_Znwm@PLT
	movq	%rax, -584(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -576(%rbp)
	movq	-576(%rbp), %rax
	leaq	-80(%rbp), %rdx
	movq	%rdx, -568(%rbp)
	movq	-584(%rbp), %rdx
	movq	%rdx, -704(%rbp)
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	leaq	-112(%rbp), %rdx
	leaq	-704(%rbp), %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rcx
	movq	%rcx, -560(%rbp)
	movq	%rax, -696(%rbp)
	movq	(%rdx), %rax
	movq	8(%rdx), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	leaq	-696(%rbp), %rax
	movq	(%rax), %rdx
	movq	-560(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-96(%rbp), %rax
	movq	-560(%rbp), %rcx
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, 8(%rcx)
	movq	%rdx, 16(%rcx)
	movq	-776(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -600(%rbp)
	movq	-600(%rbp), %rax
	movq	%rax, -592(%rbp)
	movq	-592(%rbp), %rcx
	leaq	-765(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rax, -616(%rbp)
	movq	-616(%rbp), %rax
	movq	%rax, -608(%rbp)
	movq	-608(%rbp), %rax
	movq	(%rax), %rax
	movq	$16, -632(%rbp)
	movq	%rax, -624(%rbp)
	movq	-624(%rbp), %rax
	testq	%rax, %rax
	je	.L917
	movq	%rax, -552(%rbp)
	movq	%rcx, -544(%rbp)
	movq	%rdx, -536(%rbp)
	movq	-552(%rbp), %rax
	movq	%rax, -528(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-528(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-552(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-536(%rbp), %rax
	movq	%rax, -520(%rbp)
	movq	-520(%rbp), %rax
	movq	%rax, -512(%rbp)
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
	movq	-504(%rbp), %rax
	movq	%rax, -496(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, -488(%rbp)
	movq	-488(%rbp), %rax
	leaq	-128(%rbp), %rdx
	movq	%rdx, -480(%rbp)
	movzbl	-783(%rbp), %esi
	movb	%sil, -761(%rbp)
	movzbl	-782(%rbp), %esi
	movb	%sil, -762(%rbp)
	movzbl	-781(%rbp), %edi
	movb	%dil, -763(%rbp)
	movzbl	-780(%rbp), %esi
	movb	%sil, -764(%rbp)
	movq	%rax, -472(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, -464(%rbp)
	movq	-464(%rbp), %rax
	movq	-480(%rbp), %rdx
	movq	%rdx, -456(%rbp)
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	%rax, -440(%rbp)
	movq	-440(%rbp), %rdx
	movq	-456(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movq	-544(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	%rax, -424(%rbp)
	movq	-424(%rbp), %rax
	movq	%rax, -416(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -408(%rbp)
	movzbl	-779(%rbp), %eax
	movb	%al, -757(%rbp)
	movzbl	-778(%rbp), %eax
	movb	%al, -758(%rbp)
	movzbl	-777(%rbp), %eax
	movb	%al, -759(%rbp)
	movb	%r15b, -760(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movq	-408(%rbp), %rdx
	movq	%rdx, -384(%rbp)
	movq	%rax, -376(%rbp)
	movq	-376(%rbp), %rax
	movq	%rax, -368(%rbp)
	movq	-368(%rbp), %rdx
	movq	-384(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, %rdx
	movq	-552(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -360(%rbp)
	movb	%r14b, -756(%rbp)
	movq	%rdx, -736(%rbp)
	movq	%rcx, -752(%rbp)
	leaq	-752(%rbp), %rax
	leaq	-736(%rbp), %rdx
	movq	-360(%rbp), %rcx
	movq	%rcx, -352(%rbp)
	movb	%r13b, -753(%rbp)
	movq	(%rdx), %rdx
	movq	%rdx, -128(%rbp)
	movq	(%rax), %rax
	movq	%rax, -720(%rbp)
	movb	%r12b, -754(%rbp)
	movb	%bl, -755(%rbp)
	leaq	-720(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -336(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -328(%rbp)
	movq	-328(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rdx
	movq	-352(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L917:
	leaq	-80(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -152(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	$0, (%rax)
	movq	-152(%rbp), %rax
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, -312(%rbp)
	movq	$0, -304(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -280(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	-304(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -280(%rbp)
	je	.L930
	movq	-312(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -240(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -232(%rbp)
	movq	-240(%rbp), %rax
	movq	8(%rax), %rax
	movq	-240(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, -224(%rbp)
	movq	-232(%rbp), %rdx
	movq	%rdx, -216(%rbp)
	movq	%rax, -208(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
.L930:
	movq	%rbx, %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-56(%rbp), %rbx
	xorq	(%rdx), %rbx
	je	.L931
	call	__stack_chk_fail@PLT
.L931:
	addq	$736, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4247:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE:
.LFB4248:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$392, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -408(%rbp)
	movq	%rsi, -416(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -56(%rbp)
	xorl	%esi, %esi
	movq	-408(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rcx
	movq	-408(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rdx
	movq	-416(%rbp), %rax
	movq	$16, -328(%rbp)
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rax
	testq	%rax, %rax
	je	.L957
	movq	%rax, -280(%rbp)
	movq	%rcx, -272(%rbp)
	movq	%rdx, -264(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-256(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-264(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	movq	%rax, -232(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -224(%rbp)
	movzbl	-419(%rbp), %eax
	movb	%al, -393(%rbp)
	movzbl	-418(%rbp), %eax
	movb	%al, -394(%rbp)
	movzbl	-417(%rbp), %eax
	movb	%al, -395(%rbp)
	movb	%r15b, -396(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	-224(%rbp), %rdx
	movq	%rdx, -200(%rbp)
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	-200(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, %rcx
	movq	-272(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -152(%rbp)
	movb	%r14b, -389(%rbp)
	movb	%r13b, -390(%rbp)
	movb	%r12b, -391(%rbp)
	movb	%bl, -392(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rdx, -128(%rbp)
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, %rdx
	movq	-280(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -104(%rbp)
	movb	%r11b, -388(%rbp)
	movq	%rdx, -368(%rbp)
	movq	%rcx, -384(%rbp)
	leaq	-384(%rbp), %rax
	leaq	-368(%rbp), %rdx
	movq	-104(%rbp), %rcx
	movq	%rcx, -96(%rbp)
	movb	%r10b, -385(%rbp)
	movq	(%rdx), %rdx
	movq	%rdx, -336(%rbp)
	movq	(%rax), %rax
	movq	%rax, -352(%rbp)
	movb	%r9b, -386(%rbp)
	movb	%r8b, -387(%rbp)
	leaq	-352(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rdx
	movq	-96(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L957:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-56(%rbp), %rdi
	xorq	(%rax), %rdi
	je	.L956
	call	__stack_chk_fail@PLT
.L956:
	addq	$392, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4248:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv:
.LFB4249:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4249:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv:
.LFB4250:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdx
	movq	%rdx, -8(%rbp)
	xorl	%edx, %edx
	movq	-72(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	$1, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L962
	call	__stack_chk_fail@PLT
.L962:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4250:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv:
.LFB4251:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EEEvDpOT_
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4251:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info:
.LFB4252:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	leaq	_ZTSZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_(%rip), %rax
	cmpq	%rax, %rdx
	sete	%al
	testb	%al, %al
	je	.L969
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	jmp	.L972
.L969:
	movl	$0, %eax
.L972:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4252:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv:
.LFB4253:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	leaq	_ZTIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_(%rip), %rax
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4253:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv:
.LFB4254:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	subq	$736, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movq	%rdi, -776(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	%rdi, -56(%rbp)
	xorl	%edi, %edi
	movq	-776(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -648(%rbp)
	movq	-648(%rbp), %rax
	movq	%rax, -640(%rbp)
	movq	-640(%rbp), %rax
	movq	%rax, -656(%rbp)
	movq	$1, -664(%rbp)
	leaq	-766(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-664(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	$1, -688(%rbp)
	movq	$0, -680(%rbp)
	movq	-688(%rbp), %rax
	salq	$4, %rax
	movq	%rax, -672(%rbp)
	movq	-672(%rbp), %rax
	movq	%rax, %rdi
	call	_Znwm@PLT
	movq	%rax, -584(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -576(%rbp)
	movq	-576(%rbp), %rax
	leaq	-80(%rbp), %rdx
	movq	%rdx, -568(%rbp)
	movq	-584(%rbp), %rdx
	movq	%rdx, -704(%rbp)
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	leaq	-112(%rbp), %rdx
	leaq	-704(%rbp), %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rcx
	movq	%rcx, -560(%rbp)
	movq	%rax, -696(%rbp)
	movq	(%rdx), %rax
	movq	8(%rdx), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	leaq	-696(%rbp), %rax
	movq	(%rax), %rdx
	movq	-560(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-96(%rbp), %rax
	movq	-560(%rbp), %rcx
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, 8(%rcx)
	movq	%rdx, 16(%rcx)
	movq	-776(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -600(%rbp)
	movq	-600(%rbp), %rax
	movq	%rax, -592(%rbp)
	movq	-592(%rbp), %rcx
	leaq	-765(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rax, -616(%rbp)
	movq	-616(%rbp), %rax
	movq	%rax, -608(%rbp)
	movq	-608(%rbp), %rax
	movq	(%rax), %rax
	movq	$16, -632(%rbp)
	movq	%rax, -624(%rbp)
	movq	-624(%rbp), %rax
	testq	%rax, %rax
	je	.L1010
	movq	%rax, -552(%rbp)
	movq	%rcx, -544(%rbp)
	movq	%rdx, -536(%rbp)
	movq	-552(%rbp), %rax
	movq	%rax, -528(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-528(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-552(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-536(%rbp), %rax
	movq	%rax, -520(%rbp)
	movq	-520(%rbp), %rax
	movq	%rax, -512(%rbp)
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
	movq	-504(%rbp), %rax
	movq	%rax, -496(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, -488(%rbp)
	movq	-488(%rbp), %rax
	leaq	-128(%rbp), %rdx
	movq	%rdx, -480(%rbp)
	movzbl	-783(%rbp), %esi
	movb	%sil, -761(%rbp)
	movzbl	-782(%rbp), %esi
	movb	%sil, -762(%rbp)
	movzbl	-781(%rbp), %edi
	movb	%dil, -763(%rbp)
	movzbl	-780(%rbp), %esi
	movb	%sil, -764(%rbp)
	movq	%rax, -472(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, -464(%rbp)
	movq	-464(%rbp), %rax
	movq	-480(%rbp), %rdx
	movq	%rdx, -456(%rbp)
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	%rax, -440(%rbp)
	movq	-440(%rbp), %rdx
	movq	-456(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movq	-544(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	%rax, -424(%rbp)
	movq	-424(%rbp), %rax
	movq	%rax, -416(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -408(%rbp)
	movzbl	-779(%rbp), %eax
	movb	%al, -757(%rbp)
	movzbl	-778(%rbp), %eax
	movb	%al, -758(%rbp)
	movzbl	-777(%rbp), %eax
	movb	%al, -759(%rbp)
	movb	%r15b, -760(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movq	-408(%rbp), %rdx
	movq	%rdx, -384(%rbp)
	movq	%rax, -376(%rbp)
	movq	-376(%rbp), %rax
	movq	%rax, -368(%rbp)
	movq	-368(%rbp), %rdx
	movq	-384(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, %rdx
	movq	-552(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -360(%rbp)
	movb	%r14b, -756(%rbp)
	movq	%rdx, -736(%rbp)
	movq	%rcx, -752(%rbp)
	leaq	-752(%rbp), %rax
	leaq	-736(%rbp), %rdx
	movq	-360(%rbp), %rcx
	movq	%rcx, -352(%rbp)
	movb	%r13b, -753(%rbp)
	movq	(%rdx), %rdx
	movq	%rdx, -128(%rbp)
	movq	(%rax), %rax
	movq	%rax, -720(%rbp)
	movb	%r12b, -754(%rbp)
	movb	%bl, -755(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -336(%rbp)
	leaq	-720(%rbp), %rax
	movq	%rax, -328(%rbp)
	movq	-328(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -320(%rbp)
.L1010:
	leaq	-80(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -152(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	$0, (%rax)
	movq	-152(%rbp), %rax
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, -312(%rbp)
	movq	$0, -304(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -280(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	-304(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -280(%rbp)
	je	.L1023
	movq	-312(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -240(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -232(%rbp)
	movq	-240(%rbp), %rax
	movq	8(%rax), %rax
	movq	-240(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, -224(%rbp)
	movq	-232(%rbp), %rdx
	movq	%rdx, -216(%rbp)
	movq	%rax, -208(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
.L1023:
	movq	%rbx, %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-56(%rbp), %rbx
	xorq	(%rdx), %rbx
	je	.L1024
	call	__stack_chk_fail@PLT
.L1024:
	addq	$736, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4254:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE:
.LFB4255:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$392, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -408(%rbp)
	movq	%rsi, -416(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -56(%rbp)
	xorl	%esi, %esi
	movq	-408(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rcx
	movq	-408(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rdx
	movq	-416(%rbp), %rax
	movq	$16, -328(%rbp)
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rax
	testq	%rax, %rax
	je	.L1050
	movq	%rax, -280(%rbp)
	movq	%rcx, -272(%rbp)
	movq	%rdx, -264(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-256(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEE(%rip), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-264(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	movq	%rax, -232(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -224(%rbp)
	movzbl	-419(%rbp), %eax
	movb	%al, -393(%rbp)
	movzbl	-418(%rbp), %eax
	movb	%al, -394(%rbp)
	movzbl	-417(%rbp), %eax
	movb	%al, -395(%rbp)
	movb	%r15b, -396(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	-224(%rbp), %rdx
	movq	%rdx, -200(%rbp)
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	-200(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, %rcx
	movq	-272(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -152(%rbp)
	movb	%r14b, -389(%rbp)
	movb	%r13b, -390(%rbp)
	movb	%r12b, -391(%rbp)
	movb	%bl, -392(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rdx, -128(%rbp)
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, %rdx
	movq	-280(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -104(%rbp)
	movb	%r11b, -388(%rbp)
	movq	%rdx, -368(%rbp)
	movq	%rcx, -384(%rbp)
	leaq	-384(%rbp), %rax
	leaq	-368(%rbp), %rdx
	movq	-104(%rbp), %rcx
	movq	%rcx, -96(%rbp)
	movb	%r10b, -385(%rbp)
	movq	(%rdx), %rdx
	movq	%rdx, -336(%rbp)
	movq	(%rax), %rax
	movq	%rax, -352(%rbp)
	movb	%r9b, -386(%rbp)
	movb	%r8b, -387(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	leaq	-352(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
.L1050:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-56(%rbp), %rdi
	xorq	(%rax), %rdi
	je	.L1049
	call	__stack_chk_fail@PLT
.L1049:
	addq	$392, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4255:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7__cloneEPNS0_6__baseIS6_EE
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv:
.LFB4256:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4256:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE7destroyEv
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv:
.LFB4257:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdx
	movq	%rdx, -8(%rbp)
	xorl	%edx, %edx
	movq	-72(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	$1, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L1055
	call	__stack_chk_fail@PLT
.L1055:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4257:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE18destroy_deallocateEv
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv:
.LFB4258:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x647promoteEvEUlvE_EEEvDpOT_
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4258:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEEclEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info:
.LFB4259:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	leaq	_ZTSZN14vmcs_intel_x647promoteEvEUlvE_(%rip), %rax
	cmpq	%rax, %rdx
	sete	%al
	testb	%al, %al
	je	.L1062
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	jmp	.L1065
.L1062:
	movl	$0, %eax
.L1065:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4259:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE6targetERKSt9type_info
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv:
.LFB4260:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	leaq	_ZTIZN14vmcs_intel_x647promoteEvEUlvE_(%rip), %rax
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4260:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x647promoteEvEUlvE_NS_9allocatorIS3_EEFvvEE11target_typeEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEv, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEv:
.LFB4261:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-16, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	subq	$736, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movq	%rdi, -776(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	%rdi, -56(%rbp)
	xorl	%edi, %edi
	movq	-776(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -648(%rbp)
	movq	-648(%rbp), %rax
	movq	%rax, -640(%rbp)
	movq	-640(%rbp), %rax
	movq	%rax, -656(%rbp)
	movq	$1, -664(%rbp)
	leaq	-766(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-664(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	$1, -688(%rbp)
	movq	$0, -680(%rbp)
	movq	-688(%rbp), %rax
	salq	$4, %rax
	movq	%rax, -672(%rbp)
	movq	-672(%rbp), %rax
	movq	%rax, %rdi
	call	_Znwm@PLT
	movq	%rax, -584(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -576(%rbp)
	movq	-576(%rbp), %rax
	leaq	-80(%rbp), %rdx
	movq	%rdx, -568(%rbp)
	movq	-584(%rbp), %rdx
	movq	%rdx, -704(%rbp)
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	leaq	-112(%rbp), %rdx
	leaq	-704(%rbp), %rax
	movq	(%rax), %rax
	movq	-568(%rbp), %rcx
	movq	%rcx, -560(%rbp)
	movq	%rax, -696(%rbp)
	movq	(%rdx), %rax
	movq	8(%rdx), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	leaq	-696(%rbp), %rax
	movq	(%rax), %rdx
	movq	-560(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-96(%rbp), %rax
	movq	-560(%rbp), %rcx
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, 8(%rcx)
	movq	%rdx, 16(%rcx)
	movq	-776(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -600(%rbp)
	movq	-600(%rbp), %rax
	movq	%rax, -592(%rbp)
	movq	-592(%rbp), %rcx
	leaq	-765(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rax, -616(%rbp)
	movq	-616(%rbp), %rax
	movq	%rax, -608(%rbp)
	movq	-608(%rbp), %rax
	movq	(%rax), %rax
	movq	$16, -632(%rbp)
	movq	%rax, -624(%rbp)
	movq	-624(%rbp), %rax
	testq	%rax, %rax
	je	.L1103
	movq	%rax, -552(%rbp)
	movq	%rcx, -544(%rbp)
	movq	%rdx, -536(%rbp)
	movq	-552(%rbp), %rax
	movq	%rax, -528(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-528(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE(%rip), %rdx
	movq	-552(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-536(%rbp), %rax
	movq	%rax, -520(%rbp)
	movq	-520(%rbp), %rax
	movq	%rax, -512(%rbp)
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
	movq	-504(%rbp), %rax
	movq	%rax, -496(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, -488(%rbp)
	movq	-488(%rbp), %rax
	leaq	-128(%rbp), %rdx
	movq	%rdx, -480(%rbp)
	movzbl	-783(%rbp), %esi
	movb	%sil, -761(%rbp)
	movzbl	-782(%rbp), %esi
	movb	%sil, -762(%rbp)
	movzbl	-781(%rbp), %edi
	movb	%dil, -763(%rbp)
	movzbl	-780(%rbp), %esi
	movb	%sil, -764(%rbp)
	movq	%rax, -472(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, -464(%rbp)
	movq	-464(%rbp), %rax
	movq	-480(%rbp), %rdx
	movq	%rdx, -456(%rbp)
	movq	%rax, -448(%rbp)
	movq	-448(%rbp), %rax
	movq	%rax, -440(%rbp)
	movq	-440(%rbp), %rdx
	movq	-456(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movq	-544(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	-432(%rbp), %rax
	movq	%rax, -424(%rbp)
	movq	-424(%rbp), %rax
	movq	%rax, -416(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -408(%rbp)
	movzbl	-779(%rbp), %eax
	movb	%al, -757(%rbp)
	movzbl	-778(%rbp), %eax
	movb	%al, -758(%rbp)
	movzbl	-777(%rbp), %eax
	movb	%al, -759(%rbp)
	movb	%r15b, -760(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movq	-408(%rbp), %rdx
	movq	%rdx, -384(%rbp)
	movq	%rax, -376(%rbp)
	movq	-376(%rbp), %rax
	movq	%rax, -368(%rbp)
	movq	-368(%rbp), %rdx
	movq	-384(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, %rdx
	movq	-552(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -360(%rbp)
	movb	%r14b, -756(%rbp)
	movq	%rdx, -736(%rbp)
	movq	%rcx, -752(%rbp)
	leaq	-752(%rbp), %rax
	leaq	-736(%rbp), %rdx
	movq	-360(%rbp), %rcx
	movq	%rcx, -352(%rbp)
	movb	%r13b, -753(%rbp)
	movq	(%rdx), %rdx
	movq	%rdx, -128(%rbp)
	movq	(%rax), %rax
	movq	%rax, -720(%rbp)
	movb	%r12b, -754(%rbp)
	movb	%bl, -755(%rbp)
	leaq	-720(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-344(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -336(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, -328(%rbp)
	movq	-328(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rdx
	movq	-352(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L1103:
	leaq	-80(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -152(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	$0, (%rax)
	movq	-152(%rbp), %rax
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, -312(%rbp)
	movq	$0, -304(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -280(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	-304(%rbp), %rdx
	movq	%rdx, (%rax)
	cmpq	$0, -280(%rbp)
	je	.L1116
	movq	-312(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -240(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -232(%rbp)
	movq	-240(%rbp), %rax
	movq	8(%rax), %rax
	movq	-240(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, -224(%rbp)
	movq	-232(%rbp), %rdx
	movq	%rdx, -216(%rbp)
	movq	%rax, -208(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
.L1116:
	movq	%rbx, %rax
	movq	__stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	-56(%rbp), %rbx
	xorq	(%rdx), %rbx
	je	.L1117
	call	__stack_chk_fail@PLT
.L1117:
	addq	$736, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r10
	.cfi_restore 10
	.cfi_def_cfa 10, 0
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4261:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEv, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEPNS0_6__baseISB_EE, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEPNS0_6__baseISB_EE:
.LFB4262:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$392, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -408(%rbp)
	movq	%rsi, -416(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	movq	%rsi, -56(%rbp)
	xorl	%esi, %esi
	movq	-408(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rcx
	movq	-408(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-304(%rbp), %rdx
	movq	-416(%rbp), %rax
	movq	$16, -328(%rbp)
	movq	%rax, -320(%rbp)
	movq	-320(%rbp), %rax
	testq	%rax, %rax
	je	.L1143
	movq	%rax, -280(%rbp)
	movq	%rcx, -272(%rbp)
	movq	%rdx, -264(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	_ZTVNSt3__110__function6__baseIFvvEEE@GOTPCREL(%rip), %rax
	leaq	16(%rax), %rdx
	movq	-256(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	16+_ZTVNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEE(%rip), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-264(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rax
	movq	%rax, -232(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -224(%rbp)
	movzbl	-419(%rbp), %eax
	movb	%al, -393(%rbp)
	movzbl	-418(%rbp), %eax
	movb	%al, -394(%rbp)
	movzbl	-417(%rbp), %eax
	movb	%al, -395(%rbp)
	movb	%r15b, -396(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -216(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	-224(%rbp), %rdx
	movq	%rdx, -200(%rbp)
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	-200(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, %rcx
	movq	-272(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -152(%rbp)
	movb	%r14b, -389(%rbp)
	movb	%r13b, -390(%rbp)
	movb	%r12b, -391(%rbp)
	movb	%bl, -392(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rdx, -128(%rbp)
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, %rdx
	movq	-280(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -104(%rbp)
	movb	%r11b, -388(%rbp)
	movq	%rdx, -368(%rbp)
	movq	%rcx, -384(%rbp)
	leaq	-384(%rbp), %rax
	leaq	-368(%rbp), %rdx
	movq	-104(%rbp), %rcx
	movq	%rcx, -96(%rbp)
	movb	%r10b, -385(%rbp)
	movq	(%rdx), %rdx
	movq	%rdx, -336(%rbp)
	movq	(%rax), %rax
	movq	%rax, -352(%rbp)
	movb	%r9b, -386(%rbp)
	movb	%r8b, -387(%rbp)
	leaq	-352(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	leaq	-336(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rdx
	movq	-96(%rbp), %rax
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
.L1143:
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-56(%rbp), %rdi
	xorq	(%rax), %rdi
	je	.L1142
	call	__stack_chk_fail@PLT
.L1142:
	addq	$392, %rsp
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%r13
	.cfi_restore 13
	popq	%r14
	.cfi_restore 14
	popq	%r15
	.cfi_restore 15
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4262:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEPNS0_6__baseISB_EE, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7__cloneEPNS0_6__baseISB_EE
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7destroyEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7destroyEv:
.LFB4263:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4263:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7destroyEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE7destroyEv
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE18destroy_deallocateEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE18destroy_deallocateEv:
.LFB4264:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rdx
	movq	%rdx, -8(%rbp)
	xorl	%edx, %edx
	movq	-72(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	$1, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv@PLT
	nop
	movq	__stack_chk_guard@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	xorq	(%rax), %rcx
	je	.L1148
	call	__stack_chk_fail@PLT
.L1148:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4264:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE18destroy_deallocateEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE18destroy_deallocateEv
	.align 2
	.type	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEclEv, @function
_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEclEv:
.LFB4265:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES8_EUlvE_EEEvDpOT_
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4265:
	.size	_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEclEv, .-_ZNSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEEclEv
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE6targetERKSt9type_info, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE6targetERKSt9type_info:
.LFB4266:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	leaq	_ZTSZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_(%rip), %rax
	cmpq	%rax, %rdx
	sete	%al
	testb	%al, %al
	je	.L1155
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	jmp	.L1158
.L1155:
	movl	$0, %eax
.L1158:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4266:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE6targetERKSt9type_info, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE6targetERKSt9type_info
	.align 2
	.type	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE11target_typeEv, @function
_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE11target_typeEv:
.LFB4267:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	leaq	_ZTIZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_(%rip), %rax
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4267:
	.size	_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE11target_typeEv, .-_ZNKSt3__110__function6__funcIZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES7_EUlvE_NS_9allocatorIS8_EEFvvEE11target_typeEv
	.type	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EEEvDpOT_, @function
_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EEEvDpOT_:
.LFB4316:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZZN14vmcs_intel_x6425create_exit_handler_stackEvENKUlvE_clEv
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4316:
	.size	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EEEvDpOT_, .-_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_EEEvDpOT_
	.type	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EEEvDpOT_, @function
_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EEEvDpOT_:
.LFB4360:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZZN14vmcs_intel_x6418create_vmcs_regionEvENKUlvE_clEv
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4360:
	.size	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EEEvDpOT_, .-_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_EEEvDpOT_
	.type	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x647promoteEvEUlvE_EEEvDpOT_, @function
_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x647promoteEvEUlvE_EEEvDpOT_:
.LFB4404:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZZN14vmcs_intel_x647promoteEvENKUlvE_clEv
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4404:
	.size	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x647promoteEvEUlvE_EEEvDpOT_, .-_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x647promoteEvEUlvE_EEEvDpOT_
	.type	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES8_EUlvE_EEEvDpOT_, @function
_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES8_EUlvE_EEEvDpOT_:
.LFB4448:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_ENKUlvE_clEv
	nop
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4448:
	.size	_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES8_EUlvE_EEEvDpOT_, .-_ZNSt3__128__invoke_void_return_wrapperIvE6__callIJRZN14vmcs_intel_x646launchERKNS_10shared_ptrI20vmcs_intel_x64_stateEES8_EUlvE_EEEvDpOT_
	.section	.rodata
	.align 16
	.type	_ZTSZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_, @object
	.size	_ZTSZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_, 83
_ZTSZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_:
	.string	"*ZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_"
	.section	.data.rel.ro
	.align 8
	.type	_ZTIZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_, @object
	.size	_ZTIZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_, 16
_ZTIZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_EUlvE_
	.section	.rodata
	.align 16
	.type	_ZTSZN14vmcs_intel_x647promoteEvEUlvE_, @object
	.size	_ZTSZN14vmcs_intel_x647promoteEvEUlvE_, 36
_ZTSZN14vmcs_intel_x647promoteEvEUlvE_:
	.string	"*ZN14vmcs_intel_x647promoteEvEUlvE_"
	.section	.data.rel.ro
	.align 8
	.type	_ZTIZN14vmcs_intel_x647promoteEvEUlvE_, @object
	.size	_ZTIZN14vmcs_intel_x647promoteEvEUlvE_, 16
_ZTIZN14vmcs_intel_x647promoteEvEUlvE_:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSZN14vmcs_intel_x647promoteEvEUlvE_
	.section	.rodata
	.align 16
	.type	_ZTSZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_, @object
	.size	_ZTSZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_, 48
_ZTSZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_:
	.string	"*ZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_"
	.section	.data.rel.ro
	.align 8
	.type	_ZTIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_, @object
	.size	_ZTIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_, 16
_ZTIZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSZN14vmcs_intel_x6418create_vmcs_regionEvEUlvE_
	.section	.rodata
	.align 16
	.type	_ZTSZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_, @object
	.size	_ZTSZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_, 55
_ZTSZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_:
	.string	"*ZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_"
	.section	.data.rel.ro
	.align 8
	.type	_ZTIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_, @object
	.size	_ZTIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_, 16
_ZTIZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSZN14vmcs_intel_x6425create_exit_handler_stackEvEUlvE_
	.section	.rodata
	.type	_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_E8__func__, @object
	.size	_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_E8__func__, 7
_ZZN14vmcs_intel_x646launchERKNSt3__110shared_ptrI20vmcs_intel_x64_stateEES5_E8__func__:
	.string	"launch"
	.type	_ZZNK14vmcs_intel_x646vmreadEmE8__func__, @object
	.size	_ZZNK14vmcs_intel_x646vmreadEmE8__func__, 7
_ZZNK14vmcs_intel_x646vmreadEmE8__func__:
	.string	"vmread"
	.type	_ZZN14vmcs_intel_x647vmwriteEmmE8__func__, @object
	.size	_ZZN14vmcs_intel_x647vmwriteEmmE8__func__, 8
_ZZN14vmcs_intel_x647vmwriteEmmE8__func__:
	.string	"vmwrite"
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (GNU) 6.1.0"
