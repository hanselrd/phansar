#include <phansar/client/graphics/image.hpp>

namespace phansar::client::graphics {
struct image::impl {
    bimg::ImageContainer * container;

    static bx::DefaultAllocator s_allocator;
};

bx::DefaultAllocator image::impl::s_allocator{};

image::image(std::string_view _file_path) : m_impl{nullptr} {
    auto ifs = std::ifstream{std::string{_file_path}, std::ios::binary};
    auto blob =
        std::vector<char>{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    m_impl->container = bimg::imageParse(&m_impl->s_allocator,
                                         blob.data(),
                                         static_cast<std::uint32_t>(blob.size()));
}

image::~image() {
    bimg::imageFree(m_impl->container);
}

auto image::width() const -> std::size_t {
    return static_cast<std::size_t>(m_impl->container->m_width);
}

auto image::height() const -> std::size_t {
    return static_cast<std::size_t>(m_impl->container->m_height);
}

auto image::container() const -> bimg::ImageContainer * {
    return m_impl->container;
}
} // namespace phansar::client::graphics
