#!/usr/bin/env bash

qemu-system-aarch64 \
    -machine virt \
    -cpu cortex-a57 \
    -smp 1 \
    -m 512M \
    -nographic \
    -kernel build/hypervisor.bin \
    -append "console=ttyAMA0" \
    -serial mon:stdio \
    -semihosting