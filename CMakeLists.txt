cmake_minimum_required(VERSION 3.16)
project(Noct2D LANGUAGES C CXX)

#
# Configuration
#

# Target
option(NOCT2D_TARGET_WINDOWS       "Build for Windows"       OFF)
option(NOCT2D_TARGET_MACOS         "Build for macOS"         OFF)
option(NOCT2D_TARGET_LINUX         "Build for Linux"         OFF)
option(NOCT2D_TARGET_IOS           "Build for iOS"           OFF)
option(NOCT2D_TARGET_ANDROID       "Build for Android"       OFF)
option(NOCT2D_TARGET_WASM          "Build for Emscripten"    OFF)
option(NOCT2D_TARGET_UNITY         "Build for Unity"         OFF)
option(NOCT2D_TARGET_FREEBSD       "Build for FreeBSD"       OFF)
option(NOCT2D_TARGET_NETBSD        "Build for NetBSD"        OFF)
option(NOCT2D_TARGET_OPENBSD       "Build for OpenBSD"       OFF)
option(NOCT2D_TARGET_HAIKU         "Build for Haiku"         OFF)

# Options
option(NOCT2D_ENABLE_JIT           "Enable JIT"              OFF)
option(NOCT2D_ENABLE_I18N          "Enable translation"      OFF)
option(NOCT2D_ENABLE_GLX           "Enable OpenGL on X11"    OFF)
option(NOCT2D_ENABLE_FBDEV         "Enable fbdev on Linux"   OFF)
option(NOCT2D_ENABLE_BUNDLE        "Enable macOS bundle"     OFF)
option(NOCT2D_ENABLE_PACK          "Enable packager"         OFF)
option(NOCT2D_ENABLE_STATIC        "Build a static library"  OFF)
option(NOCT2D_ENABLE_SHARED        "Build a dynamic library" OFF)
option(NOCT2D_ENABLE_DIST          "Build for packages"      OFF)

#
# Automatic Target Detection
#

# For when a target is manually specified.
if(   NOCT2D_TARGET_WINDOWS
   OR NOCT2D_TARGET_MACOS
   OR NOCT2D_TARGET_LINUX
   OR NOCT2D_TARGET_IOS
   OR NOCT2D_TARGET_ANDROID
   OR NOCT2D_TARGET_WASM
   OR NOCT2D_TARGET_UNITY
   OR NOCT2D_TARGET_FREEBSD
   OR NOCT2D_TARGET_NETBSD
   OR NOCT2D_TARGET_OPENBSD
)
  # A target and options are manually specified.
else()   
  if(WIN32)
    # Windows is detected.
    set(NOCT2D_TARGET_WINDOWS    ON)
    set(NOCT2D_ENABLE_JIT        ON)
    set(NOCT2D_ENABLE_I18N       ON)
    set(NOCT2D_ENABLE_PACK       ON)
  endif()

  if(APPLE AND NOT IOS)
    # macOS is detected.
    set(NOCT2D_TARGET_MACOS      ON)
    set(NOCT2D_ENABLE_JIT        ON)
    set(NOCT2D_ENABLE_I18N       ON)
    set(NOCT2D_ENABLE_BUNDLE     ON)
    set(NOCT2D_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux is detected.
    set(NOCT2D_TARGET_LINUX      ON)
    set(NOCT2D_ENABLE_JIT        ON)
    set(NOCT2D_ENABLE_I18N       ON)
    set(NOCT2D_ENABLE_GLX        ON)
    set(NOCT2D_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    set(NOCT2D_TARGET_FREEBSD    ON)
    set(NOCT2D_ENABLE_JIT        ON)
    set(NOCT2D_ENABLE_I18N       ON)
    set(NOCT2D_ENABLE_GLX        ON)
    set(NOCT2D_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "NetBSD")
    set(NOCT2D_TARGET_NETBSD     ON)
    set(NOCT2D_ENABLE_JIT        ON)
    set(NOCT2D_ENABLE_I18N       ON)
    set(NOCT2D_ENABLE_GLX        ON)
    set(NOCT2D_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "OpenBSD")
    set(NOCT2D_TARGET_OPENBSD    ON)
    set(NOCT2D_ENABLE_I18N       ON)
    set(NOCT2D_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "Haiku")
    set(NOCT2D_TARGET_HAIKU      ON)
    set(NOCT2D_ENABLE_JIT        ON)
    set(NOCT2D_ENABLE_I18N       ON)
    set(NOCT2D_ENABLE_PACK       ON)
  endif()

  # No automatic detection for:
  #  - Android
  #  - Wasm (Emscripten)
  #  - Unity
endif()

#
# NoctLang Configuration
#

# Merge objects into libnoct2d.
if(   NOCT2D_TARGET_IOS
   OR NOCT2D_TARGET_ANDROID
   OR NOCT2D_TARGET_UNITY
)
  set(NOCTLANG_ENABLE_OBJECT ON)
else()
  if(NOCT2D_ENABLE_DIST)
    set(NOCTLANG_ENABLE_SHARED ON)
  else()
    set(NOCTLANG_ENABLE_STATIC ON)
  endif()
endif()

# Emscripten
if(NOCT2D_TARGET_WASM)
  set(NOCTLANG_TARGET_WASM ON)
endif()

# Unity
if(NOCT2D_TARGET_UNITY)
  set(NOCTLANG_TARGET_UNITY ON)
endif()

# Use JIT.
if(NOCT2D_ENABLE_JIT)
  set(NOCTLANG_ENABLE_JIT ON)
else()
  set(NOCTLANG_ENABLE_JIT OFF)
endif()

# Use translation.
if(NOCT2D_ENABLE_I18N)
  set(NOCTLANG_ENABLE_I18N ON)
endif()

set(NOCTLANG_ENABLE_CLI OFF)

#
# Strato Configuration
#

# Set the target and its specific options.
if(NOCT2D_TARGET_WINDOWS)
  set(STRATO_TARGET_WINDOWS ON)
elseif(NOCT2D_TARGET_MACOS)
  set(STRATO_TARGET_MACOS ON)
elseif(NOCT2D_TARGET_LINUX)
  set(STRATO_TARGET_LINUX ON)
elseif(NOCT2D_TARGET_IOS)
  set(STRATO_TARGET_IOS ON)
elseif(NOCT2D_TARGET_ANDROID)
  set(STRATO_TARGET_ANDROID ON)
elseif(NOCT2D_TARGET_WASM)
  set(STRATO_TARGET_WASM ON)
elseif(NOCT2D_TARGET_UNITY)
  set(STRATO_TARGET_UNITY ON)
elseif(NOCT2D_TARGET_FREEBSD)
  set(STRATO_TARGET_FREEBSD ON)
elseif(NOCT2D_TARGET_NETBSD)
  set(STRATO_TARGET_NETBSD ON)
elseif(NOCT2D_TARGET_OPENBSD)
  set(STRATO_TARGET_OPENBSD ON)
elseif(NOCT2D_TARGET_HAIKU)
  set(STRATO_TARGET_HAIKU ON)
endif()

if(NOCT2D_TARGET_UNITY_SWITCH)
  set(STRATO_TARGET_UNITY_SWITCH)
elseif(NOCT2D_TARGET_UNITY_PS5)
  set(STRATO_TARGET_UNITY_PS5)
elseif(NOCT2D_TARGET_UNITY_XBOX)
  set(STRATO_TARGET_UNITY_XBOX)
endif()

# Merge objects into libnoct2d.
if(   NOCT2D_TARGET_IOS
   OR NOCT2D_TARGET_ANDROID
   OR NOCT2D_TARGET_UNITY
)
  set(STRATO_ENABLE_OBJECT ON)
else()
  if(NOCT2D_ENABLE_DIST)
    set(STRATO_ENABLE_SHARED ON)
  else()
    set(STRATO_ENABLE_STATIC ON)
  endif()
endif()

# OpenGL
if(   NOCT2D_TARGET_LINUX
   OR NOCT2D_TARGET_FREEBSD
   OR NOCT2D_TARGET_NETBSD
   OR NOCT2D_TARGET_OPENBSD
)
  if(NOCT2D_ENABLE_GLX)
    set(STRATO_ENABLE_GLX ON)
  endif()
endif()

# Linux Framebuffer
if(NOCT2D_ENABLE_FBDEV)
  set(STRATO_ENABLE_FBDEV ON)
endif()

# Use translation.
if(NOCT2D_ENABLE_I18N)
  set(STRATO_ENABLE_I18N ON)
endif()

#
# Release/Debug
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
    set(CMAKE_OBJC_FLAGS_DEBUG "${CMAKE_OBJC_FLAGS_RELEASE} -O0 -g3 -UNDEBUG")
endif()

# Release Configuration
if(MSVC)
  # MSVC
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
  # GCC/Clang
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -g0 -DNDEBUG")
  set(CMAKE_OBJC_FLAGS_RELEASE "${CMAKE_OBJC_FLAGS_RELEASE} -O2 -g0 -DNDEBUG")
endif()

#
# Apple Quirks
#

if(NOCT2D_TARGET_MACOS)
  set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)
endif()

#
# Dependencies
#

# NoctLang
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/NoctLang)

# StratoHAL
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/StratoHAL)

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
# Main Target
#

# Base Source
set(NOCT2D_BASE_SOURCES
  src/api.c
  src/common.c
  src/mainloop.c
  src/tag.c
  src/vm.c
)

# I18N Source
if(NOCT2D_ENABLE_I18N)
  set(NOCT2D_I18N_SOURCES
    src/i18n.c
    src/translation.c
  )
endif()

# Resource
if(NOCT2D_TARGET_WINDOWS)
  set(NOCT2D_RESOURCES
    resources/resource.rc
  )
endif()

# Add Target
if(   NOCT2D_TARGET_IOS
   OR NOCT2D_TARGET_ANDROID
   OR NOCT2D_TARGET_UNITY
)
  # Make a library.
  if(NOCT2D_ENABLE_SHARED)
    set(NOCT2D_LIB_TYPE SHARED)
  else()
    set(NOCT2D_LIB_TYPE STATIC)
  endif()
  add_library(
    noct2d
    ${NOCT2D_LIB_TYPE}
    ${NOCT2D_BASE_SOURCES}
    ${NOCT2D_I18N_SOURCES}
    ${NOCT2D_RESOURCES}
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
else()
  # Make an executable.
  add_executable(
    noct2d
    ${NOCT2D_BASE_SOURCES}
    ${NOCT2D_I18N_SOURCES}
    ${NOCT2D_RESOURCES}
  )
endif()

# Link NoctLang and Strato
target_link_libraries(noct2d PRIVATE
  noctlang
  strato
)

# -Iinclude
target_include_directories(noct2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# -DUSE_JIT
if(NOCT2D_ENABLE_JIT)
  target_compile_definitions(noct2d PRIVATE USE_JIT)
endif()

# -DUSE_TRANSLATION
if(NOCT2D_ENABLE_I18N)
  target_compile_definitions(noct2d PRIVATE USE_TRANSLATION)
endif()

# -DUSE_SHARED
if(NOCT2D_ENABLE_SHARED)
  target_compile_definitions(noct2d PRIVATE USE_SHARED)
endif()

# -DUSE_UNITY
if(NOCT2D_TARGET_UNITY)
  target_compile_definitions(noct2d PRIVATE USE_UNITY)
endif()

# Windows quirks
if(NOCT2D_TARGET_WINDOWS)
  if(MSVC)
    target_compile_options(noctlang PRIVATE /utf-8)
    target_link_options(noct2d PRIVATE /SUBSYSTEM:WINDOWS)
  else()
    target_compile_options(noctlang PRIVATE -municode -finput-charset=utf-8 -fexec-charset=utf-8)
    target_link_options(noct2d PRIVATE -mwindows -static)
  endif()
endif()

# Emscripten
if(NOCT2D_TARGET_WASM)
  # Make the output name "index.html"
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set_target_properties(noct2d PROPERTIES OUTPUT_NAME index)

  # -DUSE_EMSCRIPTEN
  target_compile_definitions(noct2d PRIVATE USE_EMSCRIPTEN)

  # Link options.
  target_link_options(noct2d PRIVATE
    -o index.html
    -sSINGLE_FILE=1
    -sTOTAL_MEMORY=536870912
    -sNO_EXIT_RUNTIME=1
    -sEXPORTED_RUNTIME_METHODS=[ccall,UTF8ToString]
    -lopenal
    -lidbfs.js
    --shell-file "${CMAKE_CURRENT_SOURCE_DIR}/src/shell.html"
    --pre-js "${CMAKE_CURRENT_SOURCE_DIR}/src/pre.js"
    --use-preload-plugins
    --profiling-funcs
  )
endif()

#
# Packager Target
#

if(NOCT2D_ENABLE_PACK)
  add_executable(
    noct2dpack
    src/noct2dpack.c
  )
  target_link_libraries(noct2dpack stratopack)
endif()

#
# Web Server target
#

if(NOCT2D_TARGET_WINDOWS)
  add_executable(
    web
    src/webserver.c
  )
  target_link_libraries(web wsock32 ws2_32)
endif()

#
# macOS Bundle
#

if(NOCT2D_TARGET_MACOS AND NOCT2D_ENABLE_BUNDLE)
  # Use capital name.
  set_target_properties(noct2d PROPERTIES OUTPUT_NAME Noct2D)

  # Make an app bundle.
  set_target_properties(noct2d PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "io.noctvm.noct2d"
    MACOSX_BUNDLE_BUNDLE_NAME "Noct2D"
  )

  # Set an icon.
  set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/icon512.png")
  target_sources(noct2d PRIVATE ${APP_ICON})
  set_source_files_properties(${APP_ICON} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  set_target_properties(noct2d PROPERTIES
    MACOSX_BUNDLE_ICON_FILE "icon512.png"
  )

  # Copy the assets.pak file.
  set(APP_GAME_DATA "${CMAKE_CURRENT_SOURCE_DIR}/resources/assets.pak.")
  set_source_files_properties(${APP_GAME_DATA} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  target_sources(noct2d PRIVATE ${APP_GAME_DATA})
endif()
