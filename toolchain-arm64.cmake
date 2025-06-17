# toolchain-arm64.cmake
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR aarch64)

# Specify the cross compiler
SET(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# Optional: adjust these for your sysroot or deployment path
# SET(CMAKE_FIND_ROOT_PATH /path/to/arm64/sysroot)ca
