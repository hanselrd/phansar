#ifndef PHANSAR_COMMON_HISTOGRAM_HPP
#define PHANSAR_COMMON_HISTOGRAM_HPP

namespace phansar::common {
template <class T>
class histogram {
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");

public:
    using bin    = std::tuple<double, double, std::uintmax_t>;
    using sample = std::tuple<T, std::uintmax_t>;

    histogram(std::string_view _name, std::string_view _units, std::size_t _num_bins);

    void               push(const T & _sample);
    [[nodiscard]] auto name() const -> const std::string &;
    [[nodiscard]] auto units() const -> const std::string &;
    [[nodiscard]] auto sample_count() const -> std::uintmax_t;
    [[nodiscard]] auto minimum() const -> T;
    [[nodiscard]] auto maximum() const -> T;
    [[nodiscard]] auto range() const -> T;
    [[nodiscard]] auto mean() const -> double;
    [[nodiscard]] auto variance() const -> double;
    [[nodiscard]] auto standard_deviation() const -> double;
    [[nodiscard]] auto percentile(double _percentile) const -> double;
    [[nodiscard]] auto bins() const -> std::vector<bin>;
    [[nodiscard]] auto samples() const -> std::vector<sample>;

private:
    std::string                 m_name, m_units;
    std::size_t                 m_num_bins;
    std::map<T, std::uintmax_t> m_samples;
};

template <class T>
void to_json(nlohmann::ordered_json & _json, const histogram<T> & _histogram);

template <class T>
auto operator<<(std::ostream & _os, const histogram<T> & _histogram) -> std::ostream &;
} // namespace phansar::common

#include <phansar/common/histogram.tpp>

#endif
