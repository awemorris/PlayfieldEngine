PicoPicoScript by PicoPicoP
===========================

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![GitHub release](https://img.shields.io/github/release/awemorris/PicoPicoScript.svg)](https://github.com/awemorris/PicoPicoScript/releases)
[![Downloads](https://img.shields.io/github/downloads/awemorris/PicoPicoScript/total.svg)](https://github.com/awemorris/PicoPicoScript/releases)

`PicoPicoScript` is a game engine fueled by your dreams!

Built completely from scratch, it provides:
- **Scripting:** Powered by [Noct](https://github.com/awemorris/NoctLang),  
  a lightweight C-like JIT-powered language designed in-house.
- **Rendering & Audio:** Driven by StratoHAL,  
  a hardware abstraction layer also designed in-house.

"PicoPico" is a Japanese onomatopoeia that represents the cute beeping sounds of retro video games.

### Current Working Platforms

- Desktop
    - Windows
    - macOS
    - Linux / FreeBSD
- Mobile
    - iOS
    - Android
- Others
    - WebAssembly
    - Consoles

### Status

- Currently in active development on the 0.8.x branch. Stable 1.0.0 release planned.
- Latest nightly builds already run across all listed platforms.
- Built on its own technologies (not based on SDL or Lua).

---

## Live Web Demo

- [Heartbeat Clock](https://noctvm.io/g/2)
<img src="https://noctvm.io/img/screenshot-2.png" alt="Heartbeat Clock" width="200">

- [DON'T RUSH IN COMIKET](https://noctvm.io/g/1)  
<img src="https://noctvm.io/img/screenshot-1.png" alt="DON'T RUSH IN COMIKET" width="200">

---

## Table of Contents

- [Key Features](#key-features)
- [Example](#example)
- [ChatGPT Support](#chatgpt-support)
- [Quick Start](#quick-start)
- [What's PicoPicoScript?](#whats-picopico-script)
- [Technical Overview](#technical-overview)
  - [Core Architecture](#core-architecture)
  - [Platform Support](#platform-support)
  - [Console Unity Plugin Notice](#console-unity-plugin-notice)
  - [NoctLang](#noctlang)
  - [Script Execution Mode](#script-execution-mode)
- [Why PicoPicoScript?](#why-picopico-script)
- [Tests](#tests)
- [CMake Presets](#cmake-presets)
  - [Runtime Footprint](#runtime-footprint)
- [Samples](#samples)
- [Noct Ecosystem](#noct-ecosystem)
- [License](#license)
- [Join Us](#join-us)
- [About the Author](#about-the-author)

---

## Key Features

- **Minimal Setup**
    - No boilerplate required.
    - Write a script and run it immediately — *Jot and Run!*
- **Lightweight Runtime**
    - Optimized for low-spec and embedded devices.
    - Runs smoothly even on mobile platforms.
- **High Performance**
    - Built-in JIT compiler accelerates execution across architectures.
    - No native dependencies required.
- **Cross-Platform**  
    - Target Windows, macOS, Linux, iOS, Android, Consoles, and WebAssembly.
    - All from a single codebase.
    - On mobile platforms (iOS, Android), ahead-of-time (AOT) compilation is available as an alternative to JIT.
- **Portable by Design**
    - `PicoPicoScript` runs on nearly any computer made after the year 2000.
    - See the [Platform Guide](docs/porting.md)
- **Console-Ready**
    - Build for platforms you don't physically own,
    - With nothing but your own machine — *Go Far, Stay Close!*

---

## Example

Here's a simple example that displays an image following the mouse
cursor. This shows the basic lifecycle: `setup` (window config),
`start` (asset loading), and `frame` (per-frame logic).

```
func setup() {
    var config = {
        title: "My Sample Game",
        width: 640,
        height: 480
    };
    return config;
}

func start() {
    myTexture = Engine.loadTexture({file: "apple.png"});
}

func frame() {
    Engine.draw({
        texture: myTexture
        x: Engine.mousePosX,
        y: Engine.mousePosY,
    });
}
```

**Note:** setup() defines the window, start() loads resources, and
frame() is called each frame to render and update.

For more examples, check the [Getting Started Guide](docs/gettingstarted.md)

---

## ChatGPT Support

To generate game templates with ChatGPT, please let it load the
following references:

- [NoctLang Syntax Reference](https://noctvm.io/noctlang/syntax.html)
- [PicoPicoScript API Reference](https://noctvm.io/picopicoscript/api.html)

ChatGPT can then create runnable `PicoPicoScript` game samples directly.

**Note:** In ChatGPT, you need to click the **"+"** button and enable
**"Web Search"** so that it can read the above references.

---

## Quick Start

### 1-a. Download the latest release:

- Precompiled binaries are available on the [Releases page](https://github.com/awemorris/PicoPicoScript/releases)

### 1-b. ...Or, clone and build from the repository:

- Visual Studio 2022
    - Install the [winflexbison](https://github.com/lexxmark/winflexbison).
        - Add the installation folder to the PATH environment variable.
        - Rename the exe files to `flex.exe` and `bison.exe`.
    - Clone the repo.
        ```
        git clone --recursive https://github.com/awemorris/PicoPicoScript.git
        ```
    - Open the folder by Visual Studio 2022.
    - Choose the `!VS2022 MSVC x64 Release` target. (Alternatively x86 and arm64 is available)
    - Build and run.

- WSL2 (Ubuntu 22.04 or later, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        sudo apt-get install cmake mingw-w64 flex bison
        
        git clone --recursive https://github.com/awemorris/PicoPicoScript.git
        cd PicoPicoScript
        cmake --preset windows-x86_64
        cmake --build --preset windows-x86_64
        ```
    - The file `picopico.exe` will be generated in the `build-win-x86_64` directory.

- macOS (macOS 11 or later, brew, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        brew install cmake flex bison
        
        git clone --recursive https://github.com/awemorris/PicoPicoScript.git
        cd PicoPicoScript
        cmake -B build .
        cmake --build build --parallel
        ```
    - The app bundle `PicoPico.app` will be generated in the `build` directory.
    - The app is a Universal Binary 2 and runs on both Intel and Apple Silicon.

- Linux (Ubuntu 22.04 or later, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        sudo apt-get install cmake build-essential flex bison libx11-dev libxpm-dev libasound2-dev mesa-common-dev
        
        git clone --recursive https://github.com/awemorris/PicoPicoScript.git
        cd PicoPicoScript
        cmake -B build .
        cmake --build build --parallel
        ```
    - The file `picopico` will be generated in the `build` directory.
    - The app uses X11 and OpenGL.

- Notes
    - Requires CMake 3.22 or later, Flex 2.6+, Bison 3.0+
    - Windows: Visual Studio 2022 (Community or higher, tested on x64 and arm64)
    - macOS: Tested on macOS 15 (Apple Silicon, Xcode required)
    - Linux: Tested on Ubuntu 22.04, 24.04 (X11 required)
    - Unity Plugin build is not included in this Quick Start. Use the CMake presets named `unity-*`.
    - A full build takes 10 seconds using 10 cores.

### 2. Run a game script

- Place the sample game files alongside the binary, i.e., `picopico.exe`, `PicoPico.app`, or `picopico`.
    - E.g., `cp samples/rush/* build/`
- Run the app.
    - Windows: Double click the `picopico.exe` file.
    - macOS: Double click the `PicoPico.app` icon.
    - Linux: Run `./picopico` on the terminal.

### 3. Explore more features

- See the [Getting Started](docs/gettingstarted.md) page for the overview.
- See the [Full Documentation](docs/index.md) for the details.

---

## What's PicoPicoScript?

_"If a game engine could run anywhere, how would the world change?"_

`PicoPicoScript` was born from this single question.

`PicoPicoScript` is a lightweight and flexible game engine written in C89,
designed to support creators across desktop, mobile, and console platforms.

It runs smoothly even on older or low-spec machines — if you have a computer,
there's a place for you to create.

And if you're using something more powerful, like a modern MacBook or
a powerful gaming PC, `PicoPicoScript` adapts to draw out the full capabilities
of your device.

You don't need the latest or most expensive hardware. `PicoPicoScript` helps you
go beyond your environment. It's a helpful companion for creators
everywhere — especially in places with fewer resources.

The goal is simple:
**To make game development accessible, thoughtful, and within reach
for everyone.**

Create at your pace, wherever you are in the world.

---

## Technical Overview

### Core Architecture

```
+-----------------------------------------------------+
|                      User Script                    |
+-----------------------------------------------------+
                          ||
+-----------------------------------------------------+
|                    PicoPico Core                    |
+-----------------------------------------------------+
                ||                          ||
+--------------------------------+  +-----------------+
|  Strato HAL (Rendering/Audio)  |  |    NoctLang     |
+--------------------------------+  +-----------------|
```

* **Scripting**:
  Integrates [NoctLang](https://github.com/awemorris/NoctLang), a
  tiny yet mighty language designed for game scripting.

* **Rendering**:
  Supports DirectX 9/11/12, Metal, OpenGL, and a fallback software
  renderer for wide compatibility.

* **Audio**:
  Provides lightweight audio support through DirectSound, Audio Unit,
  ALSA, and other APIs.

* **Small Footprint**:
  The entire runtime fits within ~2MB, making it suitable for embedded
  systems or constrained environments.

### Platform Support

|Platform Type  |OS / Platform       |Notes                                     |
|---------------|--------------------|------------------------------------------|
|Desktop        |Windows             |DirectX 12/11/9, DirectSound              |
|               |macOS               |Metal, Audio Unit                         |
|               |ChromeOS            |OpenGL, ALSA                              |
|               |Linux               |OpenGL, ALSA                              |
|               |*BSD                |OpenGL, /dev/dsp                          |
|               |Qt                  |Qt OpenGL                                 |
|Mobile         |iOS                 |Metal, Audio Unit                         |
|               |Android             |OpenGL, OpenSL ES, NDK                    |
|Web            |WebAssembly         |WebGL, OpenAL, via Emscripten             |
|Console        |Unity               |Unity Plugin                              |

### Console Unity Plugin Notice

`PicoPicoScript` provides Unity Plugin binaries for platforms including Windows 64-bit and game consoles.

- These binaries are provided for demonstration purposes only.
- They are built entirely with the open-source LLVM/Clang toolchain (no proprietary SDKs).
- For actual shipping builds, developers must re-compile using the official SDKs provided by each platform holder.

### NoctLang

**NoctLang** is a lightweight scripting language designed specifically
for `PicoPicoScript`. With a game-oriented syntax, it emphasizes clarity,
instant startup, and tight integration with the engine.

The built-in JIT compiler supports a wide range of CPU architectures,
including both 32-bit and 64-bit of: **Intel, Arm, RISC-V, PowerPC, MIPS.**

For platforms where JIT is restricted (such as mobile or consoles),
NoctLang can fall back to interpreter mode, and AOT (ahead-of-time)
compilation using a C source backend — ensuring full compatibility
even in tightly controlled environments.

### Script Execution Mode

|Platform       |Mode               |
|---------------|-------------------|
|Windows x86    |JIT                |
|Windows x64    |JIT                |
|Windows arm64  |JIT                |
|macOS x86_64   |JIT                |
|macOS arm64    |JIT                |
|Linux x86      |JIT                |
|Linux x86_64   |JIT                |
|Linux armv7    |JIT                |
|Linux arm64    |JIT                |
|FreeBSD x86_64 |JIT                |
|iOS            |Interpreter or AOT |
|Android        |Interpreter or AOT |
|WebAssembly    |Interpreter or AOT |
|Unity Plugin   |Interpreter or AOT |

---

## Why PicoPicoScript?

`PicoPicoScript` is for those who quietly hold a dream, and wish to share it, one
small step at a time.

Creativity shouldn't depend on the power of your computer, where you
live, or what tools you have.

`PicoPicoScript` was created with the belief that every creator deserves space
to explore, no matter their surroundings.

Whether you're using a Raspberry Pi in a classroom, or using a
UN-issued Chromebook in a temporary shelter, `PicoPicoScript` offers gentle
tools to help bring your ideas to life — in a way that feels simple,
thoughtful, and your own. If you have something to make, `PicoPicoScript` will
be here to walk with you.

**Dreams fuel it — and they're the only requirement.**

---

## Tests

`PicoPicoScript` is tested on the following environments in the development.

|Type       |OS              |Version |Architecture    |
|-----------|----------------|--------|----------------|
|Desktop    |Windows         |11      |x64             |
|           |                |        |arm64           |
|           |macOS           |15      |arm64           |
|           |                |13      |x86_64          |
|           |Ubuntu          |24.04   |x86_64          |
|           |                |        |arm64           |
|           |Kubuntu         |25.04   |x86_64          |
|Browser    |Chrome          |139     |WebAssembly     |
|           |Safari          |18.6    |WebAssembly     |
|Smartphone |iOS             |18      |Simulator       |
|           |Android         |15      |Simulator       |
|Console    |Unity           |6       |                |

---

## CMake Presets

|Preset                       |Platform            |Compiler       |Directory           |Target           |
|-----------------------------|--------------------|---------------|--------------------|-----------------|
|windows-x86                  |Windows             |MINGW          |build-win-x86       |picopico.exe     |
|windows-x86_64               |Windows             |MINGW          |build-win-x86_64    |picopico.exe     |
|windows-arm64                |Windows             |MINGW (LLVM)   |build-win-arm64     |picopico.exe     |
|macos                        |macOS               |Clang          |build-macos         |PicoPico.app     |
|linux                        |Linux               |GCC            |build-linux         |picopico         |
|ios-device                   |iOS Device          |Clang          |build-ios-device    |libpicopico.a    |
|ios-simulator                |iOS Simulator       |Clang          |build-ios-simulator |libpicopico.a    |
|android-x86                  |Android x86         |Clang          |build-android-x86   |libpicopico.so   |
|android-x86_64               |Android x86_64      |Clang          |build-android-x86_64|libpicopico.so   |
|android-armv7                |Android armv7       |Clang          |build-android-armv7 |libpicopico.so   |
|android-arm64                |Android arm64       |Clang          |build-android-arm64 |libpicopico.so   |
|wasm                         |WebAssembly         |Emscripten     |build-wasm          |index.html       |
|unity-win64                  |Unity Plugin        |Clang          |build-unity-win64   |libpicopico.dll  |
|unity-switch                 |Unity Plugin        |Clang          |build-unity-switch  |libpicopico.a    |
|unity-ps5                    |Unity Plugin        |Clang          |build-unity-ps5     |libpicopico.a    |
|unity-xbox                   |Unity Plugin        |Clang          |build-unity-xbox    |libpicopico.a    |
|freebsd                      |FreeBSD             |Clang          |build-freebsd       |picopico         |
|windows-msvc-x86-debug       |Windows, VS2022     |MSVC           |out                 |picopico.exe     |
|windows-msvc-x86-release     |Windows, VS2022     |MSVC           |out                 |picopico.exe     |
|windows-msvc-x64-debug       |Windows, VS2022     |MSVC           |out                 |picopico.exe     |
|windows-msvc-x64-release     |Windows, VS2022     |MSVC           |out                 |picopico.exe     |
|windows-msvc-arm64-debug     |Windows, VS2022     |MSVC           |out                 |picopico.exe     |
|windows-msvc-arm64-release   |Windows, VS2022     |MSVC           |out                 |picopico.exe     |

---

### Runtime Footprint

|Platform       |Binary Size    |Memory Usage (GC)                                              |
|---------------|---------------|---------------------------------------------------------------|
|All targets    |~2 MB          |Allocates 512 MB at startup for GC; does not exceed that limit |

The garbage collector allocates 512 MB at startup because 512 MB is the maximum heap size.

---

## Samples

Samples are added timely.

|Name          |Directory            |Description                      |
|--------------|---------------------|---------------------------------|
|bouncer       |samples/bouncer      |A block bounce demo.             |
|rush          |samples/rush         |A jumping game demo.             |

---

## Noct Ecosystem

`PicoPicoScript` is a part of the [NoctVM](https://noctvm.io/) ecosystem:

- **NoctLang** — portable scripting language (used in this project)
- **PicoPicoScript** — go-anywhere 2D game engine (this project)
- NoctUI — a declarative UI library (not used in this project)

Together, they form the foundation of the Noct ecosystem.
NoctLang itself is just the core language engine with no complex runtime.
`PicoPicoScript` is one of the runtimes that embeds and extends the NoctLang core.

---

## License

`PicoPicoScript` is available as open-source software under the **MIT License**.
You're free to use, modify, and share it — even in commercial projects.

---

## Join Us

`PicoPicoScript` is still in its early stages. We're building the game engine
with care, hoping it will inspire and empower creators around the
world.

If you're interested in contributing — whether it's code,
documentation, testing, or ideas — we'd be happy to have you with us.

Every small step helps shape what `PicoPicoScript` can become. You're welcome to
join us on this journey.

[Join us on Discord](https://discord.gg/ybHWSqDVEX)

---

## About the Author

Awe (/aːwe/, "ah-weh") is a seasoned programmer living in a remote,
small house, surrounded by fields. They love writing code — it feels
simple and clear. Understanding people's feelings takes time, but
tools can be kind.
