#!/bin/sh

set -eu

rm -rf build-linux-arm64

cmake -S . -B build-linux-arm64 -G Ninja
cmake --build build-linux-arm64
