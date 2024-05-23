package(default_visibility = ["//visibility:public"])

load(":cc_toolchain_config.bzl", "cc_toolchain_config")

cc_toolchain_config(name = "aarch64_none_elf_toolchain_config")

cc_toolchain(
    name = "aarch64_none_elf_toolchain",
    toolchain_identifier = "aarch64-none-elf-toolchain",
    toolchain_config = ":aarch64_none_elf_toolchain_config",
    all_files = ":aarch64_none_elf_toolchain_config",
    compiler_files = ":aarch64_none_elf_toolchain_config",
    dwp_files = ":aarch64_none_elf_toolchain_config",
    linker_files = ":aarch64_none_elf_toolchain_config",
    objcopy_files = ":aarch64_none_elf_toolchain_config",
    strip_files = ":aarch64_none_elf_toolchain_config",
    supports_param_files = 0,
)

toolchain(
    name = "cc_toolchain_for_linux_x86_64",
    toolchain = ":aarch64_none_elf_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
    exec_compatible_with = [
    ],
    target_compatible_with = [
    ],
)