#ifndef PHANSAR_CLIENT_GRAPHICS_IMAGE_HPP
#define PHANSAR_CLIENT_GRAPHICS_IMAGE_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::graphics {
class image : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit image(std::string_view _file_path);
    ~image();

    [[nodiscard]] auto width() const -> std::size_t;
    [[nodiscard]] auto height() const -> std::size_t;
    [[nodiscard]] auto container() const -> bimg::ImageContainer *;

private:
    static bx::DefaultAllocator s_allocator;
    bimg::ImageContainer *      m_container = nullptr;
};
} // namespace phansar::client::graphics

#endif
