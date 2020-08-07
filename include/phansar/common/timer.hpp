#ifndef PHANSAR_COMMON_TIMER_HPP
#define PHANSAR_COMMON_TIMER_HPP

#include <chrono>

namespace phansar::common {
template <class Clock = std::chrono::steady_clock>
class timer {
public:
    void start();
    void stop();
    template <class T = double, class Duration = std::chrono::nanoseconds>
    [[nodiscard]] auto get_elapsed_time() const -> T;

private:
    std::chrono::time_point<Clock> _start_time, _end_time;
    bool                           _running = false;
};
} // namespace phansar::common

#include <phansar/common/detail/timer.tpp>

#endif
