#include <phansar/common/pybind.hpp>

#include <array>
#include <cstdint>

namespace phansar::codegen {
enum class colors {
    red,
    blue,
    green,
    yellow,
    cyan,
    magenta,
    black,
    white,
};

/* [[[cog
import codegen
codegen.enum(
    "colors",
    [
        "red",
        "blue",
        "green",
        "yellow",
        "cyan",
        "magenta",
        "black",
        "white",
    ],
    pybind=True,
)
]]] */
namespace pybind {
inline void pybind_colors(pybind11::module & _m) {
    py::enum_<colors>(_m, "colors")
        .value("red", colors::red)
        .value("blue", colors::blue)
        .value("green", colors::green)
        .value("yellow", colors::yellow)
        .value("cyan", colors::cyan)
        .value("magenta", colors::magenta)
        .value("black", colors::black)
        .value("white", colors::white);
}
} // namespace pybind
/* [[[end]]] */

enum permissions {
    read               = 1 << 0,
    write              = 1 << 1,
    execute            = 1 << 2,
    read_write         = read | write,
    read_execute       = read | execute,
    write_execute      = write | execute,
    read_write_execute = read | write | execute,
};

/* [[[cog
import codegen
codegen.enum(
    "permissions",
    [
        "read",
        "write",
        "execute",
        "read_write",
        "read_execute",
        "write_execute",
        "read_write_execute",
    ],
    pybind=True,
)
]]] */
namespace pybind {
inline void pybind_permissions(pybind11::module & _m) {
    py::enum_<permissions>(_m, "permissions")
        .value("read", permissions::read)
        .value("write", permissions::write)
        .value("execute", permissions::execute)
        .value("read_write", permissions::read_write)
        .value("read_execute", permissions::read_execute)
        .value("write_execute", permissions::write_execute)
        .value("read_write_execute", permissions::read_write_execute);
}
} // namespace pybind
/* [[[end]]] */

struct material {
    std::array<float, 3> ambient;
    std::array<float, 3> diffuse;
    std::array<float, 3> specular;
    float                shininess;
};

/* [[[cog
import codegen
codegen.struct(
    "material",
    "material",
    [
        codegen.StructField(name="ambient"),
        codegen.StructField(name="diffuse"),
        codegen.StructField(name="specular"),
        codegen.StructField(name="shininess"),
    ],
    pybind=True,
)
]]] */
namespace pybind {
inline void pybind_material(pybind11::module & _m) {
    py::class_<material>(_m, "material")
        .def(py::init<>())
        .def_readwrite("ambient", &material::ambient)
        .def_readwrite("diffuse", &material::diffuse)
        .def_readwrite("specular", &material::specular)
        .def_readwrite("shininess", &material::shininess)
        .def("__repr__", [](const material & _o) {
            return fmt::format("<material object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
/* [[[end]]] */

template <class T>
struct point2 {
    T x;
    T y;
};

template <class T>
struct point3 {
    T x;
    T y;
    T z;
};

/* [[[cog
import codegen
codegen.struct_template(
    [
        ("point2i", "point2<std::int64_t>"),
        ("point2u", "point2<std::uint64_t>"),
        ("point2f", "point2<float>"),
        ("point2d", "point2<double>"),
    ],
    [
        codegen.StructField(name="x"),
        codegen.StructField(name="y"),
    ],
    pybind=True,
)
codegen.struct_template(
    [
        ("point3i", "point3<std::int64_t>"),
        ("point3u", "point3<std::uint64_t>"),
        ("point3f", "point3<float>"),
        ("point3d", "point3<double>"),
    ],
    [
        codegen.StructField(name="x"),
        codegen.StructField(name="y"),
        codegen.StructField(name="z"),
    ],
    pybind=True,
)
]]] */
namespace pybind {
inline void pybind_point2i(pybind11::module & _m) {
    py::class_<point2<std::int64_t>>(_m, "point2i")
        .def(py::init<>())
        .def_readwrite("x", &point2<std::int64_t>::x)
        .def_readwrite("y", &point2<std::int64_t>::y)
        .def("__repr__", [](const point2<std::int64_t> & _o) {
            return fmt::format("<point2i object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
namespace pybind {
inline void pybind_point2u(pybind11::module & _m) {
    py::class_<point2<std::uint64_t>>(_m, "point2u")
        .def(py::init<>())
        .def_readwrite("x", &point2<std::uint64_t>::x)
        .def_readwrite("y", &point2<std::uint64_t>::y)
        .def("__repr__", [](const point2<std::uint64_t> & _o) {
            return fmt::format("<point2u object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
namespace pybind {
inline void pybind_point2f(pybind11::module & _m) {
    py::class_<point2<float>>(_m, "point2f")
        .def(py::init<>())
        .def_readwrite("x", &point2<float>::x)
        .def_readwrite("y", &point2<float>::y)
        .def("__repr__", [](const point2<float> & _o) {
            return fmt::format("<point2f object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
namespace pybind {
inline void pybind_point2d(pybind11::module & _m) {
    py::class_<point2<double>>(_m, "point2d")
        .def(py::init<>())
        .def_readwrite("x", &point2<double>::x)
        .def_readwrite("y", &point2<double>::y)
        .def("__repr__", [](const point2<double> & _o) {
            return fmt::format("<point2d object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
namespace pybind {
inline void pybind_point3i(pybind11::module & _m) {
    py::class_<point3<std::int64_t>>(_m, "point3i")
        .def(py::init<>())
        .def_readwrite("x", &point3<std::int64_t>::x)
        .def_readwrite("y", &point3<std::int64_t>::y)
        .def_readwrite("z", &point3<std::int64_t>::z)
        .def("__repr__", [](const point3<std::int64_t> & _o) {
            return fmt::format("<point3i object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
namespace pybind {
inline void pybind_point3u(pybind11::module & _m) {
    py::class_<point3<std::uint64_t>>(_m, "point3u")
        .def(py::init<>())
        .def_readwrite("x", &point3<std::uint64_t>::x)
        .def_readwrite("y", &point3<std::uint64_t>::y)
        .def_readwrite("z", &point3<std::uint64_t>::z)
        .def("__repr__", [](const point3<std::uint64_t> & _o) {
            return fmt::format("<point3u object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
namespace pybind {
inline void pybind_point3f(pybind11::module & _m) {
    py::class_<point3<float>>(_m, "point3f")
        .def(py::init<>())
        .def_readwrite("x", &point3<float>::x)
        .def_readwrite("y", &point3<float>::y)
        .def_readwrite("z", &point3<float>::z)
        .def("__repr__", [](const point3<float> & _o) {
            return fmt::format("<point3f object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
namespace pybind {
inline void pybind_point3d(pybind11::module & _m) {
    py::class_<point3<double>>(_m, "point3d")
        .def(py::init<>())
        .def_readwrite("x", &point3<double>::x)
        .def_readwrite("y", &point3<double>::y)
        .def_readwrite("z", &point3<double>::z)
        .def("__repr__", [](const point3<double> & _o) {
            return fmt::format("<point3d object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
/* [[[end]]] */
} // namespace phansar::codegen
