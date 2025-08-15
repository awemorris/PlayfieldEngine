#!/bin/sh

set -eu

rm -rf build-wasm
emcmake cmake -S . -B build-wasm -DENABLE_I18N=OFF
cmake --build build-wasm --parallel
