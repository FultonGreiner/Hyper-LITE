/**
 * @file logging.h
 * @brief Logging module header file.
 *
 * This file contains the function prototypes and definitions for the
 * logging module, including initialization, character transmission,
 * and log message transmission functions.
 *
 * @date 2024-05-18
 * @version 1.0
 * @autor Charles Fulton Greiner
 *
 * @details
 * The logging module provides basic functionalities for logging
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
 * Function prototypes and definitions for the logging module.
 *
 * @section examples Examples
 * No examples available for logging functions.
 */

#ifndef LOGGING_H
#define LOGGING_H

/**
 * @brief Logging levels, similar to syslog levels.
 *
 * This enum defines the different severity levels for logging
 * messages. The levels range from emergency (system is unusable)
 * to debug (debug-level messages).
 *
 * @author Charles Fulton Greiner
 */
typedef enum
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
 * This function initializes the logging system by setting up
 * the UART driver for output.
 *
 * @return void
 *
 * @author Charles Fulton Greiner
 */
void log_init(void);

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
void log_putc(char c);

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
void log_puts(log_level_t level, const char* str);

/* Logging macros */
#define LOG_EMERG(msg) log_puts(LOG_EMERG, msg)
#define LOG_ALERT(msg) log_puts(LOG_ALERT, msg)
#define LOG_CRIT(msg) log_puts(LOG_CRIT, msg)
#define LOG_ERR(msg) log_puts(LOG_ERR, msg)
#define LOG_WARNING(msg) log_puts(LOG_WARNING, msg)
#define LOG_NOTICE(msg) log_puts(LOG_NOTICE, msg)
#define LOG_INFO(msg) log_puts(LOG_INFO, msg)
#define LOG_DEBUG(msg) log_puts(LOG_DEBUG, msg)

#endif // LOGGING_H
