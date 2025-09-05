How To Build PicoPicoScript
===========================

## Windows (WSL2)

### Prerequisite

* A `Windows 11` PC with an Intel, AMD, or Arm64 processor
* `WSL2` environment installed
* `Ubuntu` or `Debian` installed
* Run the folowing:
```
sudo apt-get install mingw-w64
```

### Steps

Open a terminal and enter the `PicoPicoScript` direcotry, then type the following.

```
cmake --preset windows-x86_64
cmake --build --preset windows-x86_64
```

## Windows (MSYS2)

### Prerequisite

* A `Windows 11` PC with an Intel, AMD, or Arm64 processor
* `MSYS2` environment installed

### Steps

Open a terminal and enter the `PicoPicoScript` direcotry, then type the following.

```
cmake --preset windows-x86_64
cmake --build --preset windows-x86_64
```

## Windows (Visual Studio)

### Prerequisite

* A `Windows 11` PC with an Intel, AMD, or Arm64 processor
* `Visual Studio 2022 Community` installed (C++, CMake)
* `Git for Windows` installed
* `PicoPicoScript` source tree downloaded

### Steps

- Open the source code folder by Visual Studio.
- Select a `MSVC` target.
- Build the project.

## Linux

### Prerequisite

* A Linux machine
* `Ubuntu`, `Debian`, or `Raspberry Pi OS` installed
* `GNU Make` installed

On Debian, Ubuntu, or Raspberry Pi OS:
```
sudo apt-get install build-essential libx11-dev libxpm-dev mesa-common-dev libasound2-dev
```

On RedHat, Rocky Linux, Fedora, etc.:
```
sudo dnf install patch libX11-devel libXpm-devel alsa-lib-devel mesa-libGL-devel
```

### Steps

Open a terminal and enter the `PicoPicoScript` direcotry, then type the following.

```
cmake --preset linux
cmake --build --preset linux
```

## macOS

### Prerequisite

* A Mac with an Apple Silicon or Intel processor
* `macOS 15` installed
* `Xcode 16` installed

### Steps

Open a terminal and enter th `PicoPicoScript` direcotry, then type the following.

```
./configure
make
sudo make install
```

Then, open the Xcode project at `projects/macos-dmg`, and build the project on Xcode.

## iOS

### Prerequisite

* A Mac with an Apple Silicon or Intel processor
* `macOS 15` installed
* `Xcode 16` installed

### Steps

- Merge assets into the `assets.pak` file.
- Copy the `assets.pak` file to the `ios/resources` folder in the distribution SDK.
- Open the `ios` folder in the SDK by Xcode

## Android

### Prerequisite

* A machine with one of:
    * `Windows 11`
    * `macOS 15`
    * `Linux`
* `Android Studio`

### Steps

- Copy your assets to the `android/app/src/main/assets` folder in the distribution SDK.
- Open the `android` in the distribution SDK by Android Studio

## FreeBSD

### Prerequisite

* A `FreeBSD` machine

### Steps

Open a terminal and enter the `PicoPicoScript` direcotry, then type the following.

```
cmake --preset freebsd
cmake --build --preset freebsd
```
