#!/bin/sh

set -eu

rm -rf build-wasm
emcmake cmake -S . -B build-wasm -DENABLE_I18N=OFF -DTARGET_WASM=ON
cmake --build build-wasm --parallel
