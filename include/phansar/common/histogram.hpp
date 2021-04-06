#ifndef PHANSAR_COMMON_HISTOGRAM_HPP
#define PHANSAR_COMMON_HISTOGRAM_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <phansar/vendor/rttr.hpp>

namespace phansar::common {
template <class T>
class histogram;

template <>
class histogram<double> {
public:
    struct bin {
        double         lower;
        double         upper;
        std::uintmax_t count;
    };

    struct sample {
        double         value;
        std::uintmax_t count;
    };

    histogram(std::string_view _name, std::string_view _units, std::size_t _num_bins);
    histogram(const histogram &) = default;
    auto operator=(const histogram &) -> histogram & = default;
    histogram(histogram &&)                          = default;
    auto operator=(histogram &&) -> histogram & = default;
    virtual ~histogram();

    void               push(const double & _sample);
    [[nodiscard]] auto name() const -> const std::string &;
    [[nodiscard]] auto units() const -> const std::string &;
    [[nodiscard]] auto sample_count() const -> std::uintmax_t;
    [[nodiscard]] auto minimum() const -> double;
    [[nodiscard]] auto maximum() const -> double;
    [[nodiscard]] auto range() const -> double;
    [[nodiscard]] auto mean() const -> double;
    [[nodiscard]] auto variance() const -> double;
    [[nodiscard]] auto standard_deviation() const -> double;
    [[nodiscard]] auto percentile(double _percentile) const -> double;
    [[nodiscard]] auto bins() const -> std::vector<bin>;
    [[nodiscard]] auto samples() const -> std::vector<sample>;

private:
    struct impl;
    utility::pimpl<impl> m_impl;

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE()
};

template <class T>
class histogram : public histogram<double> {
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");

public:
    histogram(std::string_view _name, std::string_view _units, std::size_t _num_bins);

    void               push(const T & _sample);
    [[nodiscard]] auto name() const -> const std::string &;
    [[nodiscard]] auto units() const -> const std::string &;
    [[nodiscard]] auto sample_count() const -> std::uintmax_t;
    auto               minimum() const -> T;
    auto               maximum() const -> T;
    auto               range() const -> T;
    [[nodiscard]] auto mean() const -> double;
    [[nodiscard]] auto variance() const -> double;
    [[nodiscard]] auto standard_deviation() const -> double;
    [[nodiscard]] auto percentile(double _percentile) const -> double;
    [[nodiscard]] auto bins() const -> std::vector<bin>;
    [[nodiscard]] auto samples() const -> std::vector<sample>;

private:
    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE(histogram<double>)
};
} // namespace phansar::common

#include <phansar/common/histogram.inl>

#endif
