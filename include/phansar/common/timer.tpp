#include <phansar/common/timer.hpp>

namespace phansar::common {
template <class T, class Duration>
auto timer::elapsed_time() const -> T {
    return static_cast<T>(
        std::chrono::duration_cast<Duration>(
            (m_running ? std::chrono::steady_clock::now() : m_end_time) - m_start_time)
            .count());
}
} // namespace phansar::common
