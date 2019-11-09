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

#ifndef LIBS_COMMON_VENDOR_CODEC_CODEC_HPP
#define LIBS_COMMON_VENDOR_CODEC_CODEC_HPP

#include <cppcodec/base32_crockford.hpp>
#include <cppcodec/base64_rfc4648.hpp>
#include <cppcodec/hex_lower.hpp>

namespace common {
namespace vendor {
namespace codec {
using base64 = cppcodec::base64_rfc4648;
using base32 = cppcodec::base32_crockford;
using base16 = cppcodec::hex_lower;
} // namespace codec
} // namespace vendor
} // namespace common

#endif
