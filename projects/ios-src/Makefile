all: src

src:
	@./build-libs.sh
	@rm -rf ios-src
	@mkdir ios-src
	@mkdir ios-src/ios
	@cp -R ios/Assets.xcassets ios-src/ios/
	@cp ios/Main.storyboard ios-src/ios/
	@cp ios/ios.entitlements ios-src/ios/
	@cp ios/entry.c ios-src/ios/
	@cp ios/libnoctvm-device.a ios-src/ios/
	@cp ios/libnoctvm-sim.a ios-src/ios/
	@cp ios/GameShaders.metal ios-src/ios/
	@cp ios/GameShaderTypes.h ios-src/ios/
	@mkdir ios-src/Resources/
	@mkdir ios-src/Resources/video
	@mkdir ios-src/ios.xcodeproj
	@cp ios.xcodeproj/project.pbxproj ios-src/ios.xcodeproj/

clean:
	@rm -rf build libroot* objs ios-src ios-src/libnoctvm.a ios-src/libnoctvm-device.a ios-src/libnoctvm-sim.a ios.xcodeproj/project.xcworkspace/xcuserdata  libnoctvm-sim-arm64.a libnoctvm-sim-x86_64.a ios/libnoctvm-device.a ios/libnoctvm-sim.a
