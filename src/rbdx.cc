#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include "librbdx.hpp"

#include <list>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <malloc.h>
#include <vector>

//#include "nlohmann/json.hpp"

namespace py = pybind11;

using Vector_uint64_t = std::vector<uint64_t>;
using Vector_string = std::vector<std::string>;
using Map_uint64_t_2_snap_info_t = std::map<uint64_t, librbdx::snap_info_t>;
using Map_uint64_t_2_du_info_t = std::map<uint64_t, librbdx::du_info_t>;

using Map_string_2_pair_du_info_t_int = std::map<std::string, std::pair<librbdx::du_info_t, int>>;
using Map_string_2_pair_map_uint64_t_2_du_info_t_int = std::map<std::string, std::pair<std::map<uint64_t, librbdx::du_info_t>, int>>;

using Map_string_2_string = std::map<std::string, std::string>;
using Map_string_2_pair_image_info_t_int = std::map<std::string, std::pair<librbdx::image_info_t, int>>;
using Map_string_2_pair_image_info_v2_t_int = std::map<std::string, std::pair<librbdx::image_info_v2_t, int>>;
using Map_string_2_pair_image_info_v3_t_int = std::map<std::string, std::pair<librbdx::image_info_v3_t, int>>;

using Map_parent_spec_t_2_vector_string = std::map<librbdx::parent_spec_t, std::vector<std::string>>;
using Map_string_2_trash_info_t = std::map<std::string, librbdx::trash_info_t>;

PYBIND11_MAKE_OPAQUE(Vector_uint64_t);
PYBIND11_MAKE_OPAQUE(Vector_string);
PYBIND11_MAKE_OPAQUE(Map_uint64_t_2_snap_info_t);
PYBIND11_MAKE_OPAQUE(Map_uint64_t_2_du_info_t);

PYBIND11_MAKE_OPAQUE(Map_string_2_pair_du_info_t_int);
PYBIND11_MAKE_OPAQUE(Map_string_2_pair_map_uint64_t_2_du_info_t_int);

PYBIND11_MAKE_OPAQUE(Map_string_2_string);
PYBIND11_MAKE_OPAQUE(Map_string_2_pair_image_info_t_int);
PYBIND11_MAKE_OPAQUE(Map_string_2_pair_image_info_v2_t_int);
PYBIND11_MAKE_OPAQUE(Map_string_2_pair_image_info_v3_t_int);

PYBIND11_MAKE_OPAQUE(Map_parent_spec_t_2_vector_string);
PYBIND11_MAKE_OPAQUE(Map_string_2_trash_info_t);

namespace rbdx {

using namespace librbdx;

PYBIND11_MODULE(x, m) {

  {
    auto b = py::bind_vector<Vector_uint64_t>(m, "Vector_uint64_t");

  }
  {
    auto b = py::bind_vector<Vector_string>(m, "Vector_string");

  }
  {
    auto b = py::bind_map<Map_uint64_t_2_snap_info_t>(m, "Map_uint64_t_2_snap_info_t");

  }
  {
    auto b = py::bind_map<Map_uint64_t_2_du_info_t>(m, "Map_uint64_t_2_du_info_t");

  }
  {
    auto b = py::bind_map<Map_string_2_string>(m, "Map_string_2_string");

  }
  {
    auto b = py::bind_map<Map_string_2_pair_image_info_t_int>(m, "Map_string_2_pair_image_info_t_int");
    b.def("clear", [](Map_string_2_pair_image_info_t_int& self) {
      self.clear();
    });

  }
  {
    auto b = py::bind_map<Map_string_2_pair_image_info_v2_t_int>(m, "Map_string_2_pair_image_info_v2_t_int");

  }
  {
    auto b = py::bind_map<Map_string_2_pair_image_info_v3_t_int>(m, "Map_string_2_pair_image_info_v3_t_int");

  }
  {
    auto b = py::bind_map<Map_string_2_pair_du_info_t_int>(m, "Map_string_2_pair_du_info_t_int");

  }
  {
    auto b = py::bind_map<Map_string_2_pair_map_uint64_t_2_du_info_t_int>(m, "Map_string_2_pair_map_uint64_t_2_du_info_t_int");

  }
  {
    auto b = py::bind_map<Map_string_2_trash_info_t>(m, "Map_string_2_trash_info_t");

  }

  {
    py::enum_<snap_ns_type_t> kind(m, "snap_ns_type_t", py::arithmetic());
    kind.value("SNAPSHOT_NAMESPACE_TYPE_USER", snap_ns_type_t::SNAPSHOT_NAMESPACE_TYPE_USER);
    kind.export_values();
  }

  {
    py::enum_<snap_protection_status_t> kind(m, "snap_protection_status_t", py::arithmetic());
    kind.value("PROTECTION_STATUS_UNPROTECTED", snap_protection_status_t::PROTECTION_STATUS_UNPROTECTED);
    kind.value("PROTECTION_STATUS_UNPROTECTING", snap_protection_status_t::PROTECTION_STATUS_UNPROTECTING);
    kind.value("PROTECTION_STATUS_PROTECTED", snap_protection_status_t::PROTECTION_STATUS_PROTECTED);
    kind.value("PROTECTION_STATUS_LAST", snap_protection_status_t::PROTECTION_STATUS_LAST);
    kind.export_values();
  }

  {
    py::enum_<trash_source_t> kind(m, "trash_source_t", py::arithmetic());
    kind.value("TRASH_IMAGE_SOURCE_USER", trash_source_t::TRASH_IMAGE_SOURCE_USER);
    kind.value("TRASH_IMAGE_SOURCE_MIRRORING", trash_source_t::TRASH_IMAGE_SOURCE_MIRRORING);
    kind.export_values();
  }

  {
    py::class_<timespec> cls(m, "timespec_t");
    cls.def(py::init<>());
    cls.def_readonly("tv_sec", &timespec::tv_sec);
    cls.def_readonly("tv_nsec", &timespec::tv_nsec);

  }

  {
    py::class_<size_info_t> cls(m, "size_info_t");
    cls.def(py::init<>());
    cls.def_readonly("image_id", &size_info_t::image_id);
    cls.def_readonly("snap_id", &size_info_t::snap_id);
    cls.def_readonly("order", &size_info_t::order);
    cls.def_readonly("size", &size_info_t::size);
    cls.def_readonly("stripe_unit", &size_info_t::stripe_unit);
    cls.def_readonly("stripe_count", &size_info_t::stripe_count);
    cls.def_readonly("features", &size_info_t::features);
    cls.def_readonly("flags", &size_info_t::flags);

  }

  {
    py::class_<snapc_t> cls(m, "snapc_t");
    cls.def(py::init<>());
    cls.def_readonly("seq", &snapc_t::seq);
    cls.def_readonly("snaps", &snapc_t::snaps);

  }

  {
    py::class_<parent_spec_t> cls(m, "parent_spec_t");
    cls.def(py::init<>());
    cls.def_readonly("pool_id", &parent_spec_t::pool_id);
    cls.def_readonly("image_id", &parent_spec_t::image_id);
    cls.def_readonly("snap_id", &parent_spec_t::snap_id);

  }

  {
    py::class_<parent_info_t> cls(m, "parent_info_t");
    cls.def(py::init<>());
    cls.def_readonly("spec", &parent_info_t::spec);
    cls.def_readonly("overlap", &parent_info_t::overlap);

  }

  {
    py::class_<child_t> cls(m, "child_t");
    cls.def(py::init<>());
    cls.def_readonly("pool_id", &child_t::pool_id);
    cls.def_readonly("image_id", &child_t::image_id);

  }

  {
    py::class_<qos_t> cls(m, "qos_t");
    cls.def(py::init<>());
    cls.def_readonly("iops", &qos_t::iops);
    cls.def_readonly("bps", &qos_t::bps);

  }

  {
    py::class_<snap_info_t> cls(m, "snap_info_t");
    cls.def(py::init<>());
    cls.def_readonly("id", &snap_info_t::id);
    cls.def_readonly("name", &snap_info_t::name);
    cls.def_readonly("snap_ns_type", &snap_info_t::snap_ns_type);
    cls.def_readonly("size", &snap_info_t::size);
    cls.def_readonly("features", &snap_info_t::features);
    cls.def_readonly("flags", &snap_info_t::flags);
    cls.def_readonly("protection_status", &snap_info_t::protection_status);
    cls.def_readonly("timestamp", &snap_info_t::timestamp);

  }

  {
    py::class_<snap_info_v2_t> cls(m, "snap_info_v2_t");
    cls.def(py::init<>());
    cls.def_readonly("id", &snap_info_v2_t::id);
    cls.def_readonly("name", &snap_info_v2_t::name);
    cls.def_readonly("snap_ns_type", &snap_info_v2_t::snap_ns_type);
    cls.def_readonly("size", &snap_info_v2_t::size);
    cls.def_readonly("features", &snap_info_v2_t::features);
    cls.def_readonly("flags", &snap_info_v2_t::flags);
    cls.def_readonly("protection_status", &snap_info_v2_t::protection_status);
    cls.def_readonly("timestamp", &snap_info_v2_t::timestamp);
    cls.def_readonly("du", &snap_info_v2_t::du);

  }

  {
    py::class_<image_info_t> cls(m, "image_info_t");
    cls.def(py::init<>());
    cls.def_readonly("id", &image_info_t::id);
    cls.def_readonly("name", &image_info_t::name);
    cls.def_readonly("order", &image_info_t::order);
    cls.def_readonly("size", &image_info_t::size);
    cls.def_readonly("stripe_unit", &image_info_t::stripe_unit);
    cls.def_readonly("stripe_count", &image_info_t::stripe_count);
    cls.def_readonly("features", &image_info_t::features);
    cls.def_readonly("flags", &image_info_t::flags);
    cls.def_readonly("snapc", &image_info_t::snapc);
    cls.def_readonly("snaps", &image_info_t::snaps);
    cls.def_readonly("parent", &image_info_t::parent);
    cls.def_readonly("timestamp", &image_info_t::timestamp);
    cls.def_readonly("data_pool_id", &image_info_t::data_pool_id);
    cls.def_readonly("watchers", &image_info_t::watchers);
    cls.def_readonly("qos", &image_info_t::qos);

  }

//  {
//      m.def("release", []() {
//          malloc_trim(0);
//      });
//  }

  //
  // xRBD
  //
  {

    py::class_<xRBD> cls(m, "xRBD");
    cls.def(py::init<>());

    cls.def("list_info", &xRBD::list_info);

  }

  {
    py::class_<librados::IoCtx> cls(m, "IoCtx");
    cls.def(py::init<>());
  }

} // PYBIND11_MODULE(rbdx, m)

} // namespace rbdx
