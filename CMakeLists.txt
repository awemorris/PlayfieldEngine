cmake_minimum_required(VERSION 3.16)
project(Noct2D LANGUAGES C CXX)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)

#
# Configuration
#

option(ENABLE_GLX    "Enable OpenGL on X11"    ON)
option(ENABLE_BUNDLE "Enable macOS bundle"     ON)
option(ENABLE_I18N   "Enable translation"      ON)
option(ENABLE_SHARED "Enable shared libraries" OFF)

# Use "Release" build type by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Debug or Release)" FORCE)
endif()

# Debug Configuration.
set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_RELEASE}     -O0 -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE}   -O0 -g3")

# Release Configuration.
set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE}   -O3 -g0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0")

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
  src/main.c
  src/api.c
  src/vm.c
)

if(ENABLE_I18N)
  set(I18N_SOURCES
    src/i18n.c
    src/translation.c
  )
endif()

if(WIN32)
  set(RESOURCES
    resources/resource.rc
  )
endif()

add_executable(
  noct2d
  ${BASE_SOURCES}
  ${I18N_SOURCES}
  ${RESOURCES}
)

target_link_libraries(noct2d PRIVATE
  noctlang
  strato
)

target_include_directories(noct2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ENABLE_SHARED)
  target_compile_definitions(noct2d PRIVATE USE_SHARED)
endif()

if(ENABLE_JIT)
  target_compile_definitions(noct2d PRIVATE USE_JIT)
endif()

if(ENABLE_I18N)
  target_compile_definitions(noct2d PRIVATE USE_TRANSLATION)
endif()

if(WIN32)
  target_link_options(noct2d PRIVATE -static)
endif()

# Change the bundle name.
if (APPLE AND NOT IOS AND ENABLE_BUNDLE)
  set_target_properties(noct2d PROPERTIES OUTPUT_NAME Noct2D)
endif()

#
# Packager
#

add_executable(
  noct2dpack
  src/noct2dpack.c
)

target_link_libraries(noct2dpack stratopack)

#
# macOS Bundle
#

if(APPLE AND NOT IOS AND ENABLE_BUNDLE)
  # Make an app bundle.
  set_target_properties(noct2d PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "io.noctvm.noct2d"
    MACOSX_BUNDLE_BUNDLE_NAME "Noct2D"
  )

  # Set an icon.
  set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon512.png")
  target_sources(noct2d PRIVATE ${APP_ICON})
  set_source_files_properties(${APP_ICON} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources")
  set_target_properties(noct2d PROPERTIES
    MACOSX_BUNDLE_ICON_FILE "icon512.png"
  )

  # product.img
  set(APP_GAME_DATA "${CMAKE_CURRENT_SOURCE_DIR}/resources/product.img")
  set_source_files_properties(${APP_GAME_DATA} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  target_sources(noct2d PRIVATE ${APP_GAME_DATA})
endif()
