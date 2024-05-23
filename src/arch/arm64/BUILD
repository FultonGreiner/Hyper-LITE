package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "arm64",
    srcs = [
        "src/syscalls.c",
    ],
    hdrs = [
        "inc/syscalls.h",
    ],
    includes = [
        "inc",
    ],
    deps = [
        "//src/drivers/uart:uart",
    ],
)
