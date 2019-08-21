cmake_minimum_required(VERSION 2.8.12)
project(x)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_PREFIX_PATH "/opt/runsisi/python3/bin")

include(BuildJemalloc)

add_subdirectory(pybind11)

pybind11_add_module(x src/rbdx.cc src/librbdx.cc)

add_dependencies(x jemalloc)
target_include_directories(x PRIVATE
  ${jemalloc_INCLUDE_DIRS})

target_link_libraries(x PRIVATE
  ${jemalloc_LIBRARIES})

#target_link_libraries(x PRIVATE
#  tcmalloc)