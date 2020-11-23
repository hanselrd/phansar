#ifndef PHANSAR_COMMON_LOG_HPP
#define PHANSAR_COMMON_LOG_HPP

#include <phansar/common/utility/singleton.hpp>

namespace phansar::common {
class log : public utility::singleton<log> {
public:
    enum class level { trace, debug, info, warning, error, critical, off };

    log(level            _level,
        std::string_view _name,
        std::string_view _file_path,
        std::uintmax_t   _file_size,
        std::size_t      _num_files);

    void set_thread_name(std::thread::id _thread_id, std::string_view _thread_name);
    void vprint(level            _level,
                std::string_view _source_file,
                int              _source_line,
                std::string_view _format,
                fmt::format_args _args);
    template <class... Args>
    void print(level            _level,
               std::string_view _source_file,
               int              _source_line,
               std::string_view _format,
               Args &&... _args);

private:
    level                                              m_level;
    std::string                                        m_name;
    std::string                                        m_file_path;
    std::uintmax_t                                     m_file_size;
    std::size_t                                        m_num_files;
    std::ofstream                                      m_out_file;
    std::chrono::time_point<std::chrono::system_clock> m_start_time;
    std::unordered_map<std::thread::id, std::string>   m_thread_name_map;
    std::shared_mutex                                  m_thread_name_map_mutex;
    std::mutex                                         m_print_mutex;
};
} // namespace phansar::common

#include <phansar/common/log.tpp>

#endif
