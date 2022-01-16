#ifndef PHANSAR_COMMON_LOGGER_HPP
#define PHANSAR_COMMON_LOGGER_HPP

#include <phansar/common/policy/static_storage_policy.hpp>
#include <phansar/common/utility/pimpl.hpp>
#include <phansar/common/utility/rule_of_n.hpp>
#include <kangaru/kangaru.hpp>
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
    PH_RULE_OF_5(logger);

    [[nodiscard]] auto handle() const -> std::shared_ptr<spdlog::logger>;
#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
    void trace(std::string_view     _message,
               std::source_location _location = std::source_location::current());
    void debug(std::string_view     _message,
               std::source_location _location = std::source_location::current());
    void info(std::string_view     _message,
              std::source_location _location = std::source_location::current());
    void warning(std::string_view     _message,
                 std::source_location _location = std::source_location::current());
    void error(std::string_view     _message,
               std::source_location _location = std::source_location::current());
    void critical(std::string_view     _message,
                  std::source_location _location = std::source_location::current());
    #else
    void trace(std::string_view _message, spdlog::source_loc _location);
    void debug(std::string_view _message, spdlog::source_loc _location);
    void info(std::string_view _message, spdlog::source_loc _location);
    void warning(std::string_view _message, spdlog::source_loc _location);
    void error(std::string_view _message, spdlog::source_loc _location);
    void critical(std::string_view _message, spdlog::source_loc _location);
    #endif
#endif

private:
    struct impl;
    utility::pimpl<impl, policy::static_storage_policy<impl, 48, 8>> m_impl;

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE()
};

struct logger_service : kgr::single_service<logger>, kgr::supplied {};
} // namespace phansar::common

#endif
