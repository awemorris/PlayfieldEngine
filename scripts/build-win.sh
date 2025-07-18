#!/bin/sh

set -eu

rm -rf build-win
mkdir build-win
cd build-win

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-i686-toolchain.cmake
make -j$(nproc)

cd ..
