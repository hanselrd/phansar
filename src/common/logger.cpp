#include <phansar/common/logger.hpp>
#include <phansar/common/macro.hpp>
#include <phansar/common/policy/freestanding_implementation_policy.hpp>
#include <phansar/common/reflect/debug_visitor.hpp>
#include <phansar/common/reflect/pybind_visitor.hpp>
#include <phansar/common/synchronized.hpp>
#include <rttr/registration>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <unordered_map>

namespace {
using namespace phansar::common;

class flag_formatter : public spdlog::custom_flag_formatter {
public:
    void format(const spdlog::details::log_msg & _msg,
                const std::tm &                  _tm_time,
                spdlog::memory_buf_t &           _dest) override {
        PH_UNUSED_FREESTANDING(_msg);
        PH_UNUSED_FREESTANDING(_tm_time);

        if (! s_thread_name_map.lock_shared()->contains(std::this_thread::get_id())) {
            auto write_lock = s_thread_name_map.lock();
            if (write_lock->empty()) {
                write_lock->insert_or_assign(std::this_thread::get_id(),
                                             fmt::format("{:{}}", "MAIN", padinfo_.width_));
            } else {
                write_lock->insert_or_assign(std::this_thread::get_id(),
                                             fmt::format("WORKER{:0{}}",
                                                         write_lock->size(),
                                                         padinfo_.width_ - std::strlen("WORKER")));
            }
        }

        auto thread_name = s_thread_name_map.lock_shared()->at(std::this_thread::get_id());
        _dest.append(thread_name.data(), thread_name.data() + thread_name.size());
    }

    [[nodiscard]] auto clone() const -> std::unique_ptr<spdlog::custom_flag_formatter> override {
        return std::make_unique<flag_formatter>();
    }

private:
    static synchronized<std::unordered_map<std::thread::id, std::string>,
                        policy::freestanding_implementation_policy<
                            std::unordered_map<std::thread::id, std::string>>>
        s_thread_name_map;
};

decltype(flag_formatter::s_thread_name_map) flag_formatter::s_thread_name_map{};
} // namespace

namespace phansar::common {
struct logger::impl {
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>  stdout_color_sink;
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> rotating_file_sink;
    std::shared_ptr<spdlog::logger>                       logger;
};

logger::logger(std::string_view _name,
               std::string_view _path,
               std::size_t      _size,
               std::size_t      _count) {
    m_impl->stdout_color_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    m_impl->rotating_file_sink =
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(std::string{_path}, _size, _count);
    m_impl->logger = std::make_shared<spdlog::logger>(
        std::string{_name},
        spdlog::sinks_init_list{m_impl->stdout_color_sink, m_impl->rotating_file_sink});
    m_impl->logger->set_level(spdlog::level::trace);
    auto formatter = std::make_unique<spdlog::pattern_formatter>(spdlog::pattern_time_type::utc);
    formatter->add_flag<flag_formatter>('t').set_pattern(
        "%Y-%m-%d %H:%M:%S.%F %z [%n/%-8t] %25s:%-5# %^%8l%$| %v");
    m_impl->logger->set_formatter(std::move(formatter));
}

logger::logger(const logger & _other) = default;

auto logger::operator=(const logger & _other) -> logger & = default;

logger::logger(logger && _other) noexcept = default;

auto logger::operator=(logger && _other) noexcept -> logger & = default;

logger::~logger() = default;

#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
void logger::smart_log(spdlog::level::level_enum _level,
                       std::string_view          _message,
                       std::source_location      _location) {
    m_impl->logger->log(spdlog::source_loc{_location.file_name(),
                                           static_cast<int>(_location.line()),
                                           _location.function_name()},
                        _level,
                        _message);
}
    #endif
#endif

void logger::log(spdlog::level::level_enum _level,
                 std::string_view          _message,
                 const spdlog::source_loc  _location) {
    m_impl->logger->log(_location, _level, _message);
}

RTTR_REGISTRATION {
    rttr::registration::class_<logger>("logger")
        .constructor<std::string_view, std::string_view, std::size_t, std::size_t>()
#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
        .method("smart_log", &logger::smart_log)
    #endif
#endif
        .method("log", &logger::log)
        .method("trace",
                [](logger & _obj, std::string_view _message) {
                    _obj.log(spdlog::level::trace, _message, spdlog::source_loc{"<none>", 1, ""});
                })
        .method("debug",
                [](logger & _obj, std::string_view _message) {
                    _obj.log(spdlog::level::debug, _message, spdlog::source_loc{"<none>", 1, ""});
                })
        .method("info",
                [](logger & _obj, std::string_view _message) {
                    _obj.log(spdlog::level::info, _message, spdlog::source_loc{"<none>", 1, ""});
                })
        .method("warning",
                [](logger & _obj, std::string_view _message) {
                    _obj.log(spdlog::level::warn, _message, spdlog::source_loc{"<none>", 1, ""});
                })
        .method("error",
                [](logger & _obj, std::string_view _message) {
                    _obj.log(spdlog::level::err, _message, spdlog::source_loc{"<none>", 1, ""});
                })
        .method("critical", [](logger & _obj, std::string_view _message) {
            _obj.log(spdlog::level::critical, _message, spdlog::source_loc{"<none>", 1, ""});
        });
}
} // namespace phansar::common
