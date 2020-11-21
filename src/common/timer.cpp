#include <phansar/common/timer.hpp>

namespace phansar::common {
void timer::start() {
    if (! m_running) {
        m_start_time = std::chrono::steady_clock::now();
        m_running    = true;
    }
}

void timer::stop() {
    if (m_running) {
        m_end_time = std::chrono::steady_clock::now();
        m_running  = false;
    }
}

void timer::restart() {
    stop();
    start();
}
} // namespace phansar::common
