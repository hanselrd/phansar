#ifndef PHANSAR_CLIENT_OPENGL_MACROS_HPP
#define PHANSAR_CLIENT_OPENGL_MACROS_HPP

#include <phansar/common/macros.hpp>

#define GL_CALL(_call)                                                                             \
    while (glGetError() != GL_NO_ERROR)                                                            \
        ;                                                                                          \
    PH_LOG_TRACE("OpenGL: {}", #_call);                                                            \
    _call;                                                                                         \
    while (auto error = glGetError()) {                                                            \
        PH_LOG_ERROR("OpenGL ({:#0{}x}): {}", error, sizeof(GLenum) + 2, #_call);                  \
        std::terminate();                                                                          \
    }

#endif
