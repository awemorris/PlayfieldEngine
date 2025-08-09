CONSOLE_CC=clang
CONSOLE_AR=ar
CONSOLE_CFLAGS="-O2"

#
# Make a source tree
#
src: unity-src

unity-src: libnoct2d-win64.dll libnoct2d-switch.a libnoct2d-ps5.a libnoct2d-xboxxs.lib
	@echo 'Making Unity source tree.'
	@rm -rf unity-src
	@mkdir unity-src
	@mkdir unity-src/Assets
	@mkdir unity-src/Assets/StreamingAssets
	@mkdir unity-src/Assets/Resources
	@cp -v ../../StratoHAL/src/NoctScript.cs unity-src/Assets/
	@cp -v ../../StratoHAL/src/NormalShader.shader unity-src/Assets/Resources/
	@cp -v ../../StratoHAL/src/AddShader.shader unity-src/Assets/Resources/
	@cp -v ../../StratoHAL/src/DimShader.shader unity-src/Assets/Resources/
	@cp -v ../../StratoHAL/src/RuleShader.shader unity-src/Assets/Resources/
	@cp -v ../../StratoHAL/src/MeltShader.shader unity-src/Assets/Resources/
	@mkdir unity-src/Assets/Plugins
	@mkdir unity-src/Assets/Plugins/x86_64
	@mkdir unity-src/Assets/Plugins/Switch
	@mkdir unity-src/Assets/Plugins/PS5
	@mkdir unity-src/Assets/Plugins/GameCoreXboxSeries
	@mkdir unity-src/Assets/Plugins/Common
	@cp libnoct2d-win64.dll unity-src/Assets/Plugins/x86_64/libnoct2d.dll
	@cp libnoct2d-switch.a unity-src/Assets/Plugins/Switch/libnoct2d.a
	@cp libnoct2d-ps5.a unity-src/Assets/Plugins/PS5/libnoct2d.a
	@cp libnoct2d-xboxxs.lib unity-src/Assets/Plugins/GameCoreXboxSeries/libnoct2d.lib
	@cp -v MainScene.unity unity-src/Assets/
	@cp README.md unity-src/
	@echo 'Done making Unity source tree.'
	@echo ''

#
# Plugin source tree
#

# unity-plugin-src.zip:
# 	@rm -rf unity-plugin-src
# 	@mkdir unity-plugin-src
# 	@mkdir unity-plugin-src/brotli
# 	@mkdir unity-plugin-src/freetype
# 	@mkdir unity-plugin-src/libogg
# 	@mkdir unity-plugin-src/libvorbis
# 	@mkdir unity-plugin-src/zlib
# 	@mkdir unity-plugin-src/bzip2
# 	@mkdir unity-plugin-src/jpeg
# 	@mkdir unity-plugin-src/libpng
# 	@mkdir unity-plugin-src/libwebp
# 	@tar xzf ../../StratoHAL/lib/archive/brotli-1.1.0.tar.gz -C unity-plugin-src/brotli --strip-components=1
# 	@tar xzf ../../StratoHAL/lib/archive/freetype-2.13.3.tar.gz -C unity-plugin-src/freetype --strip-components=1
# 	@tar xzf ../../StratoHAL/lib/archive/libogg-1.3.3.tar.gz -C unity-plugin-src/libogg --strip-components=1
# 	@tar xzf ../../StratoHAL/lib/archive/libvorbis-1.3.7.tar.gz -C unity-plugin-src/libvorbis --strip-components=1
# 	@tar xzf ../../StratoHAL/lib/archive/zlib-1.3.1.tar.gz -C unity-plugin-src/zlib --strip-components=1
# 	@tar xzf ../../StratoHAL/lib/archive/bzip2-1.0.6.tar.gz -C unity-plugin-src/bzip2 --strip-components=1
# 	@tar xzf ../../StratoHAL/lib/archive/jpegsrc.v9e.tar.gz -C unity-plugin-src/jpeg --strip-components=1
# 	@tar xzf ../../StratoHAL/lib/archive/libpng-1.6.43.tar.gz -C unity-plugin-src/libpng --strip-components=1
# 	@tar xzf ../../StratoHAL/lib/archive/libwebp-1.3.2.tar.gz -C unity-plugin-src/libwebp --strip-components=1
# 	@cp -R ../../src unity-plugin-src/
# 	@cp scripts/build-switch.bat unity-plugin-src/
# 	@cp scripts/build-ps5.bat unity-plugin-src/
# 	@cp scripts/build-xboxxs.bat unity-plugin-src/
# 	@zip -r -9 -q unity-plugin-src.zip unity-plugin-src

#
# Unity Native Plugin for Windows x86_64 (For Preview On Mac)
#
libnoct2d-win64.dll:
	@echo 'Building libnoct2d-win64.dll ...'
	@rm -rf libroot
	@../../StratoHAL/lib/build-libs.sh \
		"" \
		x86_64-w64-mingw32-gcc \
		"-O2 -g0 -fPIC" \
		x86_64-w64-mingw32-ar \
		$(shell readlink -f ../../StratoHAL/lib)
	@x86_64-w64-mingw32-gcc \
		-shared \
		-fPIC \
		-o libnoct2d-win64.dll \
		-O2 \
		-DUSE_UNITY \
		-DUSE_CSHARP \
		-DUSE_DLL \
		-I../../external/NoctLang/include \
		-I../../StratoHAL/include \
		-I../../include \
		-I../../src \
		-I./libroot/include \
		-I./libroot/include/png \
		-I./libroot/include/freetype2 \
		../../external/NoctLang/src/lexer.yy.c \
		../../external/NoctLang/src/parser.tab.c \
		../../external/NoctLang/src/ast.c \
		../../external/NoctLang/src/hir.c \
		../../external/NoctLang/src/lir.c \
		../../external/NoctLang/src/runtime.c \
		../../external/NoctLang/src/interpreter.c \
		../../external/NoctLang/src/execution.c \
		../../external/NoctLang/src/intrinsics.c \
		../../external/NoctLang/src/jit.c \
		../../external/NoctLang/src/gc.c \
		../../external/NoctLang/src/noct.c \
		../../StratoHAL/src/halwrap.c \
		../../StratoHAL/src/image.c \
		../../StratoHAL/src/glyph.c \
		../../StratoHAL/src/wave.c \
		../../src/main.c \
		../../src/api.c \
		../../src/vm.c \
		./libroot/lib/libfreetype.a \
		./libroot/lib/libpng.a \
		./libroot/lib/libjpeg.a \
		./libroot/lib/libwebp.a \
		./libroot/lib/libbrotlidec.a \
		./libroot/lib/libbrotlicommon.a \
		./libroot/lib/libvorbisfile.a \
		./libroot/lib/libvorbis.a \
		./libroot/lib/libogg.a \
		./libroot/lib/libbz2.a \
		./libroot/lib/libz.a
	@rm -rf libroot
	@echo 'Done building libnoct2d-win64.dll.'
	@echo ''

#
# Unity Native Plugin for Switch (by using an unofficial toolchain)
#
libnoct2d-switch.a:
	@echo 'Building libnoct2d-switch.a ...'
	@rm -rf libroot
	@../../StratoHAL/lib/build-libs.sh \
	    "" \
            ${HOME}/opt/LLVM/bin/clang \
            "-target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0" \
            ${HOME}/opt/LLVM/bin/llvm-ar \
            $(shell readlink -f ../../StratoHAL/lib)
	@rm -rf objs
	@mkdir objs
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/lexer.yy.c -o objs/lexer.yy.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/parser.tab.c -o objs/parser.tab.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/ast.c -o objs/ast.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/hir.c -o objs/hir.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/lir.c -o objs/lir.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/runtime.c -o objs/runtime.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/interpreter.c -o objs/interpreter.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/execution.c -o objs/execution.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/intrinsics.c -o objs/intrinsics.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/jit.c -o objs/jit.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/gc.c -o objs/gc.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/noct.c -o objs/noct.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include ../../StratoHAL/src/halwrap.c -o objs/halwrap.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include ../../StratoHAL/src/image.c -o objs/image.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include ../../StratoHAL/src/glyph.c -o objs/glyph.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include ../../StratoHAL/src/wave.c -o objs/wave.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include -I../../external/NoctLang/include -I../../include ../../src/main.c -o objs/main.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include -I../../external/NoctLang/include -I../../include ../../src/api.c -o objs/api.o
	@${HOME}/opt/LLVM/bin/clang -target aarch64-none-elf -mcpu=cortex-a57 -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include -I../../external/NoctLang/include -I../../include ../../src/vm.c -o objs/vm.o
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libfreetype.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libpng.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libjpeg.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libwebp.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libbrotlidec.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libbrotlicommon.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libvorbisfile.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libvorbis.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libogg.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libbz2.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libz.a
	@${HOME}/opt/LLVM/bin/llvm-ar rcs libnoct2d-switch.a objs/*.o
	@echo 'Done building libnoct2d-switch.a.'

#
# Unity Native Plugin for PlayStation5 (by using an unofficial toolchain)
#
libnoct2d-ps5.a:
	@echo 'Building libnoct2d-ps5.a ...'
	@rm -rf libroot
	@../../StratoHAL/lib/build-libs.sh \
	    "" \
            ${HOME}/opt/LLVM/bin/clang \
            "-target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0" \
            ${HOME}/opt/LLVM/bin/llvm-ar \
            $(shell readlink -f ../../StratoHAL/lib)
	@rm -rf objs
	@mkdir objs
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/lexer.yy.c -o objs/lexer.yy.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/parser.tab.c -o objs/parser.tab.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/ast.c -o objs/ast.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/hir.c -o objs/hir.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/lir.c -o objs/lir.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/runtime.c -o objs/runtime.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/interpreter.c -o objs/interpreter.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/execution.c -o objs/execution.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/intrinsics.c -o objs/intrinsics.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/jit.c -o objs/jit.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/gc.c -o objs/gc.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../external/NoctLang/include ../../external/NoctLang/src/noct.c -o objs/noct.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include ../../StratoHAL/src/halwrap.c -o objs/halwrap.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include ../../StratoHAL/src/image.c -o objs/image.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include ../../StratoHAL/src/glyph.c -o objs/glyph.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include ../../StratoHAL/src/wave.c -o objs/wave.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include -I../../external/NoctLang/include -I../../include ../../src/main.c -o objs/main.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include -I../../external/NoctLang/include -I../../include ../../src/api.c -o objs/api.o
	@${HOME}/opt/LLVM/bin/clang -target x86_64-unkown-freebsd -ffreestanding -nostdinc -nostdlib -I${PWD}/../../include/clang-include -O2 -g0 -c -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 -I../../StratoHAL/include -I../../external/NoctLang/include -I../../include ../../src/vm.c -o objs/vm.o
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libfreetype.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libpng.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libjpeg.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libwebp.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libbrotlidec.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libbrotlicommon.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libvorbisfile.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libvorbis.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libogg.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libbz2.a
	@cd objs && ${HOME}/opt/LLVM/bin/llvm-ar x ../libroot/lib/libz.a
	@${HOME}/opt/LLVM/bin/llvm-ar rcs libnoct2d-ps5.a objs/*.o
	@echo 'Done building libnoct2d-ps5.a.'

#
# Unity Native Plugin for Xbox Series X|S (by using an unofficial toolchain)
#
libnoct2d-xboxxs.lib:
	@echo 'Building libnoct2d-xboxxs.a ...'
	@rm -rf libroot
	@mkdir libroot
	@mkdir libroot/include
	@mkdir libroot/lib
	@echo 'Removing temporary directories...'
	@rm -rf zlib libpng jpeg libogg libvorbis freetype bzip2 libwebp
	@echo 'Building zlib...'
	@tar xzf ../../StratoHAL/lib/archive/zlib-1.3.1.tar.gz
	@mv zlib-1.3.1 zlib
	@cd zlib && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include adler32.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include infback.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include trees.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include compress.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include inffast.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include uncompr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include crc32.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include inflate.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include deflate.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include inftrees.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include zutil.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:zlib.lib adler32.obj infback.obj trees.obj compress.obj inffast.obj uncompr.obj crc32.obj inflate.obj deflate.obj inftrees.obj zutil.obj
	@cp zlib/zlib.h libroot/include/
	@cp zlib/zconf.h libroot/include/
	@cp zlib/zlib.lib libroot/lib/
	@rm -rf zlib
	@echo 'Building libpng...'
	@tar xzf ../../StratoHAL/lib/archive/libpng-1.6.43.tar.gz
	@mv libpng-1.6.43 libpng
	@cd libpng && \
	    cp scripts/pnglibconf.h.prebuilt pnglibconf.h && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngget.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngread.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngrutil.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngtrans.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngwtran.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include png.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngmem.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngrio.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngset.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngwio.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngwutil.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngerror.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngpread.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngrtran.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I../libroot/include pngwrite.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:libpng.lib pngget.obj pngread.obj pngrutil.obj pngtrans.obj pngwtran.obj png.obj pngmem.obj pngrio.obj pngset.obj pngwio.obj pngwutil.obj pngerror.obj pngpread.obj pngrtran.obj pngwrite.obj
	@mkdir libroot/include/png
	@cp libpng/*.h libroot/include/png/
	@cp libpng/libpng.lib libroot/lib/
	@rm -rf libpng
	@echo 'Building jpeg...'
	@tar xzf ../../StratoHAL/lib/archive/jpegsrc.v9e.tar.gz
	@mv jpeg-9e jpeg
	@cd jpeg && \
	    cp jconfig.txt jconfig.h && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include cdjpeg.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jaricom.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcapimin.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcapistd.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcarith.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jccoefct.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jccolor.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcdctmgr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jchuff.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcinit.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcmainct.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcmarker.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcmaster.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcomapi.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcparam.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcprepct.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jcsample.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jctrans.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdapimin.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdapistd.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdarith.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdatadst.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdatasrc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdcoefct.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdcolor.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jddctmgr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdhuff.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdinput.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdmainct.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdmarker.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdmaster.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdmerge.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdpostct.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdsample.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jdtrans.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jerror.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jfdctflt.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jfdctfst.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jfdctint.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jidctflt.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jidctfst.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jidctint.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jmemansi.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jmemmgr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jquant1.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jquant2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include jutils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include transupp.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:jpeg.lib cdjpeg.obj jaricom.obj jcapimin.obj jcapistd.obj jcarith.obj jccoefct.obj jccolor.obj jcdctmgr.obj jchuff.obj jcinit.obj jcmainct.obj jcmarker.obj jcmaster.obj jcomapi.obj jcparam.obj jcprepct.obj jcsample.obj jctrans.obj jdapimin.obj jdapistd.obj jdarith.obj jdatadst.obj jdatasrc.obj jdcoefct.obj jdcolor.obj jddctmgr.obj jdhuff.obj jdinput.obj jdmainct.obj jdmarker.obj jdmaster.obj jdmerge.obj jdpostct.obj jdsample.obj jdtrans.obj jerror.obj jfdctflt.obj jfdctfst.obj jfdctint.obj jidctflt.obj jidctfst.obj jidctint.obj jmemansi.obj jmemmgr.obj jquant1.obj jquant2.obj jutils.obj transupp.obj
	@mkdir libroot/include/jpeg
	@cp jpeg/*.h libroot/include/jpeg/
	@cp jpeg/jpeg.lib libroot/lib/
	@rm -rf jpeg
	@echo 'Building bzip2...'
	@tar xzf ../../StratoHAL/lib/archive/bzip2-1.0.6.tar.gz
	@mv bzip2-1.0.6 bzip2
	@cd bzip2 && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include blocksort.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include compress.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include decompress.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include huffman.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include randtable.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include bzlib.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include crctable.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:libbz2.lib blocksort.obj compress.obj decompress.obj huffman.obj randtable.obj bzlib.obj crctable.obj
	@cp bzip2/bzlib.h libroot/include/
	@cp bzip2/libbz2.lib libroot/lib/
	@rm -rf bzip2
	@echo 'Building libwebp...'
	@tar xzf ../../StratoHAL/lib/archive/libwebp-1.3.2.tar.gz
	@mv libwebp-1.3.2 libwebp
	@cd libwebp && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/alpha_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/buffer_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/frame_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/idec_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/io_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/quant_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/tree_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/vp8_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/vp8l_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dec/webp_dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/demux/anim_decode.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/demux/demux.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/alpha_processing.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/alpha_processing_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/alpha_processing_sse41.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/alpha_processing_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/cost.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/cost_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/cost_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/cpu.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/dec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/dec_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/dec_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/dec_sse41.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/dec_clip_tables.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/filters.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/filters_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/filters_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/lossless.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/lossless_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/lossless_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/lossless_sse41.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/lossless_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/lossless_enc_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/lossless_enc_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/lossless_enc_sse41.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/rescaler.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/rescaler_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/rescaler_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/ssim.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/ssim_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/upsampling.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/upsampling_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/upsampling_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/upsampling_sse41.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/yuv.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/yuv_neon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/yuv_sse2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/dsp/yuv_sse41.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/alpha_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/analysis_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/backward_references_cost_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/backward_references_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/config_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/cost_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/filter_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/frame_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/histogram_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/iterator_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/near_lossless_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/picture_csp_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/picture_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/picture_psnr_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/picture_rescale_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/picture_tools_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/predictor_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/quant_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/syntax_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/token_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/tree_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/vp8l_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/enc/webp_enc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/mux/anim_encode.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/mux/muxedit.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/mux/muxinternal.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/mux/muxread.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/bit_reader_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/bit_writer_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/color_cache_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/filters_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/huffman_encode_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/huffman_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/quant_levels_dec_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/quant_levels_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/random_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/rescaler_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/thread_utils.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./ src/utils/utils.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:libwebp.lib alpha_dec.obj buffer_dec.obj frame_dec.obj idec_dec.obj io_dec.obj quant_dec.obj tree_dec.obj vp8_dec.obj vp8l_dec.obj webp_dec.obj anim_decode.obj demux.obj alpha_processing.obj cost.obj cost_neon.obj cost_sse2.obj cpu.obj dec.obj dec_neon.obj dec_sse2.obj dec_sse41.obj dec_clip_tables.obj enc.obj filters.obj filters_neon.obj filters_sse2.obj lossless.obj lossless_neon.obj lossless_sse2.obj lossless_sse41.obj lossless_enc.obj lossless_enc_neon.obj lossless_enc_sse2.obj lossless_enc_sse41.obj rescaler.obj rescaler_neon.obj rescaler_sse2.obj ssim.obj ssim_sse2.obj upsampling.obj upsampling_neon.obj upsampling_sse2.obj upsampling_sse41.obj yuv.obj yuv_neon.obj yuv_sse2.obj yuv_sse41.obj alpha_enc.obj analysis_enc.obj backward_references_cost_enc.obj backward_references_enc.obj config_enc.obj cost_enc.obj filter_enc.obj frame_enc.obj histogram_enc.obj iterator_enc.obj near_lossless_enc.obj picture_csp_enc.obj picture_enc.obj picture_psnr_enc.obj picture_rescale_enc.obj picture_tools_enc.obj predictor_enc.obj quant_enc.obj syntax_enc.obj token_enc.obj tree_enc.obj vp8l_enc.obj webp_enc.obj anim_encode.obj muxedit.obj muxinternal.obj muxread.obj bit_reader_utils.obj bit_writer_utils.obj color_cache_utils.obj filters_utils.obj huffman_encode_utils.obj huffman_utils.obj quant_levels_dec_utils.obj quant_levels_utils.obj random_utils.obj rescaler_utils.obj thread_utils.obj utils.obj alpha_processing_sse2.obj alpha_processing_sse41.obj alpha_processing_neon.obj
	@mkdir libroot/include/webp
	@cp libwebp/src/webp/* libroot/include/webp/
	@cp libwebp/libwebp.lib libroot/lib/
	@rm -rf libwebp
	@echo 'Building libogg...'
	@tar xzf ../../StratoHAL/lib/archive/libogg-1.3.3.tar.gz
	@mv libogg-1.3.3 libogg
	@cd libogg && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include src/bitwise.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include src/framing.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:libogg.lib bitwise.obj framing.obj
	@cp -R libogg/include/ogg libroot/include/ogg
	@cp libogg/libogg.lib libroot/lib/
	@rm -rf libogg
	@echo 'Building libvorbis...'
	@tar xzf ../../StratoHAL/lib/archive/libvorbis-1.3.7.tar.gz
	@mv libvorbis-1.3.7 libvorbis
	@cd libvorbis && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/analysis.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/bitrate.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/block.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/codebook.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/envelope.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/floor0.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/floor1.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/info.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/lookup.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/lpc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/lsp.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/mapping0.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/mdct.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/psy.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/registry.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/res0.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/sharedbook.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/smallft.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/synthesis.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/vorbisenc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/vorbisfile.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /I./include /I./lib /I../libroot/include lib/window.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:libvorbis.lib analysis.obj bitrate.obj block.obj codebook.obj envelope.obj floor0.obj floor1.obj info.obj lookup.obj lpc.obj lsp.obj mapping0.obj mdct.obj psy.obj registry.obj res0.obj sharedbook.obj smallft.obj synthesis.obj vorbisenc.obj window.obj && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:libvorbisfile.lib vorbisfile.obj
	@cp -R libvorbis/include/vorbis libroot/include/vorbis
	@cp libvorbis/libvorbis.lib libroot/lib/
	@cp libvorbis/libvorbisfile.lib libroot/lib/
	@rm -rf libvorbis
	@echo 'Building freetype...'
	@tar xzf ../../StratoHAL/lib/archive/freetype-2.13.3.tar.gz
	@mv freetype-2.13.3 freetype
	@cd freetype && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftadvanc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftbase.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftbbox.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftbdf.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftbitmap.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftcalc.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftcid.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftcolor.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftdbgmem.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftdebug.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/fterrors.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftfntfmt.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftfstype.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftgasp.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftgloadr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftglyph.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftgxval.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/fthash.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftinit.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftlcdfil.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftmac.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftmm.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftobjs.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftotval.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftoutln.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftpatent.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftpfr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftpsprop.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftrfork.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftsnames.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftstream.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftstroke.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftsynth.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftsystem.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/fttrigon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/fttype1.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftutil.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftwinfnt.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/md5.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/bdf/bdf.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/bdf/bdfdrivr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/bdf/bdflib.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/bzip2/ftbzip2.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcache.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcbasic.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftccache.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftccmap.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcglyph.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcimage.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcmanag.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcmru.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcsbits.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cff.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffcmap.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffdrivr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffgload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffobjs.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffparse.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidgload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidobjs.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidparse.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidriver.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/type1cid.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvalid.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvbase.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvcommn.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvgdef.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvgpos.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvgsub.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvjstf.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvmath.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvmod.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrcmap.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrdrivr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrgload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrobjs.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrsbit.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/afmparse.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/cffdecode.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psarrst.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psaux.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psauxmod.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psblues.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psconv.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/pserror.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psfont.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psft.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/pshints.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psintrp.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psobjs.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psread.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psstack.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/t1decode.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/t1cmap.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshalgo.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshglob.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshinter.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshmod.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshrec.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psnames/psmodule.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psnames/psnames.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/raster/ftraster.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sdf/ftbsdf.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sdf/ftsdf.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sdf/ftsdfcommon.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sdf/ftsdfrend.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/pngshim.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/sfdriver.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/sfobjs.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttbdf.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttcmap.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttcolr.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttcpal.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttkern.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttmtx.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttpost.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttsbit.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttsvg.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/sfwoff.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/smooth/ftgrays.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/smooth/ftsmooth.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/svg/ftsvg.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/truetype.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttdriver.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttgload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttgxvar.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttinterp.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttobjs.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttpload.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/winfonts/winfnt.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/adler32.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/crc32.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/ftgzip.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/inffast.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/inftrees.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/zutil.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/lzw/ftlzw.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pcf/pcf.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/autofit/autofit.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/type1/type1.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/type42/type42.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/raster/raster.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /O2 /I../../../include/msvc-include /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/svg/svg.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:freetype.lib ftadvanc.obj ftbase.obj ftbbox.obj ftbdf.obj ftbitmap.obj ftcalc.obj ftcid.obj ftcolor.obj ftdbgmem.obj ftdebug.obj fterrors.obj ftfntfmt.obj ftfstype.obj ftgasp.obj ftgloadr.obj ftglyph.obj ftgxval.obj fthash.obj ftinit.obj ftlcdfil.obj ftmac.obj ftmm.obj ftotval.obj ftoutln.obj ftpatent.obj ftpfr.obj ftpsprop.obj ftrfork.obj ftsnames.obj ftstream.obj ftstroke.obj ftsynth.obj ftsystem.obj fttrigon.obj fttype1.obj ftutil.obj ftwinfnt.obj md5.obj bdfdrivr.obj bdflib.obj ftbzip2.obj ftcbasic.obj ftccache.obj ftccmap.obj ftcglyph.obj ftcimage.obj ftcmanag.obj ftcmru.obj ftcsbits.obj cffcmap.obj cffdrivr.obj cffgload.obj cffload.obj cffobjs.obj cffparse.obj cidgload.obj cidload.obj cidobjs.obj cidparse.obj type1cid.obj otvalid.obj otvbase.obj otvcommn.obj otvgdef.obj otvgpos.obj otvgsub.obj otvjstf.obj otvmath.obj pfrcmap.obj pfrdrivr.obj pfrgload.obj pfrload.obj pfrobjs.obj pfrsbit.obj afmparse.obj cffdecode.obj psarrst.obj psauxmod.obj psblues.obj psconv.obj pserror.obj psfont.obj psft.obj pshints.obj psintrp.obj psobjs.obj psread.obj psstack.obj pshalgo.obj pshglob.obj pshmod.obj pshrec.obj psmodule.obj t1decode.obj t1cmap.obj ftraster.obj ftbsdf.obj ftsdf.obj ftsdfcommon.obj ftsdfrend.obj pngshim.obj sfdriver.obj sfobjs.obj ttbdf.obj ttcmap.obj ttcolr.obj ttcpal.obj ttkern.obj ttload.obj ttmtx.obj ttpost.obj ttsbit.obj ttsvg.obj sfwoff.obj ftgrays.obj ftsmooth.obj ftsvg.obj ttdriver.obj ttgload.obj ttgxvar.obj ttinterp.obj ttobjs.obj ttpload.obj winfnt.obj adler32.obj crc32.obj ftgzip.obj inffast.obj inftrees.obj zutil.obj ftlzw.obj pcf.obj autofit.obj type1.obj type42.obj raster.obj
	@cp -R freetype/include/freetype libroot/include/freetype
	@cp -R freetype/include/freetype/config libroot/include/freetype/config
	@cp freetype/include/ft2build.h libroot/include/
	@cp freetype/freetype.lib libroot/lib/
	@rm -rf freetype
	@echo 'Building libnoct2d_proto.lib...'
	@rm -rf objs
	@mkdir objs
	@cd objs && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../StratoHAL/include /I../../../src -I../../../include ../../../src/main.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../StratoHAL/include /I../../../src -I../../../include ../../../src/api.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include /I../../../StratoHAL/include /I../../../src -I../../../include ../../../src/vm.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /DUSE_UNITY /DUSE_CSHARP /DUSE_DLL /I../../../StratoHAL/include /I../libroot/include ../../../StratoHAL/src/halwrap.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /DUSE_UNITY /DUSE_CSHARP /DUSE_DLL /I../../../StratoHAL/include /I../libroot/include ../../../StratoHAL/src/glyph.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /DUSE_UNITY /DUSE_CSHARP /DUSE_DLL /I../../../StratoHAL/include /I../libroot/include ../../../StratoHAL/src/wave.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /DUSE_UNITY /DUSE_CSHARP /DUSE_DLL /I../../../StratoHAL/include /I../libroot/include ../../../StratoHAL/src/image.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /DYY_NO_UNISTD_H /I../../../external/NoctLang/include ../../../external/NoctLang/src/lexer.yy.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/parser.tab.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/ast.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/hir.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/lir.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/runtime.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/interpreter.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/execution.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/intrinsics.c && \
	    ${HOME}/opt/LLVM/bin/clang-cl /nologo /c /MT /O2 /I../../../include/msvc-include /DUNICODE /D_UNICODE /I../../../external/NoctLang/include ../../../external/NoctLang/src/jit.c && \
	    ${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:libnoct2d_proto.lib halwrap.obj glyph.obj wave.obj image.obj lexer.yy.obj parser.tab.obj ast.obj hir.obj lir.obj runtime.obj interpreter.obj intrinsics.obj jit.obj main.obj api.obj vm.obj
	@echo 'Merging libraries...'
	@${HOME}/opt/LLVM/bin/llvm-lib /nologo /OUT:libnoct2d-xboxxs.lib objs/libnoct2d_proto.lib libroot/lib/zlib.lib libroot/lib/libpng.lib libroot/lib/jpeg.lib libroot/lib/libwebp.lib libroot/lib/libogg.lib libroot/lib/libvorbisfile.lib libroot/lib/libvorbis.lib libroot/lib/freetype.lib
	@rm -rf objs
	@rm -rf libroot

#
# Cleanup
#
clean:
	@rm -rf unity-src libnoct2d-win64.dll libnoct2d-switch.a libnoct2d-ps5.a libnoct2d-xboxxs.lib unity-plugin-src.zip unity-plugin-src
