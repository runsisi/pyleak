/*
 * libcrash.cc
 *
 *  Created on: Sep 1, 2019
 *      Author: runsisi
 */

#define EXPORT __attribute__((visibility("default")))

#include <iostream>
//#include <memory>

using namespace std;

extern "C" EXPORT
void libcrash_init() {
//  int* cp = (int*)std::malloc(sizeof(int));
//  std::free(cp);

  int* p = new int;
  *p = 0;
  delete p;

  cout << "libcrash_init_cpp" << endl;
}
