#ifndef PHANSAR_COMMON_LOGGER_HPP
#define PHANSAR_COMMON_LOGGER_HPP

#include <phansar/codegen/macros.hpp>
#include <phansar/common/utility/pimpl.hpp>

#include <spdlog/spdlog.h>

namespace phansar::common {
class PH_ANNOTATE() logger {
public:
    logger(std::string_view _name, std::string_view _path, std::size_t _size, std::size_t _count);
    logger(const logger & /*unused*/);
    auto operator=(const logger & /*unused*/) -> logger &;
    logger(logger && /*unused*/) noexcept;
    auto operator=(logger && /*unused*/) noexcept -> logger &;
    ~logger();

    [[nodiscard]] auto handle() const -> std::shared_ptr<spdlog::logger>;
    void               trace(std::string_view _msg);
    void               debug(std::string_view _msg);
    void               info(std::string_view _msg);
    void               warn(std::string_view _msg);
    void               error(std::string_view _msg);
    void               critical(std::string_view _msg);

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common

#endif
