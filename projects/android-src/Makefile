SRCS=\
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
    ../../external/StratoHAL/src/ndkfile.c \
    ../../external/StratoHAL/src/image.c \
    ../../external/StratoHAL/src/slsound.c \
    ../../external/StratoHAL/src/glyph.c \
    ../../external/StratoHAL/src/wave.c \
    ../../external/StratoHAL/src/ndkmain.c \
    ../../external/StratoHAL/src/glrender.c \
    ../../src/main.c \
    ../../src/api.c \
    ../../src/vm.c

src: libnoctvm-aarch64.so libnoctvm-armv7a.so libnoctvm-x86_64.so libnoctvm-i686.so
	@rm -rf app/build app/.cxx app/src/main/cpp app/src/main/java app/src/main/assets android-src
	@mkdir -p android-src
	@mkdir -p android-src/app/src/main/cpp
	@mkdir -p android-src/app/src/main/assets
	@
	@cp -R app android-src/
	@cp -R gradle.properties android-src/
	@cp -R build.gradle android-src/
	@cp -R gradlew android-src/
	@cp -R settings.gradle android-src/
	@cp -R gradlew.bat android-src/
	@cp -R gradle android-src/
	@
	@cp -R build.bat android-src/
	@
	@mkdir -p android-src/app/src/main/java/com/noctvm/engineandroid
	@cp ../../external/StratoHAL/src/MainActivity.java android-src/app/src/main/java/com/noctvm/engineandroid/
	@
	@mkdir -p android-src/app/src/main/jniLibs/arm64-v8a
	@cp libnoctvm-aarch64.so android-src/app/src/main/jniLibs/arm64-v8a/libnoctvm.so
	@mkdir -p android-src/app/src/main/jniLibs/armeabi-v7a
	@cp libnoctvm-armv7a.so android-src/app/src/main/jniLibs/armeabi-v7a/libnoctvm.so
	@mkdir -p android-src/app/src/main/jniLibs/x86_64
	@cp libnoctvm-x86_64.so android-src/app/src/main/jniLibs/x86_64/libnoctvm.so
	@mkdir -p android-src/app/src/main/jniLibs/x86
	@cp libnoctvm-i686.so android-src/app/src/main/jniLibs/x86/libnoctvm.so

libnoctvm-aarch64.so: ndk
	@echo 'Building aarch64 library...'
	@../../external/StratoHAL/lib/build-libs.sh aarch64 `pwd`/ndk/bin/clang-18 "--target=aarch64-linux-android21 -O2 -g0 -fPIC" `pwd`/ndk/bin/llvm-ar `readlink -f ../../external/StratoHAL/lib`
	@`pwd`/ndk/bin/clang-18 \
		--target=aarch64-linux-android21 \
		-O2 \
		-shared \
		-fPIC \
		-o libnoctvm-aarch64.so \
		-DUSE_DLL \
		-I../../external/StratoHAL/include \
		-I../../external/NoctLang/include \
		-I./libroot-aarch64/include \
		-I./libroot-aarch64/include/png \
		-I./libroot-aarch64/include/freetype2 \
		$(SRCS) \
		-lm \
		-lGLESv3 \
		-lOpenSLES \
		-llog \
		-L./libroot-aarch64/lib \
		-lfreetype \
		-lwebp \
		-lpng \
		-ljpeg \
		-lbrotlidec \
		-lbrotlicommon \
		-lvorbisfile \
		-lvorbis \
		-logg \
		-lbz2 \
		-lz

libnoctvm-armv7a.so: ndk
	@echo 'Building armv7a library...'
	@../../external/StratoHAL/lib/build-libs.sh armv7a `pwd`/ndk/bin/clang-18 "--target=armv7a-linux-androideabi21 -O2 -g0 -fPIC" `pwd`/ndk/bin/llvm-ar `readlink -f ../../external/StratoHAL/lib`
	@`pwd`/ndk/bin/clang-18 \
		--target=armv7a-linux-android21 \
		-O2 \
		-shared \
		-fPIC \
		-o libnoctvm-armv7a.so \
		-DUSE_DLL \
		-I../../external/StratoHAL/include \
		-I../../external/NoctLang/include \
		-I./libroot-armv7a/include \
		-I./libroot-armv7a/include/png \
		-I./libroot-armv7a/include/freetype2 \
		$(SRCS) \
		-lm \
		-lGLESv3 \
		-lOpenSLES \
		-llog \
		-L./libroot-armv7a/lib \
		-lfreetype \
		-lwebp \
		-lpng \
		-ljpeg \
		-lbrotlidec \
		-lbrotlicommon \
		-lvorbisfile \
		-lvorbis \
		-logg \
		-lbz2 \
		-lz

libnoctvm-x86_64.so: ndk
	@echo 'Building x86_64 library...'
	@../../external/StratoHAL/lib/build-libs.sh x86_64 `pwd`/ndk/bin/clang-18 "--target=x86_64-linux-android21 -O2 -g0 -fPIC" `pwd`/ndk/bin/llvm-ar `readlink -f ../../external/StratoHAL/lib`
	@`pwd`/ndk/bin/clang-18 \
		--target=x86_64-linux-android21 \
		-O2 \
		-shared \
		-fPIC \
		-o libnoctvm-x86_64.so \
		-DUSE_DLL \
		-I../../external/StratoHAL/include \
		-I../../external/NoctLang/include \
		-I./libroot-x86_64/include \
		-I./libroot-x86_64/include/png \
		-I./libroot-x86_64/include/freetype2 \
		$(SRCS) \
		-lm \
		-lGLESv3 \
		-lOpenSLES \
		-llog \
		-L./libroot-x86_64/lib \
		-lfreetype \
		-lwebp \
		-lpng \
		-ljpeg \
		-lbrotlidec \
		-lbrotlicommon \
		-lvorbisfile \
		-lvorbis \
		-logg \
		-lbz2 \
		-lz

libnoctvm-i686.so: ndk
	@echo 'Building i686 library...'
	@../../external/StratoHAL/lib/build-libs.sh i686 `pwd`/ndk/bin/clang-18 "--target=i686-linux-android21 -O2 -g0 -fPIC" `pwd`/ndk/bin/llvm-ar `readlink -f ../../external/StratoHAL/lib`
	@`pwd`/ndk/bin/clang-18 \
		--target=i686-linux-android21 \
		-O2 \
		-shared \
		-fPIC \
		-o libnoctvm-i686.so \
		-DUSE_DLL \
		-I../../external/StratoHAL/include \
		-I../../external/NoctLang/include \
		-I./libroot-i686/include \
		-I./libroot-i686/include/png \
		-I./libroot-i686/include/freetype2 \
		$(SRCS) \
		-lm \
		-lGLESv3 \
		-lOpenSLES \
		-llog \
		-L./libroot-i686/lib \
		-lfreetype \
		-lwebp \
		-lpng \
		-ljpeg \
		-lbrotlidec \
		-lbrotlicommon \
		-lvorbisfile \
		-lvorbis \
		-logg \
		-lbz2 \
		-lz

ndk:
	@if [ "`uname -a | grep Linux`" != "" ]; then \
		curl -O https://dl.google.com/android/repository/android-ndk-r27-linux.zip; \
		unzip android-ndk-r27-linux.zip; \
		mv 'android-ndk-r27/toolchains/llvm/prebuilt/linux-x86_64' ndk; \
		chmod -R +x ./ndk/bin/*; \
		rm -rf 'android-ndk-r27' android-ndk-r27-linux.zip; \
	elif [ "`uname -a | grep Darwin`" != "" ]; then \
		curl -O https://dl.google.com/android/repository/android-ndk-r27-darwin.dmg; \
		7z x android-ndk-r27-darwin.dmg; \
		mv 'Android NDK r27/AndroidNDK12077973.app/Contents/NDK/toolchains/llvm/prebuilt/darwin-x86_64' ndk; \
		chmod -R +x ./ndk/bin/*; \
		rm ndk/bin/ld.lld; \
		ln -s lld ndk/bin/ld.lld; \
		rm -rf 'Android NDK r27'; \
	else \
		curl -O https://dl.google.com/android/repository/android-ndk-r27-windows.zip; \
		unzip android-ndk-r27-windows.zip; \
		mv 'android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64' ndk; \
		chmod -R +x ./ndk/bin/*; \
		rm -rf 'android-ndk-r27' android-ndk-r27-windows.zip; \
	fi

clean:
	@rm -rf android-src android-ndk-r27-darwin.dmg android-ndk-r27-linux.zip ndk libroot-* libnoctvm-*.so
