/**
 * @file syscalls.c
 * @brief Implementation of system call stubs for the hypervisor.
 *
 * This file contains implementations of system call stubs such as _exit,
 * _sbrk, _write, _read, _close, _fstat, _isatty, _lseek, _kill, and _getpid.
 * These functions provide basic functionality for system calls and are used
 * by the hypervisor to handle system-level operations.
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
 */

/* module includes */
#include "syscalls.h"

/* standard includes */
#include <stddef.h>

/* project includes */
#include "uart.h"

/**
 * @brief Terminate the program.
 *
 * This function halts the system and enters an infinite loop.
 *
 * @param status Exit status (unused).
 */
void _exit(int status)
{
    (void)status;
    while (1)
    {
        /* Infinite loop to halt the system */
    }
}

/**
 * @brief Increase program data space.
 *
 * This function is used to allocate more memory to the program.
 *
 * @param incr Amount of memory to allocate.
 * @return Pointer to the newly allocated memory.
 */
void* _sbrk(ptrdiff_t incr)
{
    extern char _end;       /* Defined by the linker */
    static char *heap_end;  /* Current end of the heap */
    char *prev_heap_end;    /* Previous end of the heap */

    if (heap_end == 0)
    {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;

    heap_end += incr;

    return (void*) prev_heap_end;
}

/**
 * @brief Write to a file.
 *
 * This function writes data to a file. In this implementation, it writes
 * data to the UART.
 *
 * @param file File descriptor (unused).
 * @param ptr Pointer to the data to write.
 * @param len Length of the data to write.
 * @return Number of bytes written.
 */
ssize_t _write(int file, const void *ptr, size_t len)
{
    (void)file;

    const char *data = (const char*)ptr; /* Pointer to Tx buffer */

    for (size_t i = 0; i < len; i++)
    {
        uart_putc(data[i]);
    }

    return len;
}

/**
 * @brief Read from a file.
 *
 * This function reads data from a file. In this implementation, it always
 * returns -1, indicating that reading is not supported.
 *
 * @param file File descriptor (unused).
 * @param ptr Pointer to the buffer to read data into.
 * @param len Length of the data to read.
 * @return -1 to indicate reading is not supported.
 */
ssize_t _read(int file, void *ptr, size_t len)
{
    (void)file;
    (void)ptr;
    (void)len;

    return -1;
}

/**
 * @brief Close a file.
 *
 * This function closes a file. In this implementation, it always returns -1,
 * indicating that closing is not supported.
 *
 * @param file File descriptor (unused).
 * @return -1 to indicate closing is not supported.
 */
int _close(int file)
{
    (void)file;

    return -1;
}

/**
 * @brief Get the status of an open file.
 *
 * This function returns the status of an open file. In this implementation,
 * it always returns -1, indicating that the status is not available.
 *
 * @param file File descriptor (unused).
 * @param st Pointer to the stat structure to fill (unused).
 * @return -1 to indicate status is not available.
 */
int _fstat(int file, struct stat *st)
{
    (void)file;
    (void)st;

    return -1;
}

/**
 * @brief Query whether the output stream is a terminal.
 *
 * This function checks if the output stream is a terminal. In this
 * implementation, it always returns 1, indicating that it is a terminal.
 *
 * @param file File descriptor (unused).
 * @return 1 to indicate the output stream is a terminal.
 */
int _isatty(int file)
{
    (void)file;

    return 1;
}

/**
 * @brief Set the position in a file.
 *
 * This function sets the position in a file. In this implementation, it
 * always returns 0, indicating success.
 *
 * @param file File descriptor (unused).
 * @param ptr Position offset (unused).
 * @param dir Direction to move (unused).
 * @return 0 to indicate success.
 */
off_t _lseek(int file, off_t ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;

    return 0;
}

/**
 * @brief Send a signal to a process.
 *
 * This function sends a signal to a process. In this implementation, it
 * always returns -1, indicating that signaling is not supported.
 *
 * @param pid Process ID (unused).
 * @param sig Signal to send (unused).
 * @return -1 to indicate signaling is not supported.
 */
int _kill(pid_t pid, int sig)
{
    (void)pid;
    (void)sig;
    
    return -1;
}

/**
 * @brief Get the process ID.
 *
 * This function returns the process ID. In this implementation, it always
 * returns 1, indicating a single process environment.
 *
 * @return 1 to indicate a single process environment.
 */
pid_t _getpid(void)
{
    return 1;
}
