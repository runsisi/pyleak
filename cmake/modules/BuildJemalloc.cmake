##
# Make file for jemalloc project
##

# v5.2.1
set(jemalloc_root_dir "${CMAKE_BINARY_DIR}/jemalloc")
set(jemalloc_url "https://github.com/jemalloc/jemalloc/releases/download/5.2.1/jemalloc-5.2.1.tar.bz2")
set(jemalloc_url_hash "SHA256=34330e5ce276099e2e8950d9335db5a875689a4c6a56751ef3b1d8c537f887f6")
set(jemalloc_config_args "--disable-initial-exec-tls")
list(APPEND jemalloc_config_args "--without-export")
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
