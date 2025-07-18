#!/bin/sh

set -eu

rm -rf build-linux
mkdir build-linux
cd build-linux

cmake ..
make -j$(nproc)

cd ..
