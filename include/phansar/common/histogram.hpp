#ifndef PHANSAR_COMMON_HISTOGRAM_HPP
#define PHANSAR_COMMON_HISTOGRAM_HPP

#include <phansar/common/containers.hpp>
#include <phansar/common/log.hpp>

#include <phansar/vendor/rangev3.hpp>

#include <cstdint>
#include <type_traits>

#define LOG_HISTOGRAM(hist, name, units, num_bins)                                                 \
    do {                                                                                           \
        LOGI("Histogram:");                                                                        \
        LOGI("  name: {}", name);                                                                  \
        LOGI("  units: {}", units);                                                                \
        LOGI("  sample count: {}", (hist).get_sample_count());                                     \
        LOGI("  minimum: {}", (hist).get_minimum());                                               \
        LOGI("  maximum: {}", (hist).get_maximum());                                               \
        LOGI("  range: {}", (hist).get_range());                                                   \
        LOGI("  mean: {}", (hist).get_mean());                                                     \
        LOGI("  variance: {}", (hist).get_variance());                                             \
        LOGI("  standard deviation: {}", (hist).get_standard_deviation());                         \
        LOGI("  percentiles:");                                                                    \
        LOGI("    00.01: {}", (hist).get_percentile(.01));                                         \
        LOGI("    00.10: {}", (hist).get_percentile(.1));                                          \
        LOGI("    01.00: {}", (hist).get_percentile(1.));                                          \
        LOGI("    05.00: {}", (hist).get_percentile(5.));                                          \
        LOGI("    10.00: {}", (hist).get_percentile(10.));                                         \
        LOGI("    25.00: {}", (hist).get_percentile(25.));                                         \
        LOGI("    50.00: {}", (hist).get_percentile(50.));                                         \
        LOGI("    75.00: {}", (hist).get_percentile(75.));                                         \
        LOGI("    90.00: {}", (hist).get_percentile(90.));                                         \
        LOGI("    95.00: {}", (hist).get_percentile(95.));                                         \
        LOGI("    99.00: {}", (hist).get_percentile(99.));                                         \
        LOGI("    99.90: {}", (hist).get_percentile(99.9));                                        \
        LOGI("    99.99: {}", (hist).get_percentile(99.99));                                       \
        LOGI("  bins:");                                                                           \
        auto bins_width = (hist).get_bin_width(num_bins);                                          \
        auto bins       = (hist).get_bins(num_bins);                                               \
        for (const auto & [first, second] : bins | ranges::views::enumerate) {                     \
            LOGI("    [{}, {}): {}",                                                               \
                 (hist).get_minimum() + static_cast<double>(first) * bins_width,                   \
                 (hist).get_minimum() + static_cast<double>(first) * bins_width + bins_width,      \
                 second);                                                                          \
        }                                                                                          \
    } while (0)

namespace phansar::common {
template <class T>
class histogram {
    static_assert(std::is_arithmetic_v<T>);

public:
    void               push(const T & sample);
    [[nodiscard]] auto get_sample_count() const -> std::uint64_t;
    auto               get_minimum() const -> T;
    auto               get_maximum() const -> T;
    auto               get_range() const -> T;
    [[nodiscard]] auto get_mean() const -> double;
    [[nodiscard]] auto get_variance() const -> double;
    [[nodiscard]] auto get_standard_deviation() const -> double;
    [[nodiscard]] auto get_percentile(double percentile) const -> double;
    [[nodiscard]] auto get_bin_width(std::size_t num_bins) const -> double;
    [[nodiscard]] auto get_bins(std::size_t num_bins) const
        -> containers::stdlib::vector<std::uint64_t>;

private:
    containers::stdlib::vector<T> _samples;
};
} // namespace phansar::common

#include <phansar/common/detail/histogram.tpp>

#endif
