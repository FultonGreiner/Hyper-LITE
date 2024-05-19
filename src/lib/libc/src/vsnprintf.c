/**
 * @file vsnprintf.c
 * @brief Implementation of the vsnprintf function.
 *
 * This file contains the implementation of the vsnprintf function,
 * which formats a string and stores it in a buffer, using a variable argument list.
 *
 * @date 2024-05-19
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * This file provides the implementation of the vsnprintf function,
 * which formats a string and stores it in a buffer, using a variable argument list.
 * It supports format specifiers for strings, integers, hexadecimal, and floating-point numbers.
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
 * Provides the implementation of the vsnprintf function.
 */

#include "math.h"
#include "libc.h"

/**
 * @brief Reverses a string.
 *
 * This helper function reverses the characters in a string.
 *
 * @param str Pointer to the string to be reversed.
 * @param len Length of the string to be reversed.
 */
static void reverse(char *str, int len) {
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

/**
 * @brief Converts an integer to a string.
 *
 * This helper function converts an integer to a string, using the specified base.
 *
 * @param num The integer to be converted.
 * @param str Pointer to the buffer where the resulting string will be stored.
 * @param base The base to be used for the conversion (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The length of the resulting string.
 */
static int itoa(int num, char *str, int base) {
    int i = 0;
    int isNegative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return i;
    }

    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str, i);

    return i;
}

/**
 * @brief Converts a float to a string.
 *
 * This helper function converts a floating-point number to a string, with a specified number of digits after the decimal point.
 *
 * @param num The floating-point number to be converted.
 * @param str Pointer to the buffer where the resulting string will be stored.
 * @param afterpoint The number of digits to be displayed after the decimal point.
 * @return The length of the resulting string.
 */
static int ftoa(float num, char *str, int afterpoint) {
    int ipart = (int)num;
    float fpart = num - (float)ipart;

    int i = itoa(ipart, str, 10);

    if (afterpoint != 0) {
        str[i] = '.';

        fpart = fpart * pow(10, afterpoint);

        itoa((int)fpart, str + i + 1, 10);
    }

    return i;
}

/**
 * @brief Formats a string and stores it in a buffer.
 *
 * This function formats a string and stores it in a buffer, using a variable argument list.
 * It supports format specifiers for strings, integers, hexadecimal, and floating-point numbers.
 *
 * @param str Pointer to the buffer where the formatted string will be stored.
 * @param size The size of the buffer.
 * @param format The format string.
 * @param ap The variable argument list.
 * @return The number of characters written to the buffer, excluding the null byte.
 */
int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
    char *buf = str;
    const char *p;
    int written = 0;

    for (p = format; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            if (*p == 's') {
                const char *s = va_arg(ap, const char *);
                while (*s && written < size - 1) {
                    *buf++ = *s++;
                    written++;
                }
            } else if (*p == 'd') {
                int num = va_arg(ap, int);
                char temp[16];
                itoa(num, temp, 10);
                char *num_str = temp;
                while (*num_str && written < size - 1) {
                    *buf++ = *num_str++;
                    written++;
                }
            } else if (*p == 'x') {
                int num = va_arg(ap, int);
                char temp[16];
                itoa(num, temp, 16);
                char *num_str = temp;
                while (*num_str && written < size - 1) {
                    *buf++ = *num_str++;
                    written++;
                }
            } else if (*p == 'f') {
                double num = va_arg(ap, double);
                char temp[32];
                ftoa(num, temp, 6);  // 6 digits after the decimal point
                char *num_str = temp;
                while (*num_str && written < size - 1) {
                    *buf++ = *num_str++;
                    written++;
                }
            }
        } else {
            if (written < size - 1) {
                *buf++ = *p;
                written++;
            }
        }
    }
    if (size > 0) {
        *buf = '\0';
    }
    return written;
}
