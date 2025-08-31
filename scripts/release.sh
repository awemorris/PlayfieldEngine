#!/bin/sh

set -eu

# Check that git-diff is empty.
if git diff --quiet; then
    echo "Repository is clean.";
    git push github main;
else
    echo "Repository is dirty.";
    exit 1;
fi    

rm -rf dist PicoPico-Script.zip
mkdir dist

#
# Windows x86
#

# Build.
rm -rf build-win-x86
cmake --preset windows-x86
cmake --build --preset windows-x86

# Strip.
i686-w64-mingw32-strip build-win-x86/picopico.exe
i686-w64-mingw32-strip build-win-x86/picopico-pack.exe
i686-w64-mingw32-strip build-win-x86/picopico-web.exe

# Copy.
mkdir                                  dist/windows-x86
cp build-win-x86/picopico.exe          dist/windows-x86/
cp build-win-x86/picopico-pack.exe     dist/windows-x86/
cp SAMPLES/bouncer/main.noct           dist/windows-x86/
mkdir                                  dist/wasm
cp build-win-x86/picopico-web.exe      dist/wasm/

rm -rf build-win-x86

#
# Windows x86_64
#

# Build.
rm -rf build-win-x86_64
cmake --preset windows-x86_64
cmake --build --preset windows-x86_64

# Strip.
x86_64-w64-mingw32-strip build-win-x86_64/picopico.exe
x86_64-w64-mingw32-strip build-win-x86_64/picopico-pack.exe

# Copy.
mkdir                                   dist/windows-x86_64
cp build-win-x86_64/picopico.exe        dist/windows-x86_64/
cp build-win-x86_64/picopico-pack.exe   dist/windows-x86_64/
cp SAMPLES/bouncer/main.noct            dist/windows-x86_64/

rm -rf build-win-x86_64

#
# Windows arm64
#

# Build.
rm -rf build-win-arm64
cmake --preset windows-arm64
cmake --build --preset windows-arm64

# Strip.
aarch64-w64-mingw32-strip build-win-arm64/picopico.exe
aarch64-w64-mingw32-strip build-win-arm64/picopico-pack.exe

# Copy.
mkdir                                   dist/windows-arm64
cp build-win-arm64/picopico.exe         dist/windows-arm64/
cp build-win-arm64/picopico-pack.exe    dist/windows-arm64/
cp SAMPLES/bouncer/main.noct            dist/windows-arm64/

rm -rf build-win-arm64

#
# macOS
#

export MACOSX_DEPLOYMENT_TARGET=10.13

# Build.
rm -rf build-macos
cmake --preset macos
cmake --build --preset macos

cd build-macos

# Sign & Notarize.
codesign --timestamp --options runtime --entitlements ../resources/macos/macos.entitlements --deep --force --sign "Developer ID Application" PicoPico.app
ditto -c -k --sequesterRsrc --keepParent PicoPico.app PicoPico.zip
source ../.credential
xcrun notarytool submit PicoPico.zip --apple-id "$APPLE_ID" --team-id "$TEAM_ID" --password "$APP_PASSWORD" --wait
xcrun stapler staple PicoPico.app

# Pack.
mkdir tmp
cp -Rv PicoPico.app tmp/PicoPico.app
hdiutil create -fs HFS+ -format UDBZ -srcfolder tmp -volname PicoPico PicoPico.dmg
codesign --sign 'Developer ID Application' PicoPico.dmg

cd ..

# Copy.
mkdir                             dist/macos
cp build-macos/PicoPico.dmg       dist/macos/
cp build-macos/picopico-pack      dist/macos/
cp SAMPLES/bouncer/main.noct      dist/macos/

rm -rf build-macos

#
# Wasm
#

# Build.
rm -rf build-wasm
cmake --preset wasm
cmake --build --preset wasm

# Copy.
mkdir -p                   dist/wasm
cp build-wasm/index.html   dist/wasm/
cp resources/assets.pak    dist/wasm/
cp docs/wasm.md            dist/wasm/readme.txt

rm -rf build-wasm

#
# iOS
#

# Build for devices.
rm -rf build-ios-device
cmake --preset ios-device
cmake --build --preset ios-device

# Build for the simulator.
rm -rf build-ios-simulator 
cmake --preset ios-simulator
cmake --build --preset ios-simulator

# Make a XCFramework.
rm -rf PicoPico.xcframework
xcodebuild -create-xcframework \
  -library build-ios-device/libpicopico.a -headers include \
  -library build-ios-simulator/libpicopico.a -headers include \
  -output PicoPico.xcframework

# Copy.
mkdir                                             dist/ios
mkdir                                             dist/ios/ios.xcodeproj
cp    projects/ios/ios.xcodeproj/project.pbxproj  dist/ios/ios.xcodeproj/
mkdir                                             dist/ios/ios
cp -R projects/ios/ios/Assets.xcassets            dist/ios/ios/
cp    projects/ios/ios/entry.c                    dist/ios/ios/
cp    projects/ios/ios/Info.plist                 dist/ios/ios/
cp    projects/ios/ios/ios.entitlements           dist/ios/ios/
cp    projects/ios/ios/LaunchScreen.storyboard    dist/ios/ios/
cp -R PicoPico.xcframework                        dist/ios/ios/
mkdir                                             dist/ios/Resources/
cp    resources/assets.pak                        dist/ios/Resources/
mkdir                                             dist/ios/Resources/video

rm -rf build-ios-device
rm -rf build-ios-simulator
rm -rf PicoPico.xcframework

#
# Android
#

# Build for Arm64.
rm -rf build-android-arm64
cmake --preset android-arm64
cmake --build --preset android-arm64

# Build for armv7.
rm -rf build-android-armv7
cmake --preset android-armv7
cmake --build --preset android-armv7

# Build for x86_64.
rm -rf build-android-x86_64
cmake --preset android-x86_64
cmake --build --preset android-x86_64

# Build for x86.
rm -rf build-android-x86
cmake --preset android-x86
cmake --build --preset android-x86

# Copy.
mkdir                                        dist/android
cp -R projects/android/app                   dist/android/
cp -R projects/android/gradle.properties     dist/android/
cp -R projects/android/build.gradle          dist/android/
cp -R projects/android/gradlew               dist/android/
cp -R projects/android/settings.gradle       dist/android/
cp -R projects/android/gradlew.bat           dist/android/
cp -R projects/android/gradle                dist/android/
cp -R projects/android/build.bat             dist/android/

mkdir -p dist/android/app/src/main/assets
cp SAMPLES/bouncer/main.noct                 dist/android/app/src/main/assets/

mkdir -p dist/android/app/src/main/java/io/noctvm/picopico/engineandroid
cp external/StratoHAL/src/MainActivity.java  dist/android/app/src/main/java/io/noctvm/picopico/engineandroid/

mkdir -p dist/android/app/src/main/jniLibs/arm64-v8a
cp build-android-arm64/libpicopico.so        dist/android/app/src/main/jniLibs/arm64-v8a/

mkdir -p dist/android/app/src/main/jniLibs/armeabi-v7a
cp build-android-armv7/libpicopico.so        dist/android/app/src/main/jniLibs/armeabi-v7a/

mkdir -p dist/android/app/src/main/jniLibs/x86_64
cp build-android-x86_64/libpicopico.so       dist/android/app/src/main/jniLibs/x86_64/

mkdir -p dist/android/app/src/main/jniLibs/x86
cp build-android-x86/libpicopico.so          dist/android/app/src/main/jniLibs/x86/

rm -rf build-android-arm64
rm -rf build-android-armv7
rm -rf build-android-x86_64
rm -rf build-android-x86

#
# Unity
#

# Build for Win64.
rm -rf build-unity-win64
cmake --preset unity-win64
cmake --build --preset unity-win64

# Build for Switch.
rm -rf build-unity-switch
cmake --preset unity-switch
cmake --build --preset unity-switch

# Build for PS5.
rm -rf build-unity-ps5
cmake --preset unity-ps5
cmake --build --preset unity-ps5

# Build for Xbox.
rm -rf build-unity-xbox
cmake --preset unity-xbox
cmake --build --preset unity-xbox

# Copy.
mkdir                                              dist/unity
mkdir                                              dist/unity/Assets
mkdir                                              dist/unity/Assets/StreamingAssets
cp    SAMPLES/bouncer/main.noct                    dist/unity/Assets/StreamingAssets/
mkdir                                              dist/unity/Assets/Resources
cp    external/StratoHAL/src/PicoPicoScript.cs     dist/unity/Assets/
cp    external/StratoHAL/src/NormalShader.shader   dist/unity/Assets/Resources/
cp    external/StratoHAL/src/AddShader.shader      dist/unity/Assets/Resources/
cp    external/StratoHAL/src/DimShader.shader      dist/unity/Assets/Resources/
cp    external/StratoHAL/src/RuleShader.shader     dist/unity/Assets/Resources/
cp    external/StratoHAL/src/MeltShader.shader     dist/unity/Assets/Resources/
cp    external/StratoHAL/src/MainScene.unity       dist/unity/Assets/
mkdir                                              dist/unity/Assets/Plugins
mkdir                                              dist/unity/Assets/Plugins/x86_64
mkdir                                              dist/unity/Assets/Plugins/Switch
mkdir                                              dist/unity/Assets/Plugins/PS5
mkdir                                              dist/unity/Assets/Plugins/GameCoreXboxSeries
mkdir                                              dist/unity/Assets/Plugins/Common
cp    build-unity-win64/libpicopico.dll            dist/unity/Assets/Plugins/x86_64/
cp    build-unity-switch/libpicopico.a             dist/unity/Assets/Plugins/Switch/
cp    build-unity-ps5/libpicopico.a                dist/unity/Assets/Plugins/PS5/
cp    build-unity-xbox/picopico.lib                dist/unity/Assets/Plugins/GameCoreXboxSeries/
cp    docs/unity.md                                dist/unity/

rm -rf build-unity-win64
rm -rf build-unity-switch
rm -rf build-unity-ps5
rm -rf build-unity-xbox

#
# Samples
#

find . -name .DS_Store | xargs rm
cp -R samples dist/SAMPLES

#
# mkdocs
#

mkdocs build
mv site dist/DOCS

#
# License and README
#

cp resources/readme.txt      dist/
cp resources/hajimeni.txt    dist/

#
# ZIP
#

cd dist
zip -r -9 PicoPicoScript.zip *
cd ..

#
# GitHub Release
#

VERSION="$(date +%Y%m%d)-dev+$(git rev-parse --short HEAD)"
gh release create $VERSION \
   dist/PicoPicoScript.zip \
   --title "PicoPicoScript $VERSION" \
   --notes "This is the latest version of PicoPicoScript!"

rm -rf dist
