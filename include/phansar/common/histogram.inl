#include <phansar/common/histogram.hpp>

namespace phansar::common {
template <class T>
histogram<T>::histogram(std::string_view _name, std::string_view _units, std::size_t _num_bins)
    : histogram<double>{_name, _units, _num_bins} {}

template <class T>
void histogram<T>::push(const T & _sample) {
    histogram<double>::push(static_cast<double>(_sample));
}

template <class T>
auto histogram<T>::name() const -> const std::string & {
    return histogram<double>::name();
}

template <class T>
auto histogram<T>::units() const -> const std::string & {
    return histogram<double>::units();
}

template <class T>
auto histogram<T>::sample_count() const -> std::uintmax_t {
    return histogram<double>::sample_count();
}

template <class T>
auto histogram<T>::minimum() const -> T {
    return static_cast<T>(histogram<double>::minimum());
}

template <class T>
auto histogram<T>::maximum() const -> T {
    return static_cast<T>(histogram<double>::maximum());
}

template <class T>
auto histogram<T>::range() const -> T {
    return static_cast<T>(histogram<double>::range());
}

template <class T>
auto histogram<T>::mean() const -> double {
    return histogram<double>::mean();
}

template <class T>
auto histogram<T>::variance() const -> double {
    return histogram<double>::variance();
}

template <class T>
auto histogram<T>::standard_deviation() const -> double {
    return histogram<double>::standard_deviation();
}

template <class T>
auto histogram<T>::percentile(double _percentile) const -> double {
    return histogram<double>::percentile(_percentile);
}

template <class T>
auto histogram<T>::bins() const -> std::vector<bin> {
    return histogram<double>::bins();
}

template <class T>
auto histogram<T>::samples() const -> std::vector<sample> {
    return histogram<double>::samples();
}
} // namespace phansar::common
