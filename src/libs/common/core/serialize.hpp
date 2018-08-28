#ifndef COMMON_CORE_SERIALIZE_HPP
#define COMMON_CORE_SERIALIZE_HPP

#include <cstdint>

namespace common {
namespace core {
namespace serialize {
std::uint16_t hton16(std::uint16_t host);
std::uint32_t hton32(std::uint32_t host);
std::uint64_t hton64(std::uint64_t host);
float htonf(float host);
double htond(double host);

std::uint16_t ntoh16(std::uint16_t net);
std::uint32_t ntoh32(std::uint32_t net);
std::uint64_t ntoh64(std::uint64_t net);
float ntohf(float net);
double ntohd(double net);
} // namespace serialize
} // namespace core
} // namespace common

#endif
