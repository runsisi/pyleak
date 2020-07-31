#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace x {

int add(int i, int j) {
  return i + j;
}

PYBIND11_MODULE(x, m) {

  m.def("add", &add, "A function which adds two numbers");

}

}
