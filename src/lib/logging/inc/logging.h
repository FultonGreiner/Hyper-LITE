/**
 * @file logging.h
 * @brief Logging functionality for the hypervisor.
 *
 * Provides logging levels and functions to log messages.
 *
 * @date 2024-05-18
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * This file defines the logging levels and functions to log messages
 * with different severity levels. It includes macros for logging
 * messages with a specific logging level.
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
 * Defines logging levels and functions for logging messages with
 * various severity levels.
 */

#ifndef LOGGING_H
#define LOGGING_H

/* standard includes */
#include <stdarg.h>

/**
 * @brief Logging levels, similar to syslog levels.
 *
 * Defines various logging levels that can be used to categorize
 * log messages by severity.
 */
typedef enum log_level
{
    LOG_EMERG = 0, /**< system is unusable */
    LOG_ALERT,     /**< action must be taken immediately */
    LOG_CRIT,      /**< critical conditions */
    LOG_ERR,       /**< error conditions */
    LOG_WARNING,   /**< warning conditions */
    LOG_NOTICE,    /**< normal but significant condition */
    LOG_INFO,      /**< informational */
    LOG_DEBUG,     /**< debug-level messages */
    LOG_LVL_NUM,   /**< number of log levels */
} log_level_t;

/**
 * @brief Initialize the logging system.
 *
 * Sets up the UART for logging.
 */
void log_init(void);

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
void log_printf(log_level_t level, const char* format, ...);

#define LOG_EMERG(...) log_printf(LOG_EMERG, __VA_ARGS__)
#define LOG_ALERT(...) log_printf(LOG_ALERT, __VA_ARGS__)
#define LOG_CRIT(...) log_printf(LOG_CRIT, __VA_ARGS__)
#define LOG_ERR(...) log_printf(LOG_ERR, __VA_ARGS__)
#define LOG_WARNING(...) log_printf(LOG_WARNING, __VA_ARGS__)
#define LOG_NOTICE(...) log_printf(LOG_NOTICE, __VA_ARGS__)
#define LOG_INFO(...) log_printf(LOG_INFO, __VA_ARGS__)
#define LOG_DEBUG(...) log_printf(LOG_DEBUG, __VA_ARGS__)

#endif // LOGGING_H
