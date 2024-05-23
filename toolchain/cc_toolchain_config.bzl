load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
)

all_link_actions = [
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
    tool_paths = [
        tool_path(
            name = "gcc",
            path = "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-gcc",
        ),
        tool_path(
            name = "ld",
            path = "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-ld",
        ),
        tool_path(
            name = "ar",
            path = "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-ar",
        ),
        tool_path(
            name = "cpp",
            path = "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-g++",
        ),
        tool_path(
            name = "gcov",
            path = "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-gcov",
        ),
        tool_path(
            name = "nm",
            path = "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-nm",
        ),
        tool_path(
            name = "objdump",
            path = "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-objdump",
        ),
        tool_path(
            name = "strip",
            path = "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-strip",
        ),
    ]

    features = [
        # feature(
        #     name = "default_linker_flags",
        #     enabled = True,
        #     flag_sets = [
        #         flag_set(
        #             actions = all_link_actions,
        #             flag_groups = ([
        #                 flag_group(
        #                     flags = [
        #                         "-lstdc++",
        #                     ],
        #                 ),
        #             ]),
        #         ),
        #     ],
        # ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = [
            "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/../lib/gcc/aarch64-none-elf/13.2.1/../../../../aarch64-none-elf/include",
            "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/../lib/gcc/aarch64-none-elf/13.2.1/include-fixed",
            "/opt/arm-gnu-toolchain-13.2.Rel1-aarch64-aarch64-none-elf/bin/../lib/gcc/aarch64-none-elf/13.2.1/include",
        ],
        toolchain_identifier = "local",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "aarch64",
        target_libc = "unknown",
        compiler = "gcc",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)