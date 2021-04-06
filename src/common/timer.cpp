#include <phansar/common/timer.hpp>

namespace phansar::common {
struct timer::impl {
    std::chrono::time_point<std::chrono::steady_clock> start_time, end_time;
    bool                                               running{};
};

timer::timer()
    : m_impl{std::chrono::time_point<std::chrono::steady_clock>{},
             std::chrono::time_point<std::chrono::steady_clock>{},
             false} {}

timer::~timer() = default;

void timer::start() {
    if (! m_impl->running) {
        m_impl->start_time = std::chrono::steady_clock::now();
        m_impl->running    = true;
    }
}

void timer::stop() {
    if (m_impl->running) {
        m_impl->end_time = std::chrono::steady_clock::now();
        m_impl->running  = false;
    }
}

void timer::restart() {
    stop();
    start();
}

auto timer::_elapsed_time_internal() const -> std::chrono::steady_clock::duration {
    return (m_impl->running ? std::chrono::steady_clock::now() : m_impl->end_time) -
           m_impl->start_time;
}
} // namespace phansar::common
