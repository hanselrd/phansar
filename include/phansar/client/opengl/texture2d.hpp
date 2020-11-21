#ifndef PHANSAR_CLIENT_OPENGL_TEXTURE2D_HPP
#define PHANSAR_CLIENT_OPENGL_TEXTURE2D_HPP

#include <phansar/client/opengl/texture.hpp>

namespace phansar::client::opengl {
class texture2d : public texture {
public:
    explicit texture2d(std::string_view _file_path);
};
} // namespace phansar::client::opengl

#endif
