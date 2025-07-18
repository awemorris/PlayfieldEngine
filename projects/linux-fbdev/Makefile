CC=cc
LD=ld
AR=ar
STRIP=strip

CPPFLAGS=\
	-DUSE_LINUXFB \
	-I../../external/NoctLang/include \
	-I../../external/StratoHAL/include \
	-I../../src \
	-I./libroot/include

CFLAGS=\
	-O2 \
	-g0 \
	-ffast-math \
	-ftree-vectorize \
	-std=gnu11 \
	-Wall \
	-Werror \
	-Wextra \
	-Wundef \
	-Wconversion \
	-Wno-multichar \
	-Wno-strict-aliasing \
	-Wno-format-truncation

LDFLAGS=\
	./libroot/lib/libpng.a \
	./libroot/lib/libjpeg.a \
	./libroot/lib/libwebp.a \
	./libroot/lib/libfreetype.a \
	./libroot/lib/libvorbisfile.a \
	./libroot/lib/libvorbis.a \
	./libroot/lib/libogg.a \
	./libroot/lib/libbrotlidec.a \
	./libroot/lib/libbrotlicommon.a \
	./libroot/lib/libbz2.a \
	./libroot/lib/libz.a \
	-lasound \
	-lm

OBJS_LANG=\
	objs/lexer.yy.o \
	objs/parser.tab.o \
	objs/ast.o \
	objs/hir.o \
	objs/lir.o \
	objs/runtime.o \
	objs/interpreter.o \
	objs/execution.o \
	objs/intrinsics.o \
	objs/jit-common.o

OBJS_PLATFORM=\
	objs/fbmain.o \
	objs/asound.o \
	objs/stdfile.o \
	objs/image.o \
	objs/glyph.o \
	objs/wave.o

OBJS_ENGINE=\
	objs/main.o \
	objs/api.o \
	objs/vm.o

OBJS_TOP=

#
# Main Target
#

all: noctvm

noctvm: $(OBJS_LANG) $(OBJS_PLATFORM) $(OBJS_ENGINE) $(OBJS_TOP)
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)

#
# src/language
#

objs/lexer.yy.o: ../../external/NoctLang/src/lexer.yy.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) -Wno-sign-conversion -Wno-sign-compare -Wno-conversion $<

objs/parser.tab.o: ../../external/NoctLang/src/parser.tab.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/ast.o: ../../external/NoctLang/src/ast.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/hir.o: ../../external/NoctLang/src/hir.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/lir.o: ../../external/NoctLang/src/lir.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/runtime.o: ../../external/NoctLang/src/runtime.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/interpreter.o: ../../external/NoctLang/src/interpreter.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/intrinsics.o: ../../external/NoctLang/src/intrinsics.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-common.o: ../../external/NoctLang/src/jit-common.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# src/platform
#

objs/fbmain.o: ../../external/StratoHAL/src/fbmain.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/asound.o: ../../external/StratoHAL/src/asound.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/stdfile.o: ../../external/StratoHAL/src/stdfile.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/image.o: ../../external/StratoHAL/src/image.c libroot
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/glyph.o: ../../external/StratoHAL/src/glyph.c libroot
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/wave.o: ../../external/StratoHAL/src/wave.c libroot
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# engine
#

objs/main.o: ../../src/main.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/api.o: ../../src/api.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/vm.o: ../../src/vm.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# libroot
#

libroot:
	@../../lib/build-libs.sh "" $(CC) "-O2 -g0" $(AR) ../../lib

#
# Phony
#

clean:
	rm -rf libroot objs noctvm
