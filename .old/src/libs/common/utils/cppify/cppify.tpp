/**
 *  This file is part of Phansar.
 *
 *  Copyright (C) 2018  Hansel De La Cruz
 *
 *  Phansar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Phansar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../assert/assert.hpp"
#include "cppify.hpp"

namespace common {
namespace utils {
template <class T, class D>
template <class C, class... Args, class>
cppify<T, D>::cppify(C c, D d, Args &&... args) : _ptr{c(std::forward<Args>(args)...), d} {
    ASSERT(_ptr);
}

template <class T, class D> cppify<T, D>::cppify(T *t, D d) : _ptr{t, d} {
    ASSERT(_ptr);
}

template <class T, class D> cppify<T, D>::operator T *() const {
    ASSERT(_ptr);
    return _ptr.get();
}
} // namespace utils
} // namespace common
