#!/usr/bin/env bash

cmake -DCMAKE_TOOLCHAIN_FILE=cmake/aarch64-linux-gnu-gcc.cmake -S . -B build

make -C build -j 16

