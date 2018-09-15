#ifndef COMMON_SCOPES_BASE_TPP
#define COMMON_SCOPES_BASE_TPP

#include "base.hpp"

namespace common {
namespace scopes {
namespace internal {
template <class T> base<T>::base() {
    ++_guards;
}

template <class T> base<T>::~base() {
    --_guards;
}

template <class T> std::uint32_t base<T>::get_guards() const {
    return _guards;
}

template <class T> std::uint32_t base<T>::_guards = 0;
} // namespace internal
} // namespace scopes
} // namespace common

#endif
