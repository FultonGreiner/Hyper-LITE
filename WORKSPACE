workspace(name = "hyper_lite")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "rules_cc",
    remote = "https://github.com/bazelbuild/rules_cc",
    branch = "main",
)

http_archive(
    name = "rules_foreign_cc",
    integrity = "sha256-Kk0HzWSwcZs5p8EiGKPlB2crgql7mMaonThWWJTPfFE=",
    strip_prefix = "rules_foreign_cc-0.9.0",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.9.0.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

http_archive(
    name = "newlib_lib",
    urls = ["https://github.com/bminor/newlib/archive/refs/tags/newlib-4.1.0.tar.gz"],
    strip_prefix = "newlib-newlib-4.1.0",
    integrity = "sha256-/1kEhECeNEzunrtzaTwrQp7a/TMINHNYMoT3LVnTfZ8=",
    build_file = "//third_party:newlib.BUILD",
)

# bind(
#     name = "newlib_c",
#     actual = "@newlib_lib//:newlib_c",
# )
