#!/bin/sh

set -eu

rm -rf build-mac
mkdir build-mac
cd build-mac

cmake -G Ninja ..
cmake --build .

cd ..
