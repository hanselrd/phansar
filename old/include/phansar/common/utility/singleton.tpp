#include <phansar/common/utility/singleton.hpp>

namespace phansar::common::utility {
template <class T>
std::unique_ptr<T> singleton<T>::s_instance = std::unique_ptr<T>{};

template <class T>
template <class... Args>
void singleton<T>::create(Args &&... _args) {
    s_instance = std::make_unique<T>(std::forward<Args>(_args)...);
}

template <class T>
void singleton<T>::destroy() {
    s_instance.reset();
}

template <class T>
auto singleton<T>::instance() -> T * {
    return s_instance.get();
}
} // namespace phansar::common::utility
