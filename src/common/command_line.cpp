#include <phansar/common/command_line.hpp>
#include <phansar/common/version.hpp>

namespace phansar::common {
command_line::command_line(int _argc, const char * const * _argv)
    : m_program_name{std::string_view{_argv[0]}.substr(
          std::string_view{_argv[0]}.find_last_of('/') + 1)},
      m_options{m_program_name,
                fmt::format("{} {} @ {}.{} [{}]\n",
                            m_program_name,
                            version::k_version,
                            version::k_git_branch,
                            version::k_git_changes,
                            version::k_timestamp)} {
    m_options.add_options()("h,help", "Show this screen")("v,version", "Show version")(
        "l,log-level",
        "Log level",
        cxxopts::value<std::string>()->default_value("info"))(
        "L,log-file",
        "Log file",
        cxxopts::value<std::string>()->default_value(fmt::format("{}.log", m_program_name)))(
        "H,host",
        "Host",
        cxxopts::value<std::string>()->default_value(
            "0.0.0.0"))("p,port", "Port", cxxopts::value<std::uint16_t>()->default_value("7000"))(
        "j,jobs",
        "Number of jobs to run simultaneously",
        cxxopts::value<std::size_t>()->default_value(
            fmt::format("{}", std::thread::hardware_concurrency())));

    m_options.allow_unrecognised_options();

    m_result = m_options.parse(_argc, _argv);

    if (m_result.count("help") != 0) {
        std::cout << m_options.help();
        std::exit(0);
    } else if (m_result.count("version") != 0) {
        std::cout << fmt::format("{} {} @ {}.{} [{}]\n",
                                 m_program_name,
                                 version::k_version,
                                 version::k_git_branch,
                                 version::k_git_changes,
                                 version::k_timestamp);
        std::exit(0);
    }
}

auto command_line::program_name() const -> std::string {
    return m_program_name;
}

auto command_line::log_level() const -> log::level {
    auto level = m_result["log-level"].as<std::string>();

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

    return log::level::off;
}

auto command_line::log_file() const -> std::string {
    return m_result["log-file"].as<std::string>();
}

auto command_line::host() const -> std::string {
    return m_result["host"].as<std::string>();
}

auto command_line::port() const -> std::uint16_t {
    return m_result["port"].as<std::uint16_t>();
}

auto command_line::jobs() const -> std::size_t {
    return m_result["jobs"].as<std::size_t>();
}
} // namespace phansar::common
