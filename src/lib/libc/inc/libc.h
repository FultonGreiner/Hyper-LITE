/**
 * @file libc.h
 * @brief Miniature C standard library functions.
 *
 * Provides basic implementations of C standard library functions.
 *
 * @date 2024-05-19
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * This file provides the function prototypes for basic C standard
 * library functions such as memory comparison, copying, setting,
 * formatted printing, and string length calculation.
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
 * Provides basic implementations of C standard library functions.
 */

#ifndef LIBC_H
#define LIBC_H

#include <stdarg.h>
#include <stddef.h>

/**
 * @brief Compares two memory areas.
 *
 * Compares the first n bytes of the memory areas s1 and s2.
 *
 * @param s1 Pointer to the first memory area.
 * @param s2 Pointer to the second memory area.
 * @param n Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if the first n bytes of s1 are found,
 * respectively, to be less than, to match, or be greater than the first n bytes of s2.
 */
int memcmp(const void* s1, const void* s2, size_t n);

/**
 * @brief Copies memory area.
 *
 * Copies n bytes from memory area src to memory area dest.
 *
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return The pointer to dest.
 */
void* memcpy(void* dest, const void* src, size_t n);

/**
 * @brief Fills memory with a constant byte.
 *
 * Fills the first n bytes of the memory area pointed to by s with the constant byte c.
 *
 * @param s Pointer to the memory area to be filled.
 * @param c Byte value to be set.
 * @param n Number of bytes to be set to the value.
 * @return The pointer to the memory area s.
 */
void* memset(void* s, int c, size_t n);

/**
 * @brief Prints formatted output to the UART.
 *
 * Prints the formatted string to the UART.
 *
 * @param format Format string.
 * @param ... Arguments for the format string.
 * @return Number of characters printed.
 */
int printf(const char* format, ...);

/**
 * @brief Prints formatted output to a string.
 *
 * Writes the formatted string to the buffer.
 *
 * @param str Pointer to the buffer where the resulting C-string is stored.
 * @param size Maximum number of bytes to be written to the buffer.
 * @param format Format string.
 * @param ap Arguments for the format string.
 * @return Number of characters that would have been written if size had been sufficiently large.
 */
int vsnprintf(char* str, size_t size, const char* format, va_list ap);

/**
 * @brief Computes the length of a string.
 *
 * Computes the number of characters in the string s, not including the terminating null byte.
 *
 * @param s Pointer to the string.
 * @return The number of characters in the string.
 */
size_t strlen(const char* s);

#endif // LIBC_H
