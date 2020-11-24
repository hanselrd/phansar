#ifndef PHANSAR_CLIENT_GRAPHICS_IMAGE_HPP
#define PHANSAR_CLIENT_GRAPHICS_IMAGE_HPP

#include <phansar/common/utility/noncopyable.hpp>

namespace phansar::client::graphics {
class image : public common::utility::noncopyable {
public:
    explicit image(std::string_view _file_path);
    ~image() override;

    [[nodiscard]] auto width() const -> std::size_t;
    [[nodiscard]] auto height() const -> std::size_t;
    [[nodiscard]] auto channels() const -> std::size_t;
    [[nodiscard]] auto data() const -> stbi_uc *;

private:
    int       m_width    = 0;
    int       m_height   = 0;
    int       m_channels = 0;
    stbi_uc * m_data     = nullptr;
};
} // namespace phansar::client::graphics

#endif
