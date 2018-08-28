#ifndef COMMON_CORE_CODEC_HPP
#define COMMON_CORE_CODEC_HPP

#include <cppcodec/base32_crockford.hpp>
#include <cppcodec/base64_rfc4648.hpp>
#include <cppcodec/hex_lower.hpp>

namespace common {
namespace core {
namespace codec {
using base64 = cppcodec::base64_rfc4648;
using base32 = cppcodec::base32_crockford;
using base16 = cppcodec::hex_lower;
} // namespace codec
} // namespace core
} // namespace common

#endif
