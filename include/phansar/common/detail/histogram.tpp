#include <phansar/common/histogram.hpp>

#include <cmath>

namespace phansar::common {
template <class T>
void histogram<T>::push(const T & sample) {
    _samples.push_back(sample);
}

template <class T>
auto histogram<T>::get_sample_count() const -> std::uint64_t {
    return _samples.size();
}

template <class T>
auto histogram<T>::get_minimum() const -> T {
    return *ranges::min_element(_samples);
}

template <class T>
auto histogram<T>::get_maximum() const -> T {
    return *ranges::max_element(_samples);
}

template <class T>
auto histogram<T>::get_range() const -> T {
    return get_maximum() - get_minimum();
}

template <class T>
auto histogram<T>::get_mean() const -> double {
    return ranges::accumulate(_samples, 0.) / static_cast<double>(_samples.size());
}

template <class T>
auto histogram<T>::get_variance() const -> double {
    auto mean = get_mean();
    return ranges::accumulate(_samples,
                              0.,
                              [mean](auto acc, auto elem) {
                                  return acc + ((elem - mean) * (elem - mean));
                              }) /
           (static_cast<double>(_samples.size()) - 1);
}

template <class T>
auto histogram<T>::get_standard_deviation() const -> double {
    return std::sqrt(get_variance());
}

template <class T>
auto histogram<T>::get_percentile(double percentile) const -> double {
    auto rank    = (percentile / 100.) * (static_cast<double>(_samples.size()) - 1.) + 1.;
    auto samples = _samples;
    ranges::nth_element(samples, std::begin(samples) + static_cast<std::size_t>(std::floor(rank)));
    ranges::nth_element(samples,
                        std::begin(samples) + static_cast<std::size_t>(std::floor(rank)) - 1);

    return samples[static_cast<std::size_t>(std::floor(rank)) - 1] +
           (rank - std::floor(rank)) * (samples[static_cast<std::size_t>(std::floor(rank))] -
                                        samples[static_cast<std::size_t>(std::floor(rank)) - 1]);
}

template <class T>
auto histogram<T>::get_bin_width(std::size_t num_bins) const -> double {
    return get_range() / (static_cast<double>(num_bins) - 1);
}

template <class T>
auto histogram<T>::get_bins(std::size_t num_bins) const
    -> containers::stdlib::vector<std::uint64_t> {
    auto bin_width = get_bin_width(num_bins);
    auto bins      = containers::stdlib::vector<std::uint64_t>(num_bins);
    auto minimum   = get_minimum();
    ranges::for_each(_samples, [bin_width, &bins, minimum](auto a) {
        ++bins[static_cast<std::size_t>(std::floor((a - minimum) / bin_width))];
    });
    return bins;
}
} // namespace phansar::common
