/**
 * @file main.c
 * @brief Entry point of the hypervisor.
 *
 * This file contains the main function that initializes the logging system,
 * tests the MMU setup and functionality, and exits QEMU.
 *
 * @date 2024-05-18
 * @version 1.0
 * @details
 * The main function initializes the logging system, sets up the MMU, tests
 * memory access before and after enabling the MMU, logs the current Exception
 * Level (EL), and exits QEMU.
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
 */

#include <stdint.h>
#include "logging.h"
#include "mmu.h"

/**
 * @brief Exit QEMU.
 *
 * This function uses the QEMU "halt" instruction to exit QEMU.
 */
void qemu_exit(void)
{
    register uint64_t x0 asm("x0") = 0x18;
    register uint64_t x1 asm("x1") = 0x20026;
    asm volatile(
        "hlt 0xf000\n"
        :
        : "r"(x0), "r"(x1)
        : "memory");
}

/**
 * @brief Main function.
 *
 * This function initializes the logging system, sets up and tests the MMU,
 * logs the current Exception Level (EL), and exits QEMU.
 */
void main(void)
{
    log_init(); // Initialize logging system

    // Log the current EL
    uint64_t current_el;
    asm volatile("mrs %0, CurrentEL"
                 : "=r"(current_el));
    current_el = (current_el >> 2) & 0x3;

    LOG_INFO("Entered main at EL%d\n\r", current_el);

    LOG_INFO("Starting MMU Initialization\n\r");
    mmu_init(); // Initialize the MMU
    LOG_INFO("MMU Initialization Complete\n\r");

    validate_mmu_setup();
    
    qemu_exit(); // Call the function to exit QEMU
}
