#ifndef PHANSAR_CLIENT_WINDOW_HPP
#define PHANSAR_CLIENT_WINDOW_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client {
class window : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    window(std::size_t _width, std::size_t _height, std::string_view _title);
    ~window() override;

    auto open() -> bool;
    void poll_events();
    auto get() -> GLFWwindow *;

private:
    static std::uint8_t s_instance_count;
    GLFWwindow *        m_window;
};
} // namespace phansar::client

#endif
