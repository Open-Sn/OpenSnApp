cmake_minimum_required(VERSION 3.29)
project(OpenSnApp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenSn CONFIG REQUIRED)

message(STATUS "Found OpenSn ${OpenSn_VERSION} (from: ${OpenSn_DIR})")

find_library(LIBROM_LIBRARY
  NAMES ROM
  HINTS
    ENV LIBROM_DIR
    ${LIBROM_DIR}
    ${LIBROM_DIR}/install
  PATH_SUFFIXES lib
  REQUIRED)

find_path(LIBROM_INCLUDE_DIR
  NAMES librom.h
  HINTS
    ENV LIBROM_DIR
    ${LIBROM_DIR}
    ${LIBROM_DIR}/install
  PATH_SUFFIXES include
  REQUIRED)

message(STATUS "libROM include dir: ${LIBROM_INCLUDE_DIR}")
message(STATUS "libROM library: ${LIBROM_LIBRARY}")

file(GLOB_RECURSE ROM_SRCS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/rom/*.cc)

# Python module
add_library(romapp MODULE
    src/main.cc
    src/rom_py_app.cc
    src/rom.cc
    ${ROM_SRCS}
)

target_include_directories(romapp 
    PRIVATE 
    ${LIBROM_INCLUDE_DIR}
)
target_link_libraries(romapp 
    PRIVATE 
    opensn::opensn
    opensn::libopensnpy
    pybind11::module 
    ${LIBROM_LIBRARY})

set_target_properties(romapp PROPERTIES
    PREFIX ""
    OUTPUT_NAME "romapp"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
)

add_executable(rom_app_exec src/main.cc src/rom_py_app.cc src/rom.cc ${ROM_SRCS})
target_include_directories(rom_app_exec PRIVATE
    ${LIBROM_INCLUDE_DIR}
)
target_link_libraries(rom_app_exec 
    PRIVATE 
    opensn::opensn
    opensn::libopensnpy
    ${LIBROM_LIBRARY})
