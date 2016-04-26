#include <intrinsics/gdt.h>

gdt::gdt(uint16_t size) : m_size(size)
{
    m_gdt.reserve(m_size);
}

void gdt::set_base_address(uint16_t index, uint32_t address)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    entry[7] = BA_TOP_MASK(address);
    entry[4] = BA_MID_MASK(address);
    entry[3] = BA_LOW_MASK1(address);
    entry[2] = BA_LOW_MASK0(address);
}

void gdt::set_limit(uint16_t index, uint32_t limit)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    // This is the Wrong Way(TM) to do this, we have to fetch
    // the flags in byte 6, and XOR them back into this byte
    entry[6] = LM_TOP(limit);

    entry[1] = LM_LOW1(limit);
    entry[0] = LM_LOW0(limit);
}

void gdt::set_granularity(uint16_t index, bool page_granular)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];
    uint8_t mod = entry[6];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    if (page_granular)
    {
        mod |= 0x80;
    }
    else
    {
        mod &= ~(0x80);
    }

    entry[6] = mod;
}

void gdt::set_mode_width(uint16_t index, bool mode_32bit)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];
    uint8_t mod = entry[6];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    if (mode_32bit)
    {
        mod |= 0x40;
    }
    else
    {
        mod &= ~(0x40);
    }

    entry[6] = mod;
}

void gdt::set_present(uint16_t index, bool present)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];
    uint8_t mod = entry[5];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    if (present)
    {
        mod |= 0x80;
    }
    else
    {
        mod &= ~(0x80);
    }

    entry[5] = mod;
}

void gdt::set_privilege_level(uint16_t index, privilege_level level)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];
    uint8_t mod = entry[5];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    switch (level)
    {
        case ring_0:
        case ring_1:
        case ring_2:
        case ring_3:
            mod = (((uint8_t)(level)) << 5) | (mod & 0x9F);
            break;
        default:
            mod = (((uint8_t)(ring_0)) << 5) | (mod & 0x9F);
    }

    entry[5] = mod;
}

void gdt::set_executable(uint16_t index, bool executable)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];
    uint8_t mod = entry[5];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    if (executable)
        mod = (1 << 3) | (mod & 0xF7);
    else
        mod &= 0xF7;

    entry[5] = mod;
}

void gdt::set_dc_bit(uint16_t index, bool bit)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];
    uint8_t mod = entry[5];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    if (bit)
        mod = (1 << 2) | (mod & 0xFB);
    else
        mod &= 0xFB;

    entry[5] = mod;
}

void gdt::set_readwrite(uint16_t index, bool readwrite)
{
    uint8_t *entry = (uint8_t *)&m_gdt[index];
    uint8_t mod = entry[5];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    if (readwrite)
        mod = (1 << 1) | (mod & 0xFD);
    else
        mod &= 0xFD;

    entry[5] = mod;
}

void gdt::clear_entry_access(uint16_t index)
{

}

void gdt::set_gdt_entry(uint16_t index, uint32_t base, uint32_t limit)
{
    // Lets edit the entry easily at a byte level
    uint8_t *entry = (uint8_t *)&m_gdt[index];

    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    // Paging granularity
    set_granularity(index, true);

    // 32b mode
    set_mode_width(index, true);

    // Set segment entry preset
    set_present(index, true);

    // Set priviledge level
    set_privilege_level(index, ring_0);

    // Set segment executable
    set_executable(index, true);

    // Set the direction/conforming bit
    set_dc_bit(index, false);

    // Set limit index
    set_limit(index, limit);

    // Set base address
    set_base_address(index, base);
}

void gdt::set_gdt_entry(uint16_t index, uint64_t entry_value)
{
    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    m_gdt[index] = entry_value;
}

uint64_t gdt::gdt_entry(uint16_t index)
{
    if (index >= m_size)
    {
        throw invalid_gdt_entry("GDT entry is out of range\n");
    }

    return m_gdt[index];
}

uint64_t *gdt::base_entry()
{
    return &(m_gdt.front());
}
