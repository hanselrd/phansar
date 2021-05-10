#ifndef PHANSAR_VENDOR_CAPNPROTO_HPP
#define PHANSAR_VENDOR_CAPNPROTO_HPP

#include <phansar/vendor/hedley.hpp>

#ifdef HEDLEY_MSVC_VERSION
    #pragma warning(push, 0)
#endif

#include <capnp/ez-rpc.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <kj/debug.h>

#ifdef HEDLEY_MSVC_VERSION
    #pragma warning(pop)
#endif

#endif
