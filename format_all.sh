#!/usr/bin/env bash

# Find all .c, .h, .cpp, .hpp files and run clang-format on them
find ./src -regex '.*\.\(c\|h\|cpp\|hpp\)' -exec clang-format -i {} \;
