#!/bin/sh

set -eu

rm -rf build-android-aarch64
cmake -S . -B build-android-aarch64 \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DANDROID_PLATFORM=30 \
  -DANDROID_ABI=arm64-v8a \
  -DTARGET_ANDROID=ON
cmake --build build-android-aarch64 --parallel

rm -rf build-android-armv7
cmake -S . -B build-android-armv7 \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DANDROID_PLATFORM=30 \
  -DANDROID_ABI=armeabi-v7a \
  -DTARGET_ANDROID=ON
cmake --build build-android-armv7 --parallel

rm -rf build-android-x86
cmake -S . -B build-android-x86 \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DANDROID_PLATFORM=30 \
  -DANDROID_ABI=x86 \
  -DTARGET_ANDROID=ON
cmake --build build-android-x86 --parallel

rm -rf build-android-x86_64
cmake -S . -B build-android-x86_64 \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DANDROID_PLATFORM=30 \
  -DANDROID_ABI=x86_64 \
  -DTARGET_ANDROID=ON
cmake --build build-android-x86_64 --parallel

