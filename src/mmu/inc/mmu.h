/**
 * @file mmu.h
 * @brief MMU setup and management functions.
 *
 * This file contains the function prototypes and constants for setting up
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
 * Function prototypes and constants for MMU setup and management.
 *
 * @section examples Examples
 * No examples available for MMU functions.
 */

#ifndef MMU_H
#define MMU_H

#include <stdint.h>

typedef uint64_t mmu_pte_t;

typedef struct
{
    mmu_pte_t entries[64] __attribute__((__aligned__(512)));
} mmu_table_t;

void mmu_init(void);
void validate_mmu_setup(void);

#endif // MMU_H
