#ifndef COMMON_BITMASKS_PERMISSION_HPP
#define COMMON_BITMASKS_PERMISSION_HPP

#include <cstdint>
#include <type_traits>

namespace common {
namespace bitmasks {
enum permissions : std::uint8_t {
    NONE = 0,
    VETERAN = (1 << 0),
    DONOR = (1 << 1),
    INTERN = (1 << 2),
    ADVISOR = (1 << 3),
    MODERATOR = (1 << 4),
    ADMINISTRATOR = (1 << 5),
    OWNER = (1 << 6),
    ROOT = (1 << 7)
};

using permission_flags = std::underlying_type_t<permissions>;
} // namespace bitmasks
} // namespace common

#endif
