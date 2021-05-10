#ifndef PHANSAR_CLIENT_GRAPHICS_MODEL_HPP
#define PHANSAR_CLIENT_GRAPHICS_MODEL_HPP

#include <phansar/client/graphics/material.hpp>
#include <phansar/client/graphics/mesh.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>
#include <phansar/common/utility/pimpl.hpp>

#include <string_view>

namespace phansar::client::graphics {
class model : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit model(std::string_view _file_path);
    model(const model &) = default;
    auto operator=(const model &) -> model & = default;
    model(model &&)                          = default;
    auto operator=(model &&) -> model & = default;
    ~model();

    [[nodiscard]] auto meshes() const -> const std::vector<mesh> &;
    [[nodiscard]] auto materials() const -> const std::vector<material> &;

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client::graphics

#endif
