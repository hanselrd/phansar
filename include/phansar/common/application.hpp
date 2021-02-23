#ifndef PHANSAR_COMMON_APPLICATION_HPP
#define PHANSAR_COMMON_APPLICATION_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>
#include <phansar/common/utility/nonsynchronizable.hpp>

namespace phansar::common {
class application : public utility::noncopyable,
                    public utility::nonmovable,
                    public utility::nonsynchronizable {
public:
    application(int _argc, const char * const * _argv);

    virtual void run() = 0;

private:
    std::unique_ptr<tf::Executor> _executor;
};
} // namespace phansar::common

#endif
