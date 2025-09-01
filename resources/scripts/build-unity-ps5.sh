#!/bin/sh

rm -rf build-unity-ps5
cmake -S . -B build-unity-ps5 -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/unity-ps5.cmake -DTARGET_UNITY=ON
cmake --build build-unity-ps5
