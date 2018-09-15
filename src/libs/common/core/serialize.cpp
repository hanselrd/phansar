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

#include "serialize.hpp"
#include "SDL2/SDL_endian.h"

namespace common {
namespace core {
namespace serialize {
std::uint16_t hton16(std::uint16_t host) {
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        return SDL_Swap16(host);
    }
    return host;
}

std::uint32_t hton32(std::uint32_t host) {
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        return SDL_Swap32(host);
    }
    return host;
}

std::uint64_t hton64(std::uint64_t host) {
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        return SDL_Swap64(host);
    }
    return host;
}

float htonf(float host) {
    union {
        float f;
        std::uint32_t ui32;
    } swapper;
    swapper.f = host;
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        swapper.ui32 = SDL_Swap32(swapper.ui32);
    }
    return swapper.f;
}

double htond(double host) {
    union {
        double d;
        std::uint64_t ui64;
    } swapper;
    swapper.d = host;
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        swapper.ui64 = SDL_Swap64(swapper.ui64);
    }
    return swapper.d;
}

std::uint16_t ntoh16(std::uint16_t net) {
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        return SDL_Swap16(net);
    }
    return net;
}

std::uint32_t ntoh32(std::uint32_t net) {
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        return SDL_Swap32(net);
    }
    return net;
}

std::uint64_t ntoh64(std::uint64_t net) {
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        return SDL_Swap64(net);
    }
    return net;
}

float ntohf(float net) {
    union {
        float f;
        std::uint32_t ui32;
    } swapper;
    swapper.f = net;
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        swapper.ui32 = SDL_Swap32(swapper.ui32);
    }
    return swapper.f;
}

double ntohd(double net) {
    union {
        double d;
        std::uint64_t ui64;
    } swapper;
    swapper.d = net;
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
        swapper.ui64 = SDL_Swap64(swapper.ui64);
    }
    return swapper.d;
}
} // namespace serialize
} // namespace core
} // namespace common
