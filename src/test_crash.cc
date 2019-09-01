/*
 * test_crash.cc
 *
 *  Created on: Sep 1, 2019
 *      Author: runsisi
 */

#include <dlfcn.h>

typedef void (*init_t)();

int main() {
  // comment out the following three lines will crash the app
//  int* p = new int;
//  *p = 0;
//  delete p;

  void *handle = dlopen("./libcrash.so", RTLD_LAZY);
  if (!handle) {
    char* err = dlerror();
    return -1;
  }

  init_t init = (init_t)dlsym(handle, "libcrash_init");
  if (!init) {
    char* err = dlerror();
    return -1;
  }

  init();

  dlclose(handle);

  return 0;
}