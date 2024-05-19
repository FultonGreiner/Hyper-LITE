/**
 * @file uart.c
 * @brief UART driver implementation.
 *
 * This file contains the implementation of the UART driver
 * for initializing the UART, transmitting characters, and 
 * sending strings.
 *
 * @date 2024-05-18
 * @version 1.0
 * @autor Charles Fulton Greiner
 *
 * @details
 * This UART driver provides basic functionalities for UART 
 * communication including initialization, sending characters, 
 * and sending strings. The driver is designed to work with 
 * the UART0 peripheral.
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
 * Implementation of UART initialization and transmission functions.
 *
 * @section examples Examples
 * No examples available for UART functions.
 */

#include "uart.h"
#include <stdint.h>

#define UART0_BASE 0x09000000
#define UART0_DR   (*(volatile uint32_t *)(UART0_BASE + 0x00))
#define UART0_FR   (*(volatile uint32_t *)(UART0_BASE + 0x18))
#define UART0_IBRD (*(volatile uint32_t *)(UART0_BASE + 0x24))
#define UART0_FBRD (*(volatile uint32_t *)(UART0_BASE + 0x28))
#define UART0_LCRH (*(volatile uint32_t *)(UART0_BASE + 0x2C))
#define UART0_CR   (*(volatile uint32_t *)(UART0_BASE + 0x30))
#define UART0_IMSC (*(volatile uint32_t *)(UART0_BASE + 0x38))

/**
 * @brief Initialize the UART.
 *
 * This function initializes the UART0 peripheral with a baud rate
 * of 115200, 8 data bits, no parity, and 1 stop bit. It enables
 * the UART for transmission and reception.
 *
 * @author Charles Fulton Greiner
 */
void uart_init(void) {
    UART0_CR = 0x00000000;  /* Disable UART */
    UART0_IBRD = 1;         /* Set baud rate: Assuming 115200 baud with 24MHz clock */
    UART0_FBRD = 40;
    UART0_LCRH = (1 << 5) | (1 << 6);  /* 8 bits, no parity, 1 stop bit */
    UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);  /* Enable UART, TX, RX */
}

/**
 * @brief Transmit a character via UART.
 *
 * This function transmits a single character via UART0. It waits
 * until the UART is ready to transmit before sending the character.
 *
 * @param c The character to be transmitted.
 * @return void
 *
 * @author Charles Fulton Greiner
 */
void uart_putc(char c) {
    while (UART0_FR & (1 << 5));  /* Wait until UART is ready to transmit */
    UART0_DR = (uint32_t)c;
}

/**
 * @brief Transmit a string via UART.
 *
 * This function transmits a null-terminated string via UART0. It
 * calls uart_putc() to transmit each character in the string.
 *
 * @param str The null-terminated string to be transmitted.
 * @return void
 *
 * @author Charles Fulton Greiner
 */
void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}
