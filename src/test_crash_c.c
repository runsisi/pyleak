/*
 * test_crash_c.c
 *
 *  Created on: Sep 3, 2019
 *      Author: runsisi
 */

#include <stdlib.h>
#include <dlfcn.h>

typedef void (*init_t)();

int main() {
//  void* ptr = std::malloc(sizeof(int));
//  std::free(ptr);

  void *handle = dlopen("./libcrash_c.so", RTLD_LAZY);
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
