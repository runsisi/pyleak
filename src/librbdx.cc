/*
 * librbdx.cc
 *
 *  Created on: Jul 31, 2019
 *      Author: runsisi
 */

#include "librbdx.hpp"

#include <cstdlib>

namespace librbdx {

//
// xImage
//

int xRBD::list_info(librados::IoCtx& ioctx,
    mempool::rbdx::map<mempool::rbdx::string, std::pair<image_info_t, int>>* infos) {
  int r = 0;
  infos->clear();
  mempool::rbdx::map<mempool::rbdx::string, std::pair<librbd::xImageInfo, int>> tinfos;
//  r = librbd::api::xImage<>::list_info(ioctx, &tinfos);
//  if (r < 0) {
//    return r;
//  }

  for (int i = 0; i < 2000000; i++) {
    librbd::xImageInfo info;
    info.id = std::to_string(i).c_str();
    info.name = std::move(std::to_string(i));
    tinfos.insert({std::to_string(i).c_str(), {
        info, 0
    }});
  }

  for (auto& it : tinfos) {
      image_info_t info;

    auto& tinfo = it.second.first;
    auto& tr = it.second.second;

    // info
    cvt_image_info(tinfo, &info);
    // error code
    infos->insert({info.id, {
            info, 0
    }});
  }
  return r;
}

}
