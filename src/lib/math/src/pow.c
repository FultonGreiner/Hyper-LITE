/**
 * @file pow.c
 * @brief Implementation of the pow function.
 *
 * This file contains the implementation of the pow function,
 * which calculates the power of a base raised to an exponent.
 *
 * @date 2024-05-18
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * This file provides a simple implementation of the pow function,
 * which calculates the power of a base raised to an exponent.
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
 * Provides the implementation of the pow function.
 */

#include "math.h"

/**
 * @brief Calculates the power of a base raised to an exponent.
 *
 * This function calculates the power of a base raised to an exponent
 * using an efficient method known as exponentiation by squaring.
 *
 * @param base The base value.
 * @param exp The exponent value.
 * @return The result of raising the base to the exponent.
 */
double pow(double base, int exp)
{
    double result = 1.0;
    int positive_exp = exp > 0 ? exp : -exp;

    while (positive_exp)
    {
        if (positive_exp % 2 == 1)
        {
            result *= base;
        }
        base *= base;
        positive_exp /= 2;
    }

    return exp < 0 ? 1.0 / result : result;
}
