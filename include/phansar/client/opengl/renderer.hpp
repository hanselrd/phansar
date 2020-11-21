#ifndef PHANSAR_CLIENT_OPENGL_RENDERER_HPP
#define PHANSAR_CLIENT_OPENGL_RENDERER_HPP

#include <phansar/client/opengl/shader.hpp>
#include <phansar/client/opengl/vertex_array.hpp>
#include <phansar/client/window.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
class renderer : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit renderer(window & _window);

    void clear_color(const glm::vec4 & _color) const;
    void clear() const;
    void swap_buffers() const;
    void begin() const;
    void end() const;
    void submit(vertex_array & _va, shader & _shader) const;

private:
    window * m_window;
};
} // namespace phansar::client::opengl

#endif
