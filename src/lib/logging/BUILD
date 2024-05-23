package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "logging",
    srcs = [
        "src/logging.c",
    ],
    hdrs = [
        "inc/logging.h",
    ],
    includes = [
        "inc",
    ],
    deps = [
        "//src/drivers/uart:uart",
    ],
)
