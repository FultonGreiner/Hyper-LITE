#!/usr/bin/env bash

echo "."

qemu-system-aarch64 \
    -machine virt,virtualization=on \
    -cpu cortex-a53 \
    -nographic \
    -smp 1 \
    -m 2048 \
    -serial mon:stdio \
    -S -s \
    -kernel build/hyper-lite.elf
