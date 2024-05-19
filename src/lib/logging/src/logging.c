/**
 * @file logging.c
 * @brief Logging module implementation.
 *
 * This file contains the implementation of the logging module
 * for initializing the logging system, transmitting log messages,
 * and sending strings with log levels.
 *
 * @date 2024-05-18
 * @version 1.0
 * @autor Charles Fulton Greiner
 *
 * @details
 * This logging module provides basic functionalities for logging
 * messages with different severity levels. It uses the UART driver
 * for output.
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
 * Implementation of logging initialization and logging functions.
 *
 * @section examples Examples
 * No examples available for logging functions.
 */

#include "logging.h"
#include "uart.h"

/* Define log level strings */
static const char level_strings[LOG_LVL_NUM][10] =
{
    "EMERG: ",
    "ALERT: ",
    "CRIT:  ",
    "ERROR: ",
    "WARN:  ",
    "NOTICE:",
    "INFO:  ",
    "DEBUG: "
};

/**
 * @brief Initialize the logging system.
 *
 * This function initializes the logging system by setting up
 * the UART driver for output.
 *
 * @return void
 *
 * @author Charles Fulton Greiner
 */
void log_init(void) {
    uart_init(); /* Initialize UART for logging output */
}

/**
 * @brief Transmit a character via the logging system.
 *
 * This function transmits a single character via the UART driver
 * as part of the logging system.
 *
 * @param c The character to be transmitted.
 * @return void
 *
 * @author Charles Fulton Greiner
 */
void log_putc(char c) {
    uart_putc(c);
}

/**
 * @brief Transmit a log message via the logging system.
 *
 * This function transmits a log message with a specified log level
 * via the UART driver. It prefixes the message with the log level.
 *
 * @param level The log level of the message.
 * @param str The null-terminated log message to be transmitted.
 * @return void
 *
 * @author Charles Fulton Greiner
 */
void log_puts(log_level_t level, const char *str) {
    /* Prefix log message with the log level */
    const char *prefix = level_strings[level];
    while (*prefix) {
        log_putc(*prefix++);
    }

    /* Transmit the log message */
    while (*str) {
        log_putc(*str++);
    }
}
