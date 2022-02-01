function(ph_add_file_pass)
    cmake_parse_arguments(
        ARG
        "PRE_REDIRECT_OUTPUT;REDIRECT_OUTPUT;POST_REDIRECT_OUTPUT;PRE_SEQUENTIAL;SEQUENTIAL;POST_SEQUENTIAL"
        "NAME"
        "GROUPS;PRE_COMMANDS;COMMANDS;POST_COMMANDS;GLOBS;FILES;DEPENDENCIES"
        ${ARGN})

    if(ARG_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "called with unrecognized parameters: ${ARG_UNPARSED_ARGUMENTS}")
    endif()

    file(
        GLOB_RECURSE
        files
        CONFIGURE_DEPENDS
        ${ARG_GLOBS})
    list(APPEND files ${ARG_FILES})

    if(ARG_PRE_COMMANDS)
        set(pre_commands ${ARG_PRE_COMMANDS})

        list(TRANSFORM pre_commands REPLACE "@TMP_DIR@" "${CMAKE_BINARY_DIR}/file-pass/${ARG_NAME}")

        add_custom_target(
            pre-${ARG_NAME}
            COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/file-pass/${ARG_NAME}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/file-pass/${ARG_NAME}
            COMMAND
                # cmake-format: off
                ${CMAKE_COMMAND}
                -DCOMMANDS:STRING="${pre_commands}"
                -DWORKING_DIRECTORY:STRING=${CMAKE_SOURCE_DIR}
                -DREDIRECT_OUTPUT:BOOL=${ARG_PRE_REDIRECT_OUTPUT}
                -DSEQUENTIAL:BOOL=${ARG_PRE_SEQUENTIAL}
                -P ${CMAKE_SOURCE_DIR}/cmake/scripts/execute-process.cmake
                # cmake-format: on
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running ${ARG_NAME} file pass ...")
    else()
        add_custom_target(
            pre-${ARG_NAME}
            COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/file-pass/${ARG_NAME}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/file-pass/${ARG_NAME})
    endif()

    add_custom_target(intra-${ARG_NAME} DEPENDS pre-${ARG_NAME})

    if(ARG_DEPENDENCIES)
        add_dependencies(pre-${ARG_NAME} ${ARG_DEPENDENCIES})
    endif()

    foreach(file IN LISTS files)
        # cmake_path(RELATIVE_PATH file BASE_DIRECTORY ${CMAKE_SOURCE_DIR})
        # cmake-format: off
        cmake_path(GET file ROOT_NAME root_name)
        cmake_path(GET file ROOT_DIRECTORY root_directory)
        cmake_path(GET file ROOT_PATH root_path)
        cmake_path(GET file FILENAME filename)
        cmake_path(GET file EXTENSION extension)
        cmake_path(GET file EXTENSION LAST_ONLY last_extension)
        cmake_path(GET file STEM stem)
        cmake_path(GET file STEM LAST_ONLY last_stem)
        cmake_path(GET file RELATIVE_PART relative_part)
        cmake_path(GET file PARENT_PATH parent_path)
        # cmake-format: on

        string(SHA1 hash ${file})

        set(commands ${ARG_COMMANDS})

        list(TRANSFORM commands REPLACE "@HASH@" "${hash}")
        list(TRANSFORM commands REPLACE "@TMP_DIR@" "${CMAKE_BINARY_DIR}/file-pass/${ARG_NAME}")
        list(TRANSFORM commands REPLACE "@INPUT_FILE@" "${file}")
        list(TRANSFORM commands REPLACE "@INPUT_ROOT_NAME@" "${root_name}")
        list(TRANSFORM commands REPLACE "@INPUT_ROOT_DIRECTORY@" "${root_directory}")
        list(TRANSFORM commands REPLACE "@INPUT_ROOT_PATH@" "${root_path}")
        list(TRANSFORM commands REPLACE "@INPUT_FILENAME@" "${filename}")
        list(TRANSFORM commands REPLACE "@INPUT_EXTENSION@" "${extension}")
        list(TRANSFORM commands REPLACE "@INPUT_LAST_EXTENSION@" "${last_extension}")
        list(TRANSFORM commands REPLACE "@INPUT_STEM@" "${stem}")
        list(TRANSFORM commands REPLACE "@INPUT_LAST_STEM@" "${last_stem}")
        list(TRANSFORM commands REPLACE "@INPUT_RELATIVE_PART@" "${relative_part}")
        list(TRANSFORM commands REPLACE "@INPUT_PARENT_PATH@" "${parent_path}")

        add_custom_target(
            intra-${ARG_NAME}-${hash}
            COMMAND
                # cmake-format: off
                ${CMAKE_COMMAND}
                -DCOMMANDS:STRING="${commands}"
                -DWORKING_DIRECTORY:STRING=${CMAKE_SOURCE_DIR}
                -DREDIRECT_OUTPUT:BOOL=${ARG_REDIRECT_OUTPUT}
                -DSEQUENTIAL:BOOL=${ARG_SEQUENTIAL}
                -P ${CMAKE_SOURCE_DIR}/cmake/scripts/execute-process.cmake
                # cmake-format: on
            DEPENDS pre-${ARG_NAME}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running ${ARG_NAME} file pass on ${file} ...")
        add_dependencies(intra-${ARG_NAME} intra-${ARG_NAME}-${hash})
    endforeach()

    add_custom_target(${ARG_NAME})

    if(ARG_POST_COMMANDS)
        set(post_commands ${ARG_POST_COMMANDS})

        list(TRANSFORM post_commands REPLACE "@TMP_DIR@"
                                             "${CMAKE_BINARY_DIR}/file-pass/${ARG_NAME}")

        add_custom_target(
            post-${ARG_NAME}
            COMMAND
                # cmake-format: off
                ${CMAKE_COMMAND}
                -DCOMMANDS:STRING="${post_commands}"
                -DWORKING_DIRECTORY:STRING=${CMAKE_SOURCE_DIR}
                -DREDIRECT_OUTPUT:BOOL=${ARG_POST_REDIRECT_OUTPUT}
                -DSEQUENTIAL:BOOL=${ARG_POST_SEQUENTIAL}
                -P ${CMAKE_SOURCE_DIR}/cmake/scripts/execute-process.cmake
                # cmake-format: on
            DEPENDS intra-${ARG_NAME}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running ${ARG_NAME} file pass ...")
        add_dependencies(${ARG_NAME} post-${ARG_NAME})
    else()
        add_dependencies(${ARG_NAME} intra-${ARG_NAME})
    endif()

    if(ARG_GROUPS)
        foreach(group IN LISTS ARG_GROUPS)
            if(NOT TARGET ${group})
                add_custom_target(${group})
            endif()
            add_dependencies(${group} ${ARG_NAME})
        endforeach()
    endif()
endfunction()

find_program(PIPENV_EXECUTABLE pipenv REQUIRED)

ph_add_file_pass(
    NAME codegen
    COMMANDS
        "${PIPENV_EXECUTABLE} run cog --verbosity=0 -I ${CMAKE_SOURCE_DIR}/codegen -r @INPUT_FILE@"
    GLOBS "include/*.cog.hpp"
          "include/*.cog.inl"
          "include/*.cog.cpp"
          "src/*.cog.hpp"
          "src/*.cog.inl"
          "src/*.cog.cpp"
          "src/*.cog.cpp.in"
          "src/*.cog.capnp"
          "test/*.cog.hpp"
          "test/*.cog.inl"
          "test/*.cog.cpp"
          "vendor/*.cog.hpp"
          "vendor/*.cog.inl"
          "vendor/*.cog.cpp")

ph_add_file_pass(
    NAME clean-codegen
    COMMANDS
        "${PIPENV_EXECUTABLE} run cog --verbosity=0 -I ${CMAKE_SOURCE_DIR}/codegen -rx @INPUT_FILE@"
    GLOBS "include/*.cog.hpp"
          "include/*.cog.inl"
          "include/*.cog.cpp"
          "src/*.cog.hpp"
          "src/*.cog.inl"
          "src/*.cog.cpp"
          "src/*.cog.cpp.in"
          "src/*.cog.capnp"
          "test/*.cog.hpp"
          "test/*.cog.inl"
          "test/*.cog.cpp"
          "vendor/*.cog.hpp"
          "vendor/*.cog.inl"
          "vendor/*.cog.cpp")

ph_add_file_pass(
    NAME assets-shaders-vertex
    GROUPS assets assets-shaders
    PRE_COMMANDS
        $<$<BOOL:${CMAKE_CROSSCOMPILING}>:"\"${PIPENV_EXECUTABLE} run ${CMAKE_SOURCE_DIR}/tools/flock.py ${CMAKE_BINARY_DIR}/host --directory -c ${CMAKE_COMMAND} \\-B ${CMAKE_BINARY_DIR}/host \\-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}\"">
        $<$<BOOL:${CMAKE_CROSSCOMPILING}>:"\"${PIPENV_EXECUTABLE} run ${CMAKE_SOURCE_DIR}/tools/flock.py ${CMAKE_BINARY_DIR}/host --directory -c ${CMAKE_COMMAND} \\--build ${CMAKE_BINARY_DIR}/host \\--target shaderc\"">
        "${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/shaders"
    COMMANDS
        $<$<PLATFORM_ID:Windows>:"\"$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx9.bin --platform windows -p vs_3_0 -O 3\"">
        $<$<PLATFORM_ID:Windows>:"\"$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx11.bin --platform windows -p vs_5_0 -O 3\"">
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-metal.bin --platform osx -p metal"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-glsl.bin --platform linux"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-spirv.bin --platform linux -p spirv"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-essl.bin --platform android"
    GLOBS "assets/shaders/vs_*.sc"
    PRE_SEQUENTIAL
    SEQUENTIAL)

ph_add_file_pass(
    NAME assets-shaders-fragment
    GROUPS assets assets-shaders
    PRE_COMMANDS
        $<$<BOOL:${CMAKE_CROSSCOMPILING}>:"\"${PIPENV_EXECUTABLE} run ${CMAKE_SOURCE_DIR}/tools/flock.py ${CMAKE_BINARY_DIR}/host --directory -c ${CMAKE_COMMAND} \\-B ${CMAKE_BINARY_DIR}/host \\-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}\"">
        $<$<BOOL:${CMAKE_CROSSCOMPILING}>:"\"${PIPENV_EXECUTABLE} run ${CMAKE_SOURCE_DIR}/tools/flock.py ${CMAKE_BINARY_DIR}/host --directory -c ${CMAKE_COMMAND} \\--build ${CMAKE_BINARY_DIR}/host \\--target shaderc\"">
        "${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/shaders"
    COMMANDS
        $<$<PLATFORM_ID:Windows>:"\"$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx9.bin --platform windows -p ps_3_0 -O 3\"">
        $<$<PLATFORM_ID:Windows>:"\"$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx11.bin --platform windows -p ps_5_0 -O 3\"">
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-metal.bin --platform osx -p metal"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-glsl.bin --platform linux"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-spirv.bin --platform linux -p spirv"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-essl.bin --platform android"
    GLOBS "assets/shaders/fs_*.sc"
    PRE_SEQUENTIAL
    SEQUENTIAL)

ph_add_file_pass(
    NAME assets-shaders-compute
    GROUPS assets assets-shaders
    PRE_COMMANDS
        $<$<BOOL:${CMAKE_CROSSCOMPILING}>:"\"${PIPENV_EXECUTABLE} run ${CMAKE_SOURCE_DIR}/tools/flock.py ${CMAKE_BINARY_DIR}/host --directory -c ${CMAKE_COMMAND} \\-B ${CMAKE_BINARY_DIR}/host \\-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}\"">
        $<$<BOOL:${CMAKE_CROSSCOMPILING}>:"\"${PIPENV_EXECUTABLE} run ${CMAKE_SOURCE_DIR}/tools/flock.py ${CMAKE_BINARY_DIR}/host --directory -c ${CMAKE_COMMAND} \\--build ${CMAKE_BINARY_DIR}/host \\--target shaderc\"">
        "${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/shaders"
    COMMANDS
        $<$<PLATFORM_ID:Windows>:"\"$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx11.bin --platform windows -p cs_5_0 -O 1\"">
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-metal.bin --platform osx -p metal"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-glsl.bin --platform linux -p 430"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-spirv.bin --platform linux -p spirv"
        "$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,${CMAKE_BINARY_DIR}/host/bin/shaderc,$<TARGET_FILE:shaderc>> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_SOURCE_DIR}/assets/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-essl.bin --platform android"
    GLOBS "assets/shaders/cs_*.sc"
    PRE_SEQUENTIAL
    SEQUENTIAL)

foreach(
    asset_type
    "fonts"
    "maps"
    "models"
    "textures"
    "tilesets")
    ph_add_file_pass(
        NAME assets-${asset_type}
        GROUPS assets
        PRE_COMMANDS "${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/${asset_type}"
        COMMANDS
            "${CMAKE_COMMAND} -E copy_if_different @INPUT_FILE@ ${CMAKE_BINARY_DIR}/assets/${asset_type}/@INPUT_FILENAME@"
        GLOBS "assets/${asset_type}/*")
endforeach()

if(ENABLE_CMAKE_FORMAT)
    find_program(CMAKE_FORMAT_EXECUTABLE cmake-format)
    if(CMAKE_FORMAT_EXECUTABLE)
        ph_add_file_pass(
            NAME check-format-cmake-format
            GROUPS check-format
            COMMANDS "${CMAKE_FORMAT_EXECUTABLE} --check @INPUT_FILE@"
            GLOBS "assets/CMakeLists.txt"
                  "cmake/*.cmake"
                  "include/CMakeLists.txt"
                  "src/CMakeLists.txt"
                  "test/CMakeLists.txt"
                  "vendor/CMakeLists.txt"
            FILES "${CMAKE_SOURCE_DIR}/CMakeLists.txt")

        ph_add_file_pass(
            NAME fix-format-cmake-format
            GROUPS fix-format
            COMMANDS "${CMAKE_FORMAT_EXECUTABLE} -i @INPUT_FILE@"
            GLOBS "assets/CMakeLists.txt"
                  "cmake/*.cmake"
                  "include/CMakeLists.txt"
                  "src/CMakeLists.txt"
                  "test/CMakeLists.txt"
                  "vendor/CMakeLists.txt"
            FILES "${CMAKE_SOURCE_DIR}/CMakeLists.txt")
    endif()
endif()

if(ENABLE_BLACK)
    find_program(BLACK_EXECUTABLE black)
    if(BLACK_EXECUTABLE)
        ph_add_file_pass(
            NAME check-format-black
            GROUPS check-format
            COMMANDS "${BLACK_EXECUTABLE} --check @INPUT_FILE@"
            GLOBS "codegen/*.py" "tools/*.py"
            FILES "${CMAKE_SOURCE_DIR}/.cmake-format.py")

        ph_add_file_pass(
            NAME fix-format-black
            GROUPS fix-format
            COMMANDS "${BLACK_EXECUTABLE} @INPUT_FILE@"
            GLOBS "codegen/*.py" "tools/*.py"
            FILES "${CMAKE_SOURCE_DIR}/.cmake-format.py")
    endif()
endif()

if(ENABLE_CLANG_FORMAT)
    find_program(CLANG_FORMAT_EXECUTABLE clang-format)
    if(CLANG_FORMAT_EXECUTABLE)
        ph_add_file_pass(
            NAME check-format-clang-format
            GROUPS check-format
            COMMANDS "${CLANG_FORMAT_EXECUTABLE} --style=file --dry-run --Werror @INPUT_FILE@"
            GLOBS "include/*.hpp"
                  "include/*.inl"
                  "include/*.cpp"
                  "src/*.hpp"
                  "src/*.inl"
                  "src/*.cpp"
                  "src/*.cpp.in"
                  "test/*.hpp"
                  "test/*.inl"
                  "test/*.cpp"
                  "vendor/*.hpp"
                  "vendor/*.inl"
                  "vendor/*.cpp")

        ph_add_file_pass(
            NAME fix-format-clang-format
            GROUPS fix-format
            COMMANDS "${CLANG_FORMAT_EXECUTABLE} --style=file -i @INPUT_FILE@"
            GLOBS "include/*.hpp"
                  "include/*.inl"
                  "include/*.cpp"
                  "src/*.hpp"
                  "src/*.inl"
                  "src/*.cpp"
                  "src/*.cpp.in"
                  "test/*.hpp"
                  "test/*.inl"
                  "test/*.cpp"
                  "vendor/*.hpp"
                  "vendor/*.inl"
                  "vendor/*.cpp")
    endif()
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXECUTABLE clang-tidy)
    find_program(CLANG_APPLY_REPLACEMENTS_EXECUTABLE clang-apply-replacements)
    if(CLANG_TIDY_EXECUTABLE AND CLANG_APPLY_REPLACEMENTS_EXECUTABLE)
        ph_add_file_pass(
            NAME check-format-clang-tidy
            GROUPS check-format
            COMMANDS
                "${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_BINARY_DIR} -extra-arg=-Wno-unknown-warning-option -warnings-as-errors=\"*\" @INPUT_FILE@"
            GLOBS "include/*.cpp"
                  "src/*.cpp"
                  "src/*.cpp.in"
                  "test/*.cpp"
            DEPENDENCIES ph_common ph_client_lib ph_server_lib)

        ph_add_file_pass(
            NAME fix-format-clang-tidy
            COMMANDS
                "${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_BINARY_DIR} -extra-arg=-Wno-unknown-warning-option -export-fixes=@TMP_DIR@/@HASH@.yaml @INPUT_FILE@"
            POST_COMMANDS "${CLANG_APPLY_REPLACEMENTS_EXECUTABLE} -format -style=file @TMP_DIR@"
            GLOBS "include/*.cpp"
                  "src/*.cpp"
                  "src/*.cpp.in"
                  "test/*.cpp"
            DEPENDENCIES ph_common ph_client_lib ph_server_lib)
    endif()
endif()
