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

#ifndef COMMON_UTILS_CPPIFY_HPP
#define COMMON_UTILS_CPPIFY_HPP

#include <memory>
#include <type_traits>

namespace common {
namespace utils {
template <class T, class D> class cppify {
public:
    template <class C,
              class... Args,
              class = std::void_t<std::enable_if_t<
                  std::is_same_v<std::invoke_result_t<std::decay_t<C>, std::decay_t<Args>...>,
                                 std::add_pointer_t<T>>>>>
    explicit cppify(C c, D d, Args &&... args);

    operator T *() const;

private:
    std::unique_ptr<T, std::decay_t<D>> _ptr;
};
} // namespace utils
} // namespace common

#include "cppify.tpp"

#endif
