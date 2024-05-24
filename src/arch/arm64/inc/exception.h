#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdint.h>

/* Define Exception Levels (EL) */
#define EL0 (0ULL)
#define EL1 (1ULL)
#define EL2 (2ULL)
#define EL3 (3ULL)

/* Define Exception Types */
#define SYNC_EXCEPTION   (0x00ULL)
#define IRQ_EXCEPTION    (0x01ULL)
#define FIQ_EXCEPTION    (0x02ULL)
#define SERROR_EXCEPTION (0x03ULL)

/* Define Exception Syndrome Register (ESR) EC codes */
#define ESR_ELx_EC_UNKNOWN              (0x00ULL)
#define ESR_ELx_EC_WFI_WFE              (0x01ULL)
#define ESR_ELx_EC_MCR_MRC              (0x03ULL)
#define ESR_ELx_EC_MCRR_MRRC            (0x04ULL)
#define ESR_ELx_EC_ILLEGAL_EXEC         (0x0EULL)
#define ESR_ELx_EC_SVC_AARCH32          (0x11ULL)
#define ESR_ELx_EC_SVC_AARCH64          (0x15ULL)
#define ESR_ELx_EC_HVC_AARCH64          (0x16ULL)
#define ESR_ELx_EC_SMC_AARCH64          (0x17ULL)
#define ESR_ELx_EC_SYSREG               (0x18ULL)
#define ESR_ELx_EC_INSTR_ABORT_LOWER_EL (0x20ULL)
#define ESR_ELx_EC_INSTR_ABORT_CUR_EL   (0x21ULL)
#define ESR_ELx_EC_PC_ALIGN             (0x22ULL)
#define ESR_ELx_EC_DATA_ABORT_LOWER_EL  (0x24ULL)
#define ESR_ELx_EC_DATA_ABORT_CUR_EL    (0x25ULL)
#define ESR_ELx_EC_SP_ALIGN             (0x26ULL)
#define ESR_ELx_EC_FP_ASIMD             (0x28ULL)
#define ESR_ELx_EC_SERROR               (0x2FULL)
#define ESR_ELx_EC_BREAKPOINT_LOWER_EL  (0x30ULL)
#define ESR_ELx_EC_BREAKPOINT_CUR_EL    (0x31ULL)
#define ESR_ELx_EC_SOFTSTEP_LOWER_EL    (0x32ULL)
#define ESR_ELx_EC_SOFTSTEP_CUR_EL      (0x33ULL)
#define ESR_ELx_EC_WATCHPOINT_LOWER_EL  (0x34ULL)
#define ESR_ELx_EC_WATCHPOINT_CUR_EL    (0x35ULL)
#define ESR_ELx_EC_BKPT_AARCH32         (0x38ULL)
#define ESR_ELx_EC_VECTOR_CATCH         (0x3AULL)
#define ESR_ELx_EC_BRK_AARCH64          (0x3CULL)

/* Define DAIF (Debug, Asynchronous Abort, IRQ, FIQ) flags */
#define DAIF_FIQ (0x01ULL)
#define DAIF_IRQ (0x02ULL)
#define DAIF_ABT (0x04ULL)
#define DAIF_DBG (0x08ULL)

/* Macros to set, clear and check DAIF flags */
#define DAIF_SET_MASK(mask) asm volatile("msr daifset, %0" \
                                         :                 \
                                         : "r"(mask)       \
                                         : "memory")
#define DAIF_CLR_MASK(mask) asm volatile("msr daifclr, %0" \
                                         :                 \
                                         : "r"(mask)       \
                                         : "memory")
#define DAIF_IS_SET(mask) ({    \
    uint64_t daif;              \
    asm volatile("mrs %0, daif" \
                 : "=r"(daif)   \
                 :              \
                 : "memory");   \
    (daif & (mask));            \
})

/* Define System Control Register (SCTLR) flags */
#define SCTLR_MMU_ENABLE              (1ULL << 0)
#define SCTLR_ALIGN_CHECK             (1ULL << 1)
#define SCTLR_CACHE_ENABLE            (1ULL << 2)
#define SCTLR_BRANCH_PREDICTOR_ENABLE (1ULL << 11)
#define SCTLR_ICACHE_ENABLE           (1ULL << 12)

/* Macros to read/write system registers */
#define READ_SYSREG(reg) ({      \
    uint64_t val;                \
    asm volatile("mrs %0, " #reg \
                 : "=r"(val));   \
    val;                         \
})

#define WRITE_SYSREG(reg, val) asm volatile("msr " #reg ", %0" \
                                            :                  \
                                            : "r"(val))

/* Define macros to manage exception vectors */
#define VECTOR_TABLE_ALIGNMENT (0x200ULL)
#define SET_VECTOR_TABLE(base) asm volatile("msr vbar_el1, %0" \
                                            :                  \
                                            : "r"(base))

/* Function declarations */
void configure_hcr_el2(void);
void exception_handler(uint64_t esr_el2);
void emulate_privileged_instruction(void);

#endif // EXCEPTION_H
