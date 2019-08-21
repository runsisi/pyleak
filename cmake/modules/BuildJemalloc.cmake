##
# Make file for jemalloc project
##

# v4.5.0
set(jemalloc_root_dir "${CMAKE_BINARY_DIR}/jemalloc")
set(jemalloc_url "https://github.com/jemalloc/jemalloc/releases/download/4.5.0/jemalloc-4.5.0.tar.bz2")
set(jemalloc_url_hash "SHA256=9409d85664b4f135b77518b0b118c549009dc10f6cba14557d170476611f6780")
set(jemalloc_config_args "")
#list(APPEND jemalloc_config_args "--without-export")
list(APPEND jemalloc_config_args "--enable-debug")

include(ExternalProject)
ExternalProject_Add(jemalloc
  URL ${jemalloc_url}
  URL_HASH ${jemalloc_url_hash}
  CONFIGURE_COMMAND ${jemalloc_env} ./configure ${jemalloc_config_args}

# Temporarily forcing single thread as multi-threaded make is causing build
# failues.
  BUILD_COMMAND make -j1
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND ""
  TEST_COMMAND ""
  PREFIX ${jemalloc_root_dir})

set(jemalloc_INCLUDE_DIRS
  ${jemalloc_root_dir}/src/jemalloc/include)

set(jemalloc_LIBRARIES
  ${jemalloc_root_dir}/src/jemalloc/lib/libjemalloc_pic.a)
#  ${jemalloc_root_dir}/src/jemalloc/lib/libjemalloc.so)