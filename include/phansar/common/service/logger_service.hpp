#ifndef PHANSAR_COMMON_SERVICE_LOGGER_SERVICE_HPP
#define PHANSAR_COMMON_SERVICE_LOGGER_SERVICE_HPP

#include <phansar/common/logger.hpp>
#include <kangaru/kangaru.hpp>

namespace phansar::common::service {
struct logger_service
    : kgr::single_service<logger>
    , kgr::supplied {};
} // namespace phansar::common::service

#endif
