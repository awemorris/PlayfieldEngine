Noct2D
======

Welcome to Noct2D, a game engine fueled by your dreams.

---

* For Beginners
    * [Getting Started](gettingstarted.md)
    * [Noct2D Syntax](syntax.md)
    * [Noct2D Engine API](api.md)

* For Contributors
    * [How To Build](build.md)
    * [Design Overview](design.md)
    * [Porting Information](porting.md)

---

## What's Noct2D?

“If a game engine could run anywhere, how would the world change?”

Noct2D was born from this single question.

Noct2D is a lightweight and flexible game engine written in C89,
designed to support creators across desktop, mobile, and console platforms.

It runs smoothly even on older or low-spec machines — if you have a computer,
there's a place for you to create. 💻🌱

And if you're using something more powerful, like a modern MacBook or
iPhone, Noct2D adapts to draw out the full capabilities of your
device. 🎮📱

You don't need the latest hardware. Noct2D helps you go beyond your
environment. It's a helpful companion for creators everywhere —
especially in places with fewer resources.

Create at your pace, wherever you are in the world. 🌍✨

--

## ✨ Key Features

* **Jot & Run** — No boilerplates. Jot down an idea, and it comes alive.
* **Lightweight** — Runs even on small or older machines.
* **Ultra Fast** — Built-in JIT compiler brings ultra speed into your code.
* **Go Far, Stay Close** — Develop for distant platforms, with nothing but your own machine.
* **Amazingly Portable** — Runs on [any post-2000 computer,](porting.md) from under-resourced hardware to cutting-edge systems.

---

## Why Noct2D?

Noct2D is for those who quietly hold a dream, and wish to share it, one
small step at a time.

Creativity shouldn't depend on the power of your computer, where you
live, or what tools you have.

Noct2D was created with the hope that every creator deserves space to
explore, no matter their surroundings.

Whether you're using a Raspberry Pi in a classroom, or using a
UN-issued Chromebook in a temporary shelter — including refugee camps
and disaster relief environments — Noct2D offers gentle tools to help
bring your ideas to life — in a way that feels simple, thoughtful,
and yours. If you have something to make, Noct2D will be here to walk
with you.

Dreams fuel it — and they're the only requirement.

---

## Technical Overview

### Core Architecture

* **Engine Core**: Written in C89, portable and dependency-free.
* **Scripting**: Uses `Noct2D`, a custom language designed for clarity and fast execution.
* **JIT Compilation**: Built-in JIT for many architectures, with optional AOT for mobile platforms.
* **Rendering**: Supports DirectX 9/11/12, Metal, OpenGL, and a fallback software renderer.
* **Audio**: Lightweight backend supporting DirectSound, Audio Unit, ALSA, and others.
* **Small Footprint**: Runtime is less than 2MB.

### Platform Support

|Platform Type  |OS / Platform       |Notes                                     |
|---------------|--------------------|------------------------------------------|
|Desktop        |Windows             |Supports DirectX                          |
|               |macOS               |Supports Metal                            |
|               |Linux               |Supports OpenGL                           |
|               |FreeBSD             |Supports OpenGL                           |
|Mobile         |iOS                 |Source export for Xcode projects          |
|               |Android             |Source export for Android Studio projects |
|Console        |Nintendo Switch™   |NDA license required                      |
|               |PlayStation® 5     |NDA license required                      |
|               |Xbox Series X\|S    |NDA license required                      |
|Web            |WebAssembly         |Supports WebGL                            |

### NoctLang

`NoctLang` is a lightweight scripting language designed specifically
for Noct2D. Featuring a game-oriented syntax, it emphasizes clarity,
instant startup, and seamless integration with the engine.

Built-in JIT compiler supports multiple architectures:
**Both 32-bit and 64-bit of x86, Arm, RISC-V, PowerPC, MIPS.**

For platforms where JIT is restricted, its C source backend enables
AOT compilation, making it ideal for mobile deployment.

---

## License Overview

Noct2D uses dual-licensing.

### Open Source License

Noct2D is available as open-source software under the MIT License.
You're free to use, modify, and share it — even in commercial
projects.  Please see the LICENSE file in the repository for full
details.

Support is provided on a best-effort, community-driven basis.  If you
require guaranteed support, please contact the author to discuss an
agreement.

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

Awe (/aːwe/, "ah-weh") is a programmer living alone in a small house,
surrounded by fields. They love writing code — it feels simple and
clear.  Understanding people's feelings takes time, but tools can be
kind.

This software is Awe's small universe. Thank you for visiting. And
thank you for receiving their seasoned craftsmanship.

Please use this dream-fueled engine with confidence.
It was made for you, even before we met.
