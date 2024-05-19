/**
 * @file strlen.c
 * @brief Implementation of the strlen function.
 *
 * This file contains the implementation of the strlen function,
 * which calculates the length of a null-terminated string.
 *
 * @date 2024-05-19
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * This file provides the implementation of the strlen function,
 * which returns the number of characters in a null-terminated string,
 * excluding the terminating null byte.
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
 * Provides the implementation of the strlen function.
 */

#include "libc.h"

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * This function returns the number of characters in the string s,
 * excluding the terminating null byte ('\0').
 *
 * @param s Pointer to the null-terminated string.
 * @return The number of characters in the string s.
 */
size_t strlen(const char* s)
{
    const char* p = s;
    while (*p)
    {
        p++;
    }
    return p - s;
}
