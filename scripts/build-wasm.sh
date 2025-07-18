#!/bin/sh

set -eu

rm -rf build-wasm
mkdir build-wasm
cd build-wasm

emcmake cmake ..
cmake --build . -j

cd ..
