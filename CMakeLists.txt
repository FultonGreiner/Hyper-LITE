cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME            "Hyper-LITE")
set(PROJECT_TYPE            "exe")

project(${PROJECT_NAME} LANGUAGES ASM C CXX)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

string(TOLOWER ${PROJECT_NAME} EXE_NAME)

# Set the toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/aarch64-linux-gnu-gcc.cmake")

# Define the output binary
set(HYPER_LITE_ELF "${EXE_NAME}.elf")
set(HYPER_LITE_BIN "${EXE_NAME}.bin")

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
    src/mmu/src/mmu.c
)

# Define include directories
set(PROJECT_INCLUDES
    src/drivers/uart/inc
    src/lib/logging/inc
    src/lib/libc/inc
    src/lib/math/inc
    src/mmu/inc
)

# Define compiler definitions
set(PROJECT_DEFINES
    # Add compiler definitions here
)

# Define compiler flags
set(PROJECT_C_FLAGS
    # Add C compiler flags here
    -ffreestanding
    -Wall
    -g3
    -O0
)

set(PROJECT_ASM_FLAGS
    # Add assembler flags here
    -g3
    -O0
)

# Define link flags
set(PROJECT_LINK_FLAGS
    -T ${CMAKE_SOURCE_DIR}/linker.ld
    -nostartfiles
    -g3
    -O0
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
    LINK_FLAGS          "${PROJECT_LINK_FLAGS_STR}"
    COMPILE_DEFINITIONS "${PROJECT_DEFINES_STR}"
    COMPILE_FLAGS       "${PROJECT_C_FLAGS_STR} ${PROJECT_ASM_FLAGS_STR}"
    OUTPUT_NAME         "${EXE_NAME}"
)

# Create the binary file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${HYPER_LITE_ELF} ${HYPER_LITE_BIN}
)
