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

#ifndef LIBS_COMMON_SCOPES_BASE_SCOPE_BASE_SCOPE_HPP
#define LIBS_COMMON_SCOPES_BASE_SCOPE_BASE_SCOPE_HPP

#include <cstdint>

namespace common {
namespace scopes {
namespace detail {
template <class T> class base_scope {
public:
    base_scope();
    virtual ~base_scope();

    std::uint32_t get_guards() const;

private:
    static std::uint32_t _guards;
};
} // namespace detail
} // namespace scopes
} // namespace common

#include "base_scope.tpp"

#endif