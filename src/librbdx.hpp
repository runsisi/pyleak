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

#include <foonathan/memory/container.hpp> // vector, list, list_node_size,...
#include <foonathan/memory/memory_pool.hpp> // memory_pool
#include <foonathan/memory/namespace_alias.hpp>

#include <boost/pool/pool_alloc.hpp>

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

using K = std::string;
using V = std::pair<image_info_t, int>;
using RawAllocator = memory::memory_pool<>;

using Map = std::map<K, V, std::less<K>, boost::pool_allocator<std::pair<const K, V>>>;
using Pool = boost::singleton_pool<boost::pool_allocator_tag, (sizeof(Map::value_type) + 32)>;

class xRBD {
public:
  //
  // xImage
  //
  int list_info(librados::IoCtx& ioctx,
      Map* infos);
//  memory::map<std::string, std::pair<image_info_t, int>, memory::memory_pool<>>* infos);
};

}

#endif /* SRC_INCLUDE_RBD_LIBRBDX_HPP_ */
