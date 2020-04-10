#include "common_containers_stdlib.hpp"
#include <catch2/catch.hpp>

TEST_CASE("common_containers_stdlib", "[common][containers][stdlib]") {
    SECTION("can use vector") {
        auto v = common::containers::stdlib::vector<int>{};
        v.push_back(3);
        v.push_back(4);

        REQUIRE(v.size() == 2);
    }

    SECTION("can use deque") {
        auto d = common::containers::stdlib::deque<int>{};
        d.push_back(3);
        d.push_back(4);

        REQUIRE(d.size() == 2);
    }

    SECTION("can use forward_list") {
        auto fl = common::containers::stdlib::forward_list<int>{};
        fl.push_front(3);
        fl.push_front(4);
    }

    SECTION("can use list") {
        auto l = common::containers::stdlib::list<int>{};
        l.push_back(3);
        l.push_back(4);

        REQUIRE(l.size() == 2);
    }

    SECTION("can use set") {
        auto s = common::containers::stdlib::set<int>{};
        s.insert(3);
        s.insert(4);

        REQUIRE(s.size() == 2);
    }

    SECTION("can use map") {
        auto m = common::containers::stdlib::map<int, int>{};
        m[0]   = 3;
        m[1]   = 4;

        REQUIRE(m.size() == 2);
    }

    SECTION("can use multiset") {
        auto ms = common::containers::stdlib::multiset<int>{};
        ms.insert(3);
        ms.insert(4);

        REQUIRE(ms.size() == 2);
    }

    SECTION("can use multimap") {
        auto mm = common::containers::stdlib::multimap<int, int>{};
        mm.insert(std::make_pair(0, 3));
        mm.insert(std::make_pair(1, 4));

        REQUIRE(mm.size() == 2);
    }

    SECTION("can use unordered_set") {
        auto us = common::containers::stdlib::unordered_set<int>{};
        us.insert(3);
        us.insert(4);

        REQUIRE(us.size() == 2);
    }

    SECTION("can use unordered_map") {
        auto um = common::containers::stdlib::unordered_map<int, int>{};
        um[0]   = 3;
        um[1]   = 4;

        REQUIRE(um.size() == 2);
    }

    SECTION("can use unordered_multiset") {
        auto ums = common::containers::stdlib::unordered_multiset<int>{};
        ums.insert(3);
        ums.insert(4);

        REQUIRE(ums.size() == 2);
    }

    SECTION("can use unordered_multimap") {
        auto umm = common::containers::stdlib::unordered_multimap<int, int>{};
        umm.insert(std::make_pair(0, 3));
        umm.insert(std::make_pair(1, 4));

        REQUIRE(umm.size() == 2);
    }

    SECTION("can use stack") {
        auto st = common::containers::stdlib::stack<int>{};
        st.push(3);
        st.push(4);

        REQUIRE(st.size() == 2);
    }

    SECTION("can use queue") {
        auto q = common::containers::stdlib::queue<int>{};
        q.push(3);
        q.push(4);

        REQUIRE(q.size() == 2);
    }

    SECTION("can use priority_queue") {
        auto pq = common::containers::stdlib::priority_queue<int>{};
        pq.push(3);
        pq.push(4);

        REQUIRE(pq.size() == 2);
    }
}
