#ifndef PHANSAR_CLIENT_GRAPHICS_TEXTURE_HPP
#define PHANSAR_CLIENT_GRAPHICS_TEXTURE_HPP

#include <phansar/client/graphics/image.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::graphics {
class texture : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit texture(const image & _image, std::uint64_t _flags = 0);
    explicit texture(std::string_view _file_path, std::uint64_t _flags = 0);
    ~texture() override;

    [[nodiscard]] auto handle() const -> const bgfx::TextureHandle &;
    auto handle() -> bgfx::TextureHandle &;

private:
    bgfx::TextureHandle m_handle;
};
} // namespace phansar::client::graphics

#endif
