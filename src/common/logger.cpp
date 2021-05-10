#include <phansar/common/logger.hpp>

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
        (void)_msg;
        (void)_tm_time;

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

logger::logger(const logger &) = default;

auto logger::operator=(const logger &) -> logger & = default;

logger::logger(logger &&) noexcept = default;

auto logger::operator=(logger &&) noexcept -> logger & = default;

logger::~logger() = default;

auto logger::log() const -> std::shared_ptr<spdlog::logger> {
    return m_impl->logger;
}
} // namespace phansar::common
