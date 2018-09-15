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

#ifndef COMMON_NETWORK_ADDRESS_HPP
#define COMMON_NETWORK_ADDRESS_HPP

#include <cstdint>
#include <enet/enet.h>
#include <string>

namespace common {
namespace network {
class address {
public:
    address() = default;
    explicit address(const std::string &host, std::uint16_t port);
    explicit address(ENetAddress address);

    operator const ENetAddress *() const;
    std::string get_host() const;
    std::uint16_t get_port() const;

private:
    ENetAddress _address;
};
} // namespace network
} // namespace common

#endif
