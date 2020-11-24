#include <phansar/client/graphics/image.hpp>

namespace phansar::client::graphics {
image::image(std::string_view _file_path) {
    stbi_set_flip_vertically_on_load(1);

    m_data = stbi_load(std::string{_file_path}.c_str(), &m_width, &m_height, &m_channels, 0);
}

image::~image() {
    stbi_image_free(m_data);
}

auto image::width() const -> std::size_t {
    return static_cast<std::size_t>(m_width);
}

auto image::height() const -> std::size_t {
    return static_cast<std::size_t>(m_height);
}

auto image::channels() const -> std::size_t {
    return static_cast<std::size_t>(m_channels);
}

auto image::data() const -> stbi_uc * {
    return m_data;
}
} // namespace phansar::client::graphics
