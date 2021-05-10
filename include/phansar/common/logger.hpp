#ifndef PHANSAR_COMMON_LOGGER_HPP
#define PHANSAR_COMMON_LOGGER_HPP

#include <phansar/common/utility/pimpl.hpp>

#include <spdlog/spdlog.h>

namespace phansar::common {
class logger {
public:
    logger(std::string_view _name, std::string_view _path, std::size_t _size, std::size_t _count);
    logger(const logger & /*unused*/);
    auto operator=(const logger & /*unused*/) -> logger &;
    logger(logger && /*unused*/) noexcept;
    auto operator=(logger && /*unused*/) noexcept -> logger &;
    ~logger();

    [[nodiscard]] auto log() const -> std::shared_ptr<spdlog::logger>;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common

#endif
