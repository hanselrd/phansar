#ifndef PHANSAR_COMMON_COMMAND_LINE_HPP
#define PHANSAR_COMMON_COMMAND_LINE_HPP

#include <phansar/common/log.hpp>
#include <phansar/common/utility/singleton.hpp>

namespace phansar::common {
class command_line : public utility::singleton<command_line> {
public:
    command_line(int _argc, const char * const * _argv);

    [[nodiscard]] auto program_name() const -> std::string;
    [[nodiscard]] auto log_level() const -> log::level;
    [[nodiscard]] auto log_file() const -> std::string;
    [[nodiscard]] auto host() const -> std::string;
    [[nodiscard]] auto port() const -> std::uint16_t;
    [[nodiscard]] auto jobs() const -> std::size_t;

private:
    std::string          m_program_name;
    cxxopts::Options     m_options;
    cxxopts::ParseResult m_result;
};
} // namespace phansar::common

#endif
