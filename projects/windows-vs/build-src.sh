#!/bin/sh

if [ ! -d libroot ]; then
    ./build-libs.sh;
fi

echo '[x86]'
rm -rf objs
mkdir objs
cd objs
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/main.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/api.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/vm.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DWINMAIN2 /I../../../external/StratoHAL/include  /I../../../src /I../../win32/res ../../../external/StratoHAL/src/winmain.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3drender.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../dx12headers/include/directx ../../../external/StratoHAL/src/d3d12render.cc
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3d11render.cc
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3d9render.cc
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/gdirender.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/dsound.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/dsvideo.cc
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ./../../external/StratoHAL/src/stdfile.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/glyph.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/wave.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/image.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/cpuid.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/scalar.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:SSE ../../../external/StratoHAL/src/sse.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:SSE2 ../../../external/StratoHAL/src/sse2.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:AVX  ../../../external/StratoHAL/src/avx.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:AVX2 ../../../external/StratoHAL/src/avx2.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /DYY_NO_UNISTD_H /I../../../external/NoctLang/include ../../../external/NoctLang/src/lexer.yy.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/parser.tab.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/ast.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/hir.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/lir.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/runtime.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/interpreter.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/execution.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/intrinsics.c
clang-cl -target i686-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/jit.c
cd ..
llvm-lib /nologo /OUT:libroot/lib-x86/libnoctvm.lib objs/main.obj objs/api.obj objs/tag.obj objs/vm.obj objs/common.obj objs/render.obj objs/sound.obj objs/font.obj objs/winmain.obj objs/d3drender.obj objs/d3d12render.obj objs/d3d11render.obj objs/d3d9render.obj objs/gdirender.obj objs/dsound.obj objs/dsvideo.obj objs/stdfile.obj objs/image.obj objs/glyph.obj objs/wave.obj objs/cpuid.obj objs/scalar.obj objs/sse.obj objs/sse2.obj objs/avx.obj objs/avx2.obj objs/lexer.yy.obj objs/parser.tab.obj objs/ast.obj objs/hir.obj objs/lir.obj objs/runtime.obj objs/interpreter.obj objs/intrinsics.obj objs/jit.obj

echo '[x64]'
rm -rf objs
mkdir objs
cd objs
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/main.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/api.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/vm.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DWINMAIN2 /I../../../external/StratoHAL/include  /I../../../src /I../../win32/res ../../../external/StratoHAL/src/winmain.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3drender.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../dx12headers/include/directx ../../../external/StratoHAL/src/d3d12render.cc
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3d11render.cc
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3d9render.cc
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/gdirender.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/dsound.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/dsvideo.cc
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ./../../external/StratoHAL/src/stdfile.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/glyph.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/wave.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/image.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/cpuid.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/scalar.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:SSE ../../../external/StratoHAL/src/sse.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:SSE2 ../../../external/StratoHAL/src/sse2.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:AVX  ../../../external/StratoHAL/src/avx.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:AVX2 ../../../external/StratoHAL/src/avx2.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /DYY_NO_UNISTD_H /I../../../external/NoctLang/include ../../../external/NoctLang/src/lexer.yy.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/parser.tab.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/ast.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/hir.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/lir.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/runtime.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/interpreter.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/execution.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/intrinsics.c
clang-cl -target x86_64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/jit.c
cd ..
llvm-lib /nologo /OUT:libroot/lib-x64/libnoctvm.lib objs/main.obj objs/api.obj objs/tag.obj objs/vm.obj objs/common.obj objs/render.obj objs/sound.obj objs/font.obj objs/winmain.obj objs/d3drender.obj objs/d3d12render.obj objs/d3d11render.obj objs/d3d9render.obj objs/gdirender.obj objs/dsound.obj objs/dsvideo.obj objs/stdfile.obj objs/image.obj objs/glyph.obj objs/wave.obj objs/cpuid.obj objs/scalar.obj objs/sse.obj objs/sse2.obj objs/avx.obj objs/avx2.obj objs/lexer.yy.obj objs/parser.tab.obj objs/ast.obj objs/hir.obj objs/lir.obj objs/runtime.obj objs/interpreter.obj objs/intrinsics.obj objs/jit.obj

echo '[arm64]'
rm -rf objs
mkdir objs
cd objs
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/main.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/api.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../external/StratoHAL/include /I../../../src ../../../src/vm.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DWINMAIN2 /I../../../external/StratoHAL/include  /I../../../src /I../../win32/res ../../../external/StratoHAL/src/winmain.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3drender.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../dx12headers/include/directx ../../../external/StratoHAL/src/d3d12render.cc
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3d11render.cc
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/d3d9render.cc
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/gdirender.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/dsound.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ../../../external/StratoHAL/src/dsvideo.cc
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include ./../../external/StratoHAL/src/stdfile.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/glyph.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/wave.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/image.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/cpuid.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include ../../../external/StratoHAL/src/scalar.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:SSE ../../../external/StratoHAL/src/sse.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:SSE2 ../../../external/StratoHAL/src/sse2.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:AVX  ../../../external/StratoHAL/src/avx.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../external/StratoHAL/include /I../libroot/include /arch:AVX2 ../../../external/StratoHAL/src/avx2.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /DYY_NO_UNISTD_H /I../../../external/NoctLang/include ../../../external/NoctLang/src/lexer.yy.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/parser.tab.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/ast.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/hir.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/lir.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/runtime.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/interpreter.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/execution.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/intrinsics.c
clang-cl -target aarch64-pc-windows-msvc /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../external/NoctLang/include ../../../external/NoctLang/src/jit.c
cd ..
llvm-lib /nologo /OUT:libroot/lib-arm64/libnoctvm.lib objs/main.obj objs/api.obj objs/tag.obj objs/vm.obj objs/common.obj objs/render.obj objs/sound.obj objs/font.obj objs/winmain.obj objs/d3drender.obj objs/d3d12render.obj objs/d3d11render.obj objs/d3d9render.obj objs/gdirender.obj objs/dsound.obj objs/dsvideo.obj objs/stdfile.obj objs/image.obj objs/glyph.obj objs/wave.obj objs/cpuid.obj objs/scalar.obj objs/sse.obj objs/sse2.obj objs/avx.obj objs/avx2.obj objs/lexer.yy.obj objs/parser.tab.obj objs/ast.obj objs/hir.obj objs/lir.obj objs/runtime.obj objs/interpreter.obj objs/intrinsics.obj objs/jit.obj

rm -rd vs-src/lib
mkdir vs-src/lib

cp libroot/lib-x86/libnoctvm.lib vs-src/lib/
cp libroot/lib-x86/zlib.lib vs-src/lib/
cp libroot/lib-x86/libpng.lib vs-src/lib/
cp libroot/lib-x86/jpeg.lib vs-src/lib/
cp libroot/lib-x86/libbz2.lib vs-src/lib/
cp libroot/lib-x86/libwebp.lib vs-src/lib/
cp libroot/lib-x86/libogg.lib vs-src/lib/
cp libroot/lib-x86/libvorbis.lib vs-src/lib/
cp libroot/lib-x86/freetype.lib vs-src/lib/

cp libroot/lib-x64/libnoctvm.lib vs-src/lib/
cp libroot/lib-x64/zlib.lib vs-src/lib/
cp libroot/lib-x64/libpng.lib vs-src/lib/
cp libroot/lib-x64/jpeg.lib vs-src/lib/
cp libroot/lib-x64/libbz2.lib vs-src/lib/
cp libroot/lib-x64/libwebp.lib vs-src/lib/
cp libroot/lib-x64/libogg.lib vs-src/lib/
cp libroot/lib-x64/libvorbis.lib vs-src/lib/
cp libroot/lib-x64/freetype.lib vs-src/lib/

cp libroot/lib-arm64/libnoctvm.lib vs-src/lib/
cp libroot/lib-arm64/zlib.lib vs-src/lib/
cp libroot/lib-arm64/libpng.lib vs-src/lib/
cp libroot/lib-arm64/jpeg.lib vs-src/lib/
cp libroot/lib-arm64/libbz2.lib vs-src/lib/
cp libroot/lib-arm64/libwebp.lib vs-src/lib/
cp libroot/lib-arm64/libogg.lib vs-src/lib/
cp libroot/lib-arm64/libvorbis.lib vs-src/lib/
cp libroot/lib-arm64/freetype.lib vs-src/lib/

rm -rf vs-src/res
mkdir vs-src/res
cp ../../resources/icon.ico vs-src/res/
cp ../../resources/manifest.xml vs-src/res/
cp ../../resources/resource.h vs-src/res/
cp ../../resources/resource.rc vs-src/res/
