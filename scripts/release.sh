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

rm -rf dist Noct2D-latest.zip
mkdir dist

#
# Windows x86_64
#

mkdir dist/windows-x86_64

./scripts/build-win-x86_64.sh
cp build-win-x86_64/noct2d.exe dist/windows/
cp build-win-x86_64/noct2dpack.exe dist/windows/
rm -rf build-win-x86_64

#
# Windows arm64
#

mkdir dist/windows-arm64

./scripts/build-win-arm64.sh
cp build-win-arm64/noct2d.exe dist/windows-arm64/
cp build-win-arm64/noct2dpack.exe dist/windows-arm64/
rm -rf build-win-arm64

#
# macOS
#

mkdir dist/macos

export MACOSX_DEPLOYMENT_TARGET=10.13

# Build.
./scripts/build-macos.sh

cd build-macos

# Sign & Notarize.
codesign --timestamp --options runtime --entitlements ../resources/macos.entitlements --deep --force --sign "Developer ID Application" Noct2D.app
ditto -c -k --sequesterRsrc --keepParent Noct2D.app Noct2D.zip
source ../.credential
xcrun notarytool submit Noct2D.zip --apple-id "$APPLE_ID" --team-id "$TEAM_ID" --password "$APP_PASSWORD" --wait
xcrun stapler staple Noct2D.app

# Pack.
mkdir tmp
cp -Rv Noct2D.app tmp/Noct2D.app
hdiutil create -fs HFS+ -format UDBZ -srcfolder tmp -volname Noct2D Noct2D.dmg
codesign --sign 'Developer ID Application' Noct2D.dmg

cd ..

cp build-macos/Noct2D.dmg dist/macos/
cp build-macos/noct2dpack dist/macos/
rm -rf build-macos

#
# Linux x86_64
#

mkdir dist/linux-x86_64

docker build --platform=linux/amd64 -t ubuntu22-x86_64 ./scripts
docker run --rm -it -v "$PWD":/src -w /src ubuntu22-x86_64 ./scripts/build-linux-x86_64.sh
cp build-linux-x86_64/noct2d dist/linux-x86_64/
cp build-linux-x86_64/noct2dpack dist/linux-x86_64/
rm -rf build-linux-x86_64

#
# Linux arm64
#

mkdir dist/linux-arm64

docker build --platform=linux/arm64 -t ubuntu22-arm64 ./scripts
docker run --rm -it -v "$PWD":/src -w /src ubuntu22-arm64 ./scripts/build-linux-arm64.sh
cp build-linux-arm64/noct2d dist/linux-arm64/
cp build-linux-arm64/noct2dpack dist/linux-arm64/
rm -rf build-linux-arm64

#
# Wasm
#

mkdir dist/wasm

./scripts/build-wasm.sh

cp build-wasm/index.html dist/wasm/
cp docs/wasm.md dist/wasm

#
# Android
#

mkdir dist/android

./scripts/build-android.sh

mkdir dist/android
mkdir dist/android/app/src/main/cpp
mkdir dist/android/app/src/main/assets

cp -R projects/android/app               dist/android/
cp -R projects/android/gradle.properties dist/android/
cp -R projects/android/build.gradle      dist/android/
cp -R projects/android/gradlew           dist/android/
cp -R projects/android/settings.gradle   dist/android/
cp -R projects/android/gradlew.bat       dist/android/
cp -R projects/gradle                    dist/android/
cp -R projects/build.bat                 dist/android/

mkdir dist/android/app/src/main/java/com/noct2d/engineandroid
cp StratoHAL/src/MainActivity.java       dist/android/app/src/main/java/com/noct2d/engineandroid/

mkdir dist/android/app/src/main/jniLibs/arm64-v8a
cp build-android-aarch64/libnoct2d.so      dist/android/app/src/main/jniLibs/arm64-v8a/

mkdir dist/android/app/src/main/jniLibs/armeabi-v7a
cp build-android-armv7/libnoct2d.so      dist/android/app/src/main/jniLibs/armeabi-v7a/

mkdir dist/android/app/src/main/jniLibs/x86_64
cp build-android-x86_64/libnoct2d.so     dist/android/app/src/main/jniLibs/x86_64/

mkdir dist/android/app/src/main/jniLibs/x86
cp build-android-x86/libnoct2d.so        dist/android/app/src/main/jniLibs/x86/

rm -rf build-android-aarch64
rm -rf build-android-armv7
rm -rf build-android-x86_64
rm -rf build-android-x86

#
# Unity
#

mkdir dist/unity

./scripts/build-unity-win64.sh
./scripts/build-unity-switch.sh
./scripts/build-unity-ps5.sh
./scripts/build-unity-xbox.sh

mkdir dist/unity/Assets
mkdir dist/unity/Assets/StreamingAssets
mkdir dist/unity/Assets/Resources
cp -v StratoHAL/src/Noct2D.cs dist/unity/Assets/
cp -v StratoHAL/src/NormalShader.shader dist/unity/Assets/Resources/
cp -v StratoHAL/src/AddShader.shader dist/unity/Assets/Resources/
cp -v StratoHAL/src/DimShader.shader dist/unity/Assets/Resources/
cp -v StratoHAL/src/RuleShader.shader dist/unity/Assets/Resources/
cp -v StratoHAL/src/MeltShader.shader dist/unity/Assets/Resources/
mkdir dist/unity/Assets/Plugins
mkdir dist/unity/Assets/Plugins/x86_64
mkdir dist/unity/Assets/Plugins/Switch
mkdir dist/unity/Assets/Plugins/PS5
mkdir dist/unity/Assets/Plugins/GameCoreXboxSeries
mkdir dist/unity/Assets/Plugins/Common
cp -v build-unity-win64/libnoct2d.dll dist/unity/Assets/Plugins/x86_64/libnoct2d.dll
cp -v build-unity-switch/libnoct2d.a dist/unity/Assets/Plugins/Switch/libnoct2d.a
cp -v build-unity-ps5/libnoct2d.a dist/unity/Assets/Plugins/PS5/libnoct2d.a
cp -v build-unity-xbox/noct2d.lib dist/unity/Assets/Plugins/GameCoreXboxSeries/libnoct2d.lib
cp -v src/MainScene.unity dist/unity/Assets/
cp -v docs/unity.md dist/unity/

rm -rf build-unity-win64
rm -rf build-unity-switch
rm -rf build-unity-ps5
rm -rf build-unity-xbox

#
# Sample
#

cp -R sample/* dist/sample/

#
# ZIP
#

cd dist
zip -r -9 Noct2D-all-platforms.zip *
cd ..

#
# GitHub Release
#

VERSION="$(date +%Y%m%d)-dev+$(git rev-parse --short HEAD)"
gh release create $VERSION \
   dist/Noct2D-all-platforms.zip \
   --title "Noct2D $VERSION" \
   --notes "This is the latest version of Noct2D!"
