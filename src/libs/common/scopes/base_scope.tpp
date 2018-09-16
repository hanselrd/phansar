/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_SCOPES_BASE_SCOPE_TPP
#define COMMON_SCOPES_BASE_SCOPE_TPP

#include "base_scope.hpp"

namespace common {
namespace scopes {
namespace internal {
template <class T> base_scope<T>::base_scope() {
    ++_guards;
}

template <class T> base_scope<T>::~base_scope() {
    --_guards;
}

template <class T> std::uint32_t base_scope<T>::get_guards() const {
    return _guards;
}

template <class T> std::uint32_t base_scope<T>::_guards = 0;
} // namespace internal
} // namespace scopes
} // namespace common

#endif
