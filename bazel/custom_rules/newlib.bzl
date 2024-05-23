def _newlib_impl(ctx):
    # Define the outputs
    output_libc = ctx.actions.declare_directory(ctx.attr.output_libc)
    output_libm = ctx.actions.declare_directory(ctx.attr.output_libm)
    output_include = ctx.actions.declare_directory(ctx.attr.output_include)

    script_content = """
    #!/bin/bash
    ./configure --target=aarch64-none-elf --disable-shared --disable-newlib-supplied-syscalls
    make -j 16 all
    """

    ctx.actions.run_shell(
        outputs = [output_libc, output_libm, output_include],
        command = script_content,
    )

    return [
        DefaultInfo(
            files = depset([output_libc, output_libm, output_include]),
        ),
    ]

newlib = rule(
    implementation = _newlib_impl,
    attrs = {
        "output_libc": attr.string(default = "newlib-install/lib"),
        "output_libm": attr.string(default = "newlib-install/lib"),
        "output_include": attr.string(default = "newlib-install/include"),
    },
)
