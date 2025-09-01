#!/bin/sh

rm -rf build-unity-xbox
cmake -S . -B build-unity-xbox -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/unity-xbox.cmake -DTARGET_UNITY=ON
cmake --build build-unity-xbox
