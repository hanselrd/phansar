#include <cstddef>
#include <phansar/common/errc.hpp>
#include <phansar/common/error.hpp>
#include <phansar/common/logger.hpp>
#include <phansar/common/meta/is_complete.hpp>
#include <phansar/common/meta/y_combinator.hpp>
#include <phansar/common/rttr/debug_visitor.hpp>
#include <phansar/common/rttr/pybind_visitor.hpp>

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <rttr/type>
#include <rttr/visitor.h>

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    // phansar::common::pybind::pybind_logger(m);
    auto visitor = phansar::common::rttr::pybind_visitor{m};
    visitor.visit(rttr::type::get<phansar::common::logger>());
}

auto main(int _argc, char * _argv[]) -> int {
    (void)_argc;
    (void)_argv;

    auto logger  = phansar::common::logger{"client",
                                          "log/client.log",
                                          static_cast<std::size_t>(1024 * 1024 * 5),
                                          3};
    auto visitor = phansar::common::rttr::debug_visitor{};
    visitor.visit(rttr::type::get<phansar::common::logger>());
    logger.debug("testing from C++");
    auto ec = std::error_code{phansar::common::errc::error102};
    logger.debug(fmt::format("100 {} {}", ec.message(), ec == phansar::common::error::error100));
    logger.debug(fmt::format("200 {} {}", ec, ec == phansar::common::error::error200));
    logger.debug(fmt::format("300 {} {}", ec, ec == phansar::common::error::error300));
    logger.debug(fmt::format("400 {} {}", ec, ec == phansar::common::error::error400));

    auto t = rttr::type::get<phansar::common::errc>();
    logger.debug(fmt::format("{} {}", t.get_name(), t.get_sizeof()));
    t = rttr::type::get<phansar::common::logger>();
    logger.debug(fmt::format("{} {}", t.get_name(), t.get_sizeof()));

    auto guard = py::scoped_interpreter{};
    py::exec(R"python(
        from phansar import logger#, material, colors, permissions

        l = logger("client", "logs/client.log", 1024 * 1024 * 5, 3)
        l.trace("trace")
        l.debug("debug")
        l.info("info")
        l.warn("warn")
        l.error("error")
        l.critical("critical")
        l.debug(f"{l}")

        #m = material()
        #l.debug(f"{m}")
        #m.ambient = [1, 2, 3]
        #l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")
        #m.diffuse = [4, 5, 6]
        #l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")
        #m.specular = [7, 8, 9]
        #l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")

        #l.debug(f"{colors.white}")
        #l.debug(f"{colors.black}")
        #l.debug(f"{colors.red}")
        #l.debug(f"{colors.blue}")
        #l.debug(f"{colors.green}")
        #l.debug(f"{colors.yellow}")
        #l.debug(f"{int(colors.cyan)}")
        #l.debug(f"{colors.magenta}")
        #l.debug(f"{colors.pink}")

        #l.debug(f"{permissions.read}")
        #l.debug(f"{permissions.write}")
        #l.debug(f"{permissions.execute}")
        #l.debug(f"{permissions.read_write}")
        #l.debug(f"{permissions.read_execute}")
        #l.debug(f"{permissions.write_execute}")
        #l.debug(f"{permissions.read_write_execute}")
    )python");

    return 0;
}
