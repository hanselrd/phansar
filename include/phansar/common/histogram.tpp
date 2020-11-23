#include <phansar/common/histogram.hpp>

namespace phansar::common {
template <class T>
histogram<T>::histogram(std::string_view _name, std::string_view _units, std::size_t _num_bins)
    : m_name{_name}, m_units{_units}, m_num_bins{_num_bins} {}

template <class T>
void histogram<T>::push(const T & _sample) {
    ++m_samples[_sample];
}

template <class T>
auto histogram<T>::name() const -> const std::string & {
    return m_name;
}

template <class T>
auto histogram<T>::units() const -> const std::string & {
    return m_units;
}

template <class T>
auto histogram<T>::sample_count() const -> std::uintmax_t {
    return ranges::accumulate(m_samples, std::uintmax_t{0}, [](auto _acc, const auto & _s) {
        return _acc + _s.second;
    });
}

template <class T>
auto histogram<T>::minimum() const -> T {
    return std::cbegin(m_samples)->first;
}

template <class T>
auto histogram<T>::maximum() const -> T {
    return std::prev(std::cend(m_samples))->first;
}

template <class T>
auto histogram<T>::range() const -> T {
    return maximum() - minimum();
}

template <class T>
auto histogram<T>::mean() const -> double {
    return ranges::accumulate(m_samples,
                              0.,
                              [](auto _acc, const auto & _s) {
                                  return _acc + (static_cast<double>(_s.first) *
                                                 static_cast<double>(_s.second));
                              }) /
           static_cast<double>(sample_count());
}

template <class T>
auto histogram<T>::variance() const -> double {
    auto cached_mean = mean();
    return ranges::accumulate(m_samples,
                              0.,
                              [cached_mean](auto _acc, const auto & _s) {
                                  return _acc + (((static_cast<double>(_s.first) - cached_mean) *
                                                  (static_cast<double>(_s.first) - cached_mean)) *
                                                 static_cast<double>(_s.second));
                              }) /
           (static_cast<double>(sample_count()) - 1.);
}

template <class T>
auto histogram<T>::standard_deviation() const -> double {
    return std::sqrt(variance());
}

template <class T>
auto histogram<T>::percentile(double _percentile) const -> double {
    const auto rank    = (_percentile / 100.) * (static_cast<double>(sample_count()) - 1.) + 1.;
    auto       sample1 = T{0};
    auto       sample2 = T{0};

    auto i = std::uintmax_t{static_cast<std::uintmax_t>(std::floor(rank))};
    for (auto iter = std::cbegin(m_samples); iter != std::cend(m_samples); ++iter) {
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
auto histogram<T>::bins() const -> std::vector<bin_type> {
    auto width          = range() / (static_cast<double>(m_num_bins) - 1.);
    auto bins           = std::vector<bin_type>(m_num_bins);
    auto cached_minimum = minimum();
    for (auto && [index, b] : bins | ranges::views::enumerate) {
        std::get<0>(b) = cached_minimum + (static_cast<double>(index) * width);
        std::get<1>(b) = cached_minimum + (static_cast<double>(index) * width) + width;
    }
    for (const auto & s : m_samples) {
        std::get<2>(
            bins[static_cast<std::size_t>(std::floor((s.first - cached_minimum) / width))]) +=
            s.second;
    }
    return bins;
}

template <class T>
auto histogram<T>::samples() const -> std::vector<sample_type> {
    return m_samples | ranges::views::transform([](const auto & _s) {
               return sample_type{_s.first, _s.second};
           }) |
           ranges::to_vector;
}

template <class T>
void to_json(nlohmann::ordered_json & _json, const histogram<T> & _histogram) {
    _json = nlohmann::ordered_json{{"name", _histogram.name()},
                                   {"units", _histogram.units()},
                                   {"sample_count", _histogram.sample_count()},
                                   {"minimum", _histogram.minimum()},
                                   {"maximum", _histogram.maximum()},
                                   {"range", _histogram.range()},
                                   {"mean", _histogram.mean()},
                                   {"variance", _histogram.variance()},
                                   {"standard_deviation", _histogram.standard_deviation()},
                                   {"percentiles",
                                    {
                                        {50., _histogram.percentile(50.)},
                                        {75., _histogram.percentile(75.)},
                                        {90., _histogram.percentile(90.)},
                                        {95., _histogram.percentile(95.)},
                                        {99., _histogram.percentile(99.)},
                                        {99.9, _histogram.percentile(99.9)},
                                        {99.99, _histogram.percentile(99.99)},
                                    }},
                                   {"bins", _histogram.bins()},
                                   {"samples", _histogram.samples()}};
}

template <class T>
auto operator<<(std::ostream & _os, const histogram<T> & _histogram) -> std::ostream & {
    _os << fmt::format("histogram[name=\"{}\"]:\n", _histogram.name());
    _os << fmt::format("  name: {}\n", _histogram.name());
    _os << fmt::format("  units: {}\n", _histogram.units());
    _os << fmt::format("  sample count: {}\n", _histogram.sample_count());
    _os << fmt::format("  minimum: {}\n", _histogram.minimum());
    _os << fmt::format("  maximum: {}\n", _histogram.maximum());
    _os << fmt::format("  range: {}\n", _histogram.range());
    _os << fmt::format("  mean: {}\n", _histogram.mean());
    _os << fmt::format("  variance: {}\n", _histogram.variance());
    _os << fmt::format("  standard deviation: {}\n", _histogram.standard_deviation());
    _os << fmt::format("  percentiles:\n");
    _os << fmt::format("    50.00: {}\n", _histogram.percentile(50.));
    _os << fmt::format("    75.00: {}\n", _histogram.percentile(75.));
    _os << fmt::format("    90.00: {}\n", _histogram.percentile(90.));
    _os << fmt::format("    95.00: {}\n", _histogram.percentile(95.));
    _os << fmt::format("    99.00: {}\n", _histogram.percentile(99.));
    _os << fmt::format("    99.90: {}\n", _histogram.percentile(99.9));
    _os << fmt::format("    99.99: {}\n", _histogram.percentile(99.99));
    _os << fmt::format("  bins:\n");
    for (const auto & [lower, upper, count] : _histogram.bins()) {
        _os << fmt::format("    [ {}, {} ): {}\n", lower, upper, count);
    }
    _os << fmt::format("  samples:\n");
    for (const auto & [value, count] : _histogram.samples()) {
        _os << fmt::format("    {}: {}\n", value, count);
    }
    return _os;
}
} // namespace phansar::common
