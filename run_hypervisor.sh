#!/usr/bin/env bash

# must use the ELF, using binary breaks static/global variables?
qemu-system-aarch64 \
    -machine virt,virtualization=on \
    -cpu cortex-a53 \
    -nographic \
    -smp 1 \
    -m 2048 \
    -kernel build/Hyper-LITE \
    -serial mon:stdio \
    -monitor none \
    -no-reboot

# qemu-system-aarch64 \
#     -machine raspi3b \
#     -cpu cortex-a53 \
#     -m 1024 \
#     -serial mon:stdio \
#     -kernel build/Hyper-LITE \
#     -append "console=ttyAMA0,115200 root=/dev/mmcblk0p2 rw rootwait" \
#     -smp 4 \
#     -nographic
