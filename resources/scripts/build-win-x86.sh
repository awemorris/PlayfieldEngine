#!/bin/sh

set -eu

rm -rf build-win-x86

cmake -S . -B build-win-x86 -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-x86-toolchain.cmake
cmake --build build-win-x86
