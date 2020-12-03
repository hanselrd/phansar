#ifndef PHANSAR_CLIENT_GRAPHICS_MATERIAL_HPP
#define PHANSAR_CLIENT_GRAPHICS_MATERIAL_HPP

namespace phansar::client::graphics {
struct material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float     shininess;
};
} // namespace phansar::client::graphics

#endif
