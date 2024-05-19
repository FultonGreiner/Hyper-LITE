#!/usr/bin/env bash

# must use the ELF, using binary breaks static/global variables?
qemu-system-aarch64 \
    -machine virt,virtualization=on \
    -cpu cortex-a53 \
    -nographic \
    -smp 1 \
    -m 1024 \
    -kernel build/Hyper-LITE \
    -serial mon:stdio \
    -monitor none \
    -no-reboot
