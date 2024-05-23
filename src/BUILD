load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hyper-lite.elf",
    srcs = [
        "start.s",
        # "main.c",
    ],
    deps = [
        # "//src/arch/arm64:arm64",
        # "//src/drivers/uart:uart",
        # "//src/lib/logging:logging",
        # "//src/mmu:mmu",
        # "//external:newlib_c",
        # "@newlib_lib//:newlib_c",
        # "@newlib_lib//:newlib_m",
        "@newlib_lib//:newlib_build",
        # "@newlib_lib//:newlib_m",
    ],
    visibility = [
        "//visibility:public",
    ],
)
