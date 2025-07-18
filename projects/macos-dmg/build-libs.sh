#!/bin/sh

set -eu

rm -rf objs libroot libroot-arm64 libroot-x86_64

#####################################
echo 'Building arm64 libraries..'

echo 'Stage1.'
if [ ! -d libroot-arm64 ]; then
    MACOSX_DEPLOYMENT_TARGET=10.13 ../../external/StratoHAL/lib/build-libs.sh "arm64" clang "-O2 -g0 -arch arm64 -isysroot `xcrun --sdk macosx --show-sdk-path`" ar `readlink -f ../../external/StratoHAL/lib`;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
MACOSX_DEPLOYMENT_TARGET=10.13 clang \
    -c \
    -fmodules \
    -arch arm64 \
    -target arm64-apple-macos10.13 \
    -isysroot `xcrun --sdk macosx --show-sdk-path` \
    -mmacosx-version-min=10.13 \
    -I`xcrun --sdk macosx --show-sdk-path`/include \
    -I../../../external/NoctLang/include \
    -I../../../external/StratoHAL/include \
    -I../../../src \
    -I../libroot-arm64/include \
    -I/System/Library/Frameworks \
    -DUSE_JIT \
    -DUSE_MAIN2 \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -ffast-math \
    -ftree-vectorize \
    -std=gnu11 \
    -Wno-sign-conversion \
    -Wno-sign-compare \
    -Wno-conversion \
    -Wno-multichar \
    -Wno-strict-aliasing \
    -Wno-deprecated-declarations \
    ../../../external/NoctLang/src/lexer.yy.c \
    ../../../external/NoctLang/src/parser.tab.c \
    ../../../external/NoctLang/src/ast.c \
    ../../../external/NoctLang/src/hir.c \
    ../../../external/NoctLang/src/lir.c \
    ../../../external/NoctLang/src/runtime.c \
    ../../../external/NoctLang/src/interpreter.c \
    ../../../external/NoctLang/src/execution.c \
    ../../../external/NoctLang/src/intrinsics.c \
    ../../../external/NoctLang/src/jit-common.c \
    ../../../external/NoctLang/src/jit-arm64.c \
    ../../../external/NoctLang/src/jit-x86_64.c \
    ../../../external/StratoHAL/src/stdfile.c \
    ../../../external/StratoHAL/src/image.c \
    ../../../external/StratoHAL/src/aunit.c \
    ../../../external/StratoHAL/src/glyph.c \
    ../../../external/StratoHAL/src/wave.c \
    ../../../external/StratoHAL/src/nsmain.m \
    ../../../external/StratoHAL/src/GameRenderer.m \
    ../../../external/StratoHAL/src/GameShaders.c \
    ../../../src/main.c \
    ../../../src/api.c \
    ../../../src/vm.c \
    ../../../src/translation.c
ar rcs ../libroot-arm64/lib/libnoctvm.a *.o
cd ..
rm -rf objs

#####################################
echo 'Building x86_64 libraries..'

echo 'Stage1.'
if [ ! -d libroot-x86_64 ]; then
    MACOSX_DEPLOYMENT_TARGET=10.13 ../../external/StratoHAL/lib/build-libs.sh "x86_64" clang "-O2 -g0 -arch x86_64 -isysroot `xcrun --sdk macosx --show-sdk-path`" ar `readlink -f ../../external/StratoHAL/lib`;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
MACOSX_DEPLOYMENT_TARGET=10.13 clang \
    -c \
    -fmodules \
    -arch x86_64 \
    -target x86_64-apple-macos10.13 \
    -isysroot `xcrun --sdk macosx --show-sdk-path` \
    -mmacosx-version-min=10.13 \
    -I`xcrun --sdk macosx --show-sdk-path`/include \
    -I../../../external/NoctLang/include \
    -I../../../external/StratoHAL/include \
    -I../../../src \
    -I../libroot-x86_64/include \
    -I/System/Library/Frameworks \
    -DUSE_JIT \
    -DUSE_MAIN2 \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -ffast-math \
    -ftree-vectorize \
    -std=gnu11 \
    -Wno-sign-conversion \
    -Wno-sign-compare \
    -Wno-conversion \
    -Wno-multichar \
    -Wno-strict-aliasing \
    -Wno-deprecated-declarations \
    ../../../external/NoctLang/src/lexer.yy.c \
    ../../../external/NoctLang/src/parser.tab.c \
    ../../../external/NoctLang/src/ast.c \
    ../../../external/NoctLang/src/hir.c \
    ../../../external/NoctLang/src/lir.c \
    ../../../external/NoctLang/src/runtime.c \
    ../../../external/NoctLang/src/interpreter.c \
    ../../../external/NoctLang/src/execution.c \
    ../../../external/NoctLang/src/intrinsics.c \
    ../../../external/NoctLang/src/jit-common.c \
    ../../../external/NoctLang/src/jit-arm64.c \
    ../../../external/NoctLang/src/jit-x86_64.c \
    ../../../external/StratoHAL/src/stdfile.c \
    ../../../external/StratoHAL/src/image.c \
    ../../../external/StratoHAL/src/aunit.c \
    ../../../external/StratoHAL/src/glyph.c \
    ../../../external/StratoHAL/src/wave.c \
    ../../../external/StratoHAL/src/nsmain.m \
    ../../../external/StratoHAL/src/GameRenderer.m \
    ../../../external/StratoHAL/src/GameShaders.c \
    ../../../src/main.c \
    ../../../src/api.c \
    ../../../src/vm.c \
    ../../../src/translation.c
ar rcs ../libroot-x86_64/lib/libnoctvm.a *.o
cd ..
rm -rf objs

#####################################
echo 'Merging into Univeral Binary libraries...'

mkdir libroot
mkdir libroot/lib
cp -R libroot-arm64/include libroot/include

lipo -create libroot-arm64/lib/libnoctvm.a libroot-x86_64/lib/libnoctvm.a -output libroot/lib/libnoctvm.a
lipo -create libroot-arm64/lib/libpng.a libroot-x86_64/lib/libpng.a -output libroot/lib/libpng.a
lipo -create libroot-arm64/lib/libjpeg.a libroot-x86_64/lib/libjpeg.a -output libroot/lib/libjpeg.a
lipo -create libroot-arm64/lib/libwebp.a libroot-x86_64/lib/libwebp.a -output libroot/lib/libwebp.a
lipo -create libroot-arm64/lib/libfreetype.a libroot-x86_64/lib/libfreetype.a -output libroot/lib/libfreetype.a
lipo -create libroot-arm64/lib/libvorbisfile.a libroot-x86_64/lib/libvorbisfile.a -output libroot/lib/libvorbisfile.a
lipo -create libroot-arm64/lib/libvorbis.a libroot-x86_64/lib/libvorbis.a -output libroot/lib/libvorbis.a
lipo -create libroot-arm64/lib/libogg.a libroot-x86_64/lib/libogg.a -output libroot/lib/libogg.a
lipo -create libroot-arm64/lib/libbrotlidec.a libroot-x86_64/lib/libbrotlidec.a -output libroot/lib/libbrotlidec.a
lipo -create libroot-arm64/lib/libbrotlicommon.a libroot-x86_64/lib/libbrotlicommon.a -output libroot/lib/libbrotlicommon.a
lipo -create libroot-arm64/lib/libbz2.a libroot-x86_64/lib/libbz2.a -output libroot/lib/libbz2.a
lipo -create libroot-arm64/lib/libz.a libroot-x86_64/lib/libz.a -output libroot/lib/libz.a

rm -rf objs libroot-arm64 libroot-x86_64

#####################################
echo 'Copying libraries...'

cp libroot/lib/libnoctvm.a macos/
cp libroot/lib/libpng.a macos/
cp libroot/lib/libjpeg.a macos/
cp libroot/lib/libwebp.a macos/
cp libroot/lib/libfreetype.a macos/
cp libroot/lib/libvorbisfile.a macos/
cp libroot/lib/libvorbis.a macos/
cp libroot/lib/libogg.a macos/
cp libroot/lib/libbrotlidec.a macos/
cp libroot/lib/libbrotlicommon.a macos/
cp libroot/lib/libbz2.a macos/
cp libroot/lib/libz.a macos/
