#include <phansar/client/graphics/image.hpp>

namespace phansar::client::graphics {
bx::DefaultAllocator image::s_allocator{};

image::image(std::string_view _file_path) {
    auto ifs = std::ifstream{std::string{_file_path}, std::ios::binary};
    auto blob =
        std::vector<char>{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    m_container =
        bimg::imageParse(&s_allocator, blob.data(), static_cast<std::uint32_t>(blob.size()));
}

image::~image() {
    bimg::imageFree(m_container);
}

auto image::width() const -> std::size_t {
    return static_cast<std::size_t>(m_container->m_width);
}

auto image::height() const -> std::size_t {
    return static_cast<std::size_t>(m_container->m_height);
}

auto image::container() const -> bimg::ImageContainer * {
    return m_container;
}
} // namespace phansar::client::graphics
