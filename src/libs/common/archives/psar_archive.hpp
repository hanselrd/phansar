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

#ifndef COMMON_ARCHIVES_PSAR_ARCHIVE_HPP
#define COMMON_ARCHIVES_PSAR_ARCHIVE_HPP

#include "base_archive.hpp"

namespace common {
namespace archives {
class psar_archive : public internal::base_archive {
public:
    core::json load(std::istream &is) override;
    void save(std::ostream &os, const core::json &j) override;
};
} // namespace archives
} // namespace common

#endif
