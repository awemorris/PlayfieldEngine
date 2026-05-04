StratoHAL
=========

`StratoHAL` is a highly portable hardware abstraction layer (HAL) for
game applications. It is written as one of the core building blocks of
the [Suika3](https://github.com/awemorris/suika3) game scripting
runtime, and later, it was published as an independent library.

It provides:
- Built-in game loop and callback mechanism.
- API for 2D graphics, audio, and input.
- GPU acceleration as well as software rendering.

It runs across many modern and classic platforms:
- Windows
- macOS
- Linux
- *BSD (FreeBSD, NetBSD, and OpenBSD)
- iOS
- Android
- HarmonyOS NEXT (OpenHarmony)
- WebAssembly
- ChromeOS
- Solaris 10 / 11
- Haiku OS
- Unity (as a native plugin)
- Xbox (via Unity Plugin, DevKit required)
- PlayStation 4 / PlayStation 5 (via Unity Plugin, DevKit required)
- Switch / Switch 2 (via Unity Plugin, DevKit required)

StratoHAL supports most major platforms that SDL3 covers. In addition,
it supports software rendering for small embedded devices and older
computers.

## Backends

| Platform                    | Graphics                                                                | Audio                    | Input                                                                    |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| Windows                     | DirectX 12/11/9 and GDI (fallback)                                      | DirectSound 5            | DirectInput 8 (for PS5 controllers) and GameInput (for Xbox controllers) |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| Microsoft GDK (PC and Xbox) | DirectX 12                                                              | XAudio2                  | XInput                                                                   |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| macOS                       | Metal                                                                   | AudioUnit                | GameController                                                           |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| Linux                       | (Wayland, X11, KMS, fbdev) x (OpenGL ES2, OpenGL 3, software rendering) | ALSA                     | Wayland, X11, and evdev                                                  |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| FreeBSD                     | (Wayland, X11) x (OpenGL ES2, OpenGL 3, software rendering)             | /dev/dsp                 | Wayland or X11                                                           |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| NetBSD                      | X11 x (OpenGL 3, software rendering)                                    | /dev/audio               | X11                                                                      |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| OpenBSD                     | X11 x (OpenGL 3, software rendering)                                    | /dev/audio               | X11                                                                      |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| Solaris 10                  | X11 x software rendering                                                | /dev/audio               | X11                                                                      |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| Solaris 11                  | X11 x software rendering                                                | /dev/dsp (OSS)           | X11                                                                      |
|-----------------------------|-------------------------------------------------------------------------|--------------------------|--------------------------------------------------------------------------|
| Haiku OS                    | Haiku native + software rendering                                       | Haiku native             | Haiku native                                                             |

## About the Name

"Strato" comes from a Latin word "stratum", i.e., a layer, for hardware abstracion.
