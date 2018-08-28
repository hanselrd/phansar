#ifndef COMMON_CORE_CRYPTO_HPP
#define COMMON_CORE_CRYPTO_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace common {
namespace core {
namespace crypto {
enum class hash_type {
    MD5,
    SHA1,
    SHA2_224,
    SHA2_256,
    SHA2_384,
    SHA2_512,
    SHA3_224,
    SHA3_256,
    SHA3_384,
    SHA3_512,
    GOST
};

std::string hash(hash_type type, const std::string &str);
std::string hash(hash_type type, const std::vector<std::uint8_t> &buf);
} // namespace crypto
} // namespace core
} // namespace common

#endif
