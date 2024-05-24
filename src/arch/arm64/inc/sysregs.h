#ifndef SYSREGS_H
#define SYSREGS_H

#include <stdint.h>

/* Define system register access macros */
#define READ_SYSREG(reg) ({      \
    uint64_t val;                \
    asm volatile("mrs %0, " #reg \
                 : "=r"(val));   \
    val;                         \
})

#define WRITE_SYSREG(reg, val) asm volatile("msr " #reg ", %0" \
                                            :                  \
                                            : "r"(val))

#endif // SYSREGS_H
