#ifndef COMMON_CORE_LOG_HPP
#define COMMON_CORE_LOG_HPP

#include "sol.hpp"
#include <plog/Log.h>
#include <string>

#if defined(__FILE__) && defined(__SOURCE_PATH_SIZE__)
#    define __FILENAME__ (__FILE__ + __SOURCE_PATH_SIZE__)
#else
#    define __FILENAME__ "unknown"
#endif

#undef IF_LOG_
#undef IF_LOG

#undef LOG_
#undef LOG

#undef LOG_VERBOSE
#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_ERROR
#undef LOG_FATAL
#undef LOG_NONE

#undef LOG_VERBOSE_
#undef LOG_DEBUG_
#undef LOG_INFO_
#undef LOG_WARNING_
#undef LOG_ERROR_
#undef LOG_FATAL_
#undef LOG_NONE_

#undef LOGV
#undef LOGD
#undef LOGI
#undef LOGW
#undef LOGE
#undef LOGF
#undef LOGN

#undef LOGV_
#undef LOGD_
#undef LOGI_
#undef LOGW_
#undef LOGE_
#undef LOGF_
#undef LOGN_

#undef LOG_IF_
#undef LOG_IF

#undef LOG_VERBOSE_IF
#undef LOG_DEBUG_IF
#undef LOG_INFO_IF
#undef LOG_WARNING_IF
#undef LOG_ERROR_IF
#undef LOG_FATAL_IF
#undef LOG_NONE_IF

#undef LOG_VERBOSE_IF_
#undef LOG_DEBUG_IF_
#undef LOG_INFO_IF_
#undef LOG_WARNING_IF_
#undef LOG_ERROR_IF_
#undef LOG_FATAL_IF_
#undef LOG_NONE_IF_

#undef LOGV_IF
#undef LOGD_IF
#undef LOGI_IF
#undef LOGW_IF
#undef LOGE_IF
#undef LOGF_IF
#undef LOGN_IF

#undef LOGV_IF_
#undef LOGD_IF_
#undef LOGI_IF_
#undef LOGW_IF_
#undef LOGE_IF_
#undef LOGF_IF_
#undef LOGN_IF_

#define IF_LOG_(instance, severity)                                                                \
    if (!plog::get<instance>() || !plog::get<instance>()->checkSeverity(severity)) {               \
        ;                                                                                          \
    } else
#define IF_LOG(severity) IF_LOG_(PLOG_DEFAULT_INSTANCE, severity)

#define LOG_(instance, severity)                                                                   \
    IF_LOG_(instance, severity)                                                                    \
    (*plog::get<instance>()) +=                                                                    \
        plog::Record(severity, __FILENAME__, __LINE__, PLOG_GET_FILE(), PLOG_GET_THIS()).ref()
#define LOG(severity) LOG_(PLOG_DEFAULT_INSTANCE, severity)

#define LOG_VERBOSE LOG(plog::verbose)
#define LOG_DEBUG LOG(plog::debug)
#define LOG_INFO LOG(plog::info)
#define LOG_WARNING LOG(plog::warning)
#define LOG_ERROR LOG(plog::error)
#define LOG_FATAL LOG(plog::fatal)
#define LOG_NONE LOG(plog::none)

#define LOG_VERBOSE_(instance) LOG_(instance, plog::verbose)
#define LOG_DEBUG_(instance) LOG_(instance, plog::debug)
#define LOG_INFO_(instance) LOG_(instance, plog::info)
#define LOG_WARNING_(instance) LOG_(instance, plog::warning)
#define LOG_ERROR_(instance) LOG_(instance, plog::error)
#define LOG_FATAL_(instance) LOG_(instance, plog::fatal)
#define LOG_NONE_(instance) LOG_(instance, plog::none)

#define LOGV LOG_VERBOSE
#define LOGD LOG_DEBUG
#define LOGI LOG_INFO
#define LOGW LOG_WARNING
#define LOGE LOG_ERROR
#define LOGF LOG_FATAL
#define LOGN LOG_NONE

#define LOGV_(instance) LOG_VERBOSE_(instance)
#define LOGD_(instance) LOG_DEBUG_(instance)
#define LOGI_(instance) LOG_INFO_(instance)
#define LOGW_(instance) LOG_WARNING_(instance)
#define LOGE_(instance) LOG_ERROR_(instance)
#define LOGF_(instance) LOG_FATAL_(instance)
#define LOGN_(instance) LOG_NONE_(instance)

#define LOG_IF_(instance, severity, condition)                                                     \
    if (!(condition)) {                                                                            \
        ;                                                                                          \
    } else                                                                                         \
        LOG_(instance, severity)
#define LOG_IF(severity, condition) LOG_IF_(PLOG_DEFAULT_INSTANCE, severity, condition)

#define LOG_VERBOSE_IF(condition) LOG_IF(plog::verbose, condition)
#define LOG_DEBUG_IF(condition) LOG_IF(plog::debug, condition)
#define LOG_INFO_IF(condition) LOG_IF(plog::info, condition)
#define LOG_WARNING_IF(condition) LOG_IF(plog::warning, condition)
#define LOG_ERROR_IF(condition) LOG_IF(plog::error, condition)
#define LOG_FATAL_IF(condition) LOG_IF(plog::fatal, condition)
#define LOG_NONE_IF(condition) LOG_IF(plog::none, condition)

#define LOG_VERBOSE_IF_(instance, condition) LOG_IF_(instance, plog::verbose, condition)
#define LOG_DEBUG_IF_(instance, condition) LOG_IF_(instance, plog::debug, condition)
#define LOG_INFO_IF_(instance, condition) LOG_IF_(instance, plog::info, condition)
#define LOG_WARNING_IF_(instance, condition) LOG_IF_(instance, plog::warning, condition)
#define LOG_ERROR_IF_(instance, condition) LOG_IF_(instance, plog::error, condition)
#define LOG_FATAL_IF_(instance, condition) LOG_IF_(instance, plog::fatal, condition)
#define LOG_NONE_IF_(instance, condition) LOG_IF_(instance, plog::none, condition)

#define LOGV_IF(condition) LOG_VERBOSE_IF(condition)
#define LOGD_IF(condition) LOG_DEBUG_IF(condition)
#define LOGI_IF(condition) LOG_INFO_IF(condition)
#define LOGW_IF(condition) LOG_WARNING_IF(condition)
#define LOGE_IF(condition) LOG_ERROR_IF(condition)
#define LOGF_IF(condition) LOG_FATAL_IF(condition)
#define LOGN_IF(condition) LOG_NONE_IF(condition)

#define LOGV_IF_(instance, condition) LOG_VERBOSE_IF_(instance, condition)
#define LOGD_IF_(instance, condition) LOG_DEBUG_IF_(instance, condition)
#define LOGI_IF_(instance, condition) LOG_INFO_IF_(instance, condition)
#define LOGW_IF_(instance, condition) LOG_WARNING_IF_(instance, condition)
#define LOGE_IF_(instance, condition) LOG_ERROR_IF_(instance, condition)
#define LOGF_IF_(instance, condition) LOG_FATAL_IF_(instance, condition)
#define LOGN_IF_(instance, condition) LOG_NONE_IF_(instance, condition)

namespace common {
namespace core {
namespace log {
void init(const std::string &filename);

namespace lua_api {
void init(sol::table &t);
}
} // namespace log
} // namespace core
} // namespace common

#endif
