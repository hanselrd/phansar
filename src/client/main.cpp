#include <phansar/codegen/macros.hpp>
#include <phansar/common/logger.hpp>

#include <fmt/format.h>
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include <array>

namespace py = pybind11;

namespace phansar::test {
struct PH_ANNOTATE() material {
    PH_ANNOTATE(readonly) std::array<float, 3> ambient, diffuse, specular;
    float shininess;
};

enum class PH_ANNOTATE() colors { white, black, red, blue, green, yellow, cyan, magenta, pink };

enum PH_ANNOTATE() permissions {
    read               = 0x01,
    write              = 0x02,
    execute            = 0x04,
    read_write         = read | write,
    read_execute       = read | execute,
    write_execute      = write | execute,
    read_write_execute = read | write | execute
};

template <class T, class U, class V>
struct PH_ANNOTATE(template(name(u8), data(T(std::uint8_t), U(std::uint8_t), V(std::uint8_t))),
                   template(name(u16), data(T(std::uint16_t), U(std::uint16_t), V(std::uint16_t))),
                   template(name(u32), data(T(std::uint32_t), U(std::uint32_t), V(std::uint32_t))),
                   template(name(u64), data(T(std::uint64_t), U(std::uint64_t), V(std::uint64_t))),
                   template(name(f), data(T(float), U(float), V(float))),
                   template(name(d), data(T(double), U(double), V(double)))) point {
    T x;
    U y;
    V z;
};

/* template <class T> */
/* struct PH_ANNOTATE(template(float)) point<T, double, double> { */
/*     T      x; */
/*     double y, z; */
/* }; */

/* template <> */
/* struct PH_ANNOTATE() point<double, double, double> { */
/*     double x, y, z; */
/* }; */
} // namespace phansar::test

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
#if 1
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    py::class_<phansar::common::logger>(m, "logger")
        .def(py::init<std::string_view, std::string_view, std::size_t, std::size_t>())
        .def("handle", py::overload_cast<>(&phansar::common::logger::handle, py::const_))
        .def("trace", py::overload_cast<std::string_view>(&phansar::common::logger::trace))
        .def("debug", py::overload_cast<std::string_view>(&phansar::common::logger::debug))
        .def("info", py::overload_cast<std::string_view>(&phansar::common::logger::info))
        .def("warn", py::overload_cast<std::string_view>(&phansar::common::logger::warn))
        .def("error", py::overload_cast<std::string_view>(&phansar::common::logger::error))
        .def("critical", py::overload_cast<std::string_view>(&phansar::common::logger::critical))
        .def("__repr__", [](const phansar::common::logger & _o) {
            return fmt::format("<phansar::common::logger object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
    py::class_<phansar::test::material>(m, "material")
        .def(py::init<>())
        .def_readwrite("ambient", &phansar::test::material::ambient)
        .def_readwrite("diffuse", &phansar::test::material::diffuse)
        .def_readwrite("specular", &phansar::test::material::specular)
        .def_readwrite("shininess", &phansar::test::material::shininess)
        .def("__repr__", [](const phansar::test::material & _o) {
            return fmt::format("<phansar::test::material object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
    py::enum_<phansar::test::colors>(m, "colors")
        .value("white", phansar::test::colors::white)
        .value("black", phansar::test::colors::black)
        .value("red", phansar::test::colors::red)
        .value("blue", phansar::test::colors::blue)
        .value("green", phansar::test::colors::green)
        .value("yellow", phansar::test::colors::yellow)
        .value("cyan", phansar::test::colors::cyan)
        .value("magenta", phansar::test::colors::magenta)
        .value("pink", phansar::test::colors::pink);
    py::enum_<phansar::test::permissions>(m, "permissions")
        .value("read", phansar::test::read)
        .value("write", phansar::test::write)
        .value("execute", phansar::test::execute)
        .value("read_write", phansar::test::read_write)
        .value("read_execute", phansar::test::read_execute)
        .value("write_execute", phansar::test::write_execute)
        .value("read_write_execute", phansar::test::read_write_execute);
    /* py::class_<phansar::test::point>(m, "point") */
    /*     .def(py::init<>()) */
    /*     .def_readwrite("x", &phansar::test::point::x) */
    /*     .def_readwrite("y", &phansar::test::point::y) */
    /*     .def_readwrite("z", &phansar::test::point::z) */
    /*     .def("__repr__", [](const phansar::test::point & _o) { */
    /*         return fmt::format("<phansar::test::point object at {} with {} byte(s)>", */
    /*                            static_cast<const void *>(&_o), */
    /*                            sizeof(_o)); */
    /*     }); */
}
#endif

auto main(int _argc, char * _argv[]) -> int {
    (void)_argc;
    (void)_argv;

    auto guard = py::scoped_interpreter{};
    py::exec(R"python(
        from phansar import logger, material, colors, permissions

        l = logger("client", "logs/client.log", 1024 * 1024 * 5, 3)
        l.trace("trace")
        l.debug("debug")
        l.info("info")
        l.warn("warn")
        l.error("error")
        l.critical("critical")
        l.debug(f"{l}")

        m = material()
        l.debug(f"{m}")
        m.ambient = [1, 2, 3]
        l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")
        m.diffuse = [4, 5, 6]
        l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")
        m.specular = [7, 8, 9]
        l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")

        l.debug(f"{colors.white}")
        l.debug(f"{colors.black}")
        l.debug(f"{colors.red}")
        l.debug(f"{colors.blue}")
        l.debug(f"{colors.green}")
        l.debug(f"{colors.yellow}")
        l.debug(f"{int(colors.cyan)}")
        l.debug(f"{colors.magenta}")
        l.debug(f"{colors.pink}")

        l.debug(f"{permissions.read}")
        l.debug(f"{permissions.write}")
        l.debug(f"{permissions.execute}")
        l.debug(f"{permissions.read_write}")
        l.debug(f"{permissions.read_execute}")
        l.debug(f"{permissions.write_execute}")
        l.debug(f"{permissions.read_write_execute}")
    )python");

    return 0;
}
