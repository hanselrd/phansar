#ifndef PHANSAR_CLIENT_GRAPHICS_RENDERER_HPP
#define PHANSAR_CLIENT_GRAPHICS_RENDERER_HPP

#include <phansar/client/window.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::graphics {
class renderer : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit renderer(window & _window);
    ~renderer() override;
};
} // namespace phansar::client::graphics

#endif
