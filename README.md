Noct2D
======

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![GitHub release](https://img.shields.io/github/release/awemorris/Noct2D.svg)](https://github.com/awemorris/Noct2D/releases)
[![Downloads](https://img.shields.io/github/downloads/awemorris/Noct2D/total.svg)](https://github.com/awemorris/Noct2D/releases)

Noct2D is a crazy portable game engine that uses [NoctLang](https://github.com/awemorris/NoctLang) for scripting.

- Tiny: Core runtime ~2.0MB for instant downloads and startup.
- Fast: Low-latency game loops via JIT-optimized NoctLang.
- Portable: Desktop, mobile, Web, consoles — all from a single codebase.

It provides:

- Scripting: NoctLang, a fast, lightweight, game-oriented language.
- Graphics: DirectX12, Metal, OpenGL, Software Renderer
- Audio: DirectSound, Audio Unit, ALSA, OpenAL, etc
- Input: Keyboard, mouse, touch, and gamepad.

**Status:**

- Actively developed on the 0.1.x branch. Use the latest nightly.
- No stable release available yet, 1.0.0 will be stable.
- Actually runs on all the platforms described in this page.

---

## Live Web Demo

- [DON'T RUSH IN COMIKET](https://noctvm.io/g/1)

<img src="https://noctvm.io/img/noct2d.png" alt="Screenshot" width="200">

---

## Table of Contents

- [Key Features](#key-features)
- [Example](#example)
- [ChatGPT Support](#chatgpt-support)
- [Quick Start](#quick-start)
- [What's Noct2D?](#whats-noct2d)
- [Technical Overview](#technical-overview)
  - [Core Architecture](#core-architecture)
  - [Platform Support](#platform-support)
  - [Console Unity Plugin Notice](#console-unity-plugin-notice)
  - [NoctLang](#noctlang)
  - [Script Execution Mode](#script-execution-mode)
- [Why Noct2D?](#why-noct2d)
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
    - Noct2D runs on nearly any computer made after the year 2000.
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
- [Noct2D API Reference](https://noctvm.io/noct2d/api.html)

ChatGPT can then create runnable Noct2D game samples directly.

**Note:** In ChatGPT, you need to click the **"+"** button and enable
**"Web Search"** so that it can read the above references.

---

## Quick Start

### 1-a. Download the latest release:

- Precompiled binaries are available on the [Releases page](https://github.com/awemorris/Noct2D/releases)

### 1-b. ...Or, clone and build from the repository:

- Visual Studio 2022
    - Install the [winflexbison](https://github.com/lexxmark/winflexbison).
        - Add the installation folder to the PATH environment variable.
        - Rename the exe files to `flex.exe` and `bison.exe`.
    - Clone the repo.
        ```
        git clone --recursive https://github.com/awemorris/Noct2D.git
        ```
    - Open the folder by Visual Studio 2022.
    - Choose the `!VS2022 MSVC x64 Release` target. (Alternatively x86 and arm64 is available)
    - Build and run.

- WSL2 (Ubuntu 22.04 or later, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        sudo apt-get install cmake mingw-w64 flex bison
        
        git clone --recursive https://github.com/awemorris/Noct2D.git
        cd Noct2D
        cmake --preset windows-x86_64
        cmake --build --preset windows-x86_64
        ```
    - The file `noct2d.exe` will be generated in the `build-win-x86_64` directory.

- macOS (macOS 11 or later, brew, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        brew install cmake flex bison
        
        git clone --recursive https://github.com/awemorris/Noct2D.git
        cd Noct2D
        cmake -B build .
        cmake --build build --parallel
        ```
    - The app bundle `Noct2D.app` will be generated in the `build` directory.
    - The app is a Universal Binary 2 and runs on both Intel and Apple Silicon.

- Linux (Ubuntu 22.04 or later, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        sudo apt-get install cmake build-essential flex bison libx11-dev libxpm-dev libasound2-dev mesa-common-dev
        
        git clone --recursive https://github.com/awemorris/Noct2D.git
        cd Noct2D
        cmake -B build .
        cmake --build build --parallel
        ```
    - The file `noct2d` will be generated in the `build` directory.
    - The app uses X11 and OpenGL.

- Notes
    - Requires CMake 3.22 or later, Flex 2.6+, Bison 3.0+
    - Windows: Visual Studio 2022 (Community or higher, tested on x64 and arm64)
    - macOS: Tested on macOS 15 (Apple Silicon, Xcode required)
    - Linux: Tested on Ubuntu 22.04, 24.04 (X11 required)
    - Unity Plugin build is not included in this Quick Start. Use the CMake presets named `unity-*`.
    - A full build takes 10 seconds using 10 cores.

### 2. Run a game script

- Place the sample game files alongside the binary, i.e., `noct2d.exe`, `Noct2D.app`, or `noct2d`.
    - E.g., `cp samples/rush/* build/`
- Run the app.
    - Double click the `noct2d.exe` file on Windows.
    - Double click the `Noct2D.app` bundle on macOS.
    - Run `./noct2d` on Linux.

### 3. Explore more features

- See the [Getting Started](docs/gettingstarted.md) page for the overview.
- See the [Full Documentation](docs/index.md) for the details.

---

## What's Noct2D?

_"If a game engine could run anywhere, how would the world change?"_

Noct2D was born from this single question.

Noct2D is a lightweight and flexible game engine written in C89,
designed to support creators across desktop, mobile, and console platforms.

It runs smoothly even on older or low-spec machines — if you have a computer,
there's a place for you to create.

And if you're using something more powerful, like a modern MacBook or
a powerful gaming PC, Noct2D adapts to draw out the full capabilities
of your device.

You don't need the latest or most expensive hardware. Noct2D helps you
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
|                      Noct2D Core                    |
+-----------------------------------------------------+
         ||               ||                ||
+-----------------+--------------+  +-----------------+
|  Rendering HAL  |  Sound HAL   |  | Scripting Core  |
+-----------------+--------------+  +-----------------|
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
|               |Linux               |OpenGL / Soft Renderer, ALSA              |
|               |*BSD                |OpenGL / Soft Renderer, /dev/dsp          |
|               |Haiku               |Soft Renderer                             |
|               |Qt                  |Qt OpenGL                                 |
|Mobile         |iOS                 |Metal, Audio Unit                         |
|               |Android             |OpenGL, OpenSL ES, NDK                    |
|Web            |WebAssembly         |WebGL, OpenAL, via Emscripten             |
|Console        |Nintendo Switch™   |Unity Native Plugin                       |
|               |PlayStation® 5     |Unity Native Plugin                       |
|               |Xbox Series X\|S    |Unity Native Plugin                       |

### Console Unity Plugin Notice

Noct2D provides Unity Plugin binaries for platforms including Windows 64-bit, Nintendo Switch, PlayStation 5, and Xbox Series X|S.

- These binaries are provided for demonstration purposes only.
- They are built entirely with the open-source LLVM/Clang toolchain (no proprietary SDKs).
- For actual shipping builds, developers must re-compile using the official SDKs provided by each platform holder.
- Platform names are listed solely to describe compatibility and do not imply endorsement or approval by the respective companiese.
- Nintendo Switch™ is a trademark of Nintendo.
- PlayStation® and PlayStation®5 are registered trademarks of Sony Interactive Entertainment Inc.
- Xbox®, Xbox Series X|S are trademarks of Microsoft Corporation.
- Unity® is a trademark of Unity Technologies.
- All other company and product names are trademarks or registered trademarks of their respective owners.

### NoctLang

**NoctLang** is a lightweight scripting language designed specifically
for Noct2D. With a game-oriented syntax, it emphasizes clarity,
instant startup, and tight integration with the engine.

The built-in JIT compiler supports a wide range of CPU architectures,
including both 32-bit and 64-bit of: **Intel, Arm, RISC-V, PowerPC, MIPS.**

For platforms where JIT is restricted (such as mobile or consoles),
NoctLang can fall back to interpreter mode, and AOT (ahead-of-time)
compilation using a C source backend — ensuring full compatibility
even in tightly controlled environments.

### Script Execution Mode

|Platform      |Mode               |
|--------------|-------------------|
|Windows x86   |JIT                |
|Windows x64   |JIT                |
|Windows arm64 |JIT                |
|macOS x86_64  |JIT                |
|macOS arm64   |JIT                |
|Linux x86     |JIT                |
|Linux x86_64  |JIT                |
|Linux armv7   |JIT                |
|Linux arm64   |JIT                |
|iOS           |Interpreter or AOT |
|Android       |Interpreter or AOT |
|WebAssembly   |Interpreter or AOT |
|Unity Plugin  |Interpreter or AOT |

---

## Why Noct2D?

Noct2D is for those who quietly hold a dream, and wish to share it, one
small step at a time.

Creativity shouldn't depend on the power of your computer, where you
live, or what tools you have.

Noct2D was created with the belief that every creator deserves space
to explore, no matter their surroundings.

Whether you're using a Raspberry Pi in a classroom, or using a
UN-issued Chromebook in a temporary shelter, Noct2D offers gentle
tools to help bring your ideas to life — in a way that feels simple,
thoughtful, and your own. If you have something to make, Noct2D will
be here to walk with you.

**Dreams fuel it — and they're the only requirement.**

---

## Tests

Noct2D is tested on the following environments in the development.

- Windows 11 x64
- Windows 11 arm64
- macOS 15 arm64
- Ubuntu 24.04 aarch64 (both X11 and Wayland)
- Ubuntu 24.04 x86_64 (both X11 and wayland)
- Google Chrome (WebAssembly)
- Safari (WebAssembly)
- iOS Simulator (Xcode, tested on iOS 18)
- Android Simulator (Android Studio, tested on the API level 28 and 35)
- Unity 6 Windows 11 x86_64

Sometimes checked on Windows XP. It runs but texture stretching is not working without Direct3D 9.

---

## CMake Presets

|Preset                       |Platform            |Compiler       |Directory           |Target           |
|-----------------------------|--------------------|---------------|--------------------|-----------------|
|windows-x86                  |Windows             |MINGW          |build-win-x86       |noct2d.exe       |
|windows-x86_64               |Windows             |MINGW          |build-win-x86_64    |noct2d.exe       |
|windows-arm64                |Windows             |MINGW (LLVM)   |build-win-arm64     |noct2d.exe       |
|macos                        |macOS               |Clang          |build-macos         |Noct2D.app       |
|linux                        |Linux               |GCC            |build-linux         |noct2d           |
|ios-device                   |iOS Device          |Clang          |build-ios-device    |libnoct2d.a      |
|ios-simulator                |iOS Simulator       |Clang          |build-ios-simulator |libnoct2d.a      |
|android-x86                  |Android x86         |Clang          |build-android-x86   |libnoct2d.so     |
|android-x86_64               |Android x86_64      |Clang          |build-android-x86_64|libnoct2d.so     |
|android-armv7                |Android armv7       |Clang          |build-android-armv7 |libnoct2d.so     |
|android-arm64                |Android arm64       |Clang          |build-android-arm64 |libnoct2d.so     |
|wasm                         |WebAssembly         |Emscripten     |build-wasm          |index.html       |
|unity-win64                  |Unity Plugin        |Clang          |build-unity-win64   |libnoct2d.dll    |
|unity-switch                 |Unity Plugin        |Clang          |build-unity-switch  |libnoct2d.a      |
|unity-ps5                    |Unity Plugin        |Clang          |build-unity-ps5     |libnoct2d.a      |
|unity-xbox                   |Unity Plugin        |Clang          |build-unity-xbox    |libnoct2d.a      |
|freebsd                      |FreeBSD             |Clang          |build-freebsd       |noct2d           |
|haiku                        |Haiku               |GCC            |build-haiku         |noct2d           |
|windows-msvc-x86-debug       |Windows, VS2022     |MSVC           |out                 |noct2d.exe       |
|windows-msvc-x86-release     |Windows, VS2022     |MSVC           |out                 |noct2d.exe       |
|windows-msvc-x64-debug       |Windows, VS2022     |MSVC           |out                 |noct2d.exe       |
|windows-msvc-x64-release     |Windows, VS2022     |MSVC           |out                 |noct2d.exe       |
|windows-msvc-arm64-debug     |Windows, VS2022     |MSVC           |out                 |noct2d.exe       |
|windows-msvc-arm64-release   |Windows, VS2022     |MSVC           |out                 |noct2d.exe       |

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

Noct2D is a part of the [NoctVM](https://noctvm.io/) ecosystem:

- **NoctLang** — portable scripting language (used in this project)
- **Noct2D** — go-anywhere 2D game engine (this project)
- NoctUI — a declarative UI library (not used in this project)

Together, they form the foundation of the Noct ecosystem.
NoctLang itself is just the core language engine with no complex runtime.
Noct2D is one of the runtimes that embeds and extends the NoctLang core.

---

## License

Noct2D is available as open-source software under the **MIT License**.
You're free to use, modify, and share it — even in commercial projects.

---

## Join Us

Noct2D is still in its early stages. We're building the game engine
with care, hoping it will inspire and empower creators around the
world.

If you're interested in contributing — whether it's code,
documentation, testing, or ideas — we'd be happy to have you with us.

Every small step helps shape what Noct2D can become. You're welcome to
join us on this journey.

[Join us on Discord](https://discord.gg/ybHWSqDVEX)

---

## About the Author

Awe (/aːwe/, "ah-weh") is a seasoned programmer living in a remote,
small house, surrounded by fields. They love writing code — it feels
simple and clear. Understanding people's feelings takes time, but
tools can be kind.
