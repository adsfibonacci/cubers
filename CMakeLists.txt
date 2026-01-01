cmake_minimum_required(VERSION 3.14)
project(cube)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # avoid compiler-specific extensions

# Automatically find pybind11 from the active Python environment
execute_process(
  COMMAND python3 -m pybind11 --cmakedir
  OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(pybind11_DIR ${PYBIND11_CMAKE_DIR})

find_package(pybind11 REQUIRED)

pybind11_add_module(cube model.cpp exports.cpp)
