#include "common_containers_stdlib.hpp"
#include <catch2/catch.hpp>

TEST_CASE("can use container array", "[libcommon][containers][stdlib]") {
    auto a = common::containers::array<int, 2>{};
    a[0] = 10;
    a[1] = 11;
}

TEST_CASE("can use container vector", "[libcommon][containers][stdlib]") {
    auto v = common::containers::vector<int>{};
    v.push_back(10);
    v.push_back(11);
}

TEST_CASE("can use container deque", "[libcommon][containers][stdlib]") {
    auto d = common::containers::deque<int>{};
    d.push_back(10);
    d.push_back(11);
}

TEST_CASE("can use container forward list", "[libcommon][containers][stdlib]") {
    auto fl = common::containers::forward_list<int>{};
    fl.push_front(10);
    fl.push_front(11);
}

TEST_CASE("can use container list", "[libcommon][containers][stdlib]") {
    auto l = common::containers::list<int>{};
    l.push_back(10);
    l.push_back(11);
}

TEST_CASE("can use container set", "[libcommon][containers][stdlib]") {
    auto s = common::containers::set<int>{};
    s.insert(10);
    s.insert(11);
}

TEST_CASE("can use container map", "[libcommon][containers][stdlib]") {
    auto m = common::containers::map<int, int>{};
    m[0] = 10;
    m[1] = 11;
}

TEST_CASE("can use container multiset", "[libcommon][containers][stdlib]") {
    auto ms = common::containers::multiset<int>{};
    ms.insert(10);
    ms.insert(11);
}

TEST_CASE("can use container multimap", "[libcommon][containers][stdlib]") {
    auto mm = common::containers::multimap<int, int>{};
    mm.insert(std::make_pair(0, 10));
    mm.insert(std::make_pair(1, 11));
}

TEST_CASE("can use container unordered set", "[libcommon][containers][stdlib]") {
    auto us = common::containers::unordered_set<int>{};
    us.insert(10);
    us.insert(11);
}

TEST_CASE("can use container unordered map", "[libcommon][containers][stdlib]") {
    auto um = common::containers::unordered_map<int, int>{};
    um[0] = 10;
    um[1] = 11;
}

TEST_CASE("can use container unordered multiset", "[libcommon][containers][stdlib]") {
    auto ums = common::containers::unordered_multiset<int>{};
    ums.insert(10);
    ums.insert(11);
}

TEST_CASE("can use container unordered multimap", "[libcommon][containers][stdlib]") {
    auto umm = common::containers::unordered_multimap<int, int>{};
    umm.insert(std::make_pair(0, 10));
    umm.insert(std::make_pair(1, 11));
}

TEST_CASE("can use container stack", "[libcommon][containers][stdlib]") {
    auto st = common::containers::stack<int>{};
    st.push(10);
    st.push(11);
}

TEST_CASE("can use container queue", "[libcommon][containers][stdlib]") {
    auto q = common::containers::queue<int>{};
    q.push(10);
    q.push(11);
}

TEST_CASE("can use container priority queue", "[libcommon][containers][stdlib]") {
    auto pq = common::containers::priority_queue<int>{};
    pq.push(10);
    pq.push(11);
}
