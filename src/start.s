/**
 * @file start.s
 * @brief Bootstrap code to initialize the hypervisor.
 *
 * This file contains the initial bootstrap code that sets the CPU
 * into the appropriate mode and prepares the environment for the hypervisor.
 *
 * @date 2024-05-18
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * The bootstrap code initializes the stack, sets the CPU to EL2 (hypervisor mode),
 * and jumps to the main C entry point of the hypervisor.
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
 * Initial setup and transition to hypervisor mode.
 *
 * @section examples Examples
 * No examples available for assembly bootstrapping code.
 */

.section .text
.global _start

_start:
    // Check current Exception Level (EL)
    mrs x0, CurrentEL  /* Read current exception level into x0 */
    and x0, x0, #0b1100  /* Mask bits to get EL value */
    lsr x0, x0, #2  /* Shift right to get the EL number */

    // If not in EL2, switch to EL2
    mov x1, #2  /* Load EL2 value into x1 */
    cmp x0, x1  /* Compare current EL with EL2 */
    b.eq 1f  /* If equal, branch to label 1 */

    // Set up EL2 (Hypervisor Mode)
    mov x0, #0x3C5  /* Set up EL2 configuration */
    msr spsr_el1, x0  /* Write to Saved Program Status Register */
    adr x0, 1f  /* Get address of label 1 */
    msr elr_el1, x0  /* Set Exception Link Register to address of label 1 */
    eret  /* Return from exception to EL2 */

1:
    // Set up stack pointer
    ldr x1, =stack_top  /* Load address of stack_top into x1 */
    mov sp, x1  /* Set stack pointer to stack_top */

    // Jump to main function
    bl main  /* Branch with link to main function */
    b .  /* Infinite loop to prevent fall-through */

// Define stack
.section .bss
.align 16
.global stack_top
stack:
    .space 0x10000  /* Allocate 64KB stack */
stack_top:
