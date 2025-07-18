all: NoctVM.dmg

NoctVM.dmg: libroot/lib/libnoctvm.a
	@echo "Building NoctVM.app"
	@cp libroot/lib/libnoctvm.a macos/
	@rm -rf build
	@echo 'Archiving...'
	@xcodebuild \
		-quiet \
		-scheme NoctVM \
		-project macos.xcodeproj \
		-configuration Release \
		-archivePath `pwd`/build/Release/NoctVM.xcarchive \
		archive
	@echo 'Exporting...'
	@xcodebuild \
		-quiet \
		-exportArchive \
		-archivePath `pwd`/build/Release/NoctVM.xcarchive \
		-exportOptionsPlist ExportOptions.plist
	@echo 'Notarizing...'
	@until \
		xcodebuild \
			-quiet \
			-exportNotarizedApp \
			-archivePath `pwd`/build/Release/NoctVM.xcarchive \
			-exportPath `pwd`/build/Release; \
	do \
		echo \"Waiting 10 seconds for notarization...\"; \
		sleep 10; \
	done
	@echo "Successfully notarized."
	@rm -f NoctVM.dmg
	@rm -rf tmp
	@mkdir -p tmp
	@cp -Rv build/Release/NoctVM.app tmp/NoctVM.app
	@hdiutil create -fs HFS+ -format UDBZ -srcfolder tmp -volname NoctVM NoctVM.dmg
	@codesign --sign 'Developer ID Application' NoctVM.dmg
	@rm -rf tmp

src: libroot/lib/libnoctvm.a
	@mkdir -p macos-src/lib
	@mkdir -p macos-src/Resources/
	@touch macos-src/Resources/COPY_ASSETS_HERE
	@cp libroot/lib/* macos-src/macos/
	@cp libroot/lib/libnoctvm.a macos-src/macos/
	@cp libroot/lib/libbrotlicommon.a macos-src/macos/
	@cp libroot/lib/libfreetype.a macos-src/macos/
	@cp libroot/lib/libogg.a macos-src/macos/
	@cp libroot/lib/libvorbisfile.a macos-src/macos/
	@cp libroot/lib/libbrotlidec.a macos-src/macos/
	@cp libroot/lib/libpng.a macos-src/macos/
	@cp libroot/lib/libwebp.a macos-src/macos/
	@cp libroot/lib/libbz2.a macos-src/macos/
	@cp libroot/lib/libjpeg.a macos-src/macos/
	@cp libroot/lib/libvorbis.a macos-src/macos/
	@cp libroot/lib/libz.a macos-src/macos/
	@cp ../../src/platform/GameShaders.metal macos-src/macos/
	@cp ../../src/platform/GameShaderTypes.h macos-src/macos/

libroot/lib/libnoctvm.a:
	@./build-libs.sh

clean:
	@rm -rf build libroot* objs NoctVM.dmg macos/libnoctvm.a macos.xcodeproj/project.xcworkspace/xcuserdata macos/libbrotlicommon.a macos/libbrotlidec.a macos/libbz2.a macos/libfreetype.a macos/libjpeg.a macos/libogg.a macos/libpng.a macos/libvorbis.a macos/libvorbisfile.a macos/libwebp.a macos/libz.a
