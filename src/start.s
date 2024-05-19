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
 * and jumps to the main C entry point of the hypervisor. It also ensures that the
 * .data and .bss sections are correctly initialized.
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
    // Ensure we are in EL2 (Exception Level 2)
    // Read the current exception level into x0
    mrs x0, CurrentEL
    // Mask bits to get the EL value
    and x0, x0, #0b1100
    // Shift right to get the EL number
    lsr x0, x0, #2
    // Load EL2 value into x1
    mov x1, #2
    // Compare current EL with EL2
    cmp x0, x1
    // If not in EL2, hang (infinite loop)
    b.ne .

    // Set up stack pointer
    // Load address of stack_top into x1
    ldr x1, =stack_top
    // Set stack pointer to stack_top
    mov sp, x1

    // Initialize .data and .bss sections
    bl initialize_data_bss

    // Jump to main function
    // Branch with link to main function
    bl main
    // Infinite loop to prevent fall-through
    b .

/**
 * @brief Initialize .data and .bss sections.
 *
 * This function zeroes out the .bss section and copies the .data section
 * from its load location to its execution location.
 */
initialize_data_bss:
    // Zero out the .bss segment
    // Load start address of .bss section into x2
    ldr x2, =__bss_start__
    // Load end address of .bss section into x3
    ldr x3, =__bss_end__
    // Set zero value in x4
    mov x4, #0
zero_bss:
    // Compare current address with end address
    cmp x2, x3
    // If current address >= end address, branch to done_zero_bss
    b.ge done_zero_bss
    // Store zero value at current address
    str x4, [x2], #8
    // Increment address by 8 (size of a double word)
    add x2, x2, #8
    // Branch back to zero_bss
    b zero_bss
done_zero_bss:

    // Copy the .data segment
    // Load start address of .data section into x2
    ldr x2, =__data_start__
    // Load end address of .data section into x3
    ldr x3, =__data_end__
    // Load source address of .data section into x4
    ldr x4, =__data_load__
copy_data:
    // Compare current address with end address
    cmp x2, x3
    // If current address >= end address, branch to done_copy_data
    b.ge done_copy_data
    // Load data from source address
    ldr x5, [x4], #8
    // Store data to destination address
    str x5, [x2], #8
    // Increment destination address by 8
    add x2, x2, #8
    // Increment source address by 8
    add x4, x4, #8
    // Branch back to copy_data
    b copy_data
done_copy_data:
    ret

// Define stack
.section .bss
.align 16
.global stack_top
stack:
    .space 0x10000  /* Allocate 64KB stack */
stack_top:
