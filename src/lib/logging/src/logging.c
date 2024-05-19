/**
 * @file logging.c
 * @brief Logging functionality for the hypervisor.
 *
 * Provides implementation for logging levels and functions to log messages.
 *
 * @date 2024-05-18
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * This file implements the logging levels and functions to log messages
 * with different severity levels. It includes the log_init and log_printf
 * functions.
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
 * Implements logging functionality for the hypervisor, including
 * initialization and formatted message logging with different severity levels.
 */

#include "logging.h"
#include "libc.h"
#include "uart.h"

#define MAX_LOG_LEN (128ULL)

static const char* level_strings[LOG_LVL_NUM] = {
    "EMERG: ",
    "ALERT: ",
    "CRIT:  ",
    "ERROR: ",
    "WARN:  ",
    "NOTICE:",
    "INFO:  ",
    "DEBUG: "
};

static char log_tx_buffer[MAX_LOG_LEN] = { 0 };

/**
 * @brief Initialize the logging system.
 *
 * Sets up the UART for logging.
 */
void log_init(void)
{
    uart_init();
}

/**
 * @brief Log a formatted message with a specific logging level.
 *
 * Logs a message with the given format and arguments at the specified
 * logging level.
 *
 * @param level The logging level.
 * @param format The format string.
 * @param ... The arguments for the format string.
 */
void log_printf(log_level_t level, const char* format, ...)
{
    char buffer[256];
    memset(log_tx_buffer, 0, MAX_LOG_LEN);

    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // Add log level prefix
    uart_puts(level_strings[level]);

    // Print the formatted string
    uart_puts(buffer);
}
