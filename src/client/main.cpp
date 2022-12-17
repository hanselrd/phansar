#include <phansar/common/errc.hpp>
#include <phansar/common/error.hpp>
#include <phansar/common/logger.hpp>
#include <phansar/common/macro.hpp>
#include <phansar/common/meta.hpp>
#include <phansar/common/policy.hpp>
#include <phansar/common/reflect/sol_visitor.hpp>
#include <phansar/common/service/executor_service.hpp>
#include <phansar/common/service/logger_service.hpp>
#include <phansar/common/service_container.hpp>
#include <phansar/common/synchronized.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <hedley.h>
#include <rttr/registration>
#include <rttr/type>
#include <rttr/visitor.h>
#include <sigslot/signal.hpp>
#include <sol/sol.hpp>
#include <cstddef>

struct material {
  std::array<float, 3> ambient{}, diffuse{}, specular{};
  float                shininess{};

  static int           s_number;

  void                 func() {}

  static auto          get_x() -> int {
             return s_x;
  }

  [[nodiscard]] auto get_y() const -> int {
    return m_y;
  }

  static void set_x(int _x) {
    s_x = _x;
  }

private:
  static int s_x;
  int        m_y = 0xff;
};

int material::s_x      = 222;
int material::s_number = 10;

enum class color {
  white,
  black,
  red,
  blue,
  green,
  yellow,
  cyan,
  magenta,
  pink
};

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
      .property("shininess", &material::shininess)
      .property("x", &material::get_x, &material::set_x)
      .property_readonly("y", &material::get_y)
      .property("number", &material::s_number)
      .method("func", &material::func);

  rttr::registration::enumeration<color>("color")(
      rttr::value("white", color::white),
      rttr::value("black", color::black),
      rttr::value("red", color::red),
      rttr::value("blue", color::blue),
      rttr::value("green", color::green),
      rttr::value("yellow", color::yellow),
      rttr::value("cyan", color::cyan),
      rttr::value("magenta", color::magenta),
      rttr::value("pink", color::pink));

  rttr::registration::enumeration<permissions>("permissions")(
      rttr::value("read", permissions::READ),
      rttr::value("write", permissions::WRITE),
      rttr::value("execute", permissions::EXECUTE),
      rttr::value("read_write", permissions::READ_WRITE),
      rttr::value("read_execute", permissions::READ_EXECUTE),
      rttr::value("write_execute", permissions::WRITE_EXECUTE),
      rttr::value("read_write_execute", permissions::READ_WRITE_EXECUTE));
}

auto main(int _argc, char * _argv[]) -> int {
  PH_UNUSED(_argc);
  PH_UNUSED(_argv);

  phansar::common::g_service_container
      .emplace<phansar::common::service::logger_service>(
          "client",
          "logs/client.log",
          static_cast<std::size_t>(1024 * 1024 * 5),
          3);

  phansar::common::g_service_container
      .emplace<phansar::common::service::executor_service>();

  auto & executor = phansar::common::g_service_container
                        .service<phansar::common::service::executor_service>();

  auto lua = sol::state{};
  lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table);
  // const auto package_path = lua["package"]["path"].get<std::string>();
  // lua["package"]["path"] =
  //     package_path + (! package_path.empty() ? ";" : "") +
  //     "./assets/scripts/?.lua";

  auto visitor = phansar::common::reflect::sol_visitor{lua};
  visitor.visit<phansar::common::logger>();
  visitor.visit<material>();
  visitor.visit<color>();
  visitor.visit<permissions>();

  HEDLEY_DIAGNOSTIC_PUSH
#ifdef HEDLEY_GCC_VERSION
  HEDLEY_PRAGMA(GCC diagnostic ignored "-Wnonnull")
#endif
  lua.set_function("beep1", []() {
    PH_LOG_TRACE("boop1");
  });
  lua.set("beep2", []() {
    PH_LOG_TRACE("boop2");
  });
  lua["beep3"] = []() {
    PH_LOG_TRACE("boop3");
  };
  lua["check_material"] = [](const material & _m) {
    PH_LOG_DEBUG("material {} | {} | {} | {}",
                 fmt::join(_m.ambient, ", "),
                 fmt::join(_m.diffuse, ", "),
                 fmt::join(_m.specular, ", "),
                 _m.shininess);
  };
  HEDLEY_DIAGNOSTIC_POP

  // lua.new_usertype<material>("material", sol::no_constructor,
  // sol::base_classes, sol::bases<>());
  // //    auto mat_type = lua["material"].get<sol::usertype<material>>();
  // lua["material"]["ambient"]   = &material::ambient;
  // lua["material"]["diffuse"]   = &material::diffuse;
  // lua["material"]["specular"]  = &material::specular;
  // lua["material"]["shininess"] = &material::shininess;
  // lua["material"]["func"]      = &material::func;

  lua["l"] = &phansar::common::g_service_container
                  .service<phansar::common::service::logger_service>();
  auto m2      = material{};
  m2.shininess = 14;
  lua["m2"]    = &m2;
  // lua.safe_script(R"lua(
  //     beep1()
  //     beep2()
  //     beep3()
  // )lua");
  // lua.safe_script_file("./assets/scripts/test.lua");
  lua.script_file("./assets/scripts/index.lua");
  // lua.script(R"lua(
  //     print(m2.shininess)
  //     assert(m2.shininess == 14)
  //     m2.shininess = 15
  //     print(m2.shininess)
  //     assert(m2.shininess == 15)
  //     check_material(m2)
  //     m2.specular = {11, 22, 33}
  //     print(m2.func)

  // local m = material.new1()
  // m.shininess = 12
  // m.ambient = {1, 2, 3}
  // m.diffuse = {4, 5, 6}
  // m.specular = {7, 8, 9}
  // print(m.x)
  // m.x = 200
  // print(m.x)
  // print(m.number)
  // m.number = 101
  // print(m.number)
  // print(m.y)
  // check_material(m)
  // print(color.red)
  // )lua");

  PH_LOG_DEBUG("c++ material {} | {} | {} | {}",
               fmt::join(m2.ambient, ", "),
               fmt::join(m2.diffuse, ", "),
               fmt::join(m2.specular, ", "),
               m2.shininess);
  PH_LOG_DEBUG("number {}", m2.s_number);
  // lua.script(R"lua(
  //     beep1()
  //     beep2()
  //     beep3()

  // logger:debug("debug")
  // logger:debug("debug")
  // logger:info("info")
  // logger:warning("warning")
  // logger:error("error")
  // logger:critical("critical")
  // print(logger)

  // local l = logger.new1("client", "logs/lua-client.log", 1024 * 1024 * 5,
  // 3) l:trace("trace") l:debug("debug") l:info("info")
  // l:warning("warning")
  // l:error("error")
  // l:critical("critical")
  // print(l)

  // m = material.new1()
  // m.shininess = 12
  // --m.ambient = {1, 2, 3}
  // --m.diffuse = {4, 5, 6}
  // --m.specular = {7, 8, 9}
  // print(m.ambient)
  // print(m.diffuse)
  // print(m.specular)
  // print(m.shininess)
  // print(m)

  // check_material(m)
  // print(m2.shininess)
  // m2.shininess = 11
  // print(m2.shininess)
  // assert(m2.shininess == 11)
  // check_material(m2)
  // )lua");

  return 0;

  PH_LOG_DEBUG("testing from C++");
  auto ec = std::error_code{phansar::common::errc::error102};
  PH_LOG_DEBUG(
      "100 {} {}", ec.message(), ec == phansar::common::error::error100);
  PH_LOG_DEBUG("200 {} {}", ec, ec == phansar::common::error::error200);
  PH_LOG_DEBUG("300 {} {}", ec, ec == phansar::common::error::error300);
  PH_LOG_DEBUG("400 {} {}", ec, ec == phansar::common::error::error400);

  executor.async([]() {
    PH_LOG_INFO("Logging from a different thread");
  });
  executor.async([]() {
    PH_LOG_INFO("Logging from a different thread");
  });
  executor.async([]() {
    PH_LOG_INFO("Logging from a different thread");
  });
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

  auto policy = phansar::common::policy::
      static_storage_policy<int, sizeof(int), alignof(int)>{1337};
  PH_LOG_DEBUG("sizeof: {}, value: {}", sizeof(policy), *policy);
  PH_LOG_WARNING("sizeof: {}", sizeof(int));

  auto t = rttr::type::get<phansar::common::errc>();
  PH_LOG_DEBUG("{} {}", t.get_name(), t.get_sizeof());
  t = rttr::type::get<phansar::common::logger>();
  PH_LOG_DEBUG("{} {}", t.get_name(), t.get_sizeof());

  auto sig = sigslot::signal<double>{};
  sig.connect([](double _dt) {
    PH_LOG_DEBUG("dt: {}", _dt);
  });

  PH_LOG_DEBUG("slot_count: {}", sig.slot_count());
  sig(12.0);
  sig(15.0);

  return 0;
}
