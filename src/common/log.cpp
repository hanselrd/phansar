#include <phansar/common/log.hpp>
#include <phansar/vendor/rangev3.hpp>

#include <filesystem>
#include <fstream>
#include <shared_mutex>
#include <unordered_map>

namespace phansar::common {
struct log::impl {
    level                                              level;
    std::string                                        name;
    std::string                                        file_path;
    std::uintmax_t                                     file_size;
    std::size_t                                        num_files;
    std::ofstream                                      out_file;
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::unordered_map<std::thread::id, std::string>   thread_name_map;
    std::unique_ptr<std::shared_mutex>                 thread_name_map_mutex;
    std::unique_ptr<std::mutex>                        print_mutex;
};

log::log(level            _level,
         std::string_view _name,
         std::string_view _file_path,
         std::uintmax_t   _file_size,
         std::size_t      _num_files)
    : m_impl{_level,
             std::string{_name},
             std::string{_file_path},
             _file_size,
             _num_files,
             std::ofstream{std::string{_file_path}, std::ofstream::out | std::ofstream::app},
             std::chrono::system_clock::now(),
             std::unordered_map<std::thread::id, std::string>{},
             std::make_unique<std::shared_mutex>(),
             std::make_unique<std::mutex>()} {
    set_thread_name(std::this_thread::get_id(), "MAIN");
}

log::~log() = default;

void log::set_thread_name(std::thread::id _thread_id, std::string_view _thread_name) {
    auto lock = std::unique_lock{*m_impl->thread_name_map_mutex};
    m_impl->thread_name_map.insert_or_assign(_thread_id, _thread_name);
}

void log::vprint(level            _level,
                 std::string_view _source_file,
                 int              _source_line,
                 std::string_view _format,
                 fmt::format_args _args) {
    if (m_impl->level == level::off || m_impl->level > _level) {
        return;
    }

    static const auto style_map =
        std::unordered_map<log::level, std::pair<std::string, fmt::text_style>>{
            {log::level::trace, {"TRACE", fmt::fg(fmt::color::gray)}},
            {log::level::debug, {"DEBUG", fmt::fg(fmt::color::cadet_blue)}},
            {log::level::info, {"INFO", fmt::fg(fmt::color::sea_green)}},
            {log::level::warning, {"WARNING", fmt::fg(fmt::color::gold)}},
            {log::level::error, {"ERROR", fmt::fg(fmt::color::coral)}},
            {log::level::critical,
             {"CRITICAL", fmt::fg(fmt::color::black) | fmt::bg(fmt::color::coral)}}};
    static const auto format =
        std::string{"{:%Y-%m-%d %H:%M:%S %z} ({:>9.3f}s) [{}/{:<10}] {:>25}:{:<5} {:>8}| {}\n"};

    auto base_name = (std::strrchr(_source_file.data(), '/') != nullptr) // TODO: don't use .data()
                         ? std::string_view{std::strrchr(_source_file.data(), '/') + 1}
                         : _source_file;
    auto message   = fmt::vformat(_format, _args);
    const auto & [level_str, text_style] = style_map.at(_level);

    auto thread_name = std::string{};
    {
        auto read_lock = std::shared_lock{*m_impl->thread_name_map_mutex};
        if (m_impl->thread_name_map.count(std::this_thread::get_id()) == 0) {
            read_lock.unlock();
            {
                auto write_lock = std::unique_lock{*m_impl->thread_name_map_mutex};
                m_impl->thread_name_map.insert_or_assign(
                    std::this_thread::get_id(),
                    fmt::format("WORKER{}", m_impl->thread_name_map.size()));
            }
            read_lock.lock();
        }
        thread_name = m_impl->thread_name_map.at(std::this_thread::get_id());
    }

    {
        auto lock      = std::unique_lock{*m_impl->print_mutex};
        auto now       = std::chrono::system_clock::now();
        auto now_tm    = std::chrono::system_clock::to_time_t(now);
        auto time_info = *std::localtime(&now_tm);
        auto uptime    = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                              now - m_impl->start_time)
                                              .count()) /
                      1000.;

        for (const auto & m :
             message | ranges::views::split('\n') | ranges::to<std::vector<std::string>>()) {
            fmt::print(format,
                       time_info,
                       uptime,
                       m_impl->name,
                       thread_name,
                       base_name,
                       _source_line,
                       fmt::format(text_style, "{:>8}", level_str),
                       m);
            fmt::print(m_impl->out_file,
                       format,
                       time_info,
                       uptime,
                       m_impl->name,
                       thread_name,
                       base_name,
                       _source_line,
                       level_str,
                       m);
        }

        if (m_impl->num_files > 0) {
            auto ec = std::error_code{};
            if (std::filesystem::file_size(m_impl->file_path, ec) > m_impl->file_size) {
                for (auto i = m_impl->num_files; i > 1; --i) {
                    if (std::filesystem::exists(fmt::format("{}.{}", m_impl->file_path, i - 1),
                                                ec)) {
                        std::filesystem::rename(fmt::format("{}.{}", m_impl->file_path, i - 1),
                                                fmt::format("{}.{}", m_impl->file_path, i),
                                                ec);
                    }
                }
                m_impl->out_file.close();
                std::filesystem::rename(m_impl->file_path,
                                        fmt::format("{}.1", m_impl->file_path),
                                        ec);
                m_impl->out_file.open(m_impl->file_path, std::ofstream::out);
            }
        }
    }
}
} // namespace phansar::common
