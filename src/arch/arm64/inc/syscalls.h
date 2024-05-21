/**
 * @file syscalls.h
 * @brief Header file for system call-related definitions and structures.
 *
 * This file contains typedefs and structure definitions for system calls,
 * including ssize_t, pid_t, ptrdiff_t, off_t, and the stat structure.
 *
 * @date 2024-05-21
 * @version 1.0
 * @author Charles Fulton Greiner
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
 * This file contains typedefs and structure definitions used in system calls.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H

/**
 * @typedef ssize_t
 * @brief Typedef for signed size type.
 *
 * This type is used to represent sizes or counts that may be negative.
 */
typedef int ssize_t;

/**
 * @typedef pid_t
 * @brief Typedef for process ID.
 *
 * This type is used to represent process IDs.
 */
typedef int pid_t;

/**
 * @typedef ptrdiff_t
 * @brief Typedef for pointer difference type.
 *
 * This type is used to represent the difference between two pointers.
 */
typedef long int ptrdiff_t;

/**
 * @typedef off_t
 * @brief Typedef for file offset type.
 *
 * This type is used to represent file offsets.
 */
typedef long int off_t;

/**
 * @def S_IFCHR
 * @brief Macro for character device.
 *
 * This macro defines the value representing a character device in the file system.
 */
#define S_IFCHR 0020000 /* Character device */

/**
 * @def EINVAL
 * @brief Macro for invalid argument error code.
 *
 * This macro defines the error code for an invalid argument.
 */
#define EINVAL 22       /* Invalid argument */

/**
 * @struct stat
 * @brief Structure for file status.
 *
 * This structure is used to represent the status of a file, including its mode.
 */
struct stat
{
    int st_mode; /**< File mode (type and permissions) */
};

#endif // SYSCALLS_H
