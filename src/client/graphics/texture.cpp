#include <phansar/client/graphics/texture.hpp>

namespace phansar::client::graphics {
struct texture::impl {
    bgfx::TextureHandle handle;
};

texture::texture(const image & _image, std::uint64_t _flags) : m_impl{bgfx::TextureHandle{}} {
    if (_image.container()->m_cubeMap) {
        m_impl->handle = bgfx::createTextureCube(
            static_cast<std::uint16_t>(_image.container()->m_width),
            _image.container()->m_numMips > 1,
            _image.container()->m_numLayers,
            bgfx::TextureFormat::Enum(_image.container()->m_format),
            _flags,
            bgfx::copy(_image.container()->m_data, _image.container()->m_size));
    } else if (_image.container()->m_depth > 1) {
        m_impl->handle = bgfx::createTexture3D(
            static_cast<std::uint16_t>(_image.container()->m_width),
            static_cast<std::uint16_t>(_image.container()->m_height),
            static_cast<std::uint16_t>(_image.container()->m_depth),
            _image.container()->m_numMips > 1,
            bgfx::TextureFormat::Enum(_image.container()->m_format),
            _flags,
            bgfx::copy(_image.container()->m_data, _image.container()->m_size));
    } else if (bgfx::isTextureValid(0,
                                    false,
                                    _image.container()->m_numLayers,
                                    bgfx::TextureFormat::Enum(_image.container()->m_format),
                                    _flags)) {
        m_impl->handle = bgfx::createTexture2D(
            static_cast<std::uint16_t>(_image.container()->m_width),
            static_cast<std::uint16_t>(_image.container()->m_height),
            _image.container()->m_numMips > 1,
            _image.container()->m_numLayers,
            bgfx::TextureFormat::Enum(_image.container()->m_format),
            _flags,
            bgfx::copy(_image.container()->m_data, _image.container()->m_size));
    }
}

texture::texture(std::string_view _file_path, std::uint64_t _flags)
    : texture{image{_file_path}, _flags} {}

texture::texture(std::uint16_t             _width,
                 std::uint16_t             _height,
                 bgfx::TextureFormat::Enum _format,
                 const void *              _data,
                 std::size_t               _size,
                 std::uint64_t             _flags)
    : m_impl{bgfx::createTexture2D(_width,
                                   _height,
                                   false,
                                   1,
                                   _format,
                                   _flags,
                                   bgfx::copy(_data, static_cast<std::uint32_t>(_size)))} {}

texture::~texture() {
    if (bgfx::isValid(m_impl->handle)) {
        bgfx::destroy(m_impl->handle);
    }
}

auto texture::handle() const -> const bgfx::TextureHandle & {
    return m_impl->handle;
}

auto texture::handle() -> bgfx::TextureHandle & {
    return const_cast<bgfx::TextureHandle &>(const_cast<const texture *>(this)->handle());
}
} // namespace phansar::client::graphics
