/**
 * @file main.c
 * @brief Main entry point for the hypervisor.
 *
 * This file contains the main function that serves as the entry
 * point for the hypervisor. It includes a function to exit QEMU.
 *
 * @date 2024-05-18
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * The main function in this file is responsible for initializing
 * the hypervisor environment and then exiting QEMU for testing.
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
 * Main entry point and QEMU exit function.
 *
 * @section examples Examples
 * No examples available for the main entry point.
 */

#include <stdint.h>

/**
 * @brief Exit QEMU.
 *
 * This function triggers an exit from QEMU by issuing a hypervisor
 * call with specific parameters.
 *
 * @author Charles Fulton Greiner
 */
static void qemu_exit(void)
{
    register uint64_t x0 asm("x0") = 0x18;  /* Define exit code 0x18 */
    register uint64_t x1 asm("x1") = 0x20026;  /* Define QEMU exit status */
    asm volatile (
        "hlt 0xf000\n"  /* Hypervisor trap to exit QEMU */
        :
        : "r"(x0), "r"(x1)
        : "memory"
    );
}

/**
 * @brief Main entry point of the hypervisor.
 *
 * This function is the main entry point of the hypervisor. It
 * initializes the hypervisor environment and then exits QEMU
 * for testing purposes.
 *
 * @author Charles Fulton Greiner
 */
void main(void)
{
    qemu_exit();  /* Call the function to exit QEMU */
}
