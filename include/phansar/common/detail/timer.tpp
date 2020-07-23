#include <phansar/common/timer.hpp>

namespace phansar::common {
template <class Clock>
void timer<Clock>::start() {
    if (! _running) {
        _start_time = Clock::now();
        _running    = true;
    }
}

template <class Clock>
void timer<Clock>::stop() {
    if (_running) {
        _end_time = Clock::now();
        _running  = false;
    }
}

template <class Clock>
template <class Rep, class Period>
auto timer<Clock>::get_elapsed_time() const -> Rep {
    return std::chrono::duration<Rep, Period>{((_running) ? Clock::now() : _end_time) - _start_time}
        .count();
}
} // namespace phansar::common
