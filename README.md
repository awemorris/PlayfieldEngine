
Playfield Engine
================

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![GitHub release](https://img.shields.io/github/release/awemorris/PlayfieldEngine.svg)](https://github.com/awemorris/PlayfieldEngine/releases)
[![Downloads](https://img.shields.io/github/downloads/awemorris/PlayfieldEngine/total.svg)](https://github.com/awemorris/PlayfieldEngine/releases)

`Playfield Engine` is a 2D game scripting runtime that works everywhere.
With scripts written in `Playfield Script`,
it can render graphics and play sounds seamlessly across platforms.

Built completely from scratch, Playfield Engine features:

- **Comfortable Scripting:**
    - Powered by Playfield Script, a C/JavaScript-like scripting language designed in-house.
    - Native performance with a built-in JIT compiler.
    - Write a script and run it instantly — **Jot and Run!**
- **Portable Rendering & Audio:**
    - Powered by StratoHAL, a portable game library also designed in-house.
    - Runs virtually everywhere: Windows, macOS, Linux, Chromebook, WebAssembly, iOS, Android, and even consoles.
    - Deploy to platforms you don't even own — **Go Far, Stay Close!**
- **Minimal Runtime:**
    - The runtime is only ~1.4 MB on Windows.
    - Perfect for mobile apps — **Go Magically Small, Get Massively Loved!**

## Why Playfield Engine?

_"If a game engine could run anywhere, how would the world change?"_

Playfield Engine was born from this single question.

Creativity shouldn't depend on the power of your computer, where you
live, or what tools you have.  Playfield Engine was created with the belief
that every creator deserves space to explore, no matter their
surroundings.

It runs smoothly even on older or low-spec machines — if you have a
computer, there's a place for you to create.  It's a helpful companion
for creators everywhere — especially in places with fewer resources.
If you have something to make, Playfield Engine will be here to walk with
you.

Whether you're using a Raspberry Pi in a classroom, or using a
UN-issued Chromebook in a temporary shelter, Playfield Engine offers gentle
tools to help bring your ideas to life — in a way that feels simple,
thoughtful, and your own.

The goal is simple:
**To make game development accessible, thoughtful, and within reach
for everyone.**

**Dreams fuel it — and they're the only requirement.**

---

## Live Web Demo

- [Heartbeat Clock](https://noctvm.io/g/2)
<img src="https://noctvm.io/img/screenshot-2.png" alt="Heartbeat Clock" width="200">

- [Mini Shoot](https://noctvm.io/g/3)
<img src="https://noctvm.io/img/screenshot-3.png" alt="Mini Shoot" width="200">

- [DON'T RUSH IN COMIKET](https://noctvm.io/g/1)  
<img src="https://noctvm.io/img/screenshot-1.png" alt="DON'T RUSH IN COMIKET" width="200">

---

## Status

Currently in active development on the 0.8.x branch. Stable 1.0.0 release planned.

**Nightly Works On**

|Type       |OS         |Status                             |
|-----------|-----------|-----------------------------------|
|Desktop    |Windows    |Works                              |
|           |macOS      |Works                              |
|           |Linux      |Works                              |
|           |FreeBSD    |Works                              |
|           |Chromebook |Works [Here](https://noctvm.io/w/) |
|Mobile     |iOS        |Works                              |
|           |Android    |Works                              |
|Others     |WebAssembly|Works                              |
|           |Unity      |Works                              |

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

For more examples, check the [Getting Started Guide](docs/mkdocs-en/docs/gettingstarted.md)

---

## Quick Start

Precompiled binaries are available for Windows, macOS, Linux, and Chromebook!

### 1. Download the latest binary:

- Precompiled binaries are available on the [Releases page](https://github.com/awemorris/PlayfieldEngine/releases)

### 2. Run a game script

- For Windows, macOS, and Linux:
    - Place a binary alongside a sample game.
    - Run the app.
        - Windows: Double click the `playfield.exe` file.
        - macOS: Double click the `Playfield.app` icon.
        - Linux: Run `./PlayfieldEngine-x86_64.AppImage` on the terminal.
- For Chromebook:
    - Open [this page](https://noctvm.io/w/) on the browser, then open a game folder.

### 3. Explore more features

- See the [Getting Started](docs/mkdocs-en/docs/gettingstarted.md) page for the overview.
- See the [Full Documentation](docs/mkdocs-en/docs/index.md) for the details.

### Appendix. Build from source

- Visual Studio 2022
    - Install the [winflexbison](https://github.com/lexxmark/winflexbison).
        - Add the installation folder to the PATH environment variable.
        - Rename the exe files to `flex.exe` and `bison.exe`.
    - Clone the repo.
        ```
        git clone --recursive https://github.com/awemorris/PlayfieldEngine.git
        ```
    - Open the folder by Visual Studio 2022.
    - Choose the `!VS2022 MSVC x64 Release` target. (Alternatively x86 and arm64 is available)
    - Build and run.

- WSL2 (Ubuntu 22.04 or later, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        sudo apt-get install cmake mingw-w64 flex bison
        
        git clone --recursive https://github.com/awemorris/PlayfieldEngine.git
        cd PlayfieldEngine
        cmake --preset windows-x86_64
        cmake --build --preset windows-x86_64
        ```
    - The file `playfield.exe` will be generated in the `build-win-x86_64` directory.

- macOS (macOS 11 or later, brew, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        brew install cmake flex bison
        
        git clone --recursive https://github.com/awemorris/PlayfieldEngine.git
        cd PlayfieldEngine
        cmake -B build .
        cmake --build build --parallel
        ```
    - The app bundle `Playfield.app` will be generated in the `build` directory.
    - The app is a Universal Binary 2 and runs on both Intel and Apple Silicon.

- Linux (Ubuntu 22.04 or later, CMake >= 3.22)
    - Type the following in the terminal.
        ```
        sudo apt-get install cmake build-essential flex bison libx11-dev libxpm-dev libasound2-dev mesa-common-dev
        
        git clone --recursive https://github.com/awemorris/Playfield.git
        cd Playfield
        cmake -B build .
        cmake --build build --parallel
        ```
    - The file `playfield` will be generated in the `build` directory.
    - The app uses X11 and OpenGL.

- Notes
    - Requires CMake 3.22 or later, Flex 2.6+, Bison 3.0+
    - Windows: Visual Studio 2022 (Community or higher, tested on x64 and arm64)
    - macOS: Tested on macOS 15 (Apple Silicon, Xcode required)
	      - Linux: Tested on Ubuntu 22.04, 24.04 (X11 required)
    - Unity Plugin build is not included in this Quick Start. Use the CMake presets named `unity-*`.
    - A full build takes 10 seconds using 10 cores.

---

## Technical Overview

### Core Architecture

```
+-----------------------------------------------------+
|                     User Script                     |
+-----------------------------------------------------+
                          ||
+-----------------------------------------------------+
|                    Playfield VM                     |
+-----------------------------------------------------+
                ||                          ||
+--------------------------------+  +-----------------+
|  StratoHAL (Rendering/Audio)   |  |    NoctLang     |
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

Playfield Engine provides Unity Plugin binaries for platforms including
Windows 64-bit and game consoles.

- These binaries are provided for demonstration purposes only.
- They are built entirely with the open-source LLVM/Clang toolchain (no proprietary SDKs).
- For actual shipping builds, developers must re-compile using the official SDKs provided by each platform holder.

### NoctLang

**NoctLang** is a lightweight scripting language designed specifically
for Playfield. With a game-oriented syntax, it emphasizes clarity,
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

## Tests

Playfield Engine is tested on the following environments in the development.

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
|windows-x86                  |Windows             |MINGW          |build-win-x86       |playfield.exe    |
|windows-x86_64               |Windows             |MINGW          |build-win-x86_64    |playfield.exe    |
|windows-arm64                |Windows             |MINGW (LLVM)   |build-win-arm64     |playfield.exe    |
|macos                        |macOS               |Clang          |build-macos         |Playfield.app    |
|linux                        |Linux               |GCC            |build-linux         |playfield        |
|ios-device                   |iOS Device          |Clang          |build-ios-device    |libplayfield.a   |
|ios-simulator                |iOS Simulator       |Clang          |build-ios-simulator |libplayfield.a   |
|android-x86                  |Android x86         |Clang          |build-android-x86   |libplayfield.so  |
|android-x86_64               |Android x86_64      |Clang          |build-android-x86_64|libplayfield.so  |
|android-armv7                |Android armv7       |Clang          |build-android-armv7 |libplayfield.so  |
|android-arm64                |Android arm64       |Clang          |build-android-arm64 |libplayfield.so  |
|wasm                         |WebAssembly         |Emscripten     |build-wasm          |index.html       |
|wasm-local                   |Chromebook          |Emscripten     |build-wasm-local    |index.html       |
|unity-win64                  |Unity Plugin        |Clang          |build-unity-win64   |libplayfield.dll |
|unity-switch                 |Unity Plugin        |Clang          |build-unity-switch  |libplayfield.a   |
|unity-ps5                    |Unity Plugin        |Clang          |build-unity-ps5     |libplayfield.a   |
|unity-xbox                   |Unity Plugin        |Clang          |build-unity-xbox    |libplayfield.a   |
|freebsd                      |FreeBSD             |Clang          |build-freebsd       |playfield        |
|windows-msvc-x86-debug       |Windows, VS2022     |MSVC           |out                 |playfield.exe    |
|windows-msvc-x86-release     |Windows, VS2022     |MSVC           |out                 |playfield.exe    |
|windows-msvc-x64-debug       |Windows, VS2022     |MSVC           |out                 |playfield.exe    |
|windows-msvc-x64-release     |Windows, VS2022     |MSVC           |out                 |playfield.exe    |
|windows-msvc-arm64-debug     |Windows, VS2022     |MSVC           |out                 |playfield.exe    |
|windows-msvc-arm64-release   |Windows, VS2022     |MSVC           |out                 |playfield.exe    |

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
|heartbeatclock|samples/hearbeatclock|A clock.                         |
|shoot         |samples/shoot        |A mini shooting.                 |

---

## ChatGPT Support

To generate game templates with ChatGPT, please let it load the
following references:

- [Playfield Script Syntax](docs/mkdocs-en/docs/syntax.md)
- [Playfield Script API](docs/mkdocs-en/docs/api.md)

ChatGPT can then create runnable Playfield Engine games directly.

**Note:** In ChatGPT, you need to click the **"+"** button and enable
**"Web Search"** so that it can read the above references.

---

## NoctVM Ecosystem

Playfield Engine is a part of the [NoctVM](https://noctvm.io/) ecosystem:

- **NoctLang** — portable scripting language (used in this project)
- **Playfield Engine** — go-anywhere 2D game engine (this project)
- NoctUI — a declarative UI library (not used in this project)

Together, they form the foundation of the Noct ecosystem.
NoctLang itself is just the core language engine with no complex runtime.
Playfield Engine is one of the runtimes that embeds and extends the NoctLang core.

---

## License

```
Playfield Engine
© 2025 Awe Morris
```

Playfield Engine is available as open-source software under the **MIT License**.
You're free to use, modify, and share it — even in commercial projects.

---

## Join Us

Playfield Engine is still in its early stages. We're building the game
engine with care, hoping it will inspire and empower creators around
the world.

If you're interested in contributing — whether it's code,
documentation, testing, or ideas — we'd be happy to have you with us.

Every small step helps shape what Playfield Engine can become. You're
welcome to join us on this journey.

[Join us on Discord](https://discord.gg/ybHWSqDVEX)
