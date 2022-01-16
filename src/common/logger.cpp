#include <phansar/common/logger.hpp>
#include <phansar/common/macro.hpp>
#include <phansar/common/reflect/debug_visitor.hpp>
#include <phansar/common/reflect/pybind_visitor.hpp>
#include <rttr/registration>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

namespace {
class flag_formatter : public spdlog::custom_flag_formatter {
public:
    void format(const spdlog::details::log_msg & _msg,
                const std::tm &                  _tm_time,
                spdlog::memory_buf_t &           _dest) override {
        PH_UNUSED_FREESTANDING(_msg);
        PH_UNUSED_FREESTANDING(_tm_time);

        auto read_lock = std::shared_lock{s_thread_name_map_mutex};

        if (! s_thread_name_map.contains(std::this_thread::get_id())) {
            read_lock.unlock();
            {
                auto write_lock = std::unique_lock{s_thread_name_map_mutex};
                if (s_thread_name_map.empty()) {
                    s_thread_name_map.insert_or_assign(
                        std::this_thread::get_id(),
                        fmt::format("{:{}}", "MAIN", padinfo_.width_));
                } else {
                    s_thread_name_map.insert_or_assign(
                        std::this_thread::get_id(),
                        fmt::format("WORKER{:0{}}", s_thread_name_map.size(), padinfo_.width_ - 6));
                }
            }
            read_lock.lock();
        }

        auto thread_name = s_thread_name_map.at(std::this_thread::get_id());
        _dest.append(thread_name.data(), thread_name.data() + thread_name.size());
    }

    [[nodiscard]] auto clone() const -> std::unique_ptr<spdlog::custom_flag_formatter> override {
        return std::make_unique<flag_formatter>();
    }

private:
    static std::unordered_map<std::thread::id, std::string> s_thread_name_map;
    static std::shared_mutex                                s_thread_name_map_mutex;
};

std::unordered_map<std::thread::id, std::string> flag_formatter::s_thread_name_map{};
std::shared_mutex                                flag_formatter::s_thread_name_map_mutex{};
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

PH_RULE_OF_5_DEFAULT(logger);

auto logger::handle() const -> std::shared_ptr<spdlog::logger> {
    return m_impl->logger;
}

#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
void logger::trace(std::string_view _message, const std::source_location _location) {
    m_impl->logger->log(spdlog::source_loc{_location.file_name(),
                                           static_cast<int>(_location.line()),
                                           _location.function_name()},
                        spdlog::level::trace,
                        _message);
}

void logger::debug(std::string_view _message, const std::source_location _location) {
    m_impl->logger->log(spdlog::source_loc{_location.file_name(),
                                           static_cast<int>(_location.line()),
                                           _location.function_name()},
                        spdlog::level::debug,
                        _message);
}

void logger::info(std::string_view _message, const std::source_location _location) {
    m_impl->logger->log(spdlog::source_loc{_location.file_name(),
                                           static_cast<int>(_location.line()),
                                           _location.function_name()},
                        spdlog::level::info,
                        _message);
}

void logger::warning(std::string_view _message, const std::source_location _location) {
    m_impl->logger->log(spdlog::source_loc{_location.file_name(),
                                           static_cast<int>(_location.line()),
                                           _location.function_name()},
                        spdlog::level::warn,
                        _message);
}

void logger::error(std::string_view _message, const std::source_location _location) {
    m_impl->logger->log(spdlog::source_loc{_location.file_name(),
                                           static_cast<int>(_location.line()),
                                           _location.function_name()},
                        spdlog::level::err,
                        _message);
}

void logger::critical(std::string_view _message, const std::source_location _location) {
    m_impl->logger->log(spdlog::source_loc{_location.file_name(),
                                           static_cast<int>(_location.line()),
                                           _location.function_name()},
                        spdlog::level::critical,
                        _message);
}
    #else
void logger::trace(std::string_view _message, const spdlog::source_loc _location) {
    // m_impl->logger->log(spdlog::source_loc{"<none>", 1, SPDLOG_FUNCTION},
    //                     spdlog::level::trace,
    //                     _message);
    m_impl->logger->log(_location, spdlog::level::trace, _message);
}

void logger::debug(std::string_view _message, const spdlog::source_loc _location) {
    m_impl->logger->log(_location, spdlog::level::debug, _message);
}

void logger::info(std::string_view _message, const spdlog::source_loc _location) {
    m_impl->logger->log(_location, spdlog::level::info, _message);
}

void logger::warning(std::string_view _message, const spdlog::source_loc _location) {
    m_impl->logger->log(_location, spdlog::level::warn, _message);
}

void logger::error(std::string_view _message, const spdlog::source_loc _location) {
    m_impl->logger->log(_location, spdlog::level::err, _message);
}

void logger::critical(std::string_view _message, const spdlog::source_loc _location) {
    m_impl->logger->log(_location, spdlog::level::critical, _message);
}
    #endif
#endif

/* [[[cog
import rttr
rttr.Rttr.builder() \
    .classes([ \
        rttr.RttrClass.builder() \
            .name("logger") \
            .type("logger") \
            .constructors([ \
                rttr.RttrClass.Constructor.builder() \
                    .args([ \
                        "std::string_view",
                        "std::string_view",
                        "std::size_t",
                        "std::size_t",
                    ]) \
                    .build(), \
            ]) \
            .methods([ \
                rttr.RttrMethod.builder() \
                    .name("handle") \
                    .build(), \
                rttr.RttrMethod.builder() \
                    .name("trace") \
                    .build(), \
                rttr.RttrMethod.builder() \
                    .name("debug") \
                    .build(), \
                rttr.RttrMethod.builder() \
                    .name("info") \
                    .build(), \
                rttr.RttrMethod.builder() \
                    .name("warning") \
                    .build(), \
                rttr.RttrMethod.builder() \
                    .name("error") \
                    .build(), \
                rttr.RttrMethod.builder() \
                    .name("critical") \
                    .build(), \
            ]) \
            .build() \
    ]) \
    .build() \
    .dump()
]]] */
// NOLINTBEGIN
// clang-format off
RTTR_REGISTRATION {
    rttr::registration::class_<logger>("logger")
        .constructor<std::string_view, std::string_view, std::size_t, std::size_t>()
        .method("handle", &logger::handle)
        .method("trace", &logger::trace)
        .method("debug", &logger::debug)
        .method("info", &logger::info)
        .method("warning", &logger::warning)
        .method("error", &logger::error)
        .method("critical", &logger::critical);
}
// clang-format on
// NOLINTEND
/* [[[end]]] */
} // namespace phansar::common
