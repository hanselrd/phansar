#include <phansar/common/errc.hpp>
#include <phansar/common/error.hpp>
#include <phansar/common/logger.hpp>
#include <phansar/common/macro.hpp>
#include <phansar/common/meta.hpp>
#include <phansar/common/policy.hpp>
#include <phansar/common/reflect/debug_visitor.hpp>
#include <phansar/common/reflect/pybind_visitor.hpp>
#include <phansar/common/service/executor_service.hpp>
#include <phansar/common/service/logger_service.hpp>
#include <phansar/common/service_container.hpp>
#include <phansar/common/synchronized.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <rttr/registration>
#include <rttr/type>
#include <rttr/visitor.h>
#include <sigslot/signal.hpp>
#include <cstddef>

struct material {
    std::array<float, 3> ambient, diffuse, specular;
    float                shininess;
};

enum class color { white, black, red, blue, green, yellow, cyan, magenta, pink };

enum permissions {
    READ               = 1 << 0,
    WRITE              = 1 << 1,
    EXECUTE            = 1 << 2,
    READ_WRITE         = READ | WRITE,
    READ_EXECUTE       = READ | EXECUTE,
    WRITE_EXECUTE      = WRITE | EXECUTE,
    READ_WRITE_EXECUTE = READ | WRITE | EXECUTE
};

RTTR_REGISTRATION {
    rttr::registration::class_<material>("material")
        .constructor()
        .property("ambient", &material::ambient)
        .property("diffuse", &material::diffuse)
        .property("specular", &material::specular)
        .property("shininess", &material::shininess);

    rttr::registration::enumeration<color>("color")(rttr::value("white", color::white),
                                                    rttr::value("black", color::black),
                                                    rttr::value("red", color::red),
                                                    rttr::value("blue", color::blue),
                                                    rttr::value("green", color::green),
                                                    rttr::value("yellow", color::yellow),
                                                    rttr::value("cyan", color::cyan),
                                                    rttr::value("magenta", color::magenta),
                                                    rttr::value("pink", color::pink)

    );

    rttr::registration::enumeration<permissions>("permissions")(
        rttr::value("read", permissions::READ),
        rttr::value("write", permissions::WRITE),
        rttr::value("execute", permissions::EXECUTE),
        rttr::value("read_write", permissions::READ_WRITE),
        rttr::value("read_execute", permissions::READ_EXECUTE),
        rttr::value("write_execute", permissions::WRITE_EXECUTE),
        rttr::value("read_write_execute", permissions::READ_WRITE_EXECUTE));
}

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    auto visitor = phansar::common::reflect::pybind_visitor{m};
    visitor.visit(rttr::type::get<phansar::common::logger>());
    visitor.visit(rttr::type::get<material>());
    visitor.visit_enumeration<color>();
    visitor.visit_enumeration<permissions>();
}

auto main(int _argc, char * _argv[]) -> int {
    PH_UNUSED(_argc);
    PH_UNUSED(_argv);

    phansar::common::g_service_container.emplace<phansar::common::service::logger_service>(
        "client",
        "logs/client.log",
        static_cast<std::size_t>(1024 * 1024 * 5),
        3);

    phansar::common::g_service_container.emplace<phansar::common::service::executor_service>();

    auto & executor =
        phansar::common::g_service_container.service<phansar::common::service::executor_service>();

    // auto visitor = phansar::common::reflect::debug_visitor{};

    // {
    //     visitor.visit(rttr::type::get<Rectangle>());
    //     // return 0;
    // }

    // visitor.visit(rttr::type::get<phansar::common::logger>());
    PH_LOG_DEBUG("is_const_method: {}",
                 phansar::common::meta::is_const_method_v<decltype(&phansar::common::logger::log)>);
    PH_LOG_DEBUG("testing from C++");
    auto ec = std::error_code{phansar::common::errc::error102};
    PH_LOG_DEBUG("100 {} {}", ec.message(), ec == phansar::common::error::error100);
    PH_LOG_DEBUG("200 {} {}", ec, ec == phansar::common::error::error200);
    PH_LOG_DEBUG("300 {} {}", ec, ec == phansar::common::error::error300);
    PH_LOG_DEBUG("400 {} {}", ec, ec == phansar::common::error::error400);

    executor.async([]() { PH_LOG_INFO("Logging from a different thread"); });
    executor.async([]() { PH_LOG_INFO("Logging from a different thread"); });
    executor.async([]() { PH_LOG_INFO("Logging from a different thread"); });
    executor.wait_for_all();

    auto k = phansar::common::synchronized<int>{12};
    PH_LOG_INFO("{:{}}{}", "", 4, *k.lock_shared());
    PH_LOG_INDENTED_INFO(4, "{}", *k.lock_shared());
    PH_LOG_INFO_IF(true, "{:{}}{}", "", 4, *k.lock_shared());
    PH_LOG_INDENTED_INFO_IF(true, 4, "{}", *k.lock_shared());
    PH_LOG_CRITICAL("{:{}}{}", "", 5, *k.lock_shared());
    PH_LOG_INDENTED_CRITICAL(5, "{}", *k.lock_shared());
    PH_LOG_CRITICAL_IF(true, "{:{}}{}", "", 5, *k.lock_shared());
    PH_LOG_INDENTED_CRITICAL_IF(true, 5, "{}", *k.lock_shared());

    PH_LOG_TRACE("trace");
    PH_LOG_DEBUG("debug");
    PH_LOG_INFO("info");
    PH_LOG_WARNING("warning");
    PH_LOG_ERROR("error");
    PH_LOG_CRITICAL("critical");

    auto policy =
        phansar::common::policy::static_storage_policy<int, sizeof(int), alignof(int)>{1337};
    PH_LOG_DEBUG("sizeof: {}, value: {}", sizeof(policy), *policy);
    PH_LOG_WARNING("sizeof: {}", sizeof(int));

    auto t = rttr::type::get<phansar::common::errc>();
    PH_LOG_DEBUG("{} {}", t.get_name(), t.get_sizeof());
    t = rttr::type::get<phansar::common::logger>();
    PH_LOG_DEBUG("{} {}", t.get_name(), t.get_sizeof());

    auto sig = sigslot::signal<double>{};
    sig.connect([](double _dt) { PH_LOG_DEBUG("dt: {}", _dt); });

    PH_LOG_DEBUG("slot_count: {}", sig.slot_count());
    sig(12.0);
    sig(15.0);

    auto guard = py::scoped_interpreter{};
    py::exec(R"python(
        from phansar import logger, material, color, permissions

        l = logger("client", "logs/client.log", 1024 * 1024 * 5, 3)
        l.trace("trace")
        l.debug("debug")
        l.info("info")
        l.warning("warning")
        l.error("error")
        l.critical("critical")
        l.debug(f"{l}")

        m = material()
        m.ambient = [1, 2, 3]
        l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")
        m.diffuse = [4, 5, 6]
        l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")
        m.specular = [7, 8, 9]
        l.info(f"ambient={m.ambient} diffuse={m.diffuse} specular={m.specular} shininess={m.shininess}")
        l.debug(f"{m}")

        l.debug(f"{color.white}")
        l.debug(f"{color.black}")
        l.debug(f"{color.red}")
        l.debug(f"{color.blue}")
        l.debug(f"{color.green}")
        l.debug(f"{color.yellow}")
        l.debug(f"{int(color.cyan)}")
        l.debug(f"{color.magenta}")
        l.debug(f"{color.pink}")

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
