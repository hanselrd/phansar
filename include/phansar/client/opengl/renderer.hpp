#ifndef PHANSAR_CLIENT_OPENGL_RENDERER_HPP
#define PHANSAR_CLIENT_OPENGL_RENDERER_HPP

#include <phansar/client/graphics/camera.hpp>
#include <phansar/client/opengl/shader.hpp>
#include <phansar/client/opengl/vertex_array.hpp>
#include <phansar/client/window.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
class renderer : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit renderer(window & _window);

    void viewport(std::size_t _x, std::size_t _y, std::size_t _width, std::size_t _height);
    void clear_color(const glm::vec4 & _color) const;
    void clear() const;
    void begin(graphics::camera & _camera);
    void end();
    void
    submit(vertex_array & _va, shader & _shader, const glm::mat4 & _model = glm::mat4{1.0F}) const;

private:
    window *           m_window;
    graphics::camera * m_camera;
};
} // namespace phansar::client::opengl

#endif
