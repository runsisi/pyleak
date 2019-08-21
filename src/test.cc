#include "librbdx.hpp"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace librbdx;

#include <malloc.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <foonathan/memory/container.hpp> // vector, list, list_node_size,...
#include <foonathan/memory/memory_pool.hpp> // memory_pool
#include <foonathan/memory/namespace_alias.hpp>


int main() {
  auto xrbd = librbdx::xRBD();
  auto io = librados::IoCtx();

  {
//    using namespace memory::literals;
//    memory::memory_pool<> pool(memory::map_node_size<std::pair<K, V>>::value, 4_KiB);
//    memory::map<K, V, decltype(pool)> infos(pool);

    Map infos;

    int r = xrbd.list_info(io, &infos);
    cout << "list_info: " << r << endl;
    infos.clear();
    cout << "after clear: " << r << endl;
    Pool::release_memory();
    cout << "after release\n";
    Pool::purge_memory();
    cout << "after purge\n";
    malloc_trim(0);
    cout << "after malloc_trim\n";
  }

  std::this_thread::sleep_for(std::chrono::seconds(1000));
  return 0;
}
