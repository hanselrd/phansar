#include "common_containers_stdlib.hpp"
#include <catch2/catch.hpp>

TEST_CASE("can use container vector", "[libcommon][containers][stdlib]") {
    auto v = common::containers::stdlib::vector<int>{};
    v.push_back(3);
    v.push_back(4);
}

TEST_CASE("can use container deque", "[libcommon][containers][stdlib]") {
    auto d = common::containers::stdlib::deque<int>{};
    d.push_back(3);
    d.push_back(4);
}

TEST_CASE("can use container forward list", "[libcommon][containers][stdlib]") {
    auto fl = common::containers::stdlib::forward_list<int>{};
    fl.push_front(3);
    fl.push_front(4);
}

TEST_CASE("can use container list", "[libcommon][containers][stdlib]") {
    auto l = common::containers::stdlib::list<int>{};
    l.push_back(3);
    l.push_back(4);
}

TEST_CASE("can use container set", "[libcommon][containers][stdlib]") {
    auto s = common::containers::stdlib::set<int>{};
    s.insert(3);
    s.insert(4);
}

TEST_CASE("can use container map", "[libcommon][containers][stdlib]") {
    auto m = common::containers::stdlib::map<int, int>{};
    m[0]   = 3;
    m[1]   = 4;
}

TEST_CASE("can use container multiset", "[libcommon][containers][stdlib]") {
    auto ms = common::containers::stdlib::multiset<int>{};
    ms.insert(3);
    ms.insert(4);
}

TEST_CASE("can use container multimap", "[libcommon][containers][stdlib]") {
    auto mm = common::containers::stdlib::multimap<int, int>{};
    mm.insert(std::make_pair(0, 3));
    mm.insert(std::make_pair(1, 4));
}

TEST_CASE("can use container unordered set", "[libcommon][containers][stdlib]") {
    auto us = common::containers::stdlib::unordered_set<int>{};
    us.insert(3);
    us.insert(4);
}

TEST_CASE("can use container unordered map", "[libcommon][containers][stdlib]") {
    auto um = common::containers::stdlib::unordered_map<int, int>{};
    um[0]   = 3;
    um[1]   = 4;
}

TEST_CASE("can use container unordered multiset", "[libcommon][containers][stdlib]") {
    auto ums = common::containers::stdlib::unordered_multiset<int>{};
    ums.insert(3);
    ums.insert(4);
}

TEST_CASE("can use container unordered multimap", "[libcommon][containers][stdlib]") {
    auto umm = common::containers::stdlib::unordered_multimap<int, int>{};
    umm.insert(std::make_pair(0, 3));
    umm.insert(std::make_pair(1, 4));
}

TEST_CASE("can use container stack", "[libcommon][containers][stdlib]") {
    auto st = common::containers::stdlib::stack<int>{};
    st.push(3);
    st.push(4);
}

TEST_CASE("can use container queue", "[libcommon][containers][stdlib]") {
    auto q = common::containers::stdlib::queue<int>{};
    q.push(3);
    q.push(4);
}

TEST_CASE("can use container priority queue", "[libcommon][containers][stdlib]") {
    auto pq = common::containers::stdlib::priority_queue<int>{};
    pq.push(3);
    pq.push(4);
}
