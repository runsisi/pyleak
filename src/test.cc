#include "librbdx.hpp"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace librbdx;

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
    using namespace memory::literals;
    memory::memory_pool<> pool(memory::map_node_size<std::pair<K, V>>::value, 4_KiB);
    memory::map<K, V, decltype(pool)> infos(pool);

    int r = xrbd.list_info(io, &infos);
    infos.clear();
    cout << "list_info: " << r << endl;
  }

  std::this_thread::sleep_for(std::chrono::seconds(1000));
  return 0;
}
