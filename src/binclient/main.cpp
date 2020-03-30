#include <common.hpp>
#include <queue>

int main(int argc, char *argv[]) {
    common::system::init(argc, argv);

    auto a = common::stdlib::array<int, 2>{};
    a[0] = 10;
    a[1] = 11;

    auto v = common::stdlib::vector<int>{};
    v.push_back(10);
    v.push_back(11);

    auto d = common::stdlib::deque<int>{};
    d.push_back(10);
    d.push_back(11);

    auto fl = common::stdlib::forward_list<int>{};
    fl.push_front(10);
    fl.push_front(11);

    auto l = common::stdlib::list<int>{};
    l.push_back(10);
    l.push_back(11);

    auto s = common::stdlib::set<int>{};
    s.insert(10);
    s.insert(11);

    auto m = common::stdlib::map<int, int>{};
    m[0] = 10;
    m[1] = 11;

    auto ms = common::stdlib::multiset<int>{};
    ms.insert(10);
    ms.insert(11);

    auto mm = common::stdlib::multimap<int, int>{};
    mm.insert(std::make_pair(0, 10));
    mm.insert(std::make_pair(1, 11));

    auto us = common::stdlib::unordered_set<int>{};
    us.insert(10);
    us.insert(11);

    auto um = common::stdlib::unordered_map<int, int>{};
    um[0] = 10;
    um[1] = 11;

    auto ums = common::stdlib::unordered_multiset<int>{};
    ums.insert(10);
    ums.insert(11);

    auto umm = common::stdlib::unordered_multimap<int, int>{};
    umm.insert(std::make_pair(0, 10));
    umm.insert(std::make_pair(1, 11));

    auto st = common::stdlib::stack<int>{};
    st.push(10);
    st.push(11);

    auto q = common::stdlib::queue<int>{};
    q.push(10);
    q.push(11);

    auto pq = common::stdlib::priority_queue<int>{};
    pq.push(10);
    pq.push(11);

    common::system::shutdown();

    return 0;
}
