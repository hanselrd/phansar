#ifndef PHANSAR_CLIENT_WINDOW_HPP
#define PHANSAR_CLIENT_WINDOW_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::client {
class window : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    window(std::size_t _width, std::size_t _height, std::string_view _title);
    window(const window &) = default;
    auto operator=(const window &) -> window & = default;
    window(window &&)                          = default;
    auto operator=(window &&) -> window & = default;
    ~window();

    auto open() -> bool;
    void update();
    auto ndt() -> void *;
    auto nwh() -> void *;

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client

#endif
