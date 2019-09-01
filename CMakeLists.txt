cmake_minimum_required(VERSION 2.8.12)
project(x)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_PREFIX_PATH "/opt/runsisi/python3/bin")

include(BuildJemalloc)
build_jemalloc()

add_subdirectory(pybind11)

pybind11_add_module(x src/rbdx.cc src/librbdx.cc)

target_link_libraries(x PRIVATE
  ${JEMALLOC_SHARED_LIBRARY}
)
#target_link_libraries(x PRIVATE
#  tcmalloc
#)

#
# libcrash
#

add_library(crash SHARED
  src/libcrash.cc
)
target_compile_options(crash PRIVATE
  "-std=c++14"
)
target_link_libraries(crash PRIVATE
  ${JEMALLOC_SHARED_LIBRARY}
#  "pthread"
)

#
# test_crash
#

add_executable(test_crash src/test_crash.cc)
target_link_libraries(test_crash PRIVATE
#  ${JEMALLOC_SHARED_LIBRARY}
  "dl"
)
add_dependencies(test_crash crash)
