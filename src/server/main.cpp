#include <phansar/server/application.hpp>
/* #include <phansar/common/allocators/mallocator.hpp> */
/* #include <phansar/common/command_line.hpp> */
/* #include <phansar/common/histogram.hpp> */
/* #include <phansar/common/log.hpp> */
/* #include <phansar/common/macros.hpp> */
/* #include <phansar/common/networking/service.hpp> */
/* #include <phansar/common/networking/stream.hpp> */
/* #include <phansar/common/python.hpp> */
/* #include <phansar/common/threading/synchronized.hpp> */

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
#if 0
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    phansar::common::python::embed(m);

    auto server    = m.def_submodule("server");
    auto fast_calc = server.def_submodule("fast_calc");
    fast_calc.def("add", [](int _i, int _j) { return _i + _j; });
}
#endif

auto main(int _argc, char * _argv[]) -> int {
    auto app = phansar::server::application{_argc, _argv};
    app.run();

#if 0
    if (phansar::common::command_line::instance() != nullptr) {
        PH_LOG_INFO("Log Level: {}", phansar::common::command_line::instance()->log_level());
        PH_LOG_INFO("Log File: {}", phansar::common::command_line::instance()->log_file());
        PH_LOG_INFO("Host: {}", phansar::common::command_line::instance()->host());
        PH_LOG_INFO("Port: {}", phansar::common::command_line::instance()->port());
        PH_LOG_INFO("Jobs: {}", phansar::common::command_line::instance()->jobs());
    }

    auto guard = py::scoped_interpreter{};
    py::exec(R"python(
        from phansar.common import log
        from phansar.server import fast_calc

        log.info("Hello, {name}! The answer is {number}".format(name="Bob", number=42))
        log.info("{} + {} = {}".format(3, 4, fast_calc.add(3, 4)))
        log.info("test")
        log.trace("trace")
        log.debug('debug')
        log.info("info")
        log.warning("warning")
        log.error("error")
        log.critical("critical")
    )python");

    auto rd      = std::random_device{};
    auto gen     = std::mt19937{rd()};
    auto distrib = std::uniform_int_distribution{1, 6};

    auto h = phansar::common::histogram<int>{"XXXX", "xxxx", 6};
    for (auto i = std::size_t{0}; i < 1'000'000; ++i) {
        h.push(distrib(gen));
    }
    /* for (auto && i : {5, 5, 10, 12, 8, 3, 2, 9, 8, 4, 1, 20, 3, 2, 4, 6}) { */
    /*     h.push(i); */
    /* } */
    PH_LOG_INFO("{}", h);

    auto a = std::vector<double>{1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5};
    auto b = std::vector<double>{2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5};
    auto c = std::vector<double>(9);
    xsimd::transform(std::cbegin(a),
                     std::cend(a),
                     std::cbegin(b),
                     std::begin(c),
                     [](const auto & _x, const auto & _y) { return (_x + _y) / 2.; });
    PH_LOG_INFO("a: {}", a);
    PH_LOG_INFO("b: {}", b);
    PH_LOG_INFO("c: {}", c);

    auto executor = tf::Executor{};
    auto taskflow = tf::Taskflow{};

    auto [A, B, C, D] = taskflow.emplace([]() { PH_LOG_INFO("Task A"); },
                                         []() { PH_LOG_INFO("Task B"); },
                                         []() { PH_LOG_INFO("Task C"); },
                                         []() { PH_LOG_INFO("Task D"); });

    A.name("A");
    B.name("B");
    C.name("C");
    D.name("D");

    A.precede(B, C);
    D.succeed(B, C);

    auto sync_vector = phansar::common::threading::synchronized<std::vector<std::size_t>>{};

    /* for (auto i = std::size_t{0}; i < 100'000; ++i) { */
    /*     executor.async([i, &sync_vector]() { */
    /*         PH_LOG_INFO("Task {}", i); */
    /*         auto lock = sync_vector.lock(); */
    /*         lock->push_back(i); */
    /*     }); */
    /* } */

    /* entt::monostate<entt::hashed_string{"test"}>{} = true; */
    /* auto empty                                     =
     * entt::service_locator<std::nullopt_t>::empty(); */

    executor.run(taskflow);
    executor.wait_for_all();
    PH_LOG_INFO("\n{}", taskflow.dump());

    auto lock = sync_vector.lock_shared();
    PH_LOG_INFO("sync_vector: {}", lock->size());
#endif

    return 0;
}
