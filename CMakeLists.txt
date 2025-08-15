cmake_minimum_required(VERSION 3.16)
project(Noct2D LANGUAGES C CXX)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version")

#
# Configuration
#

option(ENABLE_GLX     "Enable OpenGL on X11"    ON)
option(ENABLE_BUNDLE  "Enable macOS bundle"     ON)
option(ENABLE_I18N    "Enable translation"      ON)
option(ENABLE_SHARED  "Enable shared libraries" OFF)

#
# Target Detection
#

option(TARGET_WASM    "Emscripten"     OFF)
option(TARGET_ANDROID "Android NDK"    OFF)
option(TARGET_UNITY   "Unity plugin"   OFF)

if(WIN32 AND NOT TARGET_UNITY)
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

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  set(TARGET_WASM ON)
  set(ENABLE_JIT        OFF)
  set(ENABLE_I18N       OFF)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Haiku")
  set(TARGET_HAIKU ON)
endif()

# Android (Manual)
if(TARGET_ADNROID)
  set(ENABLE_JIT        OFF)
  set(ENABLE_I18N       OFF)
  set(ENABLE_SHARED     ON)
  set(ENABLE_OBJECT     ON)
endif()

# Unity (Manual)
if(TARGET_UNITY)
  set(ENABLE_JIT        OFF)
  set(ENABLE_I18N       OFF)
  set(ENABLE_OBJECT     ON)
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
# Dependencies
#

# NoctLang
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/NoctLang)

# StratoHAL
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/StratoHAL)

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

set(BASE_SOURCES
  src/api.c
  src/common.c
  src/mainloop.c
  src/tag.c
  src/vm.c
)

if(ENABLE_I18N)
  set(I18N_SOURCES
    src/i18n.c
    src/translation.c
  )
endif()

if(TARGET_WINDOWS AND NOT TARGET_UNITY)
  set(RESOURCES
    resources/resource.rc
  )
endif()

if(TARGET_WASM OR TARGET_ANDROID OR TARGET_UNITY)
  if(ENABLE_SHARED)
    add_library(
      noct2d
      SHARED
      ${BASE_SOURCES}
      ${I18N_SOURCES}
      ${RESOURCES}
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
    add_library(
      noct2d
      STATIC
      ${BASE_SOURCES}
      ${I18N_SOURCES}
      ${RESOURCES}
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
else()
  add_executable(
    noct2d
    ${BASE_SOURCES}
    ${I18N_SOURCES}
    ${RESOURCES}
  )
endif()

target_link_libraries(noct2d PRIVATE
  noctlang
  strato
)

target_include_directories(noct2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ENABLE_JIT)
  target_compile_definitions(noct2d PRIVATE USE_JIT)
endif()

if(ENABLE_I18N)
  target_compile_definitions(noct2d PRIVATE USE_TRANSLATION)
endif()

if(ENABLE_SHARED)
  target_compile_definitions(noct2d PRIVATE USE_SHARED)
endif()

if(TARGET_UNITY)
  target_compile_definitions(noct2d PRIVATE USE_UNITY)
endif()

if(TARGET_WINDOWS)
  if(MSVC)
    target_compile_options(noctlang PRIVATE /utf-8)
    target_link_options(noct2d PRIVATE /SUBSYSTEM:WINDOWS)
  else()
    target_compile_options(noctlang PRIVATE -municode -finput-charset=utf-8 -fexec-charset=utf-8)
    target_link_options(noct2d PRIVATE -mwindows -static)
  endif()
endif()

# macOS: Make the bundle name capital.
if(APPLE AND NOT IOS AND ENABLE_BUNDLE)
  set_target_properties(noct2d PROPERTIES OUTPUT_NAME Noct2D)
endif()

# Emscripten
if(TARGET_WASM)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set_target_properties(noct2d PROPERTIES OUTPUT_NAME index)
  target_compile_definitions(noct2d PRIVATE USE_EMSCRIPTEN)
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
  )
endif()

#
# Packager
#

if(NOT TARGET_WASM AND NOT TARGET_ANDROID AND NOT TARGET_UNITY)
  add_executable(
    noct2dpack
    src/noct2dpack.c
  )
  target_link_libraries(noct2dpack stratopack)
endif()

#
# macOS Bundle
#

if(TARGET_MACOS)
  # Make an app bundle.
  set_target_properties(noct2d PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "io.noctvm.noct2d"
    MACOSX_BUNDLE_BUNDLE_NAME "Noct2D"
  )

  # Set an icon.
  set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon512.png")
  target_sources(noct2d PRIVATE ${APP_ICON})
  set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
  set_target_properties(noct2d PROPERTIES MACOSX_BUNDLE_ICON_FILE "icon512.png")

  # product.img
  set(APP_GAME_DATA "${CMAKE_CURRENT_SOURCE_DIR}/resources/product.img")
  set_source_files_properties(${APP_GAME_DATA} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  target_sources(noct2d PRIVATE ${APP_GAME_DATA})
endif()
