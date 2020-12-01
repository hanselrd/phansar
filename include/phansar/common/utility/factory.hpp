#ifndef PHANSAR_COMMON_UTILITY_FACTORY_HPP
#define PHANSAR_COMMON_UTILITY_FACTORY_HPP

namespace phansar::common::utility {
template <class T>
class factory {
public:
    virtual ~factory() = default;

protected:
    template <class U>
    void create(U * _derived);
    void destroy();
    auto instance() const -> const T *;
    auto instance() -> T *;

private:
    std::unique_ptr<T> m_instance;
};
} // namespace phansar::common::utility

#include <phansar/common/utility/factory.tpp>

#endif
