#ifndef PHANSAR_COMMON_TYPES_STD_HPP
#define PHANSAR_COMMON_TYPES_STD_HPP

#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace phansar::common::types::std {
template <class T, template <class> class Allocator>
using vector = ::std::vector<T, Allocator<T>>;

template <class T, template <class> class Allocator>
using deque = ::std::deque<T, Allocator<T>>;

template <class T, template <class> class Allocator>
using forward_list = ::std::forward_list<T, Allocator<T>>;

template <class T, template <class> class Allocator>
using list = ::std::list<T, Allocator<T>>;

template <class Key, template <class> class Allocator>
using set = ::std::set<Key, ::std::less<Key>, Allocator<Key>>;

template <class Key, class T, template <class> class Allocator>
using map = ::std::map<Key, T, ::std::less<Key>, Allocator<::std::pair<const Key, T>>>;

template <class Key, template <class> class Allocator>
using multiset = ::std::multiset<Key, ::std::less<Key>, Allocator<Key>>;

template <class Key, class T, template <class> class Allocator>
using multimap = ::std::multimap<Key, T, ::std::less<Key>, Allocator<::std::pair<const Key, T>>>;

template <class Key, template <class> class Allocator>
using unordered_set =
    ::std::unordered_set<Key, ::std::hash<Key>, ::std::equal_to<Key>, Allocator<Key>>;

template <class Key, class T, template <class> class Allocator>
using unordered_map = ::std::unordered_map<Key,
                                           T,
                                           ::std::hash<Key>,
                                           ::std::equal_to<Key>,
                                           Allocator<::std::pair<const Key, T>>>;

template <class Key, template <class> class Allocator>
using unordered_multiset =
    ::std::unordered_multiset<Key, ::std::hash<Key>, ::std::equal_to<Key>, Allocator<Key>>;

template <class Key, class T, template <class> class Allocator>
using unordered_multimap = ::std::unordered_multimap<Key,
                                                     T,
                                                     ::std::hash<Key>,
                                                     ::std::equal_to<Key>,
                                                     Allocator<::std::pair<const Key, T>>>;

template <class T, template <class> class Allocator>
using stack = ::std::stack<T, deque<T, Allocator>>;

template <class T, template <class> class Allocator>
using queue = ::std::queue<T, deque<T, Allocator>>;

template <class T, template <class> class Allocator>
using priority_queue = ::std::
    priority_queue<T, vector<T, Allocator>, ::std::less<typename vector<T, Allocator>::value_type>>;

template <class CharT, template <class> class Allocator>
using basic_string = ::std::basic_string<CharT, ::std::char_traits<CharT>, Allocator<CharT>>;

template <template <class> class Allocator>
using string = basic_string<char, Allocator>;

template <template <class> class Allocator>
using wstring = basic_string<wchar_t, Allocator>;
/* using u8string  = basic_string<char8_t>; */
/* using u16string = basic_string<char16_t>; */
/* using u32string = basic_string<char32_t>; */

template <class CharT, template <class> class Allocator>
using basic_stringstream =
    ::std::basic_stringstream<CharT, ::std::char_traits<CharT>, Allocator<CharT>>;

template <template <class> class Allocator>
using stringstream = basic_stringstream<char, Allocator>;

template <template <class> class Allocator>
using wstringstream = basic_stringstream<wchar_t, Allocator>;
/* using u8stringstream  = basic_stringstream<char8_t>; */
/* using u16stringstream = basic_stringstream<char16_t>; */
/* using u32stringstream = basic_stringstream<char32_t>; */
} // namespace phansar::common::types::std

#endif
