/**
 * @file main.c
 * @brief Main entry point for the hypervisor.
 *
 * This file contains the main function which initializes the logging system,
 * tests the new printf and pow functionalities, logs the current Exception Level (EL),
 * and then exits QEMU.
 *
 * @date 2024-05-18
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * The main function initializes the logging system, performs various tests
 * using the printf and pow functionalities, logs the current Exception Level (EL),
 * and finally calls qemu_exit() to exit the QEMU emulator.
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
#include "libc.h"
#include "logging.h"
#include "math.h"

/**
 * @brief Exits QEMU emulator.
 *
 * This function uses the HLT instruction with specific parameters
 * to signal QEMU to exit.
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
 * @brief Main entry point of the hypervisor.
 *
 * This function initializes the logging system, performs tests on the printf
 * and pow functions, logs the current Exception Level (EL), and exits QEMU.
 */
void main(void)
{
    log_init(); // Initialize logging system

    // Test the new printf and pow functionality
    LOG_INFO("Testing printf with integer: %d\n\r", 1234);
    LOG_INFO("Testing printf with float: %f\n\r", 1234.5678);
    LOG_INFO("Testing printf with hexadecimal: %x\n\r", 0xABCDEF);
    LOG_INFO("Testing pow function: pow(2, 3) = %f\n\r", pow(2, 3));

    // Log the current EL
    uint64_t current_el;
    asm volatile("mrs %0, CurrentEL"
                 : "=r"(current_el));
    current_el = (current_el >> 2) & 0x3;

    LOG_INFO("Entered main at EL%d\n\r", current_el);

    qemu_exit(); // Call the function to exit QEMU
}
