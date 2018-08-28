#ifndef CLIENT_GUI_WINDOW_HPP
#define CLIENT_GUI_WINDOW_HPP

#include "widget.hpp"
#include <memory>
#include <vector>

namespace client {
namespace gui {
class window : public widget {
public:
    explicit window(const SDL_Rect &rect);

    void update(double delta) override;
    void draw(const std::shared_ptr<SDL_Renderer> &renderer) const override;
    void add_widget(std::unique_ptr<widget> w);

private:
    std::vector<std::unique_ptr<widget>> _widgets;
};
} // namespace gui
} // namespace client

#endif
