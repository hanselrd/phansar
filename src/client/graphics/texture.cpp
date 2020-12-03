#include <phansar/client/graphics/texture.hpp>

namespace phansar::client::graphics {
texture::texture(const image & _image, std::uint64_t _flags) {
    if (_image.container()->m_cubeMap) {
        m_handle = bgfx::createTextureCube(
            _image.container()->m_width,
            _image.container()->m_numMips > 1,
            _image.container()->m_numLayers,
            bgfx::TextureFormat::Enum(_image.container()->m_format),
            _flags,
            bgfx::copy(_image.container()->m_data, _image.container()->m_size));
    } else if (_image.container()->m_depth > 1) {
        m_handle = bgfx::createTexture3D(
            _image.container()->m_width,
            _image.container()->m_height,
            _image.container()->m_depth,
            _image.container()->m_numMips > 1,
            bgfx::TextureFormat::Enum(_image.container()->m_format),
            _flags,
            bgfx::copy(_image.container()->m_data, _image.container()->m_size));
    } else if (bgfx::isTextureValid(0,
                                    false,
                                    _image.container()->m_numLayers,
                                    bgfx::TextureFormat::Enum(_image.container()->m_format),
                                    _flags)) {
        m_handle = bgfx::createTexture2D(
            _image.container()->m_width,
            _image.container()->m_height,
            _image.container()->m_numMips > 1,
            _image.container()->m_numLayers,
            bgfx::TextureFormat::Enum(_image.container()->m_format),
            _flags,
            bgfx::copy(_image.container()->m_data, _image.container()->m_size));
    }
}

texture::texture(std::string_view _file_path, std::uint64_t _flags)
    : texture{image{_file_path}, _flags} {}

texture::~texture() {
    if (bgfx::isValid(m_handle)) {
        bgfx::destroy(m_handle);
    }
}

auto texture::handle() const -> const bgfx::TextureHandle & {
    return m_handle;
}

auto texture::handle() -> bgfx::TextureHandle & {
    return const_cast<bgfx::TextureHandle &>(const_cast<const texture *>(this)->handle());
}
} // namespace phansar::client::graphics
