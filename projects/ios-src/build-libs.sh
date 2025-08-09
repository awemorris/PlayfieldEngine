#!/bin/sh

set -eu

rm -rf objs ios/libnoctvm.a libnoctvm-arm64.a libnoctvm-x86_64.a ios/libnoctvm-device.a ios/libnoctvm-sim.a

#####################################
echo 'Building arm64 device library.'

echo 'Stage1.'
if [ ! -d libroot-device ]; then
    IPHONEOS_DEPLOYMENT_TARGET=13.0 ../../external/StratoHAL/lib/build-libs.sh device clang "-O2 -g0 -arch arm64 -isysroot `xcrun -sdk iphoneos --show-sdk-path` -fembed-bitcode -mios-version-min=13.0" ar `readlink -f ../../external/StratoHAL/lib`;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
IPHONEOS_DEPLOYMENT_TARGET=13.0 clang \
    -c \
    -arch arm64 \
    -fmodules \
    -I../../../external/NoctLang/include \
    -I../../../external/StratoHal/include \
    -I../../../src \
    -I../libroot-device/include \
    -I/System/Library/Frameworks \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -target arm64-apple-ios13.0 \
    -isysroot `xcrun -sdk iphoneos --show-sdk-path` \
    -fembed-bitcode \
    -mios-version-min=13.0 \
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
    ../../../external/NoctLang/src/jit.c \
    ../../../external/StratoHal/src/stdfile.c \
    ../../../external/StratoHal/src/image.c \
    ../../../external/StratoHal/src/aunit.c \
    ../../../external/StratoHal/src/glyph.c \
    ../../../external/StratoHal/src/wave.c \
    ../../../external/StratoHal/src/uimain.m \
    ../../../external/StratoHal/src/GameRenderer.m \
    ../../../src/main.c \
    ../../../src/api.c \
    ../../../src/vm.c

ar x ../libroot-device/lib/libpng.a
ar x ../libroot-device/lib/libjpeg.a
ar x ../libroot-device/lib/libwebp.a
ar x ../libroot-device/lib/libfreetype.a
ar x ../libroot-device/lib/libvorbisfile.a
ar x ../libroot-device/lib/libvorbis.a
ar x ../libroot-device/lib/libogg.a
ar x ../libroot-device/lib/libbrotlidec.a
ar x ../libroot-device/lib/libbrotlicommon.a
ar x ../libroot-device/lib/libbz2.a
ar x ../libroot-device/lib/libz.a
ar rcs ../ios/libnoctvm-device.a *.o
cd ..
rm -rf objs

########################################
echo 'Building arm64 simulator library.'

echo 'Stage1.'
if [ ! -d libroot-sim-arm64 ]; then
    IPHONEOS_DEPLOYMENT_TARGET=13.0 ../../external/StratoHAL/lib/build-libs.sh sim-arm64 clang "-O2 -g0 -arch arm64 -isysroot `xcrun -sdk iphonesimulator --show-sdk-path`" ar `readlink -f ../../external/StratoHAL/lib`;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
IPHONEOS_DEPLOYMENT_TARGET=13.0 clang \
    -c \
    -arch arm64 \
    -fmodules \
    -I../../../external/NoctLang/include \
    -I../../../external/StratoHal/include \
    -I../../../src \
    -I../libroot-sim-arm64/include \
    -I/System/Library/Frameworks \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -isysroot `xcrun -sdk iphonesimulator --show-sdk-path` \
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
    ../../../external/NoctLang/src/jit.c \
    ../../../external/StratoHal/src/stdfile.c \
    ../../../external/StratoHal/src/image.c \
    ../../../external/StratoHal/src/aunit.c \
    ../../../external/StratoHal/src/glyph.c \
    ../../../external/StratoHal/src/wave.c \
    ../../../external/StratoHal/src/uimain.m \
    ../../../external/StratoHal/src/GameRenderer.m \
    ../../../src/main.c \
    ../../../src/api.c \
    ../../../src/vm.c
ar x ../libroot-sim-arm64/lib/libpng.a
ar x ../libroot-sim-arm64/lib/libjpeg.a
ar x ../libroot-sim-arm64/lib/libwebp.a
ar x ../libroot-sim-arm64/lib/libfreetype.a
ar x ../libroot-sim-arm64/lib/libvorbisfile.a
ar x ../libroot-sim-arm64/lib/libvorbis.a
ar x ../libroot-sim-arm64/lib/libogg.a
ar x ../libroot-sim-arm64/lib/libbrotlidec.a
ar x ../libroot-sim-arm64/lib/libbrotlicommon.a
ar x ../libroot-sim-arm64/lib/libbz2.a
ar x ../libroot-sim-arm64/lib/libz.a
ar rcs ../libnoctvm-sim-arm64.a *.o
cd ..
rm -rf objs

#########################################
echo 'Building x86_64 simulator library.'

echo 'Stage1.'
if [ ! -d libroot-sim-x86_64 ]; then
    IPHONEOS_DEPLOYMENT_TARGET=13.0 ../../external/StratoHal/lib/build-libs.sh sim-x86_64 clang "-O2 -g0 -arch x86_64 -isysroot `xcrun -sdk iphonesimulator --show-sdk-path`" ar `readlink -f ../../external/StratoHal/lib`;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
IPHONEOS_DEPLOYMENT_TARGET=13.0 clang \
    -c \
    -arch x86_64 \
    -fmodules \
    -I../../../external/NoctLang/include \
    -I../../../external/StratoHal/include \
    -I../../../src \
    -I../libroot-sim-x86_64/include \
    -I/System/Library/Frameworks \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -isysroot `xcrun -sdk iphonesimulator --show-sdk-path` \
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
    ../../../external/NoctLang/src/jit.c \
    ../../../external/StratoHal/src/stdfile.c \
    ../../../external/StratoHal/src/image.c \
    ../../../external/StratoHal/src/aunit.c \
    ../../../external/StratoHal/src/glyph.c \
    ../../../external/StratoHal/src/wave.c \
    ../../../external/StratoHal/src/uimain.m \
    ../../../external/StratoHal/src/GameRenderer.m \
    ../../../src/main.c \
    ../../../src/api.c \
    ../../../src/vm.c
ar x ../libroot-sim-x86_64/lib/libpng.a
ar x ../libroot-sim-x86_64/lib/libjpeg.a
ar x ../libroot-sim-x86_64/lib/libwebp.a
ar x ../libroot-sim-x86_64/lib/libfreetype.a
ar x ../libroot-sim-x86_64/lib/libvorbisfile.a
ar x ../libroot-sim-x86_64/lib/libvorbis.a
ar x ../libroot-sim-x86_64/lib/libogg.a
ar x ../libroot-sim-x86_64/lib/libbrotlidec.a
ar x ../libroot-sim-x86_64/lib/libbrotlicommon.a
ar x ../libroot-sim-x86_64/lib/libbz2.a
ar x ../libroot-sim-x86_64/lib/libz.a
ar rcs ../libnoctvm-sim-x86_64.a *.o
cd ..
rm -rf objs

##################################################
echo 'Merging into a simulator Univeral Binary...'

lipo -create libnoctvm-sim-arm64.a libnoctvm-sim-x86_64.a -output ios/libnoctvm-sim.a

