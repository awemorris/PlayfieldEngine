#!/bin/sh

rm -rf build-unity-win64

cmake -S . -B build-unity-win64 -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/unity-win64.cmake
cmake --build build-unity-win64
