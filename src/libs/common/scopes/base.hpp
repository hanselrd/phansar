#ifndef COMMON_SCOPES_BASE_HPP
#define COMMON_SCOPES_BASE_HPP

namespace common {
namespace scopes {
namespace internal {
template <class T> class base {
public:
    base() {
        ++_guards;
    }

    virtual ~base() {
        --_guards;
    }

protected:
    static unsigned _guards;
};

template <class T> unsigned base<T>::_guards = 0;
} // namespace internal
} // namespace scopes
} // namespace common

#endif
