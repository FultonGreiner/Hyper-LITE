/**
 * @file linker.ld
 * @brief Linker script for the hypervisor.
 *
 * This file defines the memory layout for the hypervisor, including the
 * allocation of sections like .text, .rodata, .data, and .bss, as well
 * as setting up the stack.
 *
 * @date 2024-05-18
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * The linker script sets the start address of the RAM and defines the
 * sections for the program. It ensures proper alignment and placement
 * of the sections in memory.
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
 * Defines the memory layout and sections for the hypervisor.
 */

ENTRY(_start)

SECTIONS {
    /**
     * @brief Set the start address of the RAM.
     *
     * The starting address for the RAM is set to 0x40000000. All sections
     * will be loaded relative to this address.
     */
    . = 0x40000000;

    /**
     * @brief Define the .startup section.
     *
     * The .startup section contains the startup code for the hypervisor.
     * It is loaded at the beginning of the RAM.
     */
    .startup . : { *(.text.startup) }

    /**
     * @brief Define the .text section.
     *
     * The .text section contains the executable code. It includes all
     * .text* sections from the input files.
     */
    .text : {
        *(.text*)
    }

    /**
     * @brief Define the .rodata section.
     *
     * The .rodata section contains read-only data. It includes all
     * .rodata* sections from the input files.
     */
    .rodata : {
        *(.rodata*)
    }

    /**
     * @brief Define the .data section.
     *
     * The .data section contains initialized data. The __data_load__,
     * __data_start__, and __data_end__ symbols are defined to mark the
     * beginning and end of this section in memory.
     */
    .data : {
        __data_load__ = LOADADDR(.data);   /* Load address of .data section */
        __data_start__ = .;                /* Start address of .data section */
        *(.data*)
        __data_end__ = .;                  /* End address of .data section */
    }

    /**
     * @brief Define the .bss section.
     *
     * The .bss section contains uninitialized data. It is marked with
     * the NOLOAD attribute to indicate that it does not need to be
     * loaded into memory from the binary file. The __bss_start__ and
     * __bss_end__ symbols are defined to mark the beginning and end
     * of this section in memory.
     */
    .bss (NOLOAD) : {
        . = ALIGN(4);
        __bss_start__ = .;   /* Start address of .bss section */
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;     /* End address of .bss section */
    }

    /**
     * @brief Allocate stack memory.
     *
     * The stack is allocated with a size of 4KB. The stack_top symbol
     * is defined to mark the top of the stack.
     */
    . = ALIGN(8);
    . += 0x1000;   /* 4KB of stack memory */
    stack_top = .;

    . = ALIGN(8);
    _end = .;
}
