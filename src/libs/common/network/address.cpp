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

#include "address.hpp"
#include <vector>

namespace common {
namespace network {
address::address(const std::string &host, std::uint16_t port) {
    if (host.empty()) {
        _address.host = ENET_HOST_ANY;
    } else {
        enet_address_set_host(&_address, host.c_str());
    }

    if (port == 0) {
        _address.port = ENET_PORT_ANY;
    } else {
        _address.port = port;
    }
}

address::address(ENetAddress address) : _address(address) {
}

address::operator const ENetAddress *() const {
    return &_address;
}

std::string address::get_host() const {
    std::vector<char> buffer(16, '\0');
    enet_address_get_host_ip(&_address, buffer.data(), buffer.size());
    return std::string(buffer.begin(), buffer.end());
}

std::uint16_t address::get_port() const {
    return _address.port;
}
} // namespace network
} // namespace common
