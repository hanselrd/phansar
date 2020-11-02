#include <phansar/common/log.hpp>

#include <functional>

namespace phansar::common {
template <class... Args>
void log::print(level            _level,
                std::string_view _source_file,
                int              _source_line,
                std::string_view _format,
                Args &&... _args) {
    vprint(_level,
           _source_file,
           _source_line,
           _format,
           fmt::make_format_args(std::forward<Args>(_args)...));
}
} // namespace phansar::common
