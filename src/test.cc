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

extern size_t getCurrentRSS();

#define rss() \
    std::cout << __func__ << ": current RSS: " << getCurrentRSS() / 1024.0 / 1024.0 << "MB" << std::endl;

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

    std::cout << "press enter to clear infos\n";
    std::cin.ignore();
    infos.clear();
    cout << "after clear: " << r << endl;
    rss();

    std::cout << "press enter to release memory\n";
    std::cin.ignore();
    cout << Pool::release_memory() << endl;
    cout << "after release\n";
    rss();

    std::cout << "press enter to purge memory\n";
    std::cin.ignore();
    cout << Pool::purge_memory() << endl;
    cout << "after purge\n";
    rss();

    std::cout << "press enter to trim memory\n";
    std::cin.ignore();
    malloc_trim(0);
    cout << "after malloc_trim\n";
    rss();
  }

  std::this_thread::sleep_for(std::chrono::seconds(1000));
  return 0;
}
