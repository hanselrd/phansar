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

#ifndef COMMON_MODELS_PLAYER_HPP
#define COMMON_MODELS_PLAYER_HPP

#include "../../bitmasks/permissions/permissions.hpp"
#include "../entity/entity.hpp"
#include <array>
#include <cstdint>
#include <string>

namespace common {
namespace models {
// test code/ need to clean up
class player : public entity {
public:
    player() : _permissions{bitmasks::permissions::ROOT | bitmasks::permissions::DONOR} {
    }
    void set_name(const std::string &name) {
        _name = name;
    }
    const std::string &get_name() const {
        return _name;
    }
    bitmasks::permission_flags get_permissions() const {
        return _permissions;
    }

    // don't use protected members
protected:
    std::string _name;
    bitmasks::permission_flags _permissions;
};
} // namespace models
} // namespace common

#endif
