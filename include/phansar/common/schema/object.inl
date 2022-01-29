#include <phansar/common/macro.hpp>
#include <phansar/common/schema/object.hpp>
#include <capnp/serialize-packed.h>
#include <memory>
#include <variant>

namespace phansar::common::schema {
template <class T>
struct object<T>::impl {
    std::variant<std::monostate,
                 std::unique_ptr<capnp::MallocMessageBuilder>,
                 capnp::MallocMessageBuilder *>
                         message{};
    capnp::BuilderFor<T> builder{nullptr};
};

template <class T>
object<T>::object(capnp::MallocMessageBuilder * _message) {
    if (_message != nullptr) {
        m_impl->message.template emplace<capnp::MallocMessageBuilder *>(_message);
        m_impl->builder =
            std::get<capnp::MallocMessageBuilder *>(m_impl->message)->template getRoot<T>();
    } else {
        m_impl->message.template emplace<std::unique_ptr<capnp::MallocMessageBuilder>>(
            new capnp::MallocMessageBuilder{});
        m_impl->builder = std::get<std::unique_ptr<capnp::MallocMessageBuilder>>(m_impl->message)
                              ->template getRoot<T>();
    }
}

template <class T>
object<T>::object(const std::vector<kj::byte> & _bytes, capnp::MallocMessageBuilder * _message)
    : object{_message} {
    auto stream = kj::ArrayInputStream{kj::arrayPtr(_bytes.data(), _bytes.size())};
    auto reader = capnp::PackedMessageReader{stream};

    if (std::holds_alternative<std::unique_ptr<capnp::MallocMessageBuilder>>(m_impl->message)) {
        auto & message = std::get<std::unique_ptr<capnp::MallocMessageBuilder>>(m_impl->message);
        message->setRoot(reader.getRoot<T>());
        m_impl->builder = message->template getRoot<T>();
    } else if (std::holds_alternative<capnp::MallocMessageBuilder *>(m_impl->message)) {
        auto message = std::get<capnp::MallocMessageBuilder *>(m_impl->message);
        message->setRoot(reader.getRoot<T>());
        m_impl->builder = message->template getRoot<T>();
    }
}

template <class T>
object<T>::object(capnp::ReaderFor<T> _reader, capnp::MallocMessageBuilder * _message)
    : object{_message} {
    if (std::holds_alternative<std::unique_ptr<capnp::MallocMessageBuilder>>(m_impl->message)) {
        auto & message = std::get<std::unique_ptr<capnp::MallocMessageBuilder>>(m_impl->message);
        message->setRoot(_reader);
        m_impl->builder = message->template getRoot<T>();
    } else if (std::holds_alternative<capnp::MallocMessageBuilder *>(m_impl->message)) {
        auto message = std::get<capnp::MallocMessageBuilder *>(m_impl->message);
        message->setRoot(_reader);
        m_impl->builder = message->template getRoot<T>();
    }
}

template <class T>
object<T>::object(capnp::BuilderFor<T> _builder, capnp::MallocMessageBuilder * _message) {
    if (_message != nullptr) {
        m_impl->message.template emplace<capnp::MallocMessageBuilder *>(_message);
    }

    m_impl->builder = _builder;
}

template <class T>
object<T>::object(object && _other) noexcept = default;

template <class T>
auto object<T>::operator=(object && _other) noexcept -> object & = default;

template <class T>
object<T>::~object() = default;

template <class T>
auto object<T>::is_self_contained() const -> bool {
    return std::holds_alternative<std::unique_ptr<capnp::MallocMessageBuilder>>(m_impl->message);
}

template <class T>
auto object<T>::get_builder() -> capnp::BuilderFor<T> {
    return m_impl->builder;
}

template <class T>
auto object<T>::get_reader() const -> capnp::ReaderFor<T> {
    return m_impl->builder.asReader();
}

template <class T>
auto object<T>::get_bytes() const -> std::vector<kj::byte> {
    PH_ASSERT(! std::holds_alternative<std::monostate>(m_impl->message));

    if (std::holds_alternative<std::unique_ptr<capnp::MallocMessageBuilder>>(m_impl->message)) {
        auto & message = std::get<std::unique_ptr<capnp::MallocMessageBuilder>>(m_impl->message);
        auto   stream  = kj::VectorOutputStream{};
        capnp::writePackedMessage(stream, *message);
        auto array = stream.getArray();
        return {array.begin(), array.end()};
    }

    if (std::holds_alternative<capnp::MallocMessageBuilder *>(m_impl->message)) {
        auto message = std::get<capnp::MallocMessageBuilder *>(m_impl->message);
        auto stream  = kj::VectorOutputStream{};
        capnp::writePackedMessage(stream, *message);
        auto array = stream.getArray();
        return {array.begin(), array.end()};
    }

    return {};
}
} // namespace phansar::common::schema
