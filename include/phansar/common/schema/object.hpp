#ifndef PHANSAR_COMMON_SCHEMA_OBJECT_HPP
#define PHANSAR_COMMON_SCHEMA_OBJECT_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <capnp/message.h>
#include <vector>

namespace phansar::common::schema {
template <class T>
class object {
public:
    explicit object(capnp::MallocMessageBuilder * _message = nullptr);
    explicit object(const std::vector<kj::byte> & _bytes,
                    capnp::MallocMessageBuilder * _message = nullptr);
    explicit object(capnp::ReaderFor<T> _reader, capnp::MallocMessageBuilder * _message = nullptr);
    explicit object(capnp::BuilderFor<T>          _builder,
                    capnp::MallocMessageBuilder * _message = nullptr);
    object(const object & _other)                     = delete;
    auto operator=(const object & _other) -> object & = delete;
    object(object && _other) noexcept;
    auto operator=(object && _other) noexcept -> object &;
    virtual ~object();

    [[nodiscard]] auto is_self_contained() const -> bool;
    auto               get_builder() -> capnp::BuilderFor<T>;
    [[nodiscard]] auto get_reader() const -> capnp::ReaderFor<T>;
    [[nodiscard]] auto get_bytes() const -> std::vector<kj::byte>;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::schema

#include <phansar/common/schema/object.inl>

#endif
