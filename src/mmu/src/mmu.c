/**
 * @file mmu.c
 * @brief MMU setup and management functions.
 *
 * This file contains the function implementations and macros for setting up
 * and managing the Memory Management Unit (MMU) on ARM64.
 *
 * @date 2024-05-20
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * The MMU setup includes defining translation table structures, initializing
 * the translation tables, and enabling the MMU.
 *
 * @section license License
 * MIT License
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
 *
 * @section description Description
 * Function implementations and macros for MMU setup and management.
 *
 * @section examples Examples
 * No examples available for MMU functions.
 */

/* this module's header */
#include "mmu.h"

/* standard includes */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Memory type attributes */
#define MT_NORMAL            (0ULL) /**< Normal memory */
#define MT_NORMAL_NO_CACHING (2ULL) /**< Normal memory without caching */
#define MT_DEVICE_NGNRNE     (3ULL) /**< Device memory - Non-Gathering, Non-Reordering, No Early write acknowledgment */
#define MT_DEVICE_NGNRE      (4ULL) /**< Device memory - Non-Gathering, Non-Reordering, Early write acknowledgment */

/* Memory attribute indirection register attributes */
#define NORMAL_MEMORY            (0xFFULL) /**< Normal memory attribute */
#define NORMAL_MEMORY_NO_CACHING (0x44ULL) /**< Normal memory without caching attribute */
#define DEVICE_NGNRNE            (0x00ULL) /**< Device memory attribute */
#define DEVICE_NGNRE             (0x04ULL) /**< Device memory attribute */

/* Page table entry flags */
#define PF_TYPE_BLOCK      (1ULL << 0)      /**< Block type */
#define PF_MEM_TYPE_NORMAL (MT_NORMAL << 2) /**< Normal memory type */
#define PF_READ_WRITE      (1ULL << 6)      /**< Read-write permission */
#define PF_INNER_SHAREABLE (3ULL << 8)      /**< Inner shareable */
#define PF_ACCESS_FLAG     (1ULL << 10)     /**< Access flag */

/* Hypervisor Configuration Register */
#define HCR_EL2_E2H_OFFSET (34ULL)                      /**< EL2 to EL1 offset */
#define HCR_MASK           (1ULL << HCR_EL2_E2H_OFFSET) /**< HCR mask */

/* Translation Control Register */
#define TCR_EL2_TG0_MASK    (0xC000ULL)   /**< Translation granule mask */
#define TCR_EL2_TG0_64KIB   (0x4000ULL)   /**< Translation granule 64KB */
#define TCR_EL2_PS_MASK     (0x70000ULL)  /**< Physical size mask */
#define TCR_EL2_PS_OFFSET   (16ULL)       /**< Physical size offset */
#define TCR_EL2_T0SZ        (0x1FULL)     /**< Translation size */
#define TCR_EL2_T0SZ_48BITS (0x10ULL)     /**< 48-bits translation size */
#define TCR_EL2_HA_MASK     (0x200000ULL) /**< Hardware access flag mask */
#define TCR_EL2_HA_DISABLED (0x000000ULL) /**< Hardware access flag disabled */

/* System Control Register */
#define SCTLR_EL2_M_MASK           (0x1ULL)       /**< MMU enable mask */
#define SCTLR_EL2_M_ENABLE         (0x1ULL)       /**< MMU enable */
#define SCTLR_EL2_EE_MASK          (0x2000000ULL) /**< Endianness mask */
#define SCTLR_EL2_EE_LITTLE_ENDIAN (0x0ULL)       /**< Little endian mode */

/* Memory model feature register */
#define ID_AA64MMFR0_EL1_TGRAN64_MASK    (0xf000000ULL) /**< Translation granule 64KB mask */
#define ID_AA64MMFR0_EL1_TGRAN64_ENABLED (0x0ULL)       /**< Translation granule 64KB enabled */
#define ID_AA64MMFR0_EL1_PARANGE_MASK    (0xfULL)       /**< Physical address range mask */

#define MAIR_ATTR(attr, idx) (attr << (8ULL * idx)) /**< MAIR attribute macro */

/* Memory attribute indirection register mask */
#define MAIR_MASK (                                             \
    MAIR_ATTR(NORMAL_MEMORY, MT_NORMAL) |                       \
    MAIR_ATTR(NORMAL_MEMORY_NO_CACHING, MT_NORMAL_NO_CACHING) | \
    MAIR_ATTR(DEVICE_NGNRNE, MT_DEVICE_NGNRNE) |                \
    MAIR_ATTR(DEVICE_NGNRE, MT_DEVICE_NGNRE))

/* Block attributes */
#define BLOCK_ATTR (     \
    PF_TYPE_BLOCK |      \
    PF_MEM_TYPE_NORMAL | \
    PF_READ_WRITE |      \
    PF_INNER_SHAREABLE | \
    PF_ACCESS_FLAG)

#define BLOCK_SIZE (0x40000000000ULL) /**< Block size */

/* MMU table instance */
static mmu_table_t mmu_table_1 = { 0 };

/**
 * @brief Sets up the page table.
 *
 * This function initializes the page table with block attributes and sets the
 * translation table base register (TTBR).
 */
void page_table_setup(void)
{
    uint64_t phys = 0x0ULL; /**< Physical address initialization */

    for (size_t i = 0; i < sizeof(mmu_table_1.entries) / sizeof(mmu_table_1.entries[0]); ++i)
    {
        mmu_table_1.entries[i] = phys | BLOCK_ATTR; /**< Setting block attributes */
        phys += BLOCK_SIZE;                         /**< Increment physical address */
    }

    asm volatile("msr ttbr0_el2, %0" ::"r"((uint64_t)(mmu_table_1.entries))); /**< Set TTBR0_EL2 */

    printf("ttbr0_el2 set to: 0x%lx\n\r", (uint64_t)(mmu_table_1.entries)); /**< Print TTBR0_EL2 value */
}

/**
 * @brief Initializes the MMU.
 *
 * This function sets up the memory attribute indirection register (MAIR),
 * configures the translation control register (TCR), and enables the MMU.
 */
void mmu_init(void)
{
    uint64_t hcr   = 0x0ULL; /**< Hypervisor Configuration Register initialization */
    uint64_t mmfr0 = 0x0ULL; /**< Memory model feature register initialization */
    uint64_t sctlr = 0x0ULL; /**< System Control Register initialization */
    uint64_t tcr   = 0x0ULL; /**< Translation Control Register initialization */

    asm volatile("msr mair_el2, %0" ::"r"(MAIR_MASK)); /**< Set MAIR_EL2 */

    page_table_setup(); /**< Setup page table */

    asm volatile("mrs %0, id_aa64mmfr0_el1"
                 : "=r"(mmfr0)); /**< Read memory model feature register */

    if ((mmfr0 & ID_AA64MMFR0_EL1_TGRAN64_MASK) != ID_AA64MMFR0_EL1_TGRAN64_ENABLED)
    {
        /* TODO: add error code, handle error */
        return; /**< Return if 64KB granule is not enabled */
    }

    asm volatile("mrs %0, tcr_el2"
                 : "=r"(tcr)); /**< Read Translation Control Register */
    asm volatile("mrs %0, hcr_el2"
                 : "=r"(hcr)); /**< Read Hypervisor Configuration Register */
    asm volatile("mrs %0, sctlr_el2"
                 : "=r"(sctlr)); /**< Read System Control Register */

    hcr &= ~(HCR_MASK);                                  /**< Clear HCR mask */
    tcr = (tcr & ~TCR_EL2_TG0_MASK) | TCR_EL2_TG0_64KIB; /**< Configure translation granule */
    tcr = (tcr & ~TCR_EL2_PS_MASK) |
          ((mmfr0 & ID_AA64MMFR0_EL1_PARANGE_MASK) << TCR_EL2_PS_OFFSET); /**< Configure physical size */
    tcr = (tcr & ~TCR_EL2_T0SZ) | TCR_EL2_T0SZ_48BITS;                    /**< Configure translation size */
    tcr = (tcr & ~TCR_EL2_HA_MASK) | TCR_EL2_HA_DISABLED;                 /**< Disable hardware access flag */

    sctlr = (sctlr & ~SCTLR_EL2_EE_MASK) | SCTLR_EL2_EE_LITTLE_ENDIAN; /**< Set little endian mode */
    sctlr = (sctlr & ~SCTLR_EL2_M_MASK) | SCTLR_EL2_M_ENABLE;          /**< Enable MMU */

    asm volatile("msr tcr_el2, %0" ::"r"(tcr));     /**< Write TCR_EL2 */
    asm volatile("msr hcr_el2, %0" ::"r"(hcr));     /**< Write HCR_EL2 */
    asm volatile("msr sctlr_el2, %0" ::"r"(sctlr)); /**< Write SCTLR_EL2 */
}

/**
 * @brief Retrieves the base address of the page table.
 *
 * @return The base address of the page table.
 */
uint64_t mmu_get_page_table_base(void)
{
    uint64_t ttbr0_el2 = 0x0ULL; /**< TTBR0_EL2 initialization */

    asm volatile("mrs %0, ttbr0_el2"
                 : "=r"(ttbr0_el2)); /**< Read TTBR0_EL2 */

    return ttbr0_el2; /**< Return TTBR0_EL2 value */
}
