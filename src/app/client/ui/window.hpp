#ifndef CLIENT_UI_WINDOW_HPP
#define CLIENT_UI_WINDOW_HPP

#include "element.hpp"
#include "panel.hpp"

namespace client {
namespace ui {
class window : public element {
public:
    explicit window(const common::core::types::vector2f &position,
                    const common::core::types::vector2u &size,
                    const SDL_Color &color);

    void update() override;
    void render() override;

private:
    panel _titlebar;
    panel _body;
};
} // namespace ui
} // namespace client

#endif
