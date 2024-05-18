#!/usr/bin/env bash

cmake -S . -B build

make -C build -j 16

