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

#ifndef LIBS_COMMON_MODELS_ENTITY_ENTITY_HPP
#define LIBS_COMMON_MODELS_ENTITY_ENTITY_HPP

#include "../../components/vec3/vec3.hpp"
#include <array>
#include <cstdint>

namespace common {
namespace models {
// test code/ need to clean up
class entity {
public:
    explicit entity(const components::vec3f &position = components::vec3f{}) : _position{position} {
    }
    void move(const components::vec3f &offset) {
        _position.x += offset.x;
        _position.y += offset.y;
        _position.z += offset.z;
    }
    void set_map_id(std::uint16_t map_id) {
        _map_id = map_id;
    }
    std::uint16_t get_map_id() const {
        return _map_id;
    }
    void set_position(const components::vec3f &position) {
        _position = position;
    }
    components::vec3f get_position() const {
        return _position;
    }

    // don't use protected members
protected:
    std::uint16_t _map_id;
    components::vec3f _position;
};
} // namespace models
} // namespace common

#endif
