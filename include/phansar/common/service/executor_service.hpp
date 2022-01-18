#ifndef PHANSAR_COMMON_SERVICE_EXECUTOR_SERVICE_HPP
#define PHANSAR_COMMON_SERVICE_EXECUTOR_SERVICE_HPP

#include <kangaru/kangaru.hpp>
#include <taskflow/taskflow.hpp>

namespace phansar::common::service {
struct executor_service : kgr::single_service<tf::Executor>, kgr::supplied {};
} // namespace phansar::common::service

#endif
