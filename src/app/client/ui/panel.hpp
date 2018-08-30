#ifndef CLIENT_UI_PANEL_HPP
#define CLIENT_UI_PANEL_HPP

#include "element.hpp"

namespace client {
namespace ui {
class panel : public element {
public:
    explicit panel(const common::core::types::vector2f &position,
                   const common::core::types::vector2u &size,
                   const SDL_Color &color);

    void update() override;
    void render() override;
};
} // namespace ui
} // namespace client

#endif
