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

#ifndef LIBS_COMMON_ARCHIVES_BASE_ARCHIVE_BASE_ARCHIVE_HPP
#define LIBS_COMMON_ARCHIVES_BASE_ARCHIVE_BASE_ARCHIVE_HPP

#include "../../vendor/json/json.hpp"
#include <iostream>

namespace common {
namespace archives {
namespace detail {
class base_archive {
public:
    virtual ~base_archive() = default;

    virtual vendor::json load(std::istream &is) = 0;
    virtual void save(std::ostream &os, const vendor::json &j) = 0;
};
} // namespace detail
} // namespace archives
} // namespace common

#endif
