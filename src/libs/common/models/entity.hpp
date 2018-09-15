#ifndef COMMON_MODELS_ENTITY_HPP
#define COMMON_MODELS_ENTITY_HPP

#include "../core/types.hpp"
#include <array>
#include <cstdint>

namespace common {
namespace models {
// test code/ need to clean up
class entity {
public:
    explicit entity(const core::types::vector3f &position = core::types::vector3f())
        : _position(position) {
    }
    void move(const core::types::vector3f &offset) {
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
    void set_position(const core::types::vector3f &position) {
        _position = position;
    }
    core::types::vector3f get_position() const {
        return _position;
    }

    // don't use protected members
protected:
    std::uint16_t _map_id;
    core::types::vector3f _position;
};
} // namespace models
} // namespace common

#endif
