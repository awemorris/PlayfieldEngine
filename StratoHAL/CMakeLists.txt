cmake_minimum_required(VERSION 3.16)
project(StratoHAL LANGUAGES C CXX)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version")

#
# Configuration
#

option(ENABLE_GLX     "Enable OpenGL on X11"    ON)
option(ENABLE_I18N    "Enable translation"      ON)
option(ENABLE_SHARED  "Enable shared libraries" OFF)
option(ENABLE_OBJECT  "Build object library"    OFF)

#
# Target Detection
#

option(TARGET_WASM    "Emscripten"     OFF)
option(TARGET_ANDROID "Android NDK"    OFF)
option(TARGET_UNITY   "Unity plugin"   OFF)

if(WIN32)
  set(TARGET_WINDOWS ON)
endif()

if(APPLE AND NOT IOS AND NOT TARGET_UNITY)
  set(TARGET_MACOS ON)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(TARGET_LINUX ON)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
  set(TARGET_FREEBSD ON)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "NetBSD")
  set(TARGET_NETBSD ON)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "OpenBSD")
  set(TARGET_OPENBSD ON)
endif()

if(UNIX)
  set(TARGET_POSIX ON)
endif()

# Haiku
if(CMAKE_SYSTEM_NAME STREQUAL "Haiku")
  set(TARGET_HAIKU ON)
endif()

# Wasm (Manual)
if(TARGET_WASM)
endif()

# Android (Manual)
if(TARGET_ADNROID)
endif()

# Unity (Manual)
if(TARGET_UNITY)
endif()

#
# Build Type
#

# Use "Release" build type by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Debug or Release)" FORCE)
endif()

# Debug Configuration
if(MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /Od /Zi /DDEBUG /UNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi /DDEBUG /UNDEBUG")
else()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -O0 -g3 -UNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O0 -g3 -UNDEBUG")
endif()

# Release Configuration
if(MSVC)
  # MSVC
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
  # GCC/Clang
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -g0 -DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -g0 -DNDEBUG")
endif()

#
# Dependency
#

if(NOT ENABLE_SHARED OR ENABLE_OBJECT)
  include(cmake/zlib.cmake)
  include(cmake/libpng.cmake)
  include(cmake/jpeg.cmake)
  include(cmake/libwebp.cmake)
  include(cmake/libogg.cmake)
  include(cmake/libvorbis.cmake)
  include(cmake/brotli.cmake)
  include(cmake/bzip2.cmake)
  include(cmake/freetype.cmake)
else()
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
  find_package(PNG REQUIRED)
  find_package(JPEG REQUIRED)
  find_package(WebP REQUIRED)
  find_package(Ogg REQUIRED)
  find_package(Vorbis MODULE REQUIRED)
  find_package(Freetype REQUIRED)
  find_package(Brotli REQUIRED)
  find_package(BZip2 REQUIRED)
  find_package(ZLIB REQUIRED)
endif()

#
# Checks
#

include(CheckIncludeFile)

check_include_file("stdint.h" HAVE_STDINT_H)
if(HAVE_STDINT_H)
  add_definitions(-DHAVE_STDINT_H=1)
endif()

check_include_file("inttypes.h" HAVE_INTTYPES_H)
if(HAVE_INTTYPES_H)
  add_definitions(-DHAVE_INTTYPES_H=1)
endif()

check_include_file("sys/types.h" HAVE_SYS_TYPES_H)
if(HAVE_SYS_TYPES_H)
  add_definitions(-DHAVE_SYS_TYPES_H=1)
endif()

#
# Source Files
#

# For Windows.
if(TARGET_WINDOWS)
  set(SOURCES
    src/image.c
    src/glyph.c
    src/wave.c
    src/stdfile.c
    src/winmain.c
    src/d3drender.c
    src/d3d12render.cc
    src/d3d11render.cc
    src/d3d9render.cc
    src/gdirender.c
    src/dsound.c
    src/dsvideo.cc
  )
endif()

# For macOS.
if(TARGET_MACOS)
  set(SOURCES
    src/image.c
    src/glyph.c
    src/wave.c
    src/stdfile.c
    src/nsmain.m
    src/aunit.c
    src/GameRenderer.m
    src/GameShaders.c
  )
endif()

# For POSIX (X11).
if(TARGET_POSIX AND NOT TARGET_MACOS AND NOT TARGET_HAIKU AND NOT TARGET_WASM AND NOT TARGET_UNITY)
  set(SOURCES
    src/image.c
    src/glyph.c
    src/wave.c
    src/stdfile.c
    src/x11main.c
    src/x11opengl.c
    src/x11softrender.c
    src/icon.c
    src/glrender.c
    src/asound.c
    src/bsdsound.c
    src/nosound.c
    src/gstplay.c
  )
endif()

# For Emscripten.
if(TARGET_WASM)
  set(SOURCES
    src/image.c
    src/glyph.c
    src/wave.c
    src/stdfile.c
    src/emmain.c
    src/alsound.c
    src/glrender.c
  )
endif()

# For Android.
if(TARGET_ANDROID)
  set(SOURCES
    src/image.c
    src/glyph.c
    src/wave.c
    src/glrender.c
    src/slsound.c
    src/ndkmain.c
    src/ndkfile.c
  )
endif()

# For Unity.
if(TARGET_UNITY)
  set(SOURCES
    src/image.c
    src/glyph.c
    src/wave.c
    src/halwrap.c
  )
endif()

# For Haiku.
if(TARGET_HAIKU)
  set(SOURCES
    src/image.c
    src/glyph.c
    src/wave.c
    src/stdfile.c
    src/platform/bemain.cc
  )
endif()

# For translation.
if(ENABLE_I18N)
  set(I18N_SOURCES
    src/translation.c
  )
endif()

if(ENABLE_OBJECT)
  add_library(strato OBJECT
    ${SOURCES}
    ${I18N_SOURCES}
    $<TARGET_OBJECTS:png>
    $<TARGET_OBJECTS:jpeg>
    $<TARGET_OBJECTS:webp>
    $<TARGET_OBJECTS:vorbisfile>
    $<TARGET_OBJECTS:vorbis>
    $<TARGET_OBJECTS:ogg>
    $<TARGET_OBJECTS:freetype>
    $<TARGET_OBJECTS:brotlidec>
    $<TARGET_OBJECTS:brotlicommon>
    $<TARGET_OBJECTS:bz2>
    $<TARGET_OBJECTS:z>
  )
elseif(ENABLE_SHARED)
  add_library(strato SHARED ${SOURCES})
else()
  add_library(strato STATIC
    ${SOURCES}
    ${I18N_SOURCES}
    $<TARGET_OBJECTS:png>
    $<TARGET_OBJECTS:jpeg>
    $<TARGET_OBJECTS:webp>
    $<TARGET_OBJECTS:vorbisfile>
    $<TARGET_OBJECTS:vorbis>
    $<TARGET_OBJECTS:ogg>
    $<TARGET_OBJECTS:freetype>
    $<TARGET_OBJECTS:brotlidec>
    $<TARGET_OBJECTS:brotlicommon>
    $<TARGET_OBJECTS:bz2>
    $<TARGET_OBJECTS:z>
  )
endif()

# Windows specific.
if(TARGET_WINDOWS)
  enable_language(RC)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  file(ARCHIVE_EXTRACT
    INPUT       ${CMAKE_CURRENT_SOURCE_DIR}/lib/archive/dx12headers.tar.gz
    DESTINATION ${CMAKE_BINARY_DIR}
  )
endif()

# macOS specific
if(TARGET_MACOS)
  enable_language(OBJC)
endif()

# For translation.
if(ENABLE_I18N)
  target_compile_definitions(strato PRIVATE USE_TRANSLATION)
endif()

# For Unity
if(TARGET_UNITY)
  target_compile_definitions(strato PRIVATE USE_UNITY)
endif()

#
# Archiver
#

if(NOT TARGET_WASM AND NOT TARGET_ANDROID AND NOT TARGET_IOS AND NOT TARGET_UNITY)
  add_library(
    stratopack
    STATIC
    src/archive.c
  )
  target_include_directories(stratopack PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

#
# CPPFLAGS
#

#-Dinclude
target_include_directories(strato PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(strato PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)

# -DUSE_SHARED if we use dynamic linking.
if(ENABLE_SHARED)
  target_compile_definitions(strato PRIVATE USE_SHARED)
endif()

# -DUSE_JIT if we use JIT.
if(ENABLE_JIT)
  target_compile_definitions(strato PRIVATE USE_JIT)
endif()

# -DUSE_GLX if we use OpenGL on X11.
if(TARGET_POSIX AND NOT TARGET_HAIKU AND NOT TARGET_WASM)
  if(ENABLE_GLX)
    target_compile_definitions(strato PRIVATE USE_X11_OPENGL)
  else()
    target_compile_definitions(strato PRIVATE USE_X11_SOFTRENDER)
  endif()
endif()

# Add library header directories.
target_include_directories(strato PRIVATE ${PNG_INCLUDE_DIRS})
target_include_directories(strato PRIVATE ${JPEG_INCLUDE_DIRS})
target_include_directories(strato PRIVATE ${WEBP_INCLUDE_DIRS})
target_include_directories(strato PRIVATE ${OGG_INCLUDE_DIRS})
target_include_directories(strato PRIVATE ${VORBIS_INCLUDE_DIRS})
target_include_directories(strato PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(strato PRIVATE ${BROTLI_INCLUDE_DIRS})
target_include_directories(strato PRIVATE ${BZIP2_INCLUDE_DIRS})
target_include_directories(strato PRIVATE ${ZLIB_INCLUDE_DIRS})

# Windows: Add -Ires -Idx12headers/include/directx -Idx12headers/include/fxguids
if(TARGET_WINDOWS)
  target_include_directories(strato PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${CMAKE_BINARY_DIR}/dx12headers/include/directx
    ${CMAKE_BINARY_DIR}/dx12headers/include/dxguids
  )
endif()

# FreeBSD: Add -I/usr/local/include
if(TARGET_FREEBSD)
  target_include_directories(strato PRIVATE /usr/local/include)
  target_include_directories(strato PUBLIC  /usr/local/include)
endif()

# NetBSD: Add -I/usr/local/include -I/usr/X11R7/include
if(TARGET_NETBSD)
  target_include_directories(strato PRIVATE /usr/local/include /usr/X11R7/include)
  target_include_directories(strato PUBLIC  /usr/local/include /usr/X11R7/include)
endif()

# OpenBSD: Add -I/usr/local/include -I/usr/X11R6/include
if(TARGET_OPENBSD)
  target_include_directories(strato PRIVATE /usr/local/include /usr/X11R6/include)
  target_include_directories(strato PUBLIC  /usr/local/include /usr/X11R6/include)
endif()

#
# CFLAGS
#

# Windows compile options.
if(TARGET_WINDOWS)
  # -municode
  if(MINGW)
    target_compile_options(strato PUBLIC -municode)
  endif()

  # /utf-8
  if(MSVC)
    target_compile_options(strato PUBLIC /utf-8)
    target_compile_definitions(strato PUBLIC UNICODE _UNICODE)
  endif()
endif()

#
# Link
#

# Libraries.
if(ENABLE_SHARED)
  target_link_libraries(strato PRIVATE
    ${PNG_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${WEBP_LIBRARIES}
    ${VORBIS_LIBRARY}
    ${VORBISFILE_LIBRARY}
    ${OGG_LIBRARY}
    ${FREETYPE_LIBRARY}
    ${BROTLIDEC_LIBRARIES}
    ${BROTLICOMMON_LIBRARIES}
    ${BZIP2_LIBRARIES}
    ${ZLIB_LIBRARIES}
  )
endif()

# Windows link options.
if(TARGET_WINDOWS)
  # DLLs.
  target_link_libraries(strato PUBLIC
    gdi32
    ole32
    dsound
    strmiids
    dxguid
  )

  # -mwindows -municode
  if(MINGW)
    target_link_options(strato PUBLIC
      -mwindows
      -municode
    )
  endif()

  # /SUBSYSTEM:WINDOWS
  if(MSVC)
    target_link_options(strato PUBLIC
      /SUBSYSTEM:WINDOWS
      /ENTRY:wWinMainCRTStartup
      /MANIFEST:NO
    )
  endif()
endif()

# macOS link options.
if(TARGET_MACOS)
  target_compile_options(strato PRIVATE -fmodules)
  target_compile_options(strato PUBLIC  -fmodules)

  target_link_libraries(strato PRIVATE
    "-framework AppKit"
    "-framework MetalKit"
    "-framework AVFoundation"
  )
  target_link_libraries(strato PUBLIC
    "-framework AppKit"
    "-framework MetalKit"
    "-framework AVFoundation"
  )
endif()

# POSIX GLX: Add -lGL -lGLX
if(TARGET_POSIX AND NOT TARGET_MACOS AND NOT TARGET_WASM)
  if(ENABLE_GLX)
    target_link_libraries(strato PRIVATE GL GLX)
    target_link_libraries(strato PUBLIC  GL GLX)
  endif()
endif()

# POSIX: Add -lm -lpthread -lXpm -lX11
if(TARGET_POSIX AND NOT TARGET_MACOS AND NOT TARGET_WASM)
  target_link_libraries(strato PRIVATE m pthread Xpm X11)
  target_link_libraries(strato PUBLIC  m pthread Xpm X11)
endif()

# Linux: Add -lasound
if(TARGET_LINUX AND NOT TARGET_UNITY)
  target_link_libraries(strato PRIVATE asound)
  target_link_libraries(strato PUBLIC  asound)
endif()

# FreeBSD: Add -L/usr/local/lib -L/usr/X11R7/lib
if(TARGET_FREEBSD)
  target_link_directories(strato PRIVATE /usr/local/lib /usr/X11R7/lib)
  target_link_directories(strato PUBLIC /usr/local/lib /usr/X11R7/lib)
endif()

# NetBSD: Add -L/usr/local/lib -L/usr/X11R7/lib
if(TARGET_NETBSD)
  target_link_directories(strato PRIVATE /usr/local/lib /usr/X11R7/lib)
  target_link_directories(strato PUBLIC  /usr/local/lib /usr/X11R7/lib)
endif()

# OpenBSD: Add -L/usr/local/lib -L/usr/X11R6/lib
if(TARGET_OPENBSD)
  target_link_directories(strato PRIVATE /usr/local/lib /usr/X11R6/lib)
  target_link_directories(strato PUBLIC  /usr/local/lib /usr/X11R6/lib)
endif()

# Android: Add -lgles
if(TARGET_ANDROID)
  target_link_libraries(strato PUBLIC -lm -lGLESv3 -lOpenSLES -llog)
endif()

# Haiku: Add -lbe -lmedia
if(TARGET_HAIKU)
  target_link_libraries(strato PRIVATE be media)
  target_link_libraries(strato PUBLIC  be media)
endif()
