#include <phansar/common/cli.hpp>

namespace phansar::common {
cli::cli(int _argc, const char * const * _argv) {
    static const auto * const usage =
        R"({name}

    Usage:
        {name} [options]

    Options:
        -h, --help                          Show this screen
        -v, --version                       Show version
        -n <name>, --name=<name>            Name of this binary [default: {name}]
        -L <level>, --log-level=<level>     Log level [default: {log_level}]
        -l <file>, --log-file=<file>        Log file [default: {log_file}]
        -H <host>, --host=<host>            Host [default: 0.0.0.0]
        -p <port>, --port=<port>            Port [default: 7000]
        -t <threads>, --threads=<threads>   Number of concurrent threads [default: 1]

    Arguments:
        <level>: trace, debug, info, warn, error, critical, off
        <host>: N.N.N.N; 0 <= N <= 255
        <port>: N; 0 <= N <= 65535
        <threads>: N; 0 <= N <= {hardware_limit}
)";

    auto bin = std::string{_argv[0]};
    bin      = bin.substr(bin.find_last_of('/') + 1);

    m_docopt_map =
        docopt::docopt(fmt::format(usage,
                                   fmt::arg("name", bin),
                                   fmt::arg("log_level",
#ifdef NDEBUG
                                            "info"
#else
                                            "debug"
#endif
                                            ),
                                   fmt::arg("log_file", bin + ".log"),
                                   fmt::arg("hardware_limit", std::thread::hardware_concurrency())),
                       {std::next(_argv), std::next(_argv, _argc)},
                       true,
                       bin + " 1.0");
}

auto cli::binary_name() const -> std::string {
    if (m_docopt_map.count("--name") != 0 && m_docopt_map.at("--name")) {
        return m_docopt_map.at("--name").asString();
    }
    return {};
}

auto cli::log_level() const -> log::level {
    if (m_docopt_map.count("--log-level") != 0 && m_docopt_map.at("--log-level")) {
        auto level = m_docopt_map.at("--log-level").asString();

        if (level == "trace") {
            return log::level::trace;
        }
        if (level == "debug") {
            return log::level::debug;
        }
        if (level == "info") {
            return log::level::info;
        }
        if (level == "warn") {
            return log::level::warning;
        }
        if (level == "error") {
            return log::level::error;
        }
        if (level == "critical") {
            return log::level::critical;
        }
        if (level == "off") {
            return log::level::off;
        }
    }
    return log::level::off;
}

auto cli::log_file_path() const -> std::string {
    if (m_docopt_map.count("--log-file") != 0 && m_docopt_map.at("--log-file")) {
        return m_docopt_map.at("--log-file").asString();
    }
    return {};
}

auto cli::host() const -> std::string {
    if (m_docopt_map.count("--host") != 0 && m_docopt_map.at("--host")) {
        return m_docopt_map.at("--host").asString();
    }
    return {};
}

auto cli::port() const -> std::uint16_t {
    if (m_docopt_map.count("--port") != 0 && m_docopt_map.at("--port")) {
        return static_cast<std::uint16_t>(m_docopt_map.at("--port").asLong());
    }
    return 0;
}

auto cli::num_threads() const -> std::size_t {
    if (m_docopt_map.count("--threads") != 0 && m_docopt_map.at("--threads")) {
        return static_cast<std::size_t>(m_docopt_map.at("--threads").asLong());
    }
    return 0;
}
} // namespace phansar::common
