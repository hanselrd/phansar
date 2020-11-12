#ifndef PHANSAR_COMMON_UTILITY_SINGLETON_HPP
#define PHANSAR_COMMON_UTILITY_SINGLETON_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::common::utility {
template <class T>
class singleton : public noncopyable, public nonmovable {
public:
    ~singleton() override = default;

    template <class... Args>
    static void create(Args &&... _args);
    static void destroy();
    static auto instance() -> T *;

protected:
    singleton() = default;

private:
    static std::unique_ptr<T> s_instance;
};
} // namespace phansar::common::utility

#include <phansar/common/utility/detail/singleton.tpp>

#endif
