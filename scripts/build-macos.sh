#!/bin/sh

set -eu

rm -rf build-macos

cmake -S . -B build-macos -G Ninja
cmake --build build-macos
