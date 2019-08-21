#include <map>
#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>

#include <iostream>

typedef struct parent {
  parent() {
    std::cout << "parent_t ctor\n";
  }
  ~parent() {
    std::cout << "parent_t dtor\n";
    image_id = "deleted";
  }
  int64_t pool_id;
  std::string image_id;
  uint64_t snap_id;
} parent_t;

typedef struct child {
  child() {
    std::cout << "child_t ctor\n";
  }
  ~child() {
    std::cout << "child_t dtor\n";
    id = "deleted";
  }
  int64_t pool_id;
  std::string id;
} child_t;

struct image_t {
  image_t() {
    std::cout << "image_t ctor\n";
  }
  ~image_t() {
    std::cout << "image_t dtor\n";
    id = "deleted";
  }
  std::string id;
  std::string name;
  parent_t parent;
  std::map<int, child_t> children;
};

namespace py = pybind11;

using MapInt2Child = std::map<int, child_t>;
using MapString2Image = std::map<std::string, image_t>;
using MapString2String = std::map<std::string, std::string>;
using MapInt2Int = std::map<int, int>;

PYBIND11_MAKE_OPAQUE(MapInt2Child);
PYBIND11_MAKE_OPAQUE(MapString2Image);
PYBIND11_MAKE_OPAQUE(MapString2String);
PYBIND11_MAKE_OPAQUE(MapInt2Int);


PYBIND11_MODULE(x, m) {
  m.def("list_name1", [](std::map<std::string, std::string> *images) {
    {
      std::string image_id{"id1"};
      std::string image_name{"name1"};

      (*images)[image_id] = std::move(image_name);
    }

    {
      std::string image_id{"id2"};
      std::string image_name{"name2"};

      (*images)[image_id] = std::move(image_name);
    }
  });

  m.def("list_name2", [](std::map<std::string, std::string> *images) {
    {
      std::string image_id{"id1"};
      std::string image_name{"name1"};

      (*images)[image_id] = std::move(image_name);
    }
  });

  m.def("list_info1", [](std::map<std::string, image_t> *images) {
    {
      for (int c = 0; c < 10000; c++) {
        std::string image_id{"id1"};
        std::string image_name{"name1"};

        auto& i = (*images)[image_id + std::to_string(c)];
        i.id = std::move(image_id);
        i.name = std::move(image_name);
        i.parent.image_id = "parent-id1";
        i.parent.pool_id = 33;
        i.parent.snap_id = 44;

        std::map<int, child_t> children;
        child_t child1;
        child1.pool_id = 1;
        child1.id = "child-id1";
        children[0] = child1;

        child_t child2;
        child2.pool_id = 1;
        child2.id = "child-id2";
        children[1] = child2;

        i.children.swap(children);
      }
    }

    {
      std::string image_id{"id2"};
      std::string image_name{"name2"};

      auto& i = (*images)[image_id];
      i.id = std::move(image_id);
      i.name = std::move(image_name);
      i.parent.image_id = "parent-id2";
      i.parent.pool_id = 33;
      i.parent.snap_id = 44;

      std::map<int, child_t> children;
      child_t child1;
      child1.pool_id = 2;
      child1.id = "child-id3";
      children[0] = child1;

      child_t child2;
      child2.pool_id = 1;
      child2.id = "child-id4";
      children[1] = child2;

      i.children.swap(children);
    }
  });

  m.def("list_info2", [](std::map<std::string, image_t> *images) {
    {
      std::string image_id{"id1"};
      std::string image_name{"name1"};

      auto& i = (*images)[image_id];
      i.id = std::move(image_id);
      i.name = std::move(image_name);
      i.parent.image_id = "parent-id1";
      i.parent.pool_id = 33;
      i.parent.snap_id = 44;

      std::map<int, child_t> children;
      child_t child1;
      child1.pool_id = 1;
      child1.id = "child-id1";
      children[0] = child1;

      child_t child2;
      child2.pool_id = 1;
      child2.id = "child-id2";
      children[1] = child2;

      i.children.swap(children);
    }
  });

  py::bind_map<MapInt2Child>(m, "MapInt2Child", py::module_local(true));

  {
    auto b = py::bind_map<MapString2Image>(m, "MapString2Image", py::module_local(true));
    b.def("__repr__", [](MapString2Image& self) {
      return "bind of MapString2Image";
    });

    b.def("clear", [](MapString2Image& self) {
      self.clear();
    });
  }

  {
    auto b = py::bind_map<MapInt2Int>(m, "MapInt2Int", py::module_local(true));
        b.def("__repr__", [](MapInt2Int& self) {
      return "bind of MapInt2Int";
    });
  }

  py::bind_map<MapString2String>(m, "MapString2String", py::module_local(true))
      .def("__repr__", [](const MapString2String& self) {
    return "bind of MapString2String";
  });


  py::class_<image_t> image(m, "image");
  image.def(py::init<>());
  image.def_readonly("id", &image_t::id);
  image.def_readonly("name", &image_t::name);
  image.def_readonly("parent", &image_t::parent);
  image.def_readonly("children", &image_t::children);

  py::class_<parent_t> parent(m, "parent");
  parent.def_readonly("image_id", &parent_t::image_id);
  parent.def_readonly("pool_id", &parent_t::pool_id);
  parent.def_readonly("snap_id", &parent_t::snap_id);

  py::class_<child_t> child(m, "child");
  child.def_readonly("id", &child_t::id);
  child.def_readonly("pool_id", &child_t::pool_id);
}
