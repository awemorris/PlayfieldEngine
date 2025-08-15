#!/bin/sh

rm -rf build-unity-switch
cmake -S . -B build-unity-switch -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/unity-switch.cmake
cmake --build build-unity-switch
