#include "crypto.hpp"
#include <memory>
#include <plibsys.h>

namespace common {
namespace core {
namespace crypto {
namespace {
std::string _hash(hash_type type, const std::uint8_t *data, std::size_t len) {
    std::shared_ptr<PCryptoHash> ch(p_crypto_hash_new(static_cast<PCryptoHashType>(type)),
                                    p_crypto_hash_free);

    p_crypto_hash_update(ch.get(), data, len);

    auto digest = p_crypto_hash_get_string(ch.get());

    std::string retval(digest);

    p_free(digest);

    return retval;
}
} // namespace

std::string hash(hash_type type, const std::string &str) {
    return _hash(type, reinterpret_cast<const std::uint8_t *>(str.data()), str.length());
}

std::string hash(hash_type type, const std::vector<std::uint8_t> &buf) {
    return _hash(type, buf.data(), buf.size());
}
} // namespace crypto
} // namespace core
} // namespace common
