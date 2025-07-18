SRCS = \
    ../../external/NoctLang/src/lexer.yy.c \
    ../../external/NoctLang/src/parser.tab.c \
    ../../external/NoctLang/src/ast.c \
    ../../external/NoctLang/src/hir.c \
    ../../external/NoctLang/src/lir.c \
    ../../external/NoctLang/src/runtime.c \
    ../../external/NoctLang/src/interpreter.c \
    ../../external/NoctLang/src/execution.c \
    ../../external/NoctLang/src/intrinsics.c \
    ../../external/NoctLang/src/jit-common.c \
    ../../external/StratoHAL/src/stdfile.c \
    ../../external/StratoHAL/src/image.c \
    ../../external/StratoHAL/src/glyph.c \
    ../../external/StratoHAL/src/wave.c \
    ../../external/StratoHAL/src/emmain.c \
    ../../external/StratoHAL/src/alsound.c \
    ../../external/StratoHAL/src/glrender.c \
    ../../src/main.c \
    ../../src/api.c \
    ../../src/vm.c \
    ../../src/translation.c

all: index.html

index.html: $(SRCS)
	@tar xzf ../../external/StratoHAL/lib/archive/libwebp-1.3.2.tar.gz
	@rm -f html/index.*
	@emcc \
		-O2 \
		-o index.html \
		-I../../external/NoctLang/include \
		-I../../external/StratoHAL/include \
		-I../../src \
		-I./libwebp-1.3.2 \
		-I./libwebp-1.3.2/src \
		$(SRCS) \
		libwebp-1.3.2/src/**/*.c \
		-s USE_ZLIB=1 \
		-s USE_LIBPNG=1 \
		-s USE_OGG=1 \
		-s USE_VORBIS=1 \
		-s USE_FREETYPE=1 \
		-s USE_LIBJPEG=1 \
		-s TOTAL_MEMORY=536870912 \
		-s NO_EXIT_RUNTIME=1 \
		-s EXPORTED_RUNTIME_METHODS=["ccall","UTF8ToString"] \
		-lz \
		-lpng \
		-logg \
		-lvorbis \
		-lfreetype \
		-lopenal \
		-lidbfs.js \
		--shell-file shell.html \
		--pre-js pre.js \
		--use-preload-plugins

clean:
	@rm -rf index.html index.js index.wasm libwebp-1.3.2
