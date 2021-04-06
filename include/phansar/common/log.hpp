#ifndef PHANSAR_COMMON_LOG_HPP
#define PHANSAR_COMMON_LOG_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <phansar/common/utility/singleton.hpp>
#include <phansar/vendor/fmt.hpp>

namespace phansar::common {
class log : public utility::singleton<log> { // TODO: replace with spdlog
public:
    enum class level { trace, debug, info, warning, error, critical, off };

    log(level            _level,
        std::string_view _name,
        std::string_view _file_path,
        std::uintmax_t   _file_size,
        std::size_t      _num_files);
    log(const log &) = default;
    auto operator=(const log &) -> log & = default;
    log(log &&)                          = default;
    auto operator=(log &&) -> log & = default;
    ~log();

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
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common

#include <phansar/common/log.tpp>

#endif
