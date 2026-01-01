#include "model.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using py::class_, py::overload_cast, py::arg, py::init, py::array_t, py::array;

PYBIND11_MODULE(cube, m) {
  class_<cube>(m, "cube")
      .def(init<>())
      .def(
          py::init([](array_t<uint8_t, array::c_style | array::forcecast> arr) {
            if (arr.ndim() != 3 || arr.shape(0) != faces ||
                arr.shape(1) != dim || arr.shape(2) != dim) {
              throw std::runtime_error("Expected array of shape (6,3,3)");
            }

            uint8_t pos[faces][dim][dim];
            memcpy(pos, arr.data(), sizeof(pos));
            return cube(pos);
          }),
          arg("pos"))
      .def(init<string>(), arg("sequence"))
      .def("reset", &cube::reset)
      .def("print", &cube::printCube)
      ;
}
