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
