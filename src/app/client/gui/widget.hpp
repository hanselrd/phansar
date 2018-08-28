#ifndef CLIENT_GUI_WIDGET_HPP
#define CLIENT_GUI_WIDGET_HPP

#include <SDL2/SDL.h>
#include <memory>

namespace client {
namespace gui {
class widget {
public:
    explicit widget(const SDL_Rect &rect);
    virtual ~widget() = default;

    virtual void update(double delta) = 0;
    virtual void draw(const std::shared_ptr<SDL_Renderer> &renderer) const = 0;
    const SDL_Rect &get_rect() const;
    void set_rect(const SDL_Rect &rect);

protected:
    bool _active = true;
    bool _enabled = true;
    SDL_Rect _rect;
};
} // namespace gui
} // namespace client

#endif
