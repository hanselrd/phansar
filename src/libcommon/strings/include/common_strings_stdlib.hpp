#ifndef LIBCOMMON_STRINGS_INCLUDE_COMMON_STRINGS_STDLIB_HPP
#define LIBCOMMON_STRINGS_INCLUDE_COMMON_STRINGS_STDLIB_HPP

#include "common_allocators.hpp"
#include <sstream>
#include <string>

namespace common::strings::stdlib {
template <class CharT,
          class Traits    = std::char_traits<CharT>,
          class Allocator = allocators::default_allocator<CharT>>
using basic_string = std::basic_string<CharT, Traits, Allocator>;

using string  = basic_string<char>;
using wstring = basic_string<wchar_t>;
/* using u8string  = basic_string<char8_t>; */
/* using u16string = basic_string<char16_t>; */
/* using u32string = basic_string<char32_t>; */

template <class CharT,
          class Traits    = std::char_traits<CharT>,
          class Allocator = allocators::default_allocator<CharT>>
using basic_stringstream = std::basic_stringstream<CharT, Traits, Allocator>;

using stringstream  = basic_stringstream<char>;
using wstringstream = basic_stringstream<wchar_t>;
/* using u8stringstream  = basic_stringstream<char8_t>; */
/* using u16stringstream = basic_stringstream<char16_t>; */
/* using u32stringstream = basic_stringstream<char32_t>; */
} // namespace common::strings::stdlib

#endif
