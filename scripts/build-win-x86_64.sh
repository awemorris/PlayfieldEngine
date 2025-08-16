#!/bin/sh

set -eu

rm -rf build-win-x86_64

cmake -S . -B build-win-x86_64 -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-x86_64-toolchain.cmake
cmake --build build-win-x86_64
