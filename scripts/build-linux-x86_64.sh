#!/bin/sh

set -eu

rm -rf build-linux-x86_64

cmake -S . -B build-linux-x86_64 -G Ninja
cmake --build build-linux-x86_64
