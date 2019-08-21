/*
 * librbdx.cc
 *
 *  Created on: Jul 31, 2019
 *      Author: runsisi
 */

#include "librbdx.hpp"

#include <cstdlib>

#include <iostream>

extern size_t getCurrentRSS();

#define rss() \
    std::cout << __func__ << ": current RSS: " << getCurrentRSS() / 1024.0 / 1024.0 << "MB" << std::endl;

namespace librbd {

using snapid_t = uint64_t;

struct ParentSpec {
  int64_t pool_id;
  std::string image_id;
  snapid_t snap_id;

  ParentSpec() : pool_id(-1), snap_id(0) {
  }
  ParentSpec(int64_t pool_id, std::string image_id, snapid_t snap_id)
    : pool_id(pool_id), image_id(image_id), snap_id(snap_id) {
  }
};

/// Full information about an image's parent.
struct ParentInfo {
  /// Identification of the parent.
  ParentSpec spec;

  /** @brief Where the portion of data shared with the child image ends.
   * Since images can be resized multiple times, the portion of data shared
   * with the child image is not necessarily min(parent size, child size).
   * If the child image is first shrunk and then enlarged, the common portion
   * will be shorter. */
  uint64_t overlap;

  ParentInfo() : overlap(0) {
  }
};

struct SnapContext {
  snapid_t seq;            // 'time' stamp
  std::vector<snapid_t> snaps;  // existent snaps, in descending order
};

// do not default initialize the fields
// https://stackoverflow.com/questions/37776823/could-not-convert-from-brace-enclosed-initializer-list-to-struct
struct xSnapInfo {
  snapid_t id;
  std::string name;
//  cls::rbd::SnapshotNamespaceType snap_ns_type;
  uint64_t size;
  uint64_t features;
  uint64_t flags;
  uint8_t protection_status;
//  utime_t timestamp;
};

struct xImageInfo {
  std::string id;
  std::string name;
  uint8_t order = 0;
  uint64_t size = 0;
  uint64_t stripe_unit = 0;
  uint64_t stripe_count = 0;
  uint64_t features = 0;
  uint64_t flags = 0;
  SnapContext snapc;
  std::map<snapid_t, xSnapInfo> snaps;
  ParentInfo parent;
//  utime_t timestamp;
  int64_t data_pool_id = -1;
//  std::vector<obj_watch_t> watchers;
  std::map<std::string, std::string> kvs;
};

}

namespace {
  constexpr const char* conf_qos_iops_str = "conf_rbd_client_qos_limit";
  constexpr const char* conf_qos_bps_str = "conf_rbd_client_qos_bandwidth";

  void cvt_snap_info(librbd::xSnapInfo& in, librbdx::snap_info_t* out) {
    out->id = in.id;
    out->name = std::move(in.name);
    out->snap_ns_type = static_cast<librbdx::snap_ns_type_t>(0);
    out->size = in.size;
    out->features = in.features;
    out->flags = in.flags;
    out->protection_status = static_cast<librbdx::snap_protection_status_t>(in.protection_status);
//    in.timestamp.to_timespec(&out->timestamp);
  }

  void cvt_image_info(librbd::xImageInfo& in, librbdx::image_info_t* out) {
    out->id = std::move(in.id);
    out->name = std::move(in.name);
    out->order = in.order;
    out->size = in.size;
    out->stripe_unit = in.stripe_unit;
    out->stripe_count = in.stripe_count;
    out->features = in.features;
    out->flags = in.flags;
    out->snapc.seq = in.snapc.seq;
    for (auto& s : in.snapc.snaps) {
      out->snapc.snaps.push_back(s);
    }
    for (auto& it : in.snaps) {
      auto& snap = out->snaps[it.first];
      auto& tsnap = in.snaps[it.first];

      cvt_snap_info(tsnap, &snap);
    }
    out->parent.spec.pool_id = in.parent.spec.pool_id;
    out->parent.spec.image_id = std::move(in.parent.spec.image_id);
    out->parent.spec.snap_id = in.parent.spec.snap_id;
    out->parent.overlap = in.parent.overlap;
//    in.timestamp.to_timespec(&out->timestamp);
//    out->data_pool_id = in.data_pool_id;
//    for (auto& w : in.watchers) {
//      out->watchers.emplace_back(std::move(w.addr));
//    }
    for (auto& kv : in.kvs) {
      if (kv.first == conf_qos_iops_str) {
        out->qos.iops = std::atoll(kv.second.c_str());
      } else if (kv.first == conf_qos_bps_str) {
        out->qos.bps = std::atoll(kv.second.c_str());
      }
    }
  }

}

namespace librbdx {

//
// xImage
//

int xRBD::list_info(librados::IoCtx& ioctx,
    Map* infos) {
  int r = 0;
  infos->clear();

  using xK = std::string;
  using xV = std::pair<librbd::xImageInfo, int>;
//  using xRawAllocator = memory::memory_pool<>;

//  using namespace memory::literals;
//  xRawAllocator pool(memory::map_node_size<std::pair<xK, xV>>::value, 4_KiB);
//  memory::map<xK, xV, xRawAllocator> tinfos(pool);

  using xMap = std::map<xK, xV, std::less<xK>, boost::pool_allocator<std::pair<const xK, xV>>>;
  using xPool = boost::singleton_pool<boost::pool_allocator_tag, (sizeof(xMap::value_type) + 32)>;
  xMap tinfos;

//  std::map<xK, xV> tinfos;

  for (int i = 0; i < 300000; i++) {
    librbd::xImageInfo info;
    info.id = std::move(std::to_string(i));
    info.name = std::move(std::to_string(i));
    tinfos.insert({std::to_string(i), {
        info, 0
    }});
  }

  for (auto& it : tinfos) {
    auto& info = (*infos)[it.first].first;
    auto& r = (*infos)[it.first].second;

    auto& tinfo = it.second.first;
    auto& tr = it.second.second;

    // info
    cvt_image_info(tinfo, &info);
    // error code
    r = tr;
  }

  rss();

  std::cout << "press enter to clear xinfos\n";
  std::cin.ignore();
  tinfos.clear();
  rss();

  std::cout << "press enter to release memory\n";
  std::cin.ignore();
  std::cout << xPool::release_memory() << std::endl;
  rss();

  std::cout << "press enter to purge memory\n";
  std::cin.ignore();
  std::cout << xPool::purge_memory() << std::endl;
  rss();
  return r;
}

}
