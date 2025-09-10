cmake_minimum_required(VERSION 3.16)
project(picopico LANGUAGES C CXX)

#
# Configuration
#

# Targets
option(PICO_TARGET_WINDOWS       "Build for Windows"       OFF)
option(PICO_TARGET_MACOS         "Build for macOS"         OFF)
option(PICO_TARGET_LINUX         "Build for Linux"         OFF)
option(PICO_TARGET_IOS           "Build for iOS"           OFF)
option(PICO_TARGET_ANDROID       "Build for Android"       OFF)
option(PICO_TARGET_WASM          "Build for Emscripten"    OFF)
option(PICO_TARGET_UNITY         "Build for Unity"         OFF)
option(PICO_TARGET_FREEBSD       "Build for FreeBSD"       OFF)

# Options
option(PICO_ENABLE_JIT           "Enable JIT"              OFF)
option(PICO_ENABLE_I18N          "Enable translation"      OFF)
option(PICO_ENABLE_BUNDLE        "Enable macOS bundle"     OFF)
option(PICO_ENABLE_PACK          "Enable packager"         OFF)
option(PICO_ENABLE_STATIC        "Build a static library"  OFF)
option(PICO_ENABLE_SHARED        "Build a dynamic library" OFF)
option(PICO_ENABLE_DIST          "Build for packages"      OFF)

#
# Automatic Target Detection
#

# For when a target is manually specified.
if(   PICO_TARGET_WINDOWS
   OR PICO_TARGET_MACOS
   OR PICO_TARGET_LINUX
   OR PICO_TARGET_IOS
   OR PICO_TARGET_ANDROID
   OR PICO_TARGET_WASM
   OR PICO_TARGET_UNITY
   OR PICO_TARGET_FREEBSD
)
  # A target and options are manually specified.
else()   
  if(WIN32)
    # Windows is detected.
    set(PICO_TARGET_WINDOWS    ON)
    set(PICO_ENABLE_JIT        ON)
    set(PICO_ENABLE_I18N       ON)
    set(PICO_ENABLE_PACK       ON)
  endif()

  if(APPLE AND NOT IOS)
    # macOS is detected.
    set(PICO_TARGET_MACOS      ON)
    set(PICO_ENABLE_JIT        ON)
    set(PICO_ENABLE_I18N       ON)
    set(PICO_ENABLE_BUNDLE     ON)
    set(PICO_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux is detected.
    set(PICO_TARGET_LINUX      ON)
    set(PICO_ENABLE_JIT        ON)
    set(PICO_ENABLE_I18N       ON)
    set(PICO_ENABLE_PACK       ON)
  endif()

  if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    set(PICO_TARGET_FREEBSD    ON)
    set(PICO_ENABLE_JIT        ON)
    set(PICO_ENABLE_I18N       ON)
    set(PICO_ENABLE_GLX        ON)
    set(PICO_ENABLE_PACK       ON)
  endif()

  # No automatic detection for:
  #  - Android
  #  - Wasm (Emscripten)
  #  - Unity
endif()

#
# NoctLang Configuration
#

# Merge objects into libpico.
if(   PICO_TARGET_IOS
   OR PICO_TARGET_ANDROID
   OR PICO_TARGET_UNITY
)
  # For library generation.
  set(NOCTLANG_ENABLE_OBJECT ON)
else()
  if(PICO_ENABLE_DIST)
    # For dynamically linked binaries.
    set(NOCTLANG_ENABLE_SHARED ON)
  else()
    # For statically linked binaries.
    set(NOCTLANG_ENABLE_STATIC ON)
  endif()
endif()

# Emscripten
if(PICO_TARGET_WASM)
  set(NOCTLANG_TARGET_WASM ON)
endif()

# Unity
if(PICO_TARGET_UNITY)
  set(NOCTLANG_TARGET_UNITY ON)
endif()

# Use JIT.
if(PICO_ENABLE_JIT)
  set(NOCTLANG_ENABLE_JIT ON)
else()
  set(NOCTLANG_ENABLE_JIT OFF)
endif()

# Use translation.
if(PICO_ENABLE_I18N)
  set(NOCTLANG_ENABLE_I18N ON)
endif()

if(NOT NOCTLANG_ENABLE_CLI)
  set(NOCTLANG_ENABLE_CLI OFF)
endif()

#
# Strato Configuration
#

# Set the target and its specific options.
if(PICO_TARGET_WINDOWS)
  set(STRATO_TARGET_WINDOWS ON)
elseif(PICO_TARGET_MACOS)
  set(STRATO_TARGET_MACOS ON)
elseif(PICO_TARGET_LINUX)
  set(STRATO_TARGET_LINUX ON)
elseif(PICO_TARGET_IOS)
  set(STRATO_TARGET_IOS ON)
elseif(PICO_TARGET_ANDROID)
  set(STRATO_TARGET_ANDROID ON)
elseif(PICO_TARGET_WASM)
  set(STRATO_TARGET_WASM ON)
elseif(PICO_TARGET_UNITY)
  set(STRATO_TARGET_UNITY ON)
elseif(PICO_TARGET_FREEBSD)
  set(STRATO_TARGET_FREEBSD ON)
endif()

if(PICO_TARGET_UNITY_SWITCH)
  set(STRATO_TARGET_UNITY_SWITCH)
elseif(PICO_TARGET_UNITY_PS5)
  set(STRATO_TARGET_UNITY_PS5)
elseif(PICO_TARGET_UNITY_XBOX)
  set(STRATO_TARGET_UNITY_XBOX)
endif()

# Merge objects into libpico.
if(   PICO_TARGET_IOS
   OR PICO_TARGET_ANDROID
   OR PICO_TARGET_UNITY
)
  # For library generation.
  set(STRATO_ENABLE_OBJECT ON)
else()
  if(PICO_ENABLE_DIST)
    # For dynamically linked binaries.
    set(STRATO_ENABLE_SHARED ON)
  else()
    # For statically linked binaries.
    set(STRATO_ENABLE_STATIC ON)
  endif()
endif()

# Linux Framebuffer
if(PICO_ENABLE_FBDEV)
  set(STRATO_ENABLE_FBDEV ON)
endif()

# Use translation.
if(PICO_ENABLE_I18N)
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

if(PICO_TARGET_MACOS)
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
set(PICO_BASE_SOURCES
  src/api.c
  src/common.c
  src/mainloop.c
  src/tag.c
  src/vm.c
)

# I18N Source
if(PICO_ENABLE_I18N)
  set(PICO_I18N_SOURCES
    src/i18n.c
    src/translation.c
  )
endif()

# Resource
if(PICO_TARGET_WINDOWS)
  set(PICO_RESOURCES
    resources/resource.rc
  )
endif()

# Add Target
if(   PICO_TARGET_IOS
   OR PICO_TARGET_ANDROID
   OR PICO_TARGET_UNITY
)
  # Make a library.
  if(PICO_ENABLE_SHARED)
    set(PICO_LIB_TYPE SHARED)
  else()
    set(PICO_LIB_TYPE STATIC)
  endif()
  add_library(
    picopico
    ${PICO_LIB_TYPE}
    ${PICO_BASE_SOURCES}
    ${PICO_I18N_SOURCES}
    ${PICO_RESOURCES}
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
    picopico
    ${PICO_BASE_SOURCES}
    ${PICO_I18N_SOURCES}
    ${PICO_RESOURCES}
  )
endif()

# Link NoctLang and Strato
target_link_libraries(picopico PRIVATE
  noctlang
  strato
)

# -Iinclude
target_include_directories(picopico PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# -DUSE_JIT
if(PICO_ENABLE_JIT)
  target_compile_definitions(picopico PRIVATE USE_JIT)
endif()

# -DUSE_TRANSLATION
if(PICO_ENABLE_I18N)
  target_compile_definitions(picopico PRIVATE USE_TRANSLATION)
endif()

# -DUSE_SHARED
if(PICO_ENABLE_SHARED)
  target_compile_definitions(picopico PRIVATE USE_SHARED)
endif()

# -DUSE_UNITY
if(PICO_TARGET_UNITY)
  target_compile_definitions(picopico PRIVATE USE_UNITY)
endif()

# Windows quirks
if(PICO_TARGET_WINDOWS)
  if(MSVC)
    target_compile_options(picopico PRIVATE /utf-8)
    target_link_options(picopico PRIVATE /SUBSYSTEM:WINDOWS)
  else()
    target_compile_options(picopico PRIVATE -municode -finput-charset=utf-8 -fexec-charset=utf-8)
    target_link_options(picopico PRIVATE -mwindows -static)
  endif()
endif()

# Emscripten
if(PICO_TARGET_WASM)
  # Make the output name "index.html"
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set_target_properties(picopico PROPERTIES OUTPUT_NAME index)

  # -DUSE_EMSCRIPTEN
  target_compile_definitions(picopico PRIVATE USE_EMSCRIPTEN)

  # Link options.
  target_link_options(picopico PRIVATE
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

if(PICO_ENABLE_PACK)
  add_executable(
    picopico-pack
    src/pack.c
  )
  target_link_libraries(picopico-pack stratopack)
endif()

#
# Web Server target
#

if(PICO_TARGET_WINDOWS)
  add_executable(
    picopico-web
    src/webserver.c
  )
  target_link_libraries(picopico-web wsock32 ws2_32)
endif()

#
# macOS Bundle
#

if(PICO_TARGET_MACOS AND PICO_ENABLE_BUNDLE)
  # Use capital name.
  set_target_properties(picopico PROPERTIES OUTPUT_NAME "PicoPico")

  # Make an app bundle.
  set_target_properties(picopico PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "io.noctvm.picopicoscript"
    MACOSX_BUNDLE_BUNDLE_NAME "PicoPico"
  )

  # Set an icon.
  set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/icon512.png")
  target_sources(picopico PRIVATE ${APP_ICON})
  set_source_files_properties(${APP_ICON} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  set_target_properties(picopico PROPERTIES
    MACOSX_BUNDLE_ICON_FILE "icon512.png"
  )

  # Copy the assets.pak file.
  set(APP_GAME_DATA "${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/assets.pak")
  set_source_files_properties(${APP_GAME_DATA} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  target_sources(picopico PRIVATE ${APP_GAME_DATA})
endif()
