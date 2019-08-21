#include "librbdx.hpp"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace librbdx;

int main() {
  auto xrbd = librbdx::xRBD();
  auto io = librados::IoCtx();

  {
    std::map<std::string, std::pair<image_info_t, int>> infos;
    int r = xrbd.list_info(io, &infos);
    infos.clear();
    cout << "list_info: " << r << endl;
  }
  {
    std::map<std::string, std::pair<image_info_t, int>> infos;
    int r = xrbd.list_info(io, &infos);
    infos.clear();
    cout << "list_info: " << r << endl;
  }
  {
    std::map<std::string, std::pair<image_info_t, int>> infos;
    int r = xrbd.list_info(io, &infos);
    infos.clear();
    cout << "list_info: " << r << endl;
  }

  std::this_thread::sleep_for(std::chrono::seconds(1000));
  return 0;
}
