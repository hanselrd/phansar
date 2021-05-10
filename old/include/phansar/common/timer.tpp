#include <phansar/common/timer.hpp>

namespace phansar::common {
template <class T, class Duration>
auto timer::elapsed_time() const -> T {
    return static_cast<T>(std::chrono::duration_cast<Duration>(_elapsed_time_internal()).count());
}
} // namespace phansar::common
