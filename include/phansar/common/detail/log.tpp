#include <phansar/common/log.hpp>

#include <functional>

namespace phansar::common::log {
namespace detail {
template <class... Args>
void print(std::string_view file, int line, level level, std::string_view format, Args &&... args) {
    vprint(file, line, level, format, fmt::make_format_args(std::forward<Args>(args)...));
}
} // namespace detail
} // namespace phansar::common::log
