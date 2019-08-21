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

struct N {
  void* ptr;
  N* next;
};

N head = {0, 0};

int main() {
//  mallopt(M_MXFAST, 0);

  cout << "press enter to begin\n";
  cin.ignore();

  cout << "starting..\n";

  for (int i = 0; i < 3000000; i++) {
    auto n = (N*)malloc(376);
    n->ptr = n;
    n->next = head.next;

    head.next = n;
  }

  cout << "malloc done\n";

  while (head.next) {
    auto n = head.next;
    head.next = head.next->next;
    free(n);
  }

  cout << "free done\n";

  cout << "press enter to quit\n";
  cin.ignore();

//  std::this_thread::sleep_for(std::chrono::seconds(1000));

  return 0;
}

