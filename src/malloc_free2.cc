/*
 * malloc_free.cc
 *
 *  Created on: Aug 25, 2019
 *      Author: runsisi
 */

// $ sudo gdb -p 24539 -ex 'call malloc_trim(0)' -ex 'set confirm off' -ex 'quit 0'

#include <iostream>
#include <chrono>
#include <thread>
#include <malloc.h>
using namespace std;

int main() {
//  mallopt(M_MXFAST, 0);

  cout << "press enter to begin\n";
  cin.ignore();

  cout << "starting..\n";

  void **pointers = new void*[3000000];

  for(int i = 0; i < 3000000; i++) {
    pointers[i] = malloc(376);
    *((int*)pointers[i]) = i;
  }

  cout << "malloc done\n";

  for(int i = 0; i < 3000000; i++) {
    free(pointers[i]);
  }
  delete []pointers;

  cout << "free done\n";

  cout << "press enter to quit\n";
  cin.ignore();

//  std::this_thread::sleep_for(std::chrono::seconds(1000));

  return 0;
}




