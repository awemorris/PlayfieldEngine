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
mkdir dist/windows
mkdir dist/windows-arm64
mkdir dist/macos
mkdir dist/linux-x86_64
mkdir dist/linux-arm64
mkdir dist/wasm
mkdir dist/unity
mkdir dist/sample

#
# Windows x86
#

rm -rf build
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-i686-toolchain.cmake
cmake --build .
cd ..
cp build/noct2d.exe dist/windows/
cp build/noct2dpack.exe dist/windows/
rm -rf build

#
# Windows arm64
#

rm -rf build
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-arm64-toolchain.cmake
cmake --build .
cd ..
cp build/noct2d.exe dist/windows-arm64/
cp build/noct2dpack.exe dist/windows-arm64/
rm -rf build

#
# macOS
#

export MACOSX_DEPLOYMENT_TARGET=10.13

rm -rf build
mkdir build
cd build

# Build.
cmake .. -G Ninja
cmake --build .

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
cp build/Noct2D.dmg dist/macos/
cp build/noct2dpack dist/macos/
rm -rf build

#
# Linux x86_64
#

docker build --platform=linux/amd64 -t ubuntu22-x86_64 ./scripts
mkdir build
docker run --rm -it -v "$PWD":/src -w /src/build ubuntu22-x86_64 cmake .. -G Ninja
docker run --rm -it -v "$PWD":/src -w /src/build ubuntu22-x86_64 cmake --build .
cp build/noct2d dist/linux-x86_64/
cp build/noct2dpack dist/linux-x86_64/
rm -rf build

#
# Linux arm64
#

docker build --platform=linux/arm64 -t ubuntu22-arm64 ./scripts
mkdir build
docker run --rm -it -v "$PWD":/src -w /src/build ubuntu22-arm64 cmake .. -G Ninja
docker run --rm -it -v "$PWD":/src -w /src/build ubuntu22-arm64 cmake --build .
cp build/noct2d dist/linux-arm64/
cp build/noct2dpack dist/linux-arm64/
rm -rf build

#
# Wasm
#

cd projects/wasm
make clean
make
cp index.html index.js index.wasm ../../dist/wasm/
cd ../..

#
# Unity
#

./scripts/build-unity-win64.sh
./scripts/build-unity-switch.sh
./scripts/build-unity-ps5.sh
./scripts/build-unity-xbox.sh

mkdir dist/unity
mkdir dist/unity/Assets
mkdir dist/unity/Assets/StreamingAssets
mkdir dist/unity/Assets/Resources
cp -v StratoHAL/src/Noct2D.cs dist/unity/Assets/
cp -v StratoHAL/src/NormalShader.shader dist/unity/Assets/Resources/
cp -v StratoHAL/src/AddShader.shader dist/unity/Assets/Resources/
cp -v StratoHAL/src/DimShader.shader dist/unity/Assets/Resources/
cp -v StratoHAL/src/RuleShader.shader dist/unity/Assets/Resources/
cp -v StratoHAL/src/MeltShader.shader dist/unity/Assets/Resources/
mkdir dist/unity-src/Assets/Plugins
mkdir dist/unity/Assets/Plugins/x86_64
mkdir dist/unity/Assets/Plugins/Switch
mkdir dist/unity/Assets/Plugins/PS5
mkdir dist/unity/Assets/Plugins/GameCoreXboxSeries
mkdir dist/unity/Assets/Plugins/Common
cp -v build-unity-win64/libnoct2d.dll dist/unity/Assets/Plugins/x86_64/libnoct2d.dll
cp -v build-unity-switch/libnoct2d.a dist/unity/Assets/Plugins/Switch/libnoct2d.a
cp -v build-unity-ps5/libnoct2d.a dist/unity/Assets/Plugins/PS5/libnoct2d.a
cp -v build-unity-xbox/libnoct2d.lib dist/unity/Assets/Plugins/GameCoreXboxSeries/libnoct2d.lib
cp -v src/MainScene.unity dist/unity/Assets/
cp -v docs/unity.md dist/unity/

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
