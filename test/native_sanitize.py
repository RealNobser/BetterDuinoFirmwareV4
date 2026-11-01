# Sanitizers must also be passed to the linker for native test builds.
Import("env")
env.Append(LINKFLAGS=["-fsanitize=address,undefined"])
