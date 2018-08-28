#ifndef COMMON_MODELS_PLAYER_HPP
#define COMMON_MODELS_PLAYER_HPP

#include "../bitmasks/permissions.hpp"
#include "../core/types.hpp"
#include "entity.hpp"
#include <array>
#include <cstdint>
#include <string>

namespace common {
namespace models {
// test code/ need to clean up
class player : public entity {
public:
    player() : _permissions(bitmasks::permissions::ROOT | bitmasks::permissions::DONOR) {
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

protected:
    std::string _name;
    bitmasks::permission_flags _permissions;
};
} // namespace models
} // namespace common

#endif
