#!/bin/sh

rm -rf build-unity-win64
mkdir build-unity-win64
cd build-unity-win64
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/unity-win64.cmake
ninja
cd ..

