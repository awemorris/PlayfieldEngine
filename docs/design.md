NoctVM Design Overview
======================

## Porting Layer

Did you know that NoctVM runs seamlessly on Windows, macOS, Linux, iPhone,
iPad, Android, Web browsers, — and even Solaris enterprise servers?

The `src/platform` directory contains NoctVM's platform abstraction layer,
which cleanly handles all platform-specific differences.

### Common Components

|File           |Description                         |
|---------------|------------------------------------|
|image.c        |Image manipulation                  |
|stdfile.c      |File access via C stdio library     |
|glyph.c        |Font drawing via FreeType library   |
|wave.c         |OggVorbis decoder via libvorbis     |

### Windows Layer

|File           |Description                         |
|---------------|------------------------------------|
|winmain.c      |wWinMain()                          |
|d3drender.c    |Rendering dispatch                  |
|d3d12render.cc |Direct3D 12 rendering               |
|d3d11render.cc |Direct3D 11 rendering               |
|d3d9render.cc  |Direct3D 9 rendering                |
|gdirender.c    |GDI rendering                       |
|dsound.c       |DirectSound audio                   |
|dsvideo.cc     |DirectShow video                    |

### macOS Layer

|File           |Description                         |
|---------------|------------------------------------|
|nsmain.m       |main() using AppKit                 |
|GameRenderer.m |Metal rendering                     |
|aunit.c        |Audio Unit audio                    |

### Linux, BSD and Unix Layer

|File           |Description                         |
|---------------|------------------------------------|
|x11main.c      |X11 main                            |
|x11opengl.c    |OpenGL backend for X11              |
|x11softrender.c|XImage backend for X11              |
|glrender.c     |OpenGL rendering                    |
|asound.c       |ALSA audio                          |
|bsdsound.c     |/dev/dsp and /dev/audio audio       |

### iOS Layer

|File           |Description                         |
|---------------|------------------------------------|
|uimain.m       |main() using UIKit                  |
|GameRenderer.m |Metal rendering                     |
|aunit.c        |Audio Unit audio                    |

### Android Layer

|File              |Description                           |
|------------------|--------------------------------------|
|MainActivity.java |Android activity                      |
|ndkmain.c         |C code using Android NDK              |
|ndkfile.c         |Asset accedd C code using Android NDK |

### SIMD Acceleration

Only enabled on x86 and x86_64 Windows target.

|File           |Description                         |
|---------------|------------------------------------|
|drawimage.h    |Definitions of drawing functions    |
|avx2.c         |AVX2                                |
|avx.c          |AVX                                 |
|sse42.c        |SSE4.2                              |
|sse4.c         |SSE4.1                              |
|sse3.c         |SSE3                                |
|sse2.c         |SSE2                                |
|sse.c          |SSE                                 |

## Language Layer

NoctScript is a simple yet powerful scripting language that supports fast JIT
compilation and seamless translation to C.

### Compilation Flow

```
Text -> AST -> HIR -> LIR
```

Script text is first translated to an AST (Anstract Syntax Tree) by the
parser. Then the AST is transformed to HIR (High-Level Intermediate
Representaion) which is suited for optimizations. Nex, the HIR is translated
to LIR (Low-Level Intermediate Representation), also known as
"bytecode". Bytecode may be directly interpreted by the interpreter.

```
LIR -> Native
```

On platforms which is specially supported by engine, bytecode is translated to
native machine code and the native code runs. This JIT compilation is
currently supported on x86, x86_64, Arm32, Arm64, PowerPC 32, PowerPC 64,
MIPS32, and MIPS64. This will be expanded to RISC-V and SPARC in the near
future.

```
LIR -> C
```

In addition, LIR-to-C backend is available. This is useful for iOS platform
which JIT compilation is prohibited by Apple.

## Main Layer

The main layer consists of `src/*.c` files, which defines API for NoctScript.

### Tag File

Tagged file support is provided by the engine and is optionally available.
Developers may define an engine to run tag file scripts.
