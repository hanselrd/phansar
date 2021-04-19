#ifndef PHANSAR_CLIENT_GRAPHICS_IMAGE_HPP
#define PHANSAR_CLIENT_GRAPHICS_IMAGE_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>
#include <phansar/common/utility/pimpl.hpp>
#include <phansar/vendor/bgfx.hpp>

#include <string_view>

namespace phansar::client::graphics {
class image : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit image(std::string_view _file_path);
    image(const image &) = default;
    auto operator=(const image &) -> image & = default;
    image(image &&)                          = default;
    auto operator=(image &&) -> image & = default;
    ~image();

    [[nodiscard]] auto width() const -> std::size_t;
    [[nodiscard]] auto height() const -> std::size_t;
    [[nodiscard]] auto container() const -> bimg::ImageContainer *;

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client::graphics

#endif
