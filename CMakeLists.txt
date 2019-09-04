cmake_minimum_required(VERSION 2.8.12)
project(x)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_PREFIX_PATH "/opt/runsisi/python3/bin")

include(BuildJemalloc)
build_jemalloc()

add_subdirectory(pybind11)

pybind11_add_module(x src/rbdx.cc src/librbdx.cc src/je.cc)

target_link_libraries(x PRIVATE
  ${JEMALLOC_STATIC_LIBRARY}
)
#target_link_libraries(x PRIVATE
#  tcmalloc
#)

#
# libcrash_cpp
#

add_library(crash_cpp SHARED
  src/libcrash_cpp.cc src/je.cc
)
target_compile_options(crash_cpp PRIVATE
  "-std=c++14"
)
target_link_libraries(crash_cpp PRIVATE
  ${JEMALLOC_SHARED_LIBRARY}
  "pthread"
#  PRIVATE "-Wl,--dynamic-list-cpp-new"
  PRIVATE "-Wl,-Bsymbolic-functions"
)

#
# test_crash_cpp
#

add_executable(test_crash_cpp src/test_crash_cpp.cc)
target_link_libraries(test_crash_cpp PRIVATE
#  ${JEMALLOC_SHARED_LIBRARY}
  "dl"
)
add_dependencies(test_crash_cpp crash_cpp)

#
# libcrash_c
#

add_library(crash_c SHARED
  src/libcrash_c.c
)
target_link_libraries(crash_c PRIVATE
  ${JEMALLOC_SHARED_LIBRARY}
  "pthread"
)

#
# test_crash_c
#

add_executable(test_crash_c src/test_crash_c.c)
target_link_libraries(test_crash_c PRIVATE
  ${JEMALLOC_SHARED_LIBRARY}
  "dl"
)
add_dependencies(test_crash_c crash_c)
