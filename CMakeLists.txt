cmake_minimum_required(VERSION 3.16)
project(NoctVM LANGUAGES C CXX)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)

#
# Configuration
#

option(USE_SHARED "Enable shared libraries" OFF)
option(USE_GLX    "Enable OpenGL on X11"    ON)
option(USE_BUNDLE "Enable macOS bundle"     ON)

#
# Dependencies
#

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/NoctLang)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/StratoHAL)

#
# Source Files
#

# Main sources.
set(NOCTVM_SOURCES
  src/main.c
  src/api.c
  src/vm.c
  src/translation.c
)

# Add NoctVM binary.
add_executable(noctvm ${NOCTVM_SOURCES})

# Change the bundle name.
if (APPLE AND NOT IOS AND USE_BUNDLE)
  set_target_properties(noctvm PROPERTIES OUTPUT_NAME NoctVM)
endif()

#
# CPPFLAGS
#

# -INoctLang/include
target_include_directories(noctvm PRIVATE {$CMAKE_SOURCE_DIR}/NoctLang/include)

# -IStratoHAL/include
target_include_directories(noctvm PRIVATE {$CMAKE_SOURCE_DIR}/StratoHAL/include)

# -DUSE_SHARED if we use dynamic linking.
if(USE_SHARED)
  target_compile_definitions(noctvm PRIVATE USE_SHARED)
endif()

# -DUSE_JIT if we use JIT.
if(USE_JIT)
  target_compile_definitions(noctvm PRIVATE USE_JIT)
endif()

# FreeBSD: Add -I/usr/local/include
if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
  target_include_directories(noctvm PRIVATE /usr/local/include)
endif()

# NetBSD: Add -I/usr/local/include -I/usr/X11R7/include
if(CMAKE_SYSTEM_NAME STREQUAL "NetBSD")
  target_include_directories(noctvm PRIVATE /usr/local/include /usr/X11R7/include)
endif()

# OpenBSD: Add -I/usr/local/include -I/usr/X11R6/include
if(CMAKE_SYSTEM_NAME STREQUAL "OpenBSD")
  target_include_directories(noctvm PRIVATE /usr/local/include /usr/X11R6/include)
endif()

#
# CFLAGS
#

# Use "Release" build type by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Debug or Release)" FORCE)
endif()

# Debug Configuration.
set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_RELEASE}   -O0 -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O0 -g3")

# Release Configuration.
set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE}   -O3 -g0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0")

#
# Link
#

# Libraries.
target_link_libraries(noctvm PRIVATE
  noctlang
  strato
)

# Windows link options.
if(WIN32)
  # No console.
  set_target_properties(noctvm PROPERTIES WIN32_EXECUTABLE TRUE)

  # DLLs.
  target_link_libraries(noctvm PRIVATE
    gdi32
    ole32
    dsound
    strmiids
    dxguid
  )

  # -municode
  if (MINGW)
    target_link_options(noctvm PRIVATE
      -municode
    )
  endif()
endif()

# macOS link options.
if(APPLE AND NOT IOS)
  target_compile_options(noctvm PRIVATE
    -fmodules
  )
  target_link_libraries(noctvm PRIVATE
    "-framework AppKit"
    "-framework MetalKit"
    "-framework AVFoundation"
  )
endif()

# POSIX GLX: Add -lGL -lGLX
if(UNIX AND NOT APPLE)
  if(USE_GLX)
    target_link_libraries(noctvm PRIVATE
      GL
      GLX
    )
  endif()
endif()

# POSIX: Add -lm -lpthread -lXpm -lX11
if(UNIX AND NOT APPLE)
  target_link_libraries(noctvm PRIVATE
    m
    pthread
    Xpm
    X11
  )
endif()

# Linux: Add -lasound
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_libraries(noctvm PRIVATE
    asound
  )
endif()

# FreeBSD: Add -L/usr/local/lib -L/usr/X11R7/lib
if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
  link_directories(
    /usr/local/lib
    /usr/X11R7/lib
  )
endif()

# NetBSD: Add -L/usr/local/lib -L/usr/X11R7/lib
if(CMAKE_SYSTEM_NAME STREQUAL "NetBSD")
  link_directories(
    /usr/local/lib
    /usr/X11R7/lib
  )
endif()

# OpenBSD: Add -L/usr/local/lib -L/usr/X11R6/lib
if(CMAKE_SYSTEM_NAME STREQUAL "OpenBSD")
  link_directories(
    /usr/local/lib
    /usr/X11R6/lib
  )
endif()

# Haiku: Add -lbe -lmedia
if(CMAKE_SYSTEM_NAME STREQUAL "Haiku")
  target_link_libraries(noctvm PRIVATE
    be
    media
  )
endif()

#
# macOS Bundle
#

if(APPLE AND NOT IOS AND USE_BUNDLE)
  # Make an app bundle.
  set_target_properties(noctvm PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "io.noctvm.noctvm"
    MACOSX_BUNDLE_BUNDLE_NAME "NoctVM"
  )

  # Set an icon.
  set(APP_ICON "${CMAKE_SOURCE_DIR}/resources/icon512.png")
  target_sources(noctvm PRIVATE ${APP_ICON})
  set_source_files_properties(${APP_ICON} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources")
  set_target_properties(noctvm PROPERTIES
    MACOSX_BUNDLE_ICON_FILE "icon512.png"
  )

  # product.img
  set(APP_GAME_DATA "${CMAKE_CURRENT_SOURCE_DIR}/resources/product.img")
  set_source_files_properties(${APP_GAME_DATA} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  target_sources(noctvm PRIVATE ${APP_GAME_DATA})
endif()
