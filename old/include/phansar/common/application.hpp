#ifndef PHANSAR_COMMON_APPLICATION_HPP
#define PHANSAR_COMMON_APPLICATION_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>
#include <phansar/common/utility/nonsynchronizable.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common {
class application : public utility::noncopyable,
                    public utility::nonmovable,
                    public utility::nonsynchronizable {
public:
    application(int _argc, const char * const * _argv);
    application(const application &) = default;
    auto operator=(const application &) -> application & = default;
    application(application &&)                          = default;
    auto operator=(application &&) -> application & = default;
    ~application();

    virtual void run() = 0;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common

#endif
