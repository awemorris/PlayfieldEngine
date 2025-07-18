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

rm -rf dist NoctVM-latest.zip
mkdir dist
mkdir dist/windows
mkdir dist/windows-arm64
mkdir dist/macos
mkdir dist/linux-x86_64
mkdir dist/linux-arm64
mkdir dist/wasm
mkdir dist/unity

#
# Windows x86
#

rm -rf build
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-i686-toolchain.cmake
cmake --build .
cd ..
cp build/noctvm.exe dist/windows/noctvm.exe
cp build/noctcli.exe dist/windows/noctcli.exe
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
cp build/noctvm.exe dist/windows-arm64/noctvm.exe
cp build/noctcli.exe dist/windows-arm64/noctcli.exe
rm -rf build

#
# macOS
#

rm -rf build
mkdir build
cd build

# Build.
cmake .. -G Ninja
cmake --build .

# Sign & Notarize.
codesign --timestamp --options runtime --entitlements ../resources/macos.entitlements --deep --force --sign "Developer ID Application" NoctVM.app
ditto -c -k --sequesterRsrc --keepParent NoctVM.app NoctVM.zip
source ../.credential
xcrun notarytool submit NoctVM.zip --apple-id "$APPLE_ID" --team-id "$TEAM_ID" --password "$APP_PASSWORD" --wait
xcrun stapler staple NoctVM.app

# Pack.
mkdir tmp
cp -Rv NoctVM.app tmp/NoctVM.app
hdiutil create -fs HFS+ -format UDBZ -srcfolder tmp -volname NoctVM NoctVM.dmg
codesign --sign 'Developer ID Application' NoctVM.dmg

cd ..
cp build/NoctVM.dmg dist/macos/NoctVM.dmg
cp build/noctcli dist/macos/noctcli
rm -rf build

#
# Linux x86_64
#

docker build --platform=linux/amd64 -t ubuntu22-x86_64 ./scripts
mkdir build
docker run --rm -it -v "$PWD":/src -w /src/build ubuntu22-x86_64 cmake .. -G Ninja
docker run --rm -it -v "$PWD":/src -w /src/build ubuntu22-x86_64 cmake --build .
cp build/noctvm dist/linux-x86_64/noctvm
cp build/noctcli dist/linux-x86_64/noctcli
rm -rf build

#
# Linux arm64
#

docker build --platform=linux/arm64 -t ubuntu22-arm_64 ./scripts
mkdir build
docker run --rm -it -v "$PWD":/src -w /src/build ubuntu22-arm64 cmake .. -G Ninja
docker run --rm -it -v "$PWD":/src -w /src/build ubuntu22-arm64 cmake --build .
cp build/noctvm dist/linux-arm64/noctvm
cp build/noctcli dist/linux-arm64/noctcli
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
# Wasm
#

cd projects/unity-src
make clean
make src
cp -R unity-src/* ../../dist/unity/
cd ../..

#
# ZIP
#

cd dist
zip -r -9 NoctVM-all-platforms.zip windows windows-arm64 macos linux-x86_64 linux-arm64 unity
cd ..

#
# GitHub Release
#

VERSION="$(date +%Y%m%d)-dev+$(git rev-parse --short HEAD)"
gh release create $VERSION \
   dist/NoctVM-all-platforms.zip \
   --title "NoctVM $VERSION" \
   --notes "This is the latest version of NoctVM!"
