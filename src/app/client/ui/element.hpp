#ifndef CLIENT_UI_ELEMENT_HPP
#define CLIENT_UI_ELEMENT_HPP

#include <SDL2/SDL.h>
#include <common/core/types.hpp>
#include <memory>
#include <vector>

namespace client {
namespace ui {
class element {
public:
    element();
    explicit element(const common::core::types::vector2f &position,
                     const common::core::types::vector2u &size,
                     const SDL_Color &color);
    virtual ~element() = default;

    virtual void update() = 0;
    virtual void render() = 0;
    const common::core::types::vector2f &get_position() const;
    void set_position(const common::core::types::vector2f &position);
    const common::core::types::vector2u &get_size() const;
    void set_size(const common::core::types::vector2u &size);
    const SDL_Color &get_color() const;
    void set_color(const SDL_Color &color);
    void add_element(const std::shared_ptr<element> &el);

protected:
    void _set_render_draw_color();
    SDL_Rect *_get_rect();

private:
    std::vector<std::shared_ptr<element>> _elements;
    common::core::types::vector2f _position;
    common::core::types::vector2u _size;
    SDL_Color _color;
    SDL_Rect _rect;
};
} // namespace ui
} // namespace client

#endif
