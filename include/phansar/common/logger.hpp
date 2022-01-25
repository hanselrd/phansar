#ifndef PHANSAR_COMMON_LOGGER_HPP
#define PHANSAR_COMMON_LOGGER_HPP

#include <phansar/common/policy/static_storage_policy.hpp>
#include <phansar/common/utility/pimpl.hpp>
#include <rttr/type>
#include <spdlog/spdlog.h>
#include <version>

#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
        #include <source_location>
        #if defined(__clang__)
            #warning                                                                               \
                "clang supports source_location now so we can rid of all the preprocessor magic"
        #endif
    #endif
#endif

namespace phansar::common {
class logger {
public:
    logger(std::string_view _name, std::string_view _path, std::size_t _size, std::size_t _count);
    logger(const logger & _other);
    auto operator=(const logger & _other) -> logger &;
    logger(logger && _other) noexcept;
    auto operator=(logger && _other) noexcept -> logger &;
    virtual ~logger();

#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
    void smart_log(spdlog::level::level_enum _level,
                   std::string_view          _message,
                   std::source_location      _location = std::source_location::current());
    #endif
#endif
    void
    log(spdlog::level::level_enum _level, std::string_view _message, spdlog::source_loc _location);

private:
    struct impl;
    utility::pimpl<impl, policy::static_storage_policy<impl, 48, 8>> m_impl;

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE()
};
} // namespace phansar::common

#endif
