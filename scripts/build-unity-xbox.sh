#!/bin/sh

rm -rf build-unity-xbox
mkdir build-unity-xbox
cd build-unity-xbox
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/unity-xbox.cmake
ninja
cd ..

