/*
 * test_crash.cc
 *
 *  Created on: Sep 1, 2019
 *      Author: runsisi
 */

#include <memory>
#include <dlfcn.h>

//typedef void (*init_t)();

extern "C" void libcrash_init();

int main() {
  // comment out the following three lines will crash the app
//  int* p = new int;
//  *p = 0;
//  delete p;

  void* ptr = std::malloc(sizeof(int));
  std::free(ptr);

//  void *handle = dlopen("./libcrash_cpp.so", RTLD_LAZY);
//  if (!handle) {
//    char* err = dlerror();
//    return -1;
//  }
//
//  init_t init = (init_t)dlsym(handle, "libcrash_init");
//  if (!init) {
//    char* err = dlerror();
//    return -1;
//  }
//
//  init();
//
//  dlclose(handle);

  libcrash_init();

  return 0;
}
