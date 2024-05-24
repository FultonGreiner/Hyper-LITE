#include "mmu.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define MT_NORMAL (0ULL)
#define MT_NORMAL_NO_CACHING (2ULL)
#define MT_DEVICE_NGNRNE (3ULL)
#define MT_DEVICE_NGNRE (4ULL)

#define NORMAL_MEMORY (0xFFULL)
#define NORMAL_MEMORY_NO_CACHING (0x44ULL)
#define DEVICE_NGNRNE (0x00ULL)
#define DEVICE_NGNRE (0x04ULL)

#define PF_TYPE_BLOCK (1ULL << 0)
#define PF_MEM_TYPE_NORMAL (MT_NORMAL << 2)
#define PF_READ_WRITE (1ULL << 6)
#define PF_INNER_SHAREABLE (3ULL << 8)
#define PF_ACCESS_FLAG (1ULL << 10)

#define HCR_EL2_E2H_OFFSET (34ULL)
#define HCR_MASK (1ULL << HCR_EL2_E2H_OFFSET)

#define TCR_EL2_TG0_MASK (0xC000ULL)
#define TCR_EL2_TG0_64KIB (0x4000ULL)
#define TCR_EL2_PS_MASK (0x70000ULL)
#define TCR_EL2_PS_OFFSET (16ULL)
#define TCR_EL2_T0SZ (0x1FULL)
#define TCR_EL2_T0SZ_48BITS (0x10ULL)
#define TCR_EL2_HA_MASK (0x200000ULL)
#define TCR_EL2_HA_DISABLED (0x000000ULL)

#define SCTLR_EL2_M_MASK (0x1ULL)
#define SCTLR_EL2_M_ENABLE (0x1ULL)
#define SCTLR_EL2_EE_MASK (0x2000000ULL)
#define SCTLR_EL2_EE_LITTLE_ENDIAN (0x0ULL)

#define ID_AA64MMFR0_EL1_TGRAN64_MASK (0xf000000ULL)
#define ID_AA64MMFR0_EL1_TGRAN64_ENABLED (0x0ULL)
#define ID_AA64MMFR0_EL1_PARANGE_MASK (0xfULL)

#define MAIR_ATTR(attr, idx) (attr << (8ULL * idx))

#define MAIR_MASK (                                             \
    MAIR_ATTR(NORMAL_MEMORY, MT_NORMAL) |                       \
    MAIR_ATTR(NORMAL_MEMORY_NO_CACHING, MT_NORMAL_NO_CACHING) | \
    MAIR_ATTR(DEVICE_NGNRNE, MT_DEVICE_NGNRNE) |                \
    MAIR_ATTR(DEVICE_NGNRE, MT_DEVICE_NGNRE))

#define BLOCK_ATTR (     \
    PF_TYPE_BLOCK |      \
    PF_MEM_TYPE_NORMAL | \
    PF_READ_WRITE |      \
    PF_INNER_SHAREABLE | \
    PF_ACCESS_FLAG)
#define BLOCK_SIZE (0x40000000000ULL)

static mmu_table_t mmu_table_1 = { 0 };

void page_table_setup(void)
{
    uint64_t phys = 0x0ULL;

    for (size_t i = 0; i < sizeof(mmu_table_1.entries) / sizeof(mmu_table_1.entries[0]); ++i)
    {
        mmu_table_1.entries[i] = phys | BLOCK_ATTR;
        phys += BLOCK_SIZE;
    }

    asm volatile("msr ttbr0_el2, %0" ::"r"((uint64_t)(mmu_table_1.entries)));

    printf("ttbr0_el2 set to: 0x%x\n\r", (uint64_t)(mmu_table_1.entries));
}

void mmu_init(void)
{
    uint64_t hcr = 0x0ULL;
    uint64_t mmfr0 = 0x0ULL;
    uint64_t sctlr = 0x0ULL;
    uint64_t tcr = 0x0ULL;

    asm volatile("msr mair_el2, %0" ::"r"(MAIR_MASK));

    page_table_setup();

    asm volatile("mrs %0, id_aa64mmfr0_el1"
                 : "=r"(mmfr0));
    if ((mmfr0 & ID_AA64MMFR0_EL1_TGRAN64_MASK) != ID_AA64MMFR0_EL1_TGRAN64_ENABLED)
    {
        /* TODO: add error code, handle error */
        return;
    }

    asm volatile("mrs %0, tcr_el2"
                 : "=r"(tcr));
    asm volatile("mrs %0, hcr_el2"
                 : "=r"(hcr));
    asm volatile("mrs %0, sctlr_el2"
                 : "=r"(sctlr));

    hcr &= ~(HCR_MASK);
    tcr = (tcr & ~TCR_EL2_TG0_MASK) | TCR_EL2_TG0_64KIB;
    tcr = (tcr & ~TCR_EL2_PS_MASK) |
          ((mmfr0 & ID_AA64MMFR0_EL1_PARANGE_MASK) << TCR_EL2_PS_OFFSET);
    tcr = (tcr & ~TCR_EL2_T0SZ) | TCR_EL2_T0SZ_48BITS;
    tcr = (tcr & ~TCR_EL2_HA_MASK) | TCR_EL2_HA_DISABLED;

    sctlr = (sctlr & ~SCTLR_EL2_EE_MASK) | SCTLR_EL2_EE_LITTLE_ENDIAN;
    sctlr = (sctlr & ~SCTLR_EL2_M_MASK) | SCTLR_EL2_M_ENABLE;

    asm volatile("msr tcr_el2, %0" ::"r"(tcr));
    asm volatile("msr hcr_el2, %0" ::"r"(hcr));
    asm volatile("msr sctlr_el2, %0" ::"r"(sctlr));

    return;
}

uint64_t mmu_get_page_table_base(void)
{
    uint64_t ttbr0_el2 = 0x0ULL;

    asm volatile("mrs %0, ttbr0_el2"
                 : "=r"(ttbr0_el2));

    return ttbr0_el2;
}
