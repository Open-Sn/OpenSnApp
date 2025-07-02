cmake_minimum_required(VERSION 3.14)
project(OpenSnApp LANGUAGES C CXX)

find_package(MPI REQUIRED)
find_package(VTK REQUIRED COMPONENTS
    CommonCore
    CommonDataModel
    IOLegacy
    IOCore
    IOXML
    ParallelCore
    IOParallelXML
    FiltersCore
    IOEnSight
    IOExodus
)
find_package(OpenSn REQUIRED)

find_package(pybind11 REQUIRED)

find_package(caliper REQUIRED)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

file(GLOB_RECURSE DIFFUSION_SRCS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/diffusion/*.cc)

# Python module
add_library(diffapp MODULE
    src/main.cc
    src/diff_py_app.cc
    src/diffusion.cc
    ${DIFFUSION_SRCS}
)

execute_process(
    COMMAND python3 -m pybind11 --includes
    OUTPUT_VARIABLE PYBIND11_INCLUDE_FLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE "-I" "" PYBIND11_INCLUDE_DIRS "${PYBIND11_INCLUDE_FLAGS}")
separate_arguments(PYBIND11_INCLUDE_DIRS)

target_include_directories(diffapp 
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/diffusion
    ${PYBIND11_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/external
    ${OpenSn_INSTALL_PREFIX}/include/opensn 
)
target_link_libraries(diffapp PRIVATE opensn::libopensn opensn::libopensnpy MPI::MPI_CXX caliper pybind11::module Python::Python)

set_target_properties(diffapp PROPERTIES
    PREFIX ""    # remove "lib" prefix
    OUTPUT_NAME "diffapp"  # Python import name
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
)

# Optional executable
add_executable(diff_app_exec src/main.cc src/diff_py_app.cc src/diffusion.cc ${DIFFUSION_SRCS})
target_include_directories(diff_app_exec PRIVATE
    ${PROJECT_SOURCE_DIR}/diffusion
    ${PROJECT_SOURCE_DIR}/external
    ${PYBIND11_INCLUDE_DIRS}
    ${OpenSn_INSTALL_PREFIX}/include/opensn 
)
target_link_libraries(diff_app_exec PRIVATE opensn::libopensn opensn::libopensnpy MPI::MPI_C caliper pybind11::module Python::Python)