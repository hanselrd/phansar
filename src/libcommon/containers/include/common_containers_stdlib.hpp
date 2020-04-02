#ifndef LIBCOMMON_CONTAINERS_INCLUDE_COMMON_CONTAINERS_STDLIB_HPP
#define LIBCOMMON_CONTAINERS_INCLUDE_COMMON_CONTAINERS_STDLIB_HPP

#include "common_allocators.hpp"
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace common::containers {
template <class T, std::size_t N> using array = std::array<T, N>;

template <class T, class Allocator = allocators::default_allocator<T>>
using vector = std::vector<T, Allocator>;

template <class T, class Allocator = allocators::default_allocator<T>>
using deque = std::deque<T, Allocator>;

template <class T, class Allocator = allocators::default_allocator<T>>
using forward_list = std::forward_list<T, Allocator>;

template <class T, class Allocator = allocators::default_allocator<T>>
using list = std::list<T, Allocator>;

template <class Key,
          class Compare = std::less<Key>,
          class Allocator = allocators::default_allocator<Key>>
using set = std::set<Key, Compare, Allocator>;

template <class Key,
          class T,
          class Compare = std::less<Key>,
          class Allocator = allocators::default_allocator<std::pair<const Key, T>>>
using map = std::map<Key, T, Compare, Allocator>;

template <class Key,
          class Compare = std::less<Key>,
          class Allocator = allocators::default_allocator<Key>>
using multiset = std::multiset<Key, Compare, Allocator>;

template <class Key,
          class T,
          class Compare = std::less<Key>,
          class Allocator = allocators::default_allocator<std::pair<const Key, T>>>
using multimap = std::multimap<Key, T, Compare, Allocator>;

template <class Key,
          class Hash = std::hash<Key>,
          class Pred = std::equal_to<Key>,
          class Allocator = allocators::default_allocator<Key>>
using unordered_set = std::unordered_set<Key, Hash, Pred, Allocator>;

template <class Key,
          class T,
          class Hash = std::hash<Key>,
          class Pred = std::equal_to<Key>,
          class Allocator = allocators::default_allocator<std::pair<const Key, T>>>
using unordered_map = std::unordered_map<Key, T, Hash, Pred, Allocator>;

template <class Key,
          class Hash = std::hash<Key>,
          class Pred = std::equal_to<Key>,
          class Allocator = allocators::default_allocator<Key>>
using unordered_multiset = std::unordered_multiset<Key, Hash, Pred, Allocator>;

template <class Key,
          class T,
          class Hash = std::hash<Key>,
          class Pred = std::equal_to<Key>,
          class Allocator = allocators::default_allocator<std::pair<const Key, T>>>
using unordered_multimap = std::unordered_multimap<Key, T, Hash, Pred, Allocator>;

template <class T, class Container = deque<T>> using stack = std::stack<T, Container>;

template <class T, class Container = deque<T>> using queue = std::queue<T, Container>;

template <class T,
          class Container = vector<T>,
          class Compare = std::less<typename Container::value_type>>
using priority_queue = std::priority_queue<T, Container, Compare>;
} // namespace common::containers

#endif
