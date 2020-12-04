# cmake-format: off
set(sources
    models/backpack/backpack.obj
    models/icosphere/Ico.fbx.fbx
    shaders/fs_phansar.sc
    shaders/fs_phansar_flat.sc
    shaders/vs_phansar.sc
    textures/blending_transparent_window.png
    textures/container.png
    textures/container_emissive.jpg
    textures/container_specular.png)
# cmake-format: on

add_custom_target(ph_assets)

add_custom_target(
    ph_assets_dirs
    COMMAND ${CMAKE_COMMAND} -E make_directory assets/shaders/dx9
    COMMAND ${CMAKE_COMMAND} -E make_directory assets/shaders/dx11
    COMMAND ${CMAKE_COMMAND} -E make_directory assets/shaders/metal
    COMMAND ${CMAKE_COMMAND} -E make_directory assets/shaders/glsl
    COMMAND ${CMAKE_COMMAND} -E make_directory assets/shaders/spirv
    COMMAND ${CMAKE_COMMAND} -E make_directory assets/shaders/essl
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

set(counter 1)
foreach(source ${sources})
    if(${source} MATCHES "^shaders/(v|f|c)(s_.*)\.sc$")
        set(type "${CMAKE_MATCH_1}")
        set(name "${CMAKE_MATCH_1}${CMAKE_MATCH_2}")

        if(${type} MATCHES "v")
            add_custom_target(
                ph_assets-${counter}
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type vertex --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/dx9/${name}.bin" --platform windows -p
                    vs_3_0 -O 3 || ${CMAKE_COMMAND} -E true
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type vertex --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/dx11/${name}.bin" --platform windows -p
                    vs_5_0 -O 3 || ${CMAKE_COMMAND} -E true
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type vertex --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/metal/${name}.bin" --platform osx -p metal
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type vertex --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/glsl/${name}.bin" --platform linux
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type vertex --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/spirv/${name}.bin" --platform linux -p
                    spirv
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type vertex --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/essl/${name}.bin" --platform android
                DEPENDS ph_assets_dirs
                COMMENT "Compiling ${CMAKE_CURRENT_SOURCE_DIR}/${source} ...")

            add_dependencies(ph_assets ph_assets-${counter})
        elseif(${type} MATCHES "f")
            add_custom_target(
                ph_assets-${counter}
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type fragment --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/dx9/${name}.bin" --platform windows -p
                    ps_3_0 -O 3 || ${CMAKE_COMMAND} -E true
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type fragment --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/dx11/${name}.bin" --platform windows -p
                    ps_5_0 -O 3 || ${CMAKE_COMMAND} -E true
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type fragment --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/metal/${name}.bin" --platform osx -p metal
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type fragment --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/glsl/${name}.bin" --platform linux
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type fragment --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/spirv/${name}.bin" --platform linux -p
                    spirv
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type fragment --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/essl/${name}.bin" --platform android
                DEPENDS ph_assets_dirs
                COMMENT "Compiling ${CMAKE_CURRENT_SOURCE_DIR}/${source} ...")

            add_dependencies(ph_assets ph_assets-${counter})
        elseif(${type} MATCHES "c")
            add_custom_target(
                ph_assets-${counter}
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type compute --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/dx11/${name}.bin" --platform windows -p
                    cs_5_0 -O 1 || ${CMAKE_COMMAND} -E true
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type compute --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/metal/${name}.bin" --platform osx -p metal
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type compute --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/glsl/${name}.bin" --platform linux -p 430
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type compute --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/spirv/${name}.bin" --platform linux -p
                    spirv
                COMMAND
                    "$<TARGET_FILE:shaderc>" -i "${BGFX_DIR}/src" --type compute --varyingdef
                    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc" -f
                    "${CMAKE_CURRENT_SOURCE_DIR}/${source}" -o
                    "${PROJECT_BINARY_DIR}/assets/shaders/essl/${name}.bin" --platform android
                DEPENDS ph_assets_dirs
                COMMENT "Compiling ${CMAKE_CURRENT_SOURCE_DIR}/${source} ...")

            add_dependencies(ph_assets ph_assets-${counter})
        endif()
    else()
        get_filename_component(basename ${source} DIRECTORY)

        add_custom_target(
            ph_assets-${counter}
            COMMAND ${CMAKE_COMMAND} -E make_directory assets/${basename}
            COMMAND ${CMAKE_COMMAND} --verbose -E copy_if_different
                    ${CMAKE_CURRENT_SOURCE_DIR}/${source} assets/${source}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

        add_dependencies(ph_assets ph_assets-${counter})
    endif()

    math(EXPR counter "${counter}+1")
endforeach()

add_dependencies(ph_client ph_assets)
