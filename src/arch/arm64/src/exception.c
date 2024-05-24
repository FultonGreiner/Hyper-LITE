#include "exception.h"
#include "emulation.h" // Include the header file where emulation functions are declared
#include "sysregs.h"   // Include the header file where the system registers are defined

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Macro definitions for HCR_EL2 settings */
#define HCR_TGE (1ULL << 27) /**< Traps General Exceptions */
#define HCR_TVM (1ULL << 26) /**< Traps Virtual Memory controls */
#define HCR_TSC (1ULL << 19) /**< Traps SMC calls */

/* Exception Class for Hypervisor Call (HVC) */
#define HVC_TRAP (0x16ULL)

/* System Register access exceptions */
#define MSR_EL1 (0x10ULL)
#define MRS_EL1 (0x11ULL)

void configure_hcr_el2(void)
{
    uint64_t hcr_el2 = READ_SYSREG(hcr_el2);
    hcr_el2 |= (HCR_TGE | HCR_TVM | HCR_TSC);
    WRITE_SYSREG(hcr_el2, hcr_el2);
}

void exception_handler(uint64_t esr_el2)
{
    uint64_t ec = (esr_el2 >> 26) & 0x3FUL; // Extract Exception Class (EC)

    if (ec == HVC_TRAP)
    {
        /* Handle HVC trap */
        emulate_privileged_instruction();
    }
    else
    {
        /* Handle other exceptions */
    }
}

void emulate_privileged_instruction(void)
{
    uint64_t esr_el2 = READ_SYSREG(esr_el2);
    uint64_t iss     = esr_el2 & 0x1FFFFFFULL; // Extract Instruction Specific Syndrome (ISS)

    switch (iss)
    {
        case MSR_EL1:
        {
            /* Emulate MSR_EL1 instruction */
            break;
        }
        case MRS_EL1:
        {
            /* Emulate MRS_EL1 instruction */
            break;
        }
        default:
        {
            /* Handle other instructions */
            break;
        }
    }
}
