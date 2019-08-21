cmake_minimum_required(VERSION 2.8.12)
project(x)

# What is the idiomatic way in CMAKE to add the -fPIC compiler option?
# https://stackoverflow.com/questions/38296756/what-is-the-idiomatic-way-in-cmake-to-add-the-fpic-compiler-option
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(memory)
set_property(TARGET foonathan_memory PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)
pybind11_add_module(x src/rbdx.cc src/librbdx.cc)
target_link_libraries(x PRIVATE foonathan_memory)

add_executable(test2 src/test.cc src/librbdx.cc)
target_link_libraries(test2 PRIVATE foonathan_memory)