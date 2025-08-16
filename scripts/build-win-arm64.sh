#!/bin/sh

set -eu

rm -rf build-win-arm64

cmake -S . -B build-win-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-arm64-toolchain.cmake
cmake --build build-win-arm64
