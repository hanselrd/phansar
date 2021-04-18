add_custom_target(check-format)
add_custom_target(fix-format)

function(ph_add_formatter)
    cmake_parse_arguments(
        ARG
        ""
        "NAME"
        "PROGRAMS;CHECK_ARGS;FIX_ARGS;POSTFIX_COMMAND;GLOBS;FILES"
        ${ARGN})

    if(ARG_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "called with unrecognized parameters: ${ARG_UNPARSED_ARGUMENTS}")
    endif()

    find_program(${ARG_NAME}_EXECUTABLE NAMES ${ARG_PROGRAMS})
    if(${ARG_NAME}_EXECUTABLE)
        file(
            GLOB_RECURSE
            files
            CONFIGURE_DEPENDS
            ${ARG_GLOBS})
        list(APPEND files ${ARG_FILES})

        add_custom_target(
            check-format-${ARG_NAME}-tmpdir
            COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/check-format-${ARG_NAME}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/check-format-${ARG_NAME})
        add_custom_target(check-format-${ARG_NAME} DEPENDS check-format-${ARG_NAME}-tmpdir)

        add_custom_target(
            fix-format-${ARG_NAME}-tmpdir
            COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/fix-format-${ARG_NAME}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/fix-format-${ARG_NAME})
        if(ARG_POSTFIX_COMMAND)
            string(
                REPLACE "%TMPDIR%"
                        "${CMAKE_BINARY_DIR}/fix-format-${ARG_NAME}"
                        ARG_POSTFIX_COMMAND
                        "${ARG_POSTFIX_COMMAND}")
            add_custom_target(
                fix-format-${ARG_NAME}
                COMMAND ${ARG_POSTFIX_COMMAND}
                DEPENDS fix-format-${ARG_NAME}-tmpdir
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Running POSTFIX command ...")
        else()
            add_custom_target(fix-format-${ARG_NAME} DEPENDS fix-format-${ARG_NAME}-tmpdir)
        endif()

        string(
            REPLACE "%TMPDIR%"
                    "${CMAKE_BINARY_DIR}/check-format-${ARG_NAME}"
                    ARG_CHECK_ARGS
                    "${ARG_CHECK_ARGS}")
        string(
            REPLACE "%TMPDIR%"
                    "${CMAKE_BINARY_DIR}/fix-format-${ARG_NAME}"
                    ARG_FIX_ARGS
                    "${ARG_FIX_ARGS}")

        foreach(file IN LISTS files)
            string(SHA1 hash ${file})

            string(
                REPLACE "%ID%"
                        "${hash}"
                        check_args
                        "${ARG_CHECK_ARGS}")
            string(
                REPLACE "%ID%"
                        "${hash}"
                        fix_args
                        "${ARG_FIX_ARGS}")
            string(
                REPLACE "%FILE%"
                        "${file}"
                        check_args
                        "${check_args}")
            string(
                REPLACE "%FILE%"
                        "${file}"
                        fix_args
                        "${fix_args}")

            add_custom_target(
                check-format-${ARG_NAME}-${hash}
                COMMAND ${${ARG_NAME}_EXECUTABLE} ${check_args}
                DEPENDS check-format-${ARG_NAME}-tmpdir
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Checking source code formatting of ${file} ...")
            add_dependencies(check-format-${ARG_NAME} check-format-${ARG_NAME}-${hash})

            add_custom_target(
                fix-format-${ARG_NAME}-${hash}
                COMMAND ${${ARG_NAME}_EXECUTABLE} ${fix_args}
                DEPENDS fix-format-${ARG_NAME}-tmpdir
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Fixing source code formatting of ${file} ...")
            add_dependencies(fix-format-${ARG_NAME} fix-format-${ARG_NAME}-${hash})
        endforeach()

        add_dependencies(check-format check-format-${ARG_NAME})
        add_dependencies(fix-format fix-format-${ARG_NAME})
    endif()
endfunction()

if(ENABLE_CMAKE_FORMAT)
    ph_add_formatter(
        NAME cmake-format
        PROGRAMS cmake-format
        CHECK_ARGS --check %FILE%
        FIX_ARGS -i %FILE%
        GLOBS "assets/CMakeLists.txt"
              "cmake/*.cmake"
              "include/CMakeLists.txt"
              "src/CMakeLists.txt"
              "test/CMakeLists.txt"
              "vendor/CMakeLists.txt"
        FILES "${CMAKE_SOURCE_DIR}/CMakeLists.txt")
endif()

if(ENABLE_BLACK)
    ph_add_formatter(
        NAME black
        PROGRAMS black
        CHECK_ARGS --check %FILE%
        FIX_ARGS %FILE%
        GLOBS "tools/*.py"
        FILES "${CMAKE_SOURCE_DIR}/.cmake-format.py")
endif()

if(ENABLE_CLANG_FORMAT)
    ph_add_formatter(
        NAME clang-format
        PROGRAMS clang-format
                 clang-format-10
                 clang-format-11
                 clang-format-12
        CHECK_ARGS --style=file
                   --dry-run
                   --Werror
                   %FILE%
        FIX_ARGS --style=file -i %FILE%
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

if(ENABLE_CLANG_TIDY)
    find_program(
        CLANG_APPLY_REPLACEMENTS_EXECUTABLE
        NAMES clang-apply-replacements
              clang-apply-replacements-10
              clang-apply-replacements-11
              clang-apply-replacements-12)
    if(CLANG_APPLY_REPLACEMENTS_EXECUTABLE)
        ph_add_formatter(
            NAME clang-tidy
            PROGRAMS clang-tidy
                     clang-tidy-10
                     clang-tidy-11
                     clang-tidy-12
            CHECK_ARGS -extra-arg=-Wno-unknown-warning-option %FILE%
            FIX_ARGS -extra-arg=-Wno-unknown-warning-option -export-fixes=%TMPDIR%/%ID%.yaml %FILE%
            POSTFIX_COMMAND
                ${CLANG_APPLY_REPLACEMENTS_EXECUTABLE}
                -format
                -style=file
                %TMPDIR%
            GLOBS "include/*.cpp"
                  "src/*.cpp"
                  "src/*.cpp.in"
                  "test/*.cpp")
    endif()
endif()

# cmake-format: off
# if(ENABLE_INCLUDE_WHAT_YOU_USE)
#     find_program(FIX_INCLUDES_EXECUTABLE NAMES fix_includes.py iwyu-fix-includes)
#     if(FIX_INCLUDES_EXECUTABLE)
#         ph_add_formatter(
#             NAME include-what-you-use
#             PROGRAMS iwyu_tool.py iwyu-tool
#             CHECK_ARGS -p
#                        ${CMAKE_BINARY_DIR}
#                        %FILE%
#                        --
#                        -Xiwyu
#                        --prefix_header_includes=remove
#                        -Xiwyu
#                        --transitive_includes_only
#                        -Xiwyu
#                        --no_fwd_decls
#                        -Xiwyu
#                        --quoted_includes_first
#                        -Xiwyu
#                        --cxx17ns
#             FIX_ARGS -p
#                      ${CMAKE_BINARY_DIR}
#                      %FILE%
#                      --
#                      -Xiwyu
#                      --prefix_header_includes=remove
#                      -Xiwyu
#                      --transitive_includes_only
#                      -Xiwyu
#                      --no_fwd_decls
#                      -Xiwyu
#                      --quoted_includes_first
#                      -Xiwyu
#                      --cxx17ns
#                      |
#                      ${FIX_INCLUDES_EXECUTABLE}
#                      ||
#                      ${CMAKE_COMMAND}
#                      -E
#                      true
#             GLOBS "include/*.cpp"
#                   "src/*.cpp"
#                   "src/*.cpp.in"
#                   "test/*.cpp"
#                   "vendor/*.cpp")
#     endif()
# endif()
# cmake-format: on
