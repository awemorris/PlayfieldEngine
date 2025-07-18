/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * C89 Compatibility
 */

#ifndef C89COMPAT_H
#define C89COMPAT_H

/*
 * Here we define a macro that indicates a target platform.
 *
 * |Macro           |Platform              |Description                 |
 * |----------------|----------------------|----------------------------|
 * |TARGET_WINDOWS  |Windows               |                            |
 * |TARGET_MACOS    |macOS                 |                            |
 * |TARGET_LINUX    |Linux                 |Excluding Adnroid           |
 * |TARGET_IOS      |iOS                   |                            |
 * |TARGET_ANDROID  |Android NDK           |                            |
 * |TARGET_WASM     |Wasm                  |Emscripten                  |
 * |TARGET_FREEBSD  |FreeBSD               |Excluding Gaming Consoles   |
 * |TARGET_NETBSD   |NetBSD                |                            |
 * |TARGET_OPENBSD  |OpenBSD               |                            |
 * |TARGET_SOLARIS  |Solaris               |                            |
 * |TARGET_POSIX    |Generic POSIX         |                            |
 * |TARGET_BEOS     |BeOS and Haiku        |                            |
 */

/* Windows */
#if defined(_WIN32) && !defined(USE_UNITY)
#define TARGET_WINDOWS
#endif

/* macOS / iOS */
#if !defined(USE_UNITY)
#if defined(__GNUC__)
#if defined(__APPLE__) && __has_include(<TargetConditionals.h>)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define TARGET_IOS
#elif TARGET_OS_OSX
#define TARGET_MACOS
#endif
#endif
#endif
#endif

/* Linux (non-Android) */
#if defined(__linux) && !defined(__ANDROID__) && !defined(USE_UNITY)
#define TARGET_LINUX
#ifndef TARGET_POSIX
#define TARGET_POSIX
#endif
#endif

/* FreeBSD */
#if defined(__FreeBSD__)
#define TARGET_FREEBSD
#ifndef TARGET_POSIX
#define TARGET_POSIX
#endif
#endif

/* NetBSD */
#if defined(__NetBSD__)
#define TARGET_NETBSD
#ifndef TARGET_POSIX
#define TARGET_POSIX
#endif
#endif

/* OpenBSD */
#if defined(__OpenBSD__)
#define TARGET_OPENBSD
#ifndef TARGET_POSIX
#define TARGET_POSIX
#endif
#endif

/* Solaris */
#if defined(__sun)
#define TARGET_SOLARIS
#ifndef TARGET_POSIX
#define TARGET_POSIX
#endif
#endif

/* Android */
#if defined(__ANDROID__)
#define TARGET_ANDROID
#endif

/* Wasm (Emscripten) */
#if defined(__EMSCRIPTEN__)
#define TARGET_WASM
#endif

/* BeOS / Haiku */
#if defined(__BEOS__) || defined(__HAIKU__)
#define TARGET_BEOS
#endif

/* Error: No target detected. */
#if !defined(TARGET_WINDOWS) && \
    !defined(TARGET_MACOS) &&   \
    !defined(TARGET_LINUX) &&   \
    !defined(TARGET_FREEBSD) &&   \
    !defined(TARGET_NETBSD) &&   \
    !defined(TARGET_OPENBSD) &&   \
    !defined(TARGET_SOLARIS) &&   \
    !defined(TARGET_IOS) &&     \
    !defined(TARGET_ANDROID) && \
    !defined(TARGET_WASM) && \
    !defined(TARGET_BEOS) && \
    !defined(USE_UNITY)
#error "No target detected."
#endif

/*
 * For GCC/Clang
 */
#if defined(__GNUC__)

/* Define a macro that indicates a target architecture. */
#if defined(__i386__) && !defined(__x86_64__)
#define ARCH_X86
#elif defined(__x86_64__)
#define ARCH_X86_64
#elif defined(__aarch64__)
#define ARCH_ARM64
#elif defined(__arm__)
#define ARCH_ARM32
#elif defined(_ARCH_PPC64)
#define ARCH_PPC64
#elif defined(_ARCH_PPC)
#define ARCH_PPC32
#endif

/* Define a macro that indicates a endian. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define ARCH_LE
#else
#define ARCH_BE
#endif

/* uint*_t and int*_t */
#include <stdint.h>

/* size_t */
#include <stddef.h>

/* bool */
#ifndef __cplusplus
#include <stdbool.h>
#endif

/* Inline function. */
#define INLINE				__inline

/* No pointer aliasing. */
#define RESTRICT			__restrict

/* Suppress unused warnings. */
#define UNUSED_PARAMETER(x)		(void)(x)

/* UTF-8 string literal. */
#define U8(s)				u8##s

/* UTF-32 character literal. */
#define U32C(literal, unicode)		U##literal

/* Secure strcpy() */
#if defined(TARGET_WINDOWS)
#define strlcpy(d, s, l)		strcpy_s(d, l, s)
#define strlcat(d, s, l)		strcat_s(d, l, s)
#endif
#if defined(TARGET_LINUX) && !(defined(__GLIBC__) && (__GLIBC__ >= 2 && __GLIBC_MINOR__ >= 38))
#include <stdio.h>
#include <string.h>
inline void strlcpy(char *d, const char *s, size_t len)
{
	snprintf(d, len, "%s", s);
}
inline void strlcat(char *d, const char *s, size_t len)
{
	size_t l = strlen(d);
	if (len > l)
		snprintf(d + l, len - l, "%s", s);
}
#endif

#endif /* End of GCC/Clang */

/*
 * For MSVC
 */
#ifdef _MSC_VER

#if defined(_M_IX86)
#define ARCH_X86
#elif defined(_M_X64)
#define ARCH_X86_64
#elif defined(_M_ARM64)
#define ARCH_ARM64
#endif

#define ARCH_LE

/* Do not get warnings for usages of string.h functions. */
#define _CRT_SECURE_NO_WARNINGS

/* POSIX libc to MSVCRT mapping */
#define strdup _strdup
#define strcasecmp _stricmp

#include <stdint.h>
#include <stddef.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#define INLINE				__inline
#define RESTRICT			__restrict
#define UNUSED_PARAMETER(x)		(void)(x)
#define U8(s)				u8##s
#define U32C(literal, unicode)		U##literal

#define strlcpy(s, d, l)		strcpy_s(s, l, d)
#define strlcat(s, d, l)		strcat_s(s, l, d)

#endif /* End of MSVC */

/*
 * For Sun Studio
 */
#if defined(__sun) && !defined(__GNUC__)

#if defined(__sparc)
#define ARCH_SPARC
#else
#define ARCH_X86_64
#endif

#include <stddef.h>
#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#define INLINE				__inline
#define RESTRICT			__restrict
#define UNUSED_PARAMETER(x)		(void)(x)
#define U8(s)				u8##s
#define U32_C(literal, unicode)		(unicode)

#endif /* End of Sun Studio */

/*
 * Byteorder
 */

#ifdef ARCH_LE
#define HOSTTOLE64(d)	(d)
#define HOSTTOLE32(d)	(d)
#define HOSTTOLE16(d)	(d)
#define HOSTTOBE64(d)	((((d) & 0xff) << 48) | ((((d) >> 8) & 0xff) << 40) | ((((d) >> 16) & 0xff) << 32) | ((((d) >> 24) & 0xff) << 24) | ((((d) >> 32) & 0xff) << 16) | ((((d) >> 40) & 0xff) << 8) | ((((d) >> 48) & 0xff)))
#define HOSTTOBE32(d)	((((d) & 0xff) << 24) | ((((d) >> 8) & 0xff) << 16) | ((((d) >> 16) & 0xff) << 8) | (((d) >> 24) & 0xff))
#define HOSTTOBE16(d)	((((d) & 0xff) << 8) | (((d) >> 8) & 0xff))
#define LETOHOST64(d)	(d)
#define LETOHOST32(d)	(d)
#define LETOHOST16(d)	(d)
#define BETOHOST64(d)	((((d) & 0xff) << 48) | ((((d) >> 8) & 0xff) << 40) | ((((d) >> 16) & 0xff) << 32) | ((((d) >> 24) & 0xff) << 24) | ((((d) >> 32) & 0xff) << 16) | ((((d) >> 40) & 0xff) << 8) | ((((d) >> 48) & 0xff)))
#define BETOHOST32(d)	((((d) & 0xff) << 24) | ((((d) >> 8) & 0xff) << 16) | ((((d) >> 16) & 0xff) << 8) | (((d) >> 24) & 0xff))
#define BETOHOST16(d)	((((d) & 0xff) << 8) | (((d) >> 8) & 0xff))
#else
#define HOSTTOLE64(d)	((((d) & 0xff) << 48) | ((((d) >> 8) & 0xff) << 40) | ((((d) >> 16) & 0xff) << 32) | ((((d) >> 24) & 0xff) << 24) | ((((d) >> 32) & 0xff) << 16) | ((((d) >> 40) & 0xff) << 8) | ((((d) >> 48) & 0xff)))
#define HOSTTOLE32(d)	((((d) & 0xff) << 24) | ((((d) >> 8) & 0xff) << 16) | ((((d) >> 16) & 0xff) << 8) | (((d) >> 24) & 0xff))
#define HOSTTOLE16(d)	((((d) & 0xff) << 8) | (((d) >> 8) & 0xff))
#define HOSTTOBE64(d)	(d)
#define HOSTTOBE32(d)	(d)
#define HOSTTOBE16(d)	(d)
#define LETOHOST64(d)	((((d) & 0xff) << 48) | ((((d) >> 8) & 0xff) << 40) | ((((d) >> 16) & 0xff) << 32) | ((((d) >> 24) & 0xff) << 24) | ((((d) >> 32) & 0xff) << 16) | ((((d) >> 40) & 0xff) << 8) | ((((d) >> 48) & 0xff)))
#define LETOHOST32(d)	((((d) & 0xff) << 24) | ((((d) >> 8) & 0xff) << 16) | ((((d) >> 16) & 0xff) << 8) | (((d) >> 24) & 0xff))
#define LETOHOST16(d)	((((d) & 0xff) << 8) | (((d) >> 8) & 0xff))
#define BETOHOST64(d)	(d)
#define BETOHOST32(d)	(d)
#define BETOHOST16(d)	(d)
#endif

/*
 * Message Translation
 */

#if !defined(USE_TRANSLATION)
#define _(text)		text
#else
#define _(text)		translation_gettext(text)
const char *translation_gettext(const char *msg);
#endif

#endif
