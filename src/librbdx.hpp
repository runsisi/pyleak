/*
 * librbdx.hpp
 *
 *  Created on: Jul 31, 2019
 *      Author: runsisi
 */

#ifndef SRC_INCLUDE_RBD_LIBRBDX_HPP_
#define SRC_INCLUDE_RBD_LIBRBDX_HPP_

#include <map>
#include <string>
#include <vector>

#include "mempool.h"

namespace librados {

class IoCtx {

};

}

namespace librbdx {

enum class snap_ns_type_t {
  SNAPSHOT_NAMESPACE_TYPE_USER = 0,
};

enum class snap_protection_status_t {
  PROTECTION_STATUS_UNPROTECTED  = 0,
  PROTECTION_STATUS_UNPROTECTING = 1,
  PROTECTION_STATUS_PROTECTED    = 2,
  PROTECTION_STATUS_LAST         = 3
};

enum class trash_source_t {
  TRASH_IMAGE_SOURCE_USER = 0,
  TRASH_IMAGE_SOURCE_MIRRORING = 1,
};

typedef struct {
  std::string image_id;
  uint64_t snap_id;
  uint8_t order;
  uint64_t size;
  uint64_t stripe_unit;
  uint64_t stripe_count;
  uint64_t features;
  uint64_t flags;
} size_info_t;

typedef struct {
  uint64_t size;
  uint64_t du;
} du_info_t;

typedef struct {
  uint64_t seq;
  std::vector<uint64_t> snaps;
} snapc_t;

typedef struct {
  int64_t pool_id;
  std::string image_id;
  uint64_t snap_id;
} parent_spec_t;

typedef struct {
  parent_spec_t spec;
  uint64_t overlap;
} parent_info_t;

typedef struct {
  int64_t pool_id;
  std::string image_id;
} child_t;

typedef struct {
  int64_t iops;
  int64_t bps;
} qos_t;

typedef struct {
  uint64_t id;
  std::string name;
  snap_ns_type_t snap_ns_type;
  uint64_t size;
  uint64_t features;
  uint64_t flags;
  snap_protection_status_t protection_status;
  timespec timestamp;
} snap_info_t;

typedef struct {
  uint64_t id;
  std::string name;
  snap_ns_type_t snap_ns_type;
  uint64_t size;
  uint64_t features;
  uint64_t flags;
  snap_protection_status_t protection_status;
  timespec timestamp;
  uint64_t du;
} snap_info_v2_t;

typedef struct {
  mempool::rbdx::string id;
  std::string name;
  uint8_t order;
  uint64_t size;
  uint64_t stripe_unit;
  uint64_t stripe_count;
  uint64_t features;
  uint64_t flags;
  snapc_t snapc;
  std::map<uint64_t, snap_info_t> snaps;
  parent_info_t parent;
  timespec timestamp;
  int64_t data_pool_id;
  std::vector<std::string> watchers;
  qos_t qos;
} image_info_t;

typedef struct {
  std::string id;
  std::string name;
  uint8_t order;
  uint64_t size;
  uint64_t stripe_unit;
  uint64_t stripe_count;
  uint64_t features;
  uint64_t flags;
  snapc_t snapc;
  std::map<uint64_t, snap_info_t> snaps;
  parent_info_t parent;
  timespec timestamp;
  int64_t data_pool_id;
  std::vector<std::string> watchers;
  qos_t qos;
  uint64_t du;
} image_info_v2_t;

typedef struct {
  std::string id;
  std::string name;
  uint8_t order;
  uint64_t size;
  uint64_t stripe_unit;
  uint64_t stripe_count;
  uint64_t features;
  uint64_t flags;
  snapc_t snapc;
  std::map<uint64_t, snap_info_v2_t> snaps;
  parent_info_t parent;
  timespec timestamp;
  int64_t data_pool_id;
  std::vector<std::string> watchers;
  qos_t qos;
  uint64_t du;
} image_info_v3_t;

typedef struct {
  std::string id;
  std::string name;
  trash_source_t source;
  timespec deletion_time;
  timespec deferment_end_time;
} trash_info_t;

class xRBD {
public:
  //
  // xImage
  //
  int list_info(librados::IoCtx& ioctx,
          mempool::rbdx::map<mempool::rbdx::string, std::pair<image_info_t, int>>* infos);
};

}

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
  mempool::rbdx::string id;
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

#endif /* SRC_INCLUDE_RBD_LIBRBDX_HPP_ */
