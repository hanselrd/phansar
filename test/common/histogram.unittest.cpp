#include <phansar/common/histogram.hpp>
#include <phansar/vendor/catch2.hpp>

SCENARIO("common::histogram", "[common][histogram]") {
    auto hist = phansar::common::histogram<int>{"A", "units", 6};

    GIVEN("a new histogram") {
        for (auto && sample : {5, 5, 10, 12, 8, 3, 2, 9, 8, 4, 1, 20, 3, 2, 4, 6}) {
            hist.push(sample);
        }

        REQUIRE(hist.name() == "A");
        REQUIRE(hist.units() == "units");
        REQUIRE(hist.sample_count() == 16);
        REQUIRE(hist.minimum() == 1);
        REQUIRE(hist.maximum() == 20);
        REQUIRE(hist.range() == 19);
        REQUIRE(hist.mean() == Approx(6.375));
        REQUIRE(hist.variance() == Approx(23.183333));
        REQUIRE(hist.standard_deviation() == Approx(4.8149074));
        REQUIRE(hist.percentile(50.) == Approx(5));
        REQUIRE(hist.percentile(75.) == Approx(8.25));
        REQUIRE(hist.percentile(90.) == Approx(11));
        REQUIRE(hist.percentile(95.) == Approx(14));
        REQUIRE(hist.percentile(99.) == Approx(18.8));
        REQUIRE(hist.percentile(99.9) == Approx(19.88));
        REQUIRE(hist.percentile(99.99) == Approx(19.988));
        REQUIRE(hist.bins().size() == 6);
        REQUIRE(hist.samples().size() == 11);
    }
}
