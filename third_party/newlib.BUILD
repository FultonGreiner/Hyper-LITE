package(default_visibility = ["//visibility:public"])

load("@rules_foreign_cc//foreign_cc:defs.bzl", "make")

filegroup(
    name = "newlib_srcs",
    srcs = glob([
        "**",
    ]),
)

# configure_make(
#     name = "newlib_build",
#     configure_in_place = True,
#     configure_options = [
#         "--target=aarch64-none-elf",
#         "--prefix=$(pwd)/newlib-build",
#         "--disable-shared",
#         "--disable-newlib-supplied-syscalls",
#     ],
#     lib_source = ":newlib_srcs",
#     env = {
#         "CC": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-gcc",
#         "LD": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-ld",
#         "AR": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-ar",
#         "AS": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-as",
#         "RANLIB": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-ranlib",
#         # "CFLAGS": "-ffreestanding -O2 -nostdlib",
#     },
#     out_include_dir = "newlib-build/aarch64-none-elf/include",
#     out_static_libs = [
#         "newlib-build/aarch64-none-elf/lib/libc.a",
#         "newlib-build/aarch64-none-elf/lib/libm.a",
#     ],
# )

make(
    name = "newlib_build",
    configure_in_place = True,
    # configure_options = [
    #     "--target=aarch64-none-elf",
    #     "--prefix=$(pwd)/newlib-build",
    #     "--disable-shared",
    #     "--disable-newlib-supplied-syscalls",
    # ],
    targets = [
        "all",
        "install",
    ],
    lib_source = ":newlib_srcs",
    env = {
        "CC": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-gcc",
        "LD": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-ld",
        "AR": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-ar",
        "AS": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-as",
        "RANLIB": "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-ranlib",
        # "CFLAGS": "-ffreestanding -O2 -nostdlib",
    },
    out_include_dir = "newlib-build/aarch64-none-elf/include",
    out_static_libs = [
        "newlib-build/aarch64-none-elf/lib/libc.a",
        "newlib-build/aarch64-none-elf/lib/libm.a",
    ],
)
