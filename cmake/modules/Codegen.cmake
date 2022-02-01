find_program(PIPENV_EXECUTABLE NAMES pipenv)
if(PIPENV_EXECUTABLE)
    add_custom_target(codegen)
    add_custom_target(clean-codegen)

    file(
        GLOB_RECURSE
        files
        CONFIGURE_DEPENDS
        "include/*.hpp"
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

    foreach(file IN LISTS files)
        string(SHA1 hash ${file})

        add_custom_target(
            codegen-${hash}
            COMMAND ${PIPENV_EXECUTABLE} run cog --verbosity=0 -I ${CMAKE_SOURCE_DIR}/codegen -r
                    ${file}
            # DEPENDS pre-codegen
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating code from ${file} ...")
        add_dependencies(codegen codegen-${hash})

        add_custom_target(
            clean-codegen-${hash}
            COMMAND ${PIPENV_EXECUTABLE} run cog --verbosity=0 -I ${CMAKE_SOURCE_DIR}/codegen -rx
                    ${file}
            # DEPENDS pre-codegen
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Cleaning generated code from ${file} ...")
        add_dependencies(clean-codegen clean-codegen-${hash})
    endforeach()
endif()
