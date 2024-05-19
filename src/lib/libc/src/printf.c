/**
 * @file printf.c
 * @brief Implementation of the printf function.
 *
 * This file contains the implementation of the printf function,
 * which formats and prints a string to the UART.
 *
 * @date 2024-05-19
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * This file provides the implementation of the printf function,
 * which uses a format string and a variable number of arguments
 * to create a formatted string and print it to the UART.
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
 * Provides the implementation of the printf function.
 */

#include "libc.h"
#include "uart.h"

/**
 * @brief Formats and prints a string to the UART.
 *
 * This function uses a format string and a variable number of arguments
 * to create a formatted string and print it to the UART.
 *
 * @param format Format string that specifies how subsequent arguments are converted for output.
 * @param ... Additional arguments to be formatted and printed according to the format string.
 * @return 0 if the function succeeds.
 */
int printf(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    uart_puts(buffer);
    return 0; // Assuming successful print
}
