/*
 * libcrash_c.c
 *
 *  Created on: Sep 3, 2019
 *      Author: runsisi
 */

#define EXPORT __attribute__((visibility("default")))

#include <stdio.h>
#include <stdlib.h>

EXPORT
void libcrash_init() {
  int* p = (int*)malloc(sizeof(int));
  *p = 0;
  free(p);

  printf("libcrash_init_c\n");
}
