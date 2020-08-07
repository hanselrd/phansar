#include <phansar/common/config.hpp>

#include <phansar/vendor/docopt.hpp>
#include <phansar/vendor/fmt.hpp>

#include <iterator>
#include <string>

namespace phansar::common::config {
static const auto _USAGE =
    R"({name}

    Usage:
        {name} [options]

    Options:
        -h, --help                          Show this screen
        -v, --version                       Show version
        -n <name>, --name=<name>            Name of this binary [default: {name}]
        -c <config>, --config=<config>      Configuration file
        -l <file>, --log-file=<file>        Log file [default: {logfile}]
        -L <level>, --log-level=<level>     Log level [default: {loglevel}]
        -i <ip>, --ip=<ip>                  IP Address [default: 0.0.0.0]
        -p <port>, --port=<port>            Port [default: 7000]
        -t <threads>, --threads=<threads>   Number of concurrent threads [default: 1]

    Arguments:
        <level>: trace, debug, info, warn, error, critical, off
        <ip>: N.N.N.N; 0 <= N <= 255
        <port>: N; 0 <= N <= 65535
        <threads>: N; 0 <= N <= {{hardware limit}}
)";

static auto _docopt_map = std::map<std::string, docopt::value>{};

void init(int argc, const char * const * argv) {
    auto bin = std::string{argv[0]};
    bin      = bin.substr(bin.find_last_of('/') + 1);

    _docopt_map = docopt::docopt(fmt::format(_USAGE,
                                             fmt::arg("name", bin),
                                             fmt::arg("logfile", bin + ".log"),
                                             fmt::arg("loglevel",
#ifdef NDEBUG
                                                      "info"
#else
                                                      "debug"
#endif
                                                      )),
                                 {std::next(argv), std::next(argv, argc)},
                                 true,
                                 bin + " 1.0");
}

auto get_binary_name() -> std::string {
    if (_docopt_map.count("--name") != 0 && _docopt_map["--name"]) {
        return _docopt_map["--name"].asString();
    }
    return {};
}

auto get_config_file() -> std::string {
    if (_docopt_map.count("--config") != 0 && _docopt_map["--config"]) {
        return _docopt_map["--config"].asString();
    }
    return {};
}

auto get_log_file() -> std::string {
    if (_docopt_map.count("--log-file") != 0 && _docopt_map["--log-file"]) {
        return _docopt_map["--log-file"].asString();
    }
    return {};
}

auto get_log_level() -> log::level {
    if (_docopt_map.count("--log-level") != 0 && _docopt_map["--log-level"]) {
        auto log_level = _docopt_map["--log-level"].asString();

        if (log_level == "trace") {
            return log::level::trace;
        }
        if (log_level == "debug") {
            return log::level::debug;
        }
        if (log_level == "info") {
            return log::level::info;
        }
        if (log_level == "warn") {
            return log::level::warning;
        }
        if (log_level == "error") {
            return log::level::error;
        }
        if (log_level == "critical") {
            return log::level::critical;
        }
        if (log_level == "off") {
            return log::level::off;
        }
    }
    return log::level::off;
}

auto get_ip_address() -> std::string {
    if (_docopt_map.count("--ip") != 0 && _docopt_map["--ip"]) {
        return _docopt_map["--ip"].asString();
    }
    return {};
}

auto get_port() -> std::uint16_t {
    if (_docopt_map.count("--port") != 0 && _docopt_map["--port"]) {
        return static_cast<std::uint16_t>(_docopt_map["--port"].asLong());
    }
    return 0;
}

auto get_num_threads() -> std::size_t {
    if (_docopt_map.count("--threads") != 0 && _docopt_map["--threads"]) {
        return static_cast<std::size_t>(_docopt_map["--threads"].asLong());
    }
    return 0;
}
} // namespace phansar::common::config
