Porting Status
==============

## Ported Platforms

### Windows Variants

|System                |Tested |2D |3D |Sound |Description                    |
|----------------------|-------|---|---|------|-------------------------------|
|Windows 11 x64        |v      |v  |v  |v     |Direct3D 12/11/9               |
|Windows 11 Arm64      |v      |v  |v  |v     |Direct3D 12/11/9               |
|Windows 10            |v      |v  |v  |v     |Direct3D 12/11/9               |
|Windows 8.1           |v      |v  |v  |v     |Direct3D 11/9                  |
|Windows 8             |v      |v  |v  |v     |Direct3D 11/9                  |
|Windows 7             |v      |v  |v  |v     |Direct3D 11/9                  |
|Windows Vista         |v      |v  |v  |v     |Direct3D 11/9                  |
|Windows XP            |v      |v  |v  |v     |Direct3D 9                     |
|Windows 2000          |v      |v  |v  |v     |Direct3D 9                     |
|Windows ME            |       |v  |v  |v     |Direct3D 9 / Not Tested        |
|Windows 98            |       |v  |v  |v     |Direct3D 9 / Not Tested        |
|Windows 95            |       |v  |   |v     |                               |

### macOS

|System                  |Tested |2D |3D |Sound |Description                    |
|------------------------|-------|---|---|------|-------------------------------|
|macOS 15 Sequoia        |v      |v  |v  |v     |                               |
|macOS 14 Sonoma         |v      |v  |v  |v     |                               |
|macOS 13 Ventura        |v      |v  |v  |v     |                               |
|macOS 12 Monterey       |v      |v  |v  |v     |                               |
|macOS 11 Big Sur        |v      |v  |v  |v     |                               |
|macOS 10.15 Catalina    |v      |v  |v  |v     |                               |
|macOS 10.14 Mojave      |v      |v  |v  |v     |                               |
|macOS 10.13 High Sierra |v      |v  |v  |v     |                               |

### Linux

|System                             |Tested |2D |3D |Sound |Description                    |
|-----------------------------------|-------|---|---|------|-------------------------------|
|Ubuntu 24.04 LTS Desktop (OpenGL)  |v      |v  |v  |v     |                               |
|Ubuntu 24.04 LTS Server (fbdev)    |v      |v  |   |v     |                               |
|Debian 12 (OpenGL)                 |v      |v  |   |v     |                               |
|Fedora 40 (OpenGL)                 |v      |v  |v  |v     |                               |
|Raspberry Pi OS (OpenGL)           |v      |v  |v  |v     |                               |

### iOS and Variants

|System                |Tested |2D |3D |Sound |Description                    |
|----------------------|-------|---|---|------|-------------------------------|
|iOS 17                |v      |   |v  |v     |                               |
|iOS 16                |v      |   |v  |v     |                               |
|iOS 15                |v      |   |v  |v     |                               |
|iOS 14                |v      |   |v  |v     |                               |
|iOS 13                |v      |   |v  |v     |                               |
|iOS 12                |v      |   |v  |v     |                               |
|iPadOS 17             |v      |   |v  |v     |                               |
|iPadOS 16             |v      |   |v  |v     |                               |
|iPadOS 15             |v      |   |v  |v     |                               |
|iPadOS 14             |v      |   |v  |v     |                               |
|iPadOS 13             |v      |   |v  |v     |                               |
|iPadOS 12             |v      |   |v  |v     |                               |
|visionOS 1            |v      |   |v  |v     |                               |
|visionOS 2            |       |   |v  |v     |                               |

### Android

|System                |Tested |2D |3D |Sound |Description                    |
|----------------------|-------|---|---|------|-------------------------------|
|Android 15            |v      |   |v  |v     |                               |
|Android 14            |v      |   |v  |v     |                               |
|Android 13            |v      |   |v  |v     |                               |
|Android 12            |v      |   |v  |v     |                               |
|Android 11            |v      |   |v  |v     |                               |
|Android 10            |v      |   |v  |v     |                               |

### Windows Compatible

|System                |Tested |2D |3D |Sound |Description                    |
|----------------------|-------|---|---|------|-------------------------------|
|Wine 10.0 macOS       |v      |v  |v  |v     |Direct3D 12                    |
|React OS              |       |v  |   |v     |                               |

### BSD Variants

|System                |Tested |2D |3D |Sound |Description                    |
|----------------------|-------|---|---|------|-------------------------------|
|FreeBSD               |v      |v  |v  |v     |                               |
|NetBSD                |v      |v  |v  |v     |                               |
|OpenBSD               |v      |v  |   |v     |                               |

### Unix Variants

|System                |Tested |2D |3D |Sound |Description                    |
|----------------------|-------|---|---|------|-------------------------------|
|Solaris 11            |v      |v  |   |v     |Sound not tested               |
|Solaris 10            |       |v  |   |v     |                               |
|AIX                   |       |v  |   |      |Generic POSIX port             |
|HP-UX                 |       |v  |   |      |Generic POSIX port             |
|Darwin                |v      |v  |   |      |Generic POSIX port             |

### Niche

|System                |Tested |2D |3D |Sound |Description                    |
|----------------------|-------|---|---|------|-------------------------------|
|Haiku                 |v      |v  |v  |      |Sound not tested               |
|BeOS                  |       |v  |v  |      |Sound not tested               |

## How To Port

* Create a source code that defines `main()` and the functions defined in `platform.h`.
* You can reuse some functions by using `image.c`, `glyph.c`, and `wave.c`.
* The Haiku/BeOS port is very simple and easy to understand how to port.
