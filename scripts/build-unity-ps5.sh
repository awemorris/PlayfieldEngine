#!/bin/sh

rm -rf build-unity-ps5
mkdir build-unity-ps5
cd build-unity-ps5
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/unity-ps5.cmake
ninja
cd ..

