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

include(ExternalProject)

# Define the Newlib version and repository
set(NEWLIB_VERSION 4.1.0)
set(NEWLIB_REPO "https://sourceware.org/git/newlib-cygwin.git")
set(NEWLIB_TAG "newlib-${NEWLIB_VERSION}")

# Define a build directory for Newlib
set(NEWLIB_BUILD_DIR ${CMAKE_BINARY_DIR}/newlib-build)
set(NEWLIB_INSTALL_DIR ${CMAKE_BINARY_DIR}/newlib-install)

# Check if Newlib is already installed
if(NOT EXISTS "${NEWLIB_INSTALL_DIR}/aarch64-none-elf/lib/libc.a")
    # ExternalProject to clone and build Newlib
    ExternalProject_Add(
        newlib
        PREFIX ${NEWLIB_BUILD_DIR}
        GIT_REPOSITORY ${NEWLIB_REPO}
        GIT_TAG ${NEWLIB_TAG}
        CONFIGURE_COMMAND ${NEWLIB_BUILD_DIR}/src/newlib/configure --target=aarch64-none-elf --prefix=${NEWLIB_INSTALL_DIR} --disable-shared --disable-newlib-supplied-syscalls
        BUILD_COMMAND make all
        INSTALL_COMMAND make install
        BUILD_IN_SOURCE 1
    )

    add_custom_target(newlib_target DEPENDS newlib)
else()
    add_custom_target(newlib_target)
endif()

# Define project sources
set(PROJECT_SOURCES
    src/start.s
    src/main.c
    src/arch/arm64/src/syscalls.c
    src/drivers/uart/src/uart.c
    src/lib/logging/src/logging.c
    src/mmu/src/mmu.c
)

# Define include directories
set(PROJECT_INCLUDES
    src/arch/arm64/inc
    src/drivers/uart/inc
    src/lib/logging/inc
    src/mmu/inc

    ${NEWLIB_INSTALL_DIR}/aarch64-none-elf/include
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

# Link directories
link_directories(${NEWLIB_INSTALL_DIR}/aarch64-none-elf/lib)

# Add executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Ensure Newlib is built first
add_dependencies(${PROJECT_NAME} newlib_target)

target_link_libraries(${PROJECT_NAME} ${NEWLIB_INSTALL_DIR}/aarch64-none-elf/lib/libc.a ${NEWLIB_INSTALL_DIR}/aarch64-none-elf/lib/libm.a)

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
