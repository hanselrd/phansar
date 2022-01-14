#ifndef PHANSAR_COMMON_LOGGER_HPP
#define PHANSAR_COMMON_LOGGER_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <phansar/common/utility/rule_of_n.hpp>

#include <rttr/type>
#include <spdlog/spdlog.h>

namespace phansar::common {
class logger {
public:
    logger(std::string_view _name, std::string_view _path, std::size_t _size, std::size_t _count);
    PH_RULE_OF_5(logger);

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

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE()
};
} // namespace phansar::common

#endif
