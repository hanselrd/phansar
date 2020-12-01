#include <phansar/common/utility/factory.hpp>

namespace phansar::common::utility {
template <class T>
template <class U>
void factory<T>::create(U * _derived) {
    static_assert(std::is_base_of_v<T, U>);

    m_instance = std::unique_ptr<T>{_derived};
}

template <class T>
void factory<T>::destroy() {
    m_instance.reset();
}

template <class T>
auto factory<T>::instance() const -> const T * {
    return m_instance.get();
}

template <class T>
auto factory<T>::instance() -> T * {
    return const_cast<T *>(const_cast<const factory<T> *>(this)->instance());
}
} // namespace phansar::common::utility
