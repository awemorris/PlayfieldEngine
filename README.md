Noct2D
======

**Noct2D** is a lightweight scripting runtime for game
development, often described as a game engine.

It is designed to provide:

- A fast scripting language with JIT or AOT compilation
- Real-time graphics and audio capabilities
- Cross-platform deployment across desktops, mobile devices, and game consoles

Originally developed under the name **Fuel** and **NoctVM**, Noct2D
was reimagined to meet the demands of modern, production-ready
environments across diverse platforms.

---

## Quick Start

1. Download the latest release:
  Precompiled binaries are available on the [Releases page](https://github.com/awemorris/Noct2D/releases)

2. Clone and build from the repository:
  ```sh
  git clone --recursive https://github.com/awemorris/Noct2D.git
  cd Noct2D
  mkdir build
  cd build
  cmake ..
  cmake --build .
  ```

3. Run your first script
  Follow the instructions in [Getting Started Guide](docs/gettingstarted.md)

4. Explore more features
  See the Full [Documentation](docs/index.md) for scripting, API
  reference, and porting guides.

---

## ✨ Key Features

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
    - Target Windows, macOS, Linux, iOS, Android, game consoles, and WebAssembly.
    - All from a single codebase.
    - On mobile platforms (iOS, Android), ahead-of-time (AOT) compilation is available as an alternative to JIT.
- **Portable by Design**
    - Noct2D runs on nearly any computer made after the year 2000.
    - See the [Platform Guide](docs/porting.md)
- **Console-Ready**
    - Build for platforms you don't physically own,
    - With nothing but your own machine — *Go Far, Stay Close!*

---

## 🧪 Example

Here's a simple example that displays an image following the mouse
cursor. This shows the basic lifecycle: `setup` (window config),
`start` (asset loading), and `frame` (per-frame logic).


```
func setup() {
    return {
        title: "My Sample Game",
        width: 640,
        height: 480
    };
}

func start() {
    App.myTexture = API.loadTexture({file: "apple.png"});
}

func frame() {
    API.renderTexture({
	dstLeft:   API.mousePosX,
	dstTop:    API.mousePosY,
	dstWidth:  App.myTexture.width,
	dstHeight: App.myTexture.height,
	texture:   App.myTexture,
	srcLeft:   0,
	srcTop:    0,
	srcWidth:  App.myTexture.width,
	srcHeight: App.myTexture.height,
	alpha:     255
    });
}
```

📝 Note: setup() defines the window, start() loads resources, and
frame() is called each frame to render and update.

For more examples, check the [Getting Started Guide](docs/gettingstarted.md)

---

## What's Noct2D?

_"If a game engine could run anywhere, how would the world change?"_

Noct2D was born from this single question.

Noct2D is a lightweight and flexible game engine written in C89,
designed to support creators across desktop, mobile, and console platforms.

It runs smoothly even on older or low-spec machines — if you have a computer,
there's a place for you to create.

And if you're using something more powerful, like a modern MacBook or
iPhone, Noct2D adapts to draw out the full capabilities of your
device.

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

* **C89**:
  Noct2D is implemented entirely in ANSI C (C89), making it highly
  portable and dependency-free.

* **Scripting**:
  Integrates [NoctLang](https://github.com/awemorris/NoctLang), a
  lightweight language designed for clarity, performance, and fast
  startup.

* **JIT Compilation**:
  Includes a built-in JIT compiler supporting multiple architectures.  
  For mobile platforms, ahead-of-time (AOT) compilation is also available.

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
|Desktop        |Windows             |DirectX 12/11/9                           |
|               |macOS               |Metal                                     |
|               |Linux               |OpenGL                                    |
|               |FreeBSD             |OpenGL                                    |
|Mobile         |iOS                 |Metal, via Xcode project                  |
|               |Android             |OpenGL, via Android Studio project        |
|Web            |WebAssembly         |WebGL, via Emscripten                     |
|Console        |Nintendo Switch™   |Unity Plugin (C++ Native)                 |
|               |PlayStation® 5     |Unity Plugin (C++ Native)                 |
|               |Xbox Series X\|S    |Unity Plugin (C++ Native)                 |

### Noct Language and Tools

**NoctLang** is a lightweight scripting language designed specifically
for Noct2D. With a game-oriented syntax, it emphasizes clarity,
instant startup, and tight integration with the engine.

The built-in JIT compiler supports a wide range of CPU architectures,
including: **x86, x86_64, Arm32, Arm64, PowerPC32, PowerPC64, MIPS32,
and MIPS64.**

For platforms where JIT is restricted (such as mobile or consoles),
NoctLang can fall back to AOT (ahead-of-time) compilation using a C
source backend — ensuring full compatibility even in tightly
controlled environments.

## NoctScript IDE

**NoctScript** is the official IDE for Noct2D-based projects, designed
to streamline development and testing.

It includes:

- A built-in editor with syntax highlighting for NoctLang
- One-click run and debug support for Noct2D scripts
- Integrated asset preview and configuration panels
- A seamless workflow between code, assets, and runtime behavior

By separating the **core runtime (Noct2D)** from the **development
environment (NoctScript)**, you can choose to use the IDE when
convenient — or embed Noct2D directly into your own tools and
pipelines.

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

## 🤝 Join Us

Noct2D is still in its early stages. We're building a game engine with
care, hoping it will inspire and empower creators around the world.

If you're interested in contributing — whether it's code,
documentation, testing, or ideas — we'd be happy to have you with us.

Every small step helps shape what Noct2D can become. You're welcome to
join us on this journey.

[Join us on Discord](https://discord.gg/ybHWSqDVEX)

---

## About the Author

Awe (/aːwe/, "ah-weh") is a seasoned programmer living in a remote,
small house, surrounded by fields. They live in a small village,
working from home for a Japanese game console company as a systems
engineer. On holidays, they visit a nearby city to teach programming
to children.

They love writing code — it feels simple and clear. Understanding
people's feelings takes time, but tools can be kind.

This software is Awe's small universe. Thank you for visiting.
And thank you for receiving their seasoned craftsmanship.

Please use this dream-fueled engine with confidence.
It was made for you, even before we met.
