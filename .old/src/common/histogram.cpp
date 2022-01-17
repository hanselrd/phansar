#include <phansar/common/bindings.hpp>
#include <phansar/common/histogram.hpp>
#include <phansar/vendor/rangev3.hpp>
#undef PHANSAR_VENDOR_RTTR_HPP
#define PH_VENDOR_RTTR_PRIVATE
#include <phansar/vendor/rttr.hpp>

namespace phansar::common {
struct histogram<double>::impl {
    std::string                      name, units;
    std::size_t                      num_bins;
    std::map<double, std::uintmax_t> samples;
};

histogram<double>::histogram(std::string_view _name, std::string_view _units, std::size_t _num_bins)
    : m_impl{std::string{_name},
             std::string{_units},
             _num_bins,
             std::map<double, std::uintmax_t>{}} {}

histogram<double>::~histogram() = default;

void histogram<double>::push(const double & _sample) {
    ++m_impl->samples[_sample];
}

auto histogram<double>::name() const -> const std::string & {
    return m_impl->name;
}

auto histogram<double>::units() const -> const std::string & {
    return m_impl->units;
}

auto histogram<double>::sample_count() const -> std::uintmax_t {
    return ranges::accumulate(m_impl->samples, std::uintmax_t{0}, [](auto _acc, const auto & _s) {
        return _acc + _s.second;
    });
}

auto histogram<double>::minimum() const -> double {
    return std::cbegin(m_impl->samples)->first;
}

auto histogram<double>::maximum() const -> double {
    return std::prev(std::cend(m_impl->samples))->first;
}

auto histogram<double>::range() const -> double {
    return maximum() - minimum();
}

auto histogram<double>::mean() const -> double {
    return ranges::accumulate(m_impl->samples,
                              0.,
                              [](auto _acc, const auto & _s) {
                                  return _acc + (static_cast<double>(_s.first) *
                                                 static_cast<double>(_s.second));
                              }) /
           static_cast<double>(sample_count());
}

auto histogram<double>::variance() const -> double {
    auto cached_mean = mean();
    return ranges::accumulate(m_impl->samples,
                              0.,
                              [cached_mean](auto _acc, const auto & _s) {
                                  return _acc + (((static_cast<double>(_s.first) - cached_mean) *
                                                  (static_cast<double>(_s.first) - cached_mean)) *
                                                 static_cast<double>(_s.second));
                              }) /
           (static_cast<double>(sample_count()) - 1.);
}

auto histogram<double>::standard_deviation() const -> double {
    return std::sqrt(variance());
}

auto histogram<double>::percentile(double _percentile) const -> double {
    const auto rank    = (_percentile / 100.) * (static_cast<double>(sample_count()) - 1.) + 1.;
    auto       sample1 = double{0};
    auto       sample2 = double{0};

    auto i = std::uintmax_t{static_cast<std::uintmax_t>(std::floor(rank))};
    for (auto iter = std::cbegin(m_impl->samples); iter != std::cend(m_impl->samples); ++iter) {
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

auto histogram<double>::bins() const -> std::vector<bin> {
    auto width          = range() / (static_cast<double>(m_impl->num_bins) - 1.);
    auto bins           = std::vector<bin>(m_impl->num_bins);
    auto cached_minimum = minimum();
    for (auto && [index, b] : bins | ranges::views::enumerate) {
        b.lower = cached_minimum + (static_cast<double>(index) * width);
        b.upper = cached_minimum + (static_cast<double>(index) * width) + width;
    }
    for (const auto & s : m_impl->samples) {
        bins[static_cast<std::size_t>(std::floor((s.first - cached_minimum) / width))].count +=
            s.second;
    }
    return bins;
}

auto histogram<double>::samples() const -> std::vector<sample> {
    return m_impl->samples | ranges::views::transform([](const auto & _s) {
               return sample{_s.first, _s.second};
           }) |
           ranges::to_vector;
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)
RTTR_REGISTRATION {
    rttr::registration::class_<histogram<double>::bin>("histogram_bin")
        .property("lower", &histogram<double>::bin::lower)
        .property("upper", &histogram<double>::bin::upper)
        .property("count", &histogram<double>::bin::count);

    rttr::registration::class_<histogram<double>::sample>("histogram_sample")
        .property("value", &histogram<double>::sample::value)
        .property("count", &histogram<double>::sample::count);

    rttr::registration::class_<histogram<double>>("histogram")
        .constructor<std::string_view, std::string_view, std::size_t>()
        .method("push", &histogram<double>::push)(rttr::metadata("no_serialize", true))
        .property_readonly("name", &histogram<double>::name)
        .property_readonly("units", &histogram<double>::units)
        .property_readonly("sample_count", &histogram<double>::sample_count)
        .property_readonly("minimum", &histogram<double>::minimum)
        .property_readonly("maximum", &histogram<double>::maximum)
        .property_readonly("range", &histogram<double>::range)
        .property_readonly("mean", &histogram<double>::mean)
        .property_readonly("variance", &histogram<double>::variance)
        .property_readonly("standard_deviation", &histogram<double>::standard_deviation)
        .method("percentile", &histogram<double>::percentile)(
            rttr::metadata("arguments",
                           std::map<std::string, std::vector<rttr::variant>>{
                               {"50.00", {50.}},
                               {"75.00", {75.}},
                               {"90.00", {90.}},
                               {"95.00", {95.}},
                               {"99.00", {99.}},
                               {"99.90", {99.9}},
                               {"99.99", {99.99}},
                           }))
        .property_readonly("bins", &histogram<double>::bins)
        .property_readonly("samples",
                           &histogram<double>::samples)(rttr::metadata("no_serialize", true));
}
} // namespace phansar::common
