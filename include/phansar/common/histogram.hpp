#ifndef PHANSAR_COMMON_HISTOGRAM_HPP
#define PHANSAR_COMMON_HISTOGRAM_HPP

#include <phansar/common/log.hpp>

#include <phansar/vendor/rangev3.hpp>

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <type_traits>

namespace phansar::common {
template <class T>
class histogram {
    static_assert(std::is_arithmetic_v<T>);

public:
    histogram(std::string_view name, std::string_view units, std::size_t num_bins);

    void               push(const T & sample);
    [[nodiscard]] auto get_sample_count() const -> std::uint64_t;
    auto               get_minimum() const -> T;
    auto               get_maximum() const -> T;
    auto               get_range() const -> T;
    [[nodiscard]] auto get_mean() const -> double;
    [[nodiscard]] auto get_variance() const -> double;
    [[nodiscard]] auto get_standard_deviation() const -> double;
    [[nodiscard]] auto get_percentile(double percentile) const -> double;
    void               log() const;

private:
    std::string                _name, _units;
    std::size_t                _num_bins;
    std::map<T, std::uint64_t> _samples;
};
} // namespace phansar::common

#include <phansar/common/detail/histogram.tpp>

#endif
