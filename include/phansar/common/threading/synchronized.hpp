#ifndef PHANSAR_COMMON_THREADING_SYNCHRONIZED_HPP
#define PHANSAR_COMMON_THREADING_SYNCHRONIZED_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonsynchronizable.hpp>

namespace phansar::common::threading {
template <class T>
class synchronized {
    static_assert(! std::is_base_of_v<utility::nonsynchronizable, T>, "T must be synchronizable");

public:
    struct write_tag {};
    struct read_tag {};

    template <class Tag>
    class proxy : public utility::noncopyable {
        static_assert(std::is_same_v<Tag, write_tag> || std::is_same_v<Tag, read_tag>,
                      "Tag must be write_tag or read_tag");

        friend class synchronized;

    public:
        proxy(proxy && _other) noexcept;
        auto operator=(proxy && _other) noexcept -> proxy &;
        ~proxy();

        template <class U = Tag>
        auto get() const -> std::enable_if_t<std::is_same_v<U, write_tag>, T *>;
        template <class U = Tag>
        auto operator*() const -> std::enable_if_t<std::is_same_v<U, write_tag>, T &>;
        template <class U = Tag>
        auto operator->() const -> std::enable_if_t<std::is_same_v<U, write_tag>, T *>;
        template <class U = Tag>
        auto get() const -> std::enable_if_t<std::is_same_v<U, read_tag>, const T *>;
        template <class U = Tag>
        auto operator*() const -> std::enable_if_t<std::is_same_v<U, read_tag>, const T &>;
        template <class U = Tag>
        auto operator->() const -> std::enable_if_t<std::is_same_v<U, read_tag>, const T *>;

    private:
        proxy(T & _obj, std::shared_mutex & _mutex);

        T *                 m_obj_p;
        std::shared_mutex * m_mutex_p;
    };

    template <class... Args>
    explicit synchronized(Args &&... _args);

    auto lock() -> proxy<write_tag>;
    auto try_lock() -> std::optional<proxy<write_tag>>;
    auto lock_shared() -> proxy<read_tag>;
    auto try_lock_shared() -> std::optional<proxy<read_tag>>;

private:
    T                 m_obj;
    std::shared_mutex m_mutex;
};
} // namespace phansar::common::threading

#include <phansar/common/threading/synchronized.tpp>

#endif
