#!/bin/sh

set -eu

rm -rf build-win
mkdir build-win
cd build-win

cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-i686-toolchain.cmake
cmake --build .

cd ..
