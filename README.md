Noct2D
======

Noct2D is a crazy portable game engine that uses [NoctLang](https://github.com/awemorris/NoctLang) for scripting.

- Tiny: Core runtime ~2.0MB for instant downloads and startup.
- Fast: Low-latency game loops via JIT-optimized NoctLang.
- Portable: Desktop, mobile, Web, consoles — all from a single codebase.

It provides:

- Scripting: NoctLang, a fast, lightweight, game-oriented language
- Graphics: DirectX12, Metal, OpenGL
- Audio: DirectSound, Audio Unit, ALSA, OpenAL
- Input: Keybaord, mouse, touch, and gamepad.

**Noct2D aims to be the most portable 2D game engine in the world!**

---

## Quick Start

1. Download the latest release:
  Precompiled binaries are available on the [Releases page](https://github.com/awemorris/Noct2D/releases)

2. Clone and build from the repository:
  ```
  git clone https://github.com/awemorris/Noct2D.git
  cd Noct2D
  git submodule update --init
  cmake -B build .
  cmake --build build
  ./build/noct2d
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

## 🧪 Example

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
    Engine.renderTexture({
	texture: myTexture
	x: Engine.mousePosX,
	y: Engine.mousePosY,
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
  The entire runtime fits within ~3MB, making it suitable for embedded
  systems or constrained environments.

### Platform Support

|Platform Type  |OS / Platform       |Notes                                     |
|---------------|--------------------|------------------------------------------|
|Desktop        |Windows             |DirectX 12/11/9                           |
|               |macOS               |Metal                                     |
|               |ChromeOS            |OpenGL                                    |
|               |Linux               |OpenGL / Soft Renderer                    |
|               |*BSD                |OpenGL / Soft Renderer                    |
|               |Haiku               |Soft Renderer                             |
|               |Qt                  |OpenGL                                    |
|Mobile         |iOS                 |Metal, via Xcode project                  |
|               |Android             |OpenGL, via Android Studio project        |
|Web            |WebAssembly         |WebGL, via Emscripten                     |
|Console        |Nintendo Switch™   |Unity Plugin (Native)                     |
|               |PlayStation® 5     |Unity Plugin (Native)                     |
|               |Xbox Series X\|S    |Unity Plugin (Native)                     |

### Noct Language

**NoctLang** is a lightweight scripting language designed specifically
for Noct2D. With a game-oriented syntax, it emphasizes clarity,
instant startup, and tight integration with the engine.

The built-in JIT compiler supports a wide range of CPU architectures,
including both 32-bit and 64-bit of: **Intel, Arm, RISC-V, PowerPC, MIPS.**

For platforms where JIT is restricted (such as mobile or consoles),
NoctLang can fall back to AOT (ahead-of-time) compilation using a C
source backend — ensuring full compatibility even in tightly
controlled environments.

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
