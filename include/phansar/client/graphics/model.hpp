#ifndef PHANSAR_CLIENT_GRAPHICS_MODEL_HPP
#define PHANSAR_CLIENT_GRAPHICS_MODEL_HPP

#include <phansar/client/graphics/material.hpp>
#include <phansar/client/graphics/mesh.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::graphics {
class model : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit model(std::string_view _file_path);

    [[nodiscard]] auto meshes() const -> const std::vector<mesh> &;
    [[nodiscard]] auto materials() const -> const std::vector<material> &;

private:
    std::vector<mesh>     m_meshes{};
    std::vector<material> m_materials{};
};
} // namespace phansar::client::graphics

#endif
