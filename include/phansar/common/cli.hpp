#ifndef PHANSAR_COMMON_CLI_HPP
#define PHANSAR_COMMON_CLI_HPP

#include <phansar/common/log.hpp>
#include <phansar/common/utility/singleton.hpp>

namespace phansar::common {
class cli : public utility::singleton<cli> {
public:
    cli(int _argc, const char * const * _argv);

    [[nodiscard]] auto binary_name() const -> std::string;
    [[nodiscard]] auto log_level() const -> log::level;
    [[nodiscard]] auto log_file_path() const -> std::string;
    [[nodiscard]] auto host() const -> std::string;
    [[nodiscard]] auto port() const -> std::uint16_t;
    [[nodiscard]] auto num_threads() const -> std::size_t;

private:
    std::map<std::string, docopt::value> m_docopt_map;
};
} // namespace phansar::common

#endif
