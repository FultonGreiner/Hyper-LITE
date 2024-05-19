cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "Hyper-LITE")
set(PROJECT_TYPE "exe")

project(${PROJECT_NAME} LANGUAGES ASM C CXX)

# Set the toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/aarch64-linux-gnu-gcc.cmake")

# Define the output binary
set(HYPERVISOR_BIN "${CMAKE_BINARY_DIR}/hypervisor.bin")

# Define project sources
set(PROJECT_SOURCES
    src/start.s
    src/main.c
    src/drivers/uart/src/uart.c
    src/lib/logging/src/logging.c
    src/lib/libc/src/memcmp.c
    src/lib/libc/src/memcpy.c
    src/lib/libc/src/memset.c
    src/lib/libc/src/printf.c
    src/lib/libc/src/strlen.c
    src/lib/libc/src/vsnprintf.c
    src/lib/math/src/pow.c
)

# Define include directories
set(PROJECT_INCLUDES
    src/drivers/uart/inc
    src/lib/logging/inc
    src/lib/libc/inc
    src/lib/math/inc
)

# Define compiler definitions
set(PROJECT_DEFINES
    # Add compiler definitions here
)

# Define compiler flags
set(PROJECT_C_FLAGS
    # Add C compiler flags here
    -ffreestanding
    -g3
    # -nostdlib
    # -O0
)

set(PROJECT_ASM_FLAGS
    # Add assembler flags here
    -g3
    # -O0
)

# Define link flags
set(PROJECT_LINK_FLAGS
    -T ${CMAKE_SOURCE_DIR}/linker.ld
    -nostartfiles
    -g3
)

# Concatenate flags into a single string
list(JOIN PROJECT_DEFINES " " PROJECT_DEFINES_STR)
list(JOIN PROJECT_C_FLAGS " " PROJECT_C_FLAGS_STR)
list(JOIN PROJECT_ASM_FLAGS " " PROJECT_ASM_FLAGS_STR)
list(JOIN PROJECT_LINK_FLAGS " " PROJECT_LINK_FLAGS_STR)

# Include directories
include_directories(${PROJECT_INCLUDES})

# Add executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINK_FLAGS "${PROJECT_LINK_FLAGS_STR}"
    COMPILE_DEFINITIONS "${PROJECT_DEFINES_STR}"
    COMPILE_FLAGS "${PROJECT_C_FLAGS_STR} ${PROJECT_ASM_FLAGS_STR}"
)

# Create the binary file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${HYPERVISOR_BIN}
)
