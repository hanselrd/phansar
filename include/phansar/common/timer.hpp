#ifndef PHANSAR_COMMON_TIMER_HPP
#define PHANSAR_COMMON_TIMER_HPP

#include <phansar/common/utility/pimpl.hpp>

#include <chrono>

namespace phansar::common {
class timer {
public:
    timer();
    timer(const timer &) = default;
    auto operator=(const timer &) -> timer & = default;
    timer(timer &&)                          = default;
    auto operator=(timer &&) -> timer & = default;
    ~timer();

    void start();
    void stop();
    void restart();
    template <class T = double, class Duration = std::chrono::nanoseconds>
    auto elapsed_time() const -> T;

private:
    [[nodiscard]] auto _elapsed_time_internal() const -> std::chrono::steady_clock::duration;

    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common

#include <phansar/common/timer.tpp>

#endif
