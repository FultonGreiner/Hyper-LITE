package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "mmu",
    srcs = [
        "src/mmu.c",
    ],
    hdrs = [
        "inc/mmu.h",
    ],
    includes = [
        "inc",
    ],
    deps = [
        "//src/lib/logging:logging",
    ],
)
