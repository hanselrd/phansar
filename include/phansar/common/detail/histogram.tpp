#include <phansar/common/histogram.hpp>

#include <phansar/vendor/rangev3.hpp>

#include <cmath>
#include <vector>

namespace phansar::common {
template <class T>
histogram<T>::histogram(std::string_view name, std::string_view units, std::size_t num_bins)
    : _name{name}, _units{units}, _num_bins{num_bins} {}

template <class T>
void histogram<T>::push(const T & sample) {
    ++_samples[sample];
}

template <class T>
auto histogram<T>::get_sample_count() const -> std::uint64_t {
    return ranges::accumulate(_samples, 0, [](auto acc, const auto & s) { return acc + s.second; });
}

template <class T>
auto histogram<T>::get_minimum() const -> T {
    return std::cbegin(_samples)->first;
}

template <class T>
auto histogram<T>::get_maximum() const -> T {
    return std::prev(std::cend(_samples))->first;
}

template <class T>
auto histogram<T>::get_range() const -> T {
    return get_maximum() - get_minimum();
}

template <class T>
auto histogram<T>::get_mean() const -> double {
    return ranges::accumulate(_samples,
                              0.,
                              [](auto acc, const auto & s) {
                                  return acc + (static_cast<double>(s.first) *
                                                static_cast<double>(s.second));
                              }) /
           static_cast<double>(get_sample_count());
}

template <class T>
auto histogram<T>::get_variance() const -> double {
    auto mean = get_mean();
    return ranges::accumulate(_samples,
                              0.,
                              [mean](auto acc, const auto & s) {
                                  return acc + (((static_cast<double>(s.first) - mean) *
                                                 (static_cast<double>(s.first) - mean)) *
                                                static_cast<double>(s.second));
                              }) /
           (static_cast<double>(get_sample_count()) - 1.);
}

template <class T>
auto histogram<T>::get_standard_deviation() const -> double {
    return std::sqrt(get_variance());
}

template <class T>
auto histogram<T>::get_percentile(double percentile) const -> double {
    const auto rank    = (percentile / 100.) * (static_cast<double>(get_sample_count()) - 1.) + 1.;
    auto       sample1 = T{0};
    auto       sample2 = T{0};

    auto i = std::uint64_t{static_cast<std::uint64_t>(std::floor(rank))};
    for (auto iter = std::cbegin(_samples); iter != std::cend(_samples); ++iter) {
        if (i > iter->second) {
            i -= iter->second;
            continue;
        }

        sample1 = iter->first;

        if (i + 1 <= iter->second) {
            sample2 = iter->first;
        } else {
            sample2 = std::next(iter)->first;
        }

        break;
    }

    return static_cast<double>(sample1) +
           (rank - std::floor(rank)) *
               (static_cast<double>(sample2) - static_cast<double>(sample1));
}

template <class T>
void histogram<T>::log() const {
    LOGI("Histogram:");
    LOGI("  name: {}", _name);
    LOGI("  units: {}", _units);
    LOGI("  sample count: {}", get_sample_count());
    LOGI("  minimum: {}", get_minimum());
    LOGI("  maximum: {}", get_maximum());
    LOGI("  range: {}", get_range());
    LOGI("  mean: {}", get_mean());
    LOGI("  variance: {}", get_variance());
    LOGI("  standard deviation: {}", get_standard_deviation());

    LOGI("  percentiles:");
    LOGI("    50.00: {}", get_percentile(50.));
    LOGI("    75.00: {}", get_percentile(75.));
    LOGI("    90.00: {}", get_percentile(90.));
    LOGI("    95.00: {}", get_percentile(95.));
    LOGI("    99.00: {}", get_percentile(99.));
    LOGI("    99.90: {}", get_percentile(99.9));
    LOGI("    99.99: {}", get_percentile(99.99));

    LOGI("  bins:");
    auto bin_width = get_range() / (static_cast<double>(_num_bins) - 1.);
    auto bins      = std::vector<std::uint64_t>(_num_bins);
    auto minimum   = get_minimum();
    ranges::for_each(_samples, [bin_width, &bins, minimum](const auto & s) {
        bins[static_cast<std::size_t>(std::floor((s.first - minimum) / bin_width))] += s.second;
    });
    ranges::for_each(bins | ranges::views::enumerate, [bin_width, minimum](const auto & p) {
        const auto & [index, b] = p;
        LOGI("    [ {}, {} ): {}",
             minimum + (static_cast<double>(index) * bin_width),
             minimum + (static_cast<double>(index) * bin_width) + bin_width,
             b);
    });

    LOGT(" samples:");
    ranges::for_each(_samples, [](const auto & s) { LOGT("   {}: {}", s.first, s.second); });
}
} // namespace phansar::common
