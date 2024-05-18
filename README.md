# Hyper-LITE

**Hyper-LITE** is a lightweight hypervisor designed for ARM64 architecture. The project aims to manage multiple VMs efficiently, providing essential functionalities such as memory management, CPU virtualization, device emulation, and a simple scheduling mechanism. Hyper-LITE is built to be a minimalistic yet powerful solution for ARM64 virtualization.

## Features

- **Initialization and Basic Setup**:
  - Bootstraps the hypervisor mode from the highest privilege level at boot.
  - Configured using QEMU for ARM64 emulation and GCC for cross-compilation.

- **Memory Management**:
  - Implements Stage 1 and Stage 2 translation tables.
  - Handles Translation Lookaside Buffers (TLBs) and manages page faults.

- **CPU State Management**:
  - Provides routines to save and restore CPU states during VM context switches.
  - Supports hypercalls for VMs to request services from the hypervisor.

- **Device Virtualization**:
  - Designs and codes virtual device models, focusing initially on timers and network interfaces.
  - Manages I/O operations for virtual devices.

- **Scheduler**:
  - Implements a basic round-robin or priority-based scheduler.
  - Provides task switching logic for efficient VM management.

- **Logging**:
  - Includes a modular logging system with different log levels similar to the Linux syslog.
  - Ensures all logs are properly prefixed with log levels for better debugging and readability.

## Directory Structure

```
Hyper-LITE/
├── src/                    # Source code for the hypervisor
│ ├── devices/              # Device-related modules
│ ├── drivers/              # Device drivers
│ ├── lib/                  # Libraries shared among modules
│ ├── mmu/                  # Memory management unit (MMU) source code
│ ├── test/                 # Test code
│ └── main.c                # Hypervisor main driver code
├── CMakeLists.txt          # Build configuration
```

## Getting Started

### Prerequisites

- QEMU for ARM64 emulation
- GCC for cross-compilation
- CMake
- GNU Make
- Google Test

#### Installation Commands

```bash

# update package repositories
sudo apt update

# Install QEMU, GCC, CMake, GNU Make, binutils
sudo apt install -y qemu-system-arm \
                    gcc-aarch64-linux-gnu \
                    cmake \
                    make \
                    binutils

# Install Google Test
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake .
sudo make
sudo cp *.a /usr/lib
```

### Building the Project

```bash
cmake -S . -B build
make -C build -j 16
```

### Running the Hypervisor

```bash
./run_hypervisor.sh
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License.
