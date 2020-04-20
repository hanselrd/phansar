#include "common_config.hpp"
#include <docopt.h>
#include <fmt/format.h>
#include <iterator>
#include <string>

static const auto USAGE =
    R"({name}

    Usage:
        {name} [options]

    Options:
        -h, --help                          Show this screen
        -v, --version                       Show version
        -n <name>, --name=<name>            Name of this binary [default: {name}]
        -c <config>, --config=<config>      Configuration file
        -l <file>, --log-file=<file>        Log file [default: {logfile}]
        -L <level>, --log-level=<level>     Log level [default: trace]
        -i <ip>, --ip=<ip>                  IP Address [default: 0.0.0.0]
        -p <port>, --port=<port>            Port [default: 7000]
        -t <threads>, --threads=<threads>   Number of concurrent threads [default: 1]

    Arguments:
        <level>: trace, debug, info, warn, error, critical, off
        <ip>: N.N.N.N; 0 <= N <= 255
        <port>: N; 0 <= N <= 65535
        <threads>: N; 0 <= N <= {{hardware limit}}
)";

static auto docopt_map = std::map<std::string, docopt::value>{};

namespace common::config {
void init(int argc, const char * const * argv) {
    auto bin = std::string{argv[0]};
    bin      = bin.substr(bin.find_last_of('/') + 1);

    docopt_map =
        docopt::docopt(fmt::format(USAGE, fmt::arg("name", bin), fmt::arg("logfile", bin + ".log")),
                       {std::next(argv), std::next(argv, argc)},
                       true,
                       bin + " 1.0");
}

auto get_binary_name() -> std::string {
    if (docopt_map.count("--name") != 0 && docopt_map["--name"]) {
        return docopt_map["--name"].asString();
    }
    return {};
}

auto get_config_file() -> std::string {
    if (docopt_map.count("--config") != 0 && docopt_map["--config"]) {
        return docopt_map["--config"].asString();
    }
    return {};
}

auto get_log_file() -> std::string {
    if (docopt_map.count("--log-file") != 0 && docopt_map["--log-file"]) {
        return docopt_map["--log-file"].asString();
    }
    return {};
}

auto get_log_level() -> spdlog::level::level_enum {
    if (docopt_map.count("--log-level") != 0 && docopt_map["--log-level"]) {
        auto log_level = docopt_map["--log-level"].asString();

        if (log_level == "trace") {
            return spdlog::level::trace;
        }
        if (log_level == "debug") {
            return spdlog::level::debug;
        }
        if (log_level == "info") {
            return spdlog::level::info;
        }
        if (log_level == "warn") {
            return spdlog::level::warn;
        }
        if (log_level == "error") {
            return spdlog::level::err;
        }
        if (log_level == "critical") {
            return spdlog::level::critical;
        }
        if (log_level == "off") {
            return spdlog::level::off;
        }
    }
    return spdlog::level::off;
}

auto get_ip_address() -> std::string {
    if (docopt_map.count("--ip") != 0 && docopt_map["--ip"]) {
        return docopt_map["--ip"].asString();
    }
    return {};
}

auto get_port() -> std::uint16_t {
    if (docopt_map.count("--port") != 0 && docopt_map["--port"]) {
        return static_cast<std::uint16_t>(docopt_map["--port"].asLong());
    }
    return 0;
}

auto get_num_threads() -> std::size_t {
    if ((docopt_map.count("--threads") != 0) && docopt_map["--threads"]) {
        return static_cast<std::size_t>(docopt_map["--threads"].asLong());
    }
    return 0;
}
} // namespace common::config
