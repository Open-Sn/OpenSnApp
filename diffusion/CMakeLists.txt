cmake_minimum_required(VERSION 3.29)
project(OpenSnApp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSn CONFIG REQUIRED)

message(STATUS "Found OpenSn ${OpenSn_VERSION} (from: ${OpenSn_DIR})")

file(GLOB_RECURSE DIFFUSION_SRCS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/diffusion/*.cc)

add_executable(
  diff_app_exec
  src/main.cc
  src/diff_py_app.cc
  src/diffusion.cc
  ${DIFFUSION_SRCS}
)

target_include_directories(diff_app_exec PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(diff_app_exec PRIVATE
  opensn::opensn
  opensn::libopensnpy
)
