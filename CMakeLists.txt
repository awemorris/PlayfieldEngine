cmake_minimum_required(VERSION 3.16)
project(playfield LANGUAGES C CXX)

#
# Configuration
#

# Targets
option(PLAYFIELD_TARGET_WINDOWS       "Build for Windows"       OFF)
option(PLAYFIELD_TARGET_MACOS         "Build for macOS"         OFF)
option(PLAYFIELD_TARGET_LINUX         "Build for Linux"         OFF)
Option(PLAYFIELD_TARGET_IOS           "Build for iOS"           OFF)
option(PLAYFIELD_TARGET_ANDROID       "Build for Android"       OFF)
option(PLAYFIELD_TARGET_WASM          "Build for Emscripten"    OFF)
option(PLAYFIELD_TARGET_UNITY         "Build for Unity"         OFF)
option(PLAYFIELD_TARGET_FREEBSD       "Build for FreeBSD"       OFF)

# Options
option(PLAYFIELD_ENABLE_JIT           "Enable JIT"              OFF)
option(PLAYFIELD_ENABLE_I18N          "Enable translation"      OFF)
option(PLAYFIELD_ENABLE_BUNDLE        "Enable macOS bundle"     OFF)
option(PLAYFIELD_ENABLE_PACK          "Enable packager"         OFF)
option(PLAYFIELD_ENABLE_STATIC        "Build a static library"  OFF)
option(PLAYFIELD_ENABLE_SHARED        "Build a dynamic library" OFF)
option(PLAYFIELD_ENABLE_DIST          "Build for packages"      OFF)

#
# Automatic Target Detection
#

# For when a target is manually specified.
if(   PLAYFIELD_TARGET_WINDOWS
   OR PLAYFIELD_TARGET_MACOS
   OR PLAYFIELD_TARGET_LINUX
   OR PLAYFIELD_TARGET_IOS
   OR PLAYFIELD_TARGET_ANDROID
   OR PLAYFIELD_TARGET_WASM
   OR PLAYFIELD_TARGET_UNITY
   OR PLAYFIELD_TARGET_FREEBSD
)
  # A target and options are manually specified.
else()   
  if(WIN32)
    # Windows is detected.
    set(PLAYFIELD_TARGET_WINDOWS    ON)
    set(PLAYFIELD_ENABLE_JIT        ON)
    set(PLAYFIELD_ENABLE_I18N       ON)
    set(PLAYFIELD_ENABLE_PACK       ON)
  endif()

  if(APPLE AND NOT IOS)
    # macOS is detected.
    set(PLAYFIELD_TARGET_MACOS      ON)
    set(PLAYFIELD_ENABLE_JIT        ON)
    set(PLAYFIELD_ENABLE_I18N       ON)
    set(PLAYFIELD_ENABLE_BUNDLE     ON)
    set(PLAYFIELD_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux is detected.
    set(PLAYFIELD_TARGET_LINUX      ON)
    set(PLAYFIELD_ENABLE_JIT        ON)
    set(PLAYFIELD_ENABLE_I18N       ON)
    set(PLAYFIELD_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    set(PLAYFIELD_TARGET_FREEBSD    ON)
    set(PLAYFIELD_ENABLE_JIT        ON)
    set(PLAYFIELD_ENABLE_I18N       ON)
    set(PLAYFIELD_ENABLE_GLX        ON)
    set(PLAYFIELD_ENABLE_PACK       ON)
  endif()

  # No automatic detection for:
  #  - Android
  #  - Wasm (Emscripten)
  #  - Unity
endif()

#
# NoctLang Configuration
#

# Merge subproject objects into libplayfield.
if(   PLAYFIELD_TARGET_IOS
   OR PLAYFIELD_TARGET_ANDROID
   OR PLAYFIELD_TARGET_UNITY
)
  # For library generation.
  set(NOCTLANG_ENABLE_OBJECT ON)
else()
  if(PLAYFIELD_ENABLE_DIST)
    # For dynamically linked binaries.
    set(NOCTLANG_ENABLE_SHARED ON)
  else()
    # For statically linked binaries.
    set(NOCTLANG_ENABLE_STATIC ON)
  endif()
endif()

# Emscripten
if(PLAYFIELD_TARGET_WASM)
  set(NOCTLANG_TARGET_WASM ON)
endif()

# Unity
if(PLAYFIELD_TARGET_UNITY)
  set(NOCTLANG_TARGET_UNITY ON)
endif()

# Use JIT.
if(PLAYFIELD_ENABLE_JIT)
  set(NOCTLANG_ENABLE_JIT ON)
else()
  set(NOCTLANG_ENABLE_JIT OFF)
endif()

# Use translation.
if(PLAYFIELD_ENABLE_I18N)
  set(NOCTLANG_ENABLE_I18N ON)
endif()

if(NOT NOCTLANG_ENABLE_CLI)
  set(NOCTLANG_ENABLE_CLI OFF)
endif()

#
# Strato Configuration
#

# Set the target and its specific options.
if(PLAYFIELD_TARGET_WINDOWS)
  set(STRATO_TARGET_WINDOWS ON)
elseif(PLAYFIELD_TARGET_MACOS)
  set(STRATO_TARGET_MACOS ON)
elseif(PLAYFIELD_TARGET_LINUX)
  set(STRATO_TARGET_LINUX ON)
elseif(PLAYFIELD_TARGET_IOS)
  set(STRATO_TARGET_IOS ON)
elseif(PLAYFIELD_TARGET_ANDROID)
  set(STRATO_TARGET_ANDROID ON)
elseif(PLAYFIELD_TARGET_WASM)
  set(STRATO_TARGET_WASM ON)
elseif(PLAYFIELD_TARGET_UNITY)
  set(STRATO_TARGET_UNITY ON)
elseif(PLAYFIELD_TARGET_FREEBSD)
  set(STRATO_TARGET_FREEBSD ON)
endif()

if(PLAYFIELD_TARGET_UNITY_SWITCH)
  set(STRATO_TARGET_UNITY_SWITCH)
elseif(PLAYFIELD_TARGET_UNITY_PS5)
  set(STRATO_TARGET_UNITY_PS5)
elseif(PLAYFIELD_TARGET_UNITY_XBOX)
  set(STRATO_TARGET_UNITY_XBOX)
endif()

# Merge subproject objects into libplayfield.
if(   PLAYFIELD_TARGET_IOS
   OR PLAYFIELD_TARGET_ANDROID
   OR PLAYFIELD_TARGET_UNITY
)
  # For library generation.
  set(STRATO_ENABLE_OBJECT ON)
else()
  if(PLAYFIELD_ENABLE_DIST)
    # For dynamically linked binaries.
    set(STRATO_ENABLE_SHARED ON)
  else()
    # For statically linked binaries.
    set(STRATO_ENABLE_STATIC ON)
  endif()
endif()

# Linux Framebuffer
if(PLAYFIELD_ENABLE_FBDEV)
  set(STRATO_ENABLE_FBDEV ON)
endif()

# Use translation.
if(PLAYFIELD_ENABLE_I18N)
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

if(PLAYFIELD_TARGET_MACOS)
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
set(PLAYFIELD_BASE_SOURCES
  src/api.c
  src/common.c
  src/mainloop.c
  src/tag.c
  src/vm.c
)

# I18N Source
if(PLAYFIELD_ENABLE_I18N)
  set(PLAYFIELD_I18N_SOURCES
    src/i18n.c
    src/translation.c
  )
endif()

# Resource
if(PLAYFIELD_TARGET_WINDOWS)
  set(PLAYFIELD_RESOURCES
    resources/resource.rc
  )
endif()

# Add Target
if(   PLAYFIELD_TARGET_IOS
   OR PLAYFIELD_TARGET_ANDROID
   OR PLAYFIELD_TARGET_UNITY
)
  # Make a library.
  if(PLAYFIELD_ENABLE_SHARED)
    set(PLAYFIELD_LIB_TYPE SHARED)
  else()
    set(PLAYFIELD_LIB_TYPE STATIC)
  endif()
  add_library(
    playfield
    ${PLAYFIELD_LIB_TYPE}
    ${PLAYFIELD_BASE_SOURCES}
    ${PLAYFIELD_I18N_SOURCES}
    ${PLAYFIELD_RESOURCES}
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
    playfield
    ${PLAYFIELD_BASE_SOURCES}
    ${PLAYFIELD_I18N_SOURCES}
    ${PLAYFIELD_RESOURCES}
  )
endif()

# Link NoctLang and Strato
target_link_libraries(playfield PRIVATE
  noctlang
  strato
)

# -Iinclude
target_include_directories(playfield PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# -DUSE_JIT
if(PLAYFIELD_ENABLE_JIT)
  target_compile_definitions(playfield PRIVATE USE_JIT)
endif()

# -DUSE_TRANSLATION
if(PLAYFIELD_ENABLE_I18N)
  target_compile_definitions(playfield PRIVATE USE_TRANSLATION)
endif()

# -DUSE_SHARED
if(PLAYFIELD_ENABLE_SHARED)
  target_compile_definitions(playfield PRIVATE USE_SHARED)
endif()

# -DUSE_UNITY
if(PLAYFIELD_TARGET_UNITY)
  target_compile_definitions(playfield PRIVATE USE_UNITY)
endif()

# Windows quirks
if(PLAYFIELD_TARGET_WINDOWS)
  if(MSVC)
    target_compile_options(playfield PRIVATE /utf-8)
    target_link_options(playfield PRIVATE /SUBSYSTEM:WINDOWS)
  else()
    target_compile_options(playfield PRIVATE -municode -finput-charset=utf-8 -fexec-charset=utf-8)
    target_link_options(playfield PRIVATE -mwindows -static)
  endif()
endif()

# Emscripten
if(PLAYFIELD_TARGET_WASM)
  # Make the output name "index.html"
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set_target_properties(playfield PROPERTIES OUTPUT_NAME index)

  # -DUSE_EMSCRIPTEN
  target_compile_definitions(playfield PRIVATE USE_EMSCRIPTEN)

  # Link options.
  target_link_options(playfield PRIVATE
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

if(PLAYFIELD_ENABLE_PACK)
  add_executable(
    playfield-pack
    src/pack.c
  )
  target_link_libraries(playfield-pack stratopack)
endif()

#
# Web Server target
#

if(PLAYFIELD_TARGET_WINDOWS)
  add_executable(
    playfield-web
    src/webserver.c
  )
  target_link_libraries(playfield-web wsock32 ws2_32)
endif()

#
# macOS Bundle
#

if(PLAYFIELD_TARGET_MACOS AND PLAYFIELD_ENABLE_BUNDLE)
  # Use capital name.
  set_target_properties(playfield PROPERTIES OUTPUT_NAME "Playfield")

  # Make an app bundle.
  set_target_properties(playfield PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "io.noctvm.playfield"
    MACOSX_BUNDLE_BUNDLE_NAME "Playfield"
  )

  # Set an icon.
  set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/icon512.png")
  target_sources(playfield PRIVATE ${APP_ICON})
  set_source_files_properties(${APP_ICON} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  set_target_properties(playfield PROPERTIES
    MACOSX_BUNDLE_ICON_FILE "icon512.png"
  )

  # Copy the assets.pak file.
  set(APP_GAME_DATA "${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/assets.pak")
  set_source_files_properties(${APP_GAME_DATA} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  target_sources(playfield PRIVATE ${APP_GAME_DATA})
endif()
