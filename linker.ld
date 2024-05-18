/**
 * @file linker.ld
 * @brief Linker script for the Hyper-LITE hypervisor.
 *
 * This file contains the linker script that defines the memory layout
 * for the Hyper-LITE hypervisor. It specifies the placement of code,
 * data, and stack sections in memory.
 *
 * @date 2024-05-18
 * @version 1.0
 * @autor Charles Fulton Greiner
 *
 * @details
 * The linker script ensures that the hypervisor is loaded at the correct
 * memory addresses and that the stack is properly allocated.
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
 * This script defines the memory sections for the hypervisor, including
 * startup code, text (code), data, BSS, and stack.
 *
 * @section examples Examples
 * No examples available for linker scripts.
 */

ENTRY(_start)

SECTIONS {
    . = 0x40100000; /* Load address in RAM (0x40000000 + offset to avoid DTB conflict) */

    /* Startup code section */
    .startup . :
    {
        *(.text)
    }

    /* Code section */
    .text . :
    {
        *(.text)
    }

    /* Data section */
    .data . :
    {
        *(.data)
    }

    /* BSS (uninitialized data) section */
    .bss . :
    {
        *(.bss COMMON)
    }

    /* Ensure alignment */
    . = ALIGN(8);

    /* Allocate stack memory */
    . += 0x1000; /* 4kB of stack memory */
    stack_top = .; /* Define stack top symbol */
}
