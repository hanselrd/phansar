#ifndef PHANSAR_CLIENT_GRAPHICS_RENDERER_HPP
#define PHANSAR_CLIENT_GRAPHICS_RENDERER_HPP

#include <phansar/client/graphics/camera.hpp>
#include <phansar/client/graphics/mesh.hpp>
#include <phansar/client/graphics/shader.hpp>
#include <phansar/client/window.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::client::graphics {
class renderer : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit renderer(window & _window);
    renderer(const renderer &) = default;
    auto operator=(const renderer &) -> renderer & = default;
    renderer(renderer &&)                          = default;
    auto operator=(renderer &&) -> renderer & = default;
    ~renderer();

    void view_clear(std::uint32_t _rgba, float _depth = 1.0F, std::uint8_t _stencil = 0);
    void touch();
    void begin(camera & _camera);
    void submit(const mesh &      _mesh,
                shader &          _shader,
                const glm::mat4 & _model   = glm::mat4{1.0F},
                std::uint32_t     _depth   = 0,
                std::uint32_t     _stencil = BGFX_STENCIL_NONE,
                std::uint64_t     _state   = BGFX_STATE_DEFAULT |
                                       BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA,
                                                             BGFX_STATE_BLEND_INV_SRC_ALPHA),
                std::uint8_t _flags = BGFX_DISCARD_ALL);
    void end();
    void flush();

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client::graphics

#endif
