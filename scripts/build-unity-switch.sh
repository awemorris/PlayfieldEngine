#!/bin/sh

rm -rf build-unity-switch
mkdir build-unity-switch
cd build-unity-switch
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/unity-switch.cmake
ninja
cd ..
