#ifndef PHANSAR_COMMON_PYTHON_HPP
#define PHANSAR_COMMON_PYTHON_HPP

#include <phansar/vendor/pybind11.hpp>

namespace phansar::common::python {
void embed(py::module & _module);
}

#endif
