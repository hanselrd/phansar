#ifndef PHANSAR_COMMON_TIMER_HPP
#define PHANSAR_COMMON_TIMER_HPP

namespace phansar::common {
class timer {
public:
    void start();
    void stop();
    void restart();
    template <class T = double, class Duration = std::chrono::nanoseconds>
    auto elapsed_time() const -> T;

private:
    std::chrono::time_point<std::chrono::steady_clock> m_start_time, m_end_time;
    bool                                               m_running = false;
};
} // namespace phansar::common

#include <phansar/common/timer.tpp>

#endif
