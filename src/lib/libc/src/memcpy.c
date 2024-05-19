/**
 * @file memcpy.c
 * @brief Implementation of the memcpy function.
 *
 * Provides the implementation of the memcpy function for copying memory areas.
 *
 * @date 2024-05-19
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * This file implements the memcpy function, which copies n bytes from the source
 * memory area to the destination memory area.
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
 * Implements the memcpy function for copying n bytes from the source memory area to the destination memory area.
 */

#include "libc.h"

void* memcpy(void* dest, const void* src, size_t n)
{
    char* d = dest;
    const char* s = src;
    while (n--)
    {
        *d++ = *s++;
    }
    return dest;
}
