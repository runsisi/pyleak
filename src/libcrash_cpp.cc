/*
 * libcrash.cc
 *
 *  Created on: Sep 1, 2019
 *      Author: runsisi
 */

#define EXPORT __attribute__((visibility("default")))

#include <iostream>

using namespace std;

extern "C" EXPORT
void libcrash_init() {
  int* p = new int;
  *p = 0;
  delete p;

  cout << "libcrash_init_cpp" << endl;
}
