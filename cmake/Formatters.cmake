option(ENABLE_CMAKE_FORMAT "Enable cmake-format" OFF)
option(ENABLE_BLACK "Enable black" OFF)
option(ENABLE_CLANG_FORMAT "Enable clang-format" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)

add_custom_target(check)
add_custom_target(format)

if(ENABLE_CMAKE_FORMAT)
    find_program(CMAKE_FORMAT_EXECUTABLE cmake-format)
    if(CMAKE_FORMAT_EXECUTABLE)
        file(
            GLOB_RECURSE
            cmake_format_files
            CONFIGURE_DEPENDS
            "cmake/*.cmake"
            "include/CMakeLists.txt"
            "src/CMakeLists.txt"
            "test/CMakeLists.txt"
            "vendor/CMakeLists.txt")
        list(APPEND cmake_format_files "${CMAKE_SOURCE_DIR}/CMakeLists.txt")

        add_custom_target(check-cmake-format)
        add_custom_target(cmake-format)

        set(counter 1)
        foreach(cmake_format_file ${cmake_format_files})
            add_custom_target(
                check-cmake-format-${counter}
                COMMAND ${CMAKE_FORMAT_EXECUTABLE} --check ${cmake_format_file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Checking ${cmake_format_file} ...")

            add_dependencies(check-cmake-format check-cmake-format-${counter})

            add_custom_target(
                cmake-format-${counter}
                COMMAND ${CMAKE_FORMAT_EXECUTABLE} -i ${cmake_format_file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Formatting ${cmake_format_file} ...")

            add_dependencies(cmake-format cmake-format-${counter})

            math(EXPR counter "${counter}+1")
        endforeach()

        add_dependencies(check check-cmake-format)
        add_dependencies(format cmake-format)
    else()
        message(FATAL_ERROR "cmake-format executable not found")
    endif()
endif()

if(ENABLE_BLACK)
    find_program(BLACK_EXECUTABLE black)
    if(BLACK_EXECUTABLE)
        file(GLOB_RECURSE black_files CONFIGURE_DEPENDS "tools/*.py")

        add_custom_target(check-black)
        add_custom_target(black)

        set(counter 1)
        foreach(black_file ${black_files})
            add_custom_target(
                check-black-${counter}
                COMMAND ${BLACK_EXECUTABLE} --check ${black_file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Checking ${black_file} ...")

            add_dependencies(check-black check-black-${counter})

            add_custom_target(
                black-${counter}
                COMMAND ${BLACK_EXECUTABLE} ${black_file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Formatting ${black_file} ...")

            add_dependencies(black black-${counter})

            math(EXPR counter "${counter}+1")
        endforeach()

        add_dependencies(check check-black)
        add_dependencies(format black)
    else()
        message(FATAL_ERROR "black executable not found")
    endif()
endif()

if(ENABLE_CLANG_FORMAT)
    find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format clang-format-9 clang-format-10
                                               clang-format-11)
    if(CLANG_FORMAT_EXECUTABLE)
        file(
            GLOB_RECURSE
            clang_format_files
            CONFIGURE_DEPENDS
            "include/*.hpp"
            "include/*.tpp"
            "include/*.cpp"
            "src/*.hpp"
            "src/*.tpp"
            "src/*.cpp"
            "test/*.hpp"
            "test/*.tpp"
            "test/*.cpp"
            "vendor/*.hpp"
            "vendor/*.tpp"
            "vendor/*.cpp")

        add_custom_target(
            check-clang-format-tmpdir
            COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/check-clang-format
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/check-clang-format)

        add_custom_target(check-clang-format DEPENDS check-clang-format-tmpdir)
        add_custom_target(clang-format)

        set(counter 1)
        foreach(clang_format_file ${clang_format_files})
            add_custom_target(
                check-clang-format-${counter}
                COMMAND ${CLANG_FORMAT_EXECUTABLE} -style=file ${clang_format_file} >
                        ${CMAKE_BINARY_DIR}/check-clang-format/${counter}
                COMMAND ${CMAKE_COMMAND} -E compare_files ${clang_format_file}
                        ${CMAKE_BINARY_DIR}/check-clang-format/${counter}
                DEPENDS check-clang-format-tmpdir
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Checking ${clang_format_file} ...")

            add_dependencies(check-clang-format check-clang-format-${counter})

            add_custom_target(
                clang-format-${counter}
                COMMAND ${CLANG_FORMAT_EXECUTABLE} -style=file -i ${clang_format_file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Formatting ${clang_format_file} ...")

            add_dependencies(clang-format clang-format-${counter})

            math(EXPR counter "${counter}+1")
        endforeach()

        add_dependencies(check check-clang-format)
        add_dependencies(format clang-format)
    else()
        message(FATAL_ERROR "clang-format executable not found")
    endif()
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy clang-tidy-9 clang-tidy-10 clang-tidy-11)
    find_program(
        CLANG_APPLY_REPLACEMENTS_EXECUTABLE
        NAMES clang-apply-replacements clang-apply-replacements-9 clang-apply-replacements-10
              clang-apply-replacements-11)
    if(CLANG_TIDY_EXECUTABLE AND CLANG_APPLY_REPLACEMENTS_EXECUTABLE)
        file(
            GLOB_RECURSE
            clang_tidy_files
            CONFIGURE_DEPENDS
            "include/*.cpp"
            "src/*.cpp"
            "test/*.cpp"
            "vendor/*.cpp")

        add_custom_target(
            check-clang-tidy-tmpdir
            COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/check-clang-tidy
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/check-clang-tidy
            COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/check-clang-tidy/empty)
        add_custom_target(
            clang-tidy-tmpdir
            COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/clang-tidy
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/clang-tidy)

        add_custom_target(check-clang-tidy DEPENDS check-clang-tidy-tmpdir)
        add_custom_target(
            clang-tidy
            COMMAND ${CLANG_APPLY_REPLACEMENTS_EXECUTABLE} -format -style=file
                    ${CMAKE_BINARY_DIR}/clang-tidy
            DEPENDS clang-tidy-tmpdir
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Applying fixes ...")

        set(CLANG_TIDY_CHECKS
            "-*,bugprone-*,-bugprone-branch-clone,-bugprone-exception-escape,-bugprone-lambda-function-name,-bugprone-sizeof-expression,cert-*,-cert-err58-cpp,clang-analyzer-*,google-explicit-constructor,google-runtime-int,llvm-header-guard,modernize-*,-modernize-avoid-c-arrays,performance-*,portability-*,readability-*,-readability-braces-around-statements,-readability-magic-numbers,-readability-misleading-indentation"
        )

        set(counter 1)
        foreach(clang_tidy_file ${clang_tidy_files})
            add_custom_target(
                check-clang-tidy-${counter}
                COMMAND
                    ${CLANG_TIDY_EXECUTABLE} -header-filter=.* -checks=${CLANG_TIDY_CHECKS}
                    -export-fixes=${CMAKE_BINARY_DIR}/check-clang-tidy/${counter}.yaml
                    -extra-arg=-Wno-unknown-warning-option -p ${CMAKE_SOURCE_DIR} ${clang_tidy_file}
                COMMAND ${CMAKE_COMMAND} -E touch
                        ${CMAKE_BINARY_DIR}/check-clang-tidy/${counter}.yaml
                COMMAND
                    ${CMAKE_COMMAND} -E compare_files
                    ${CMAKE_BINARY_DIR}/check-clang-tidy/${counter}.yaml
                    ${CMAKE_BINARY_DIR}/check-clang-tidy/empty
                DEPENDS check-clang-tidy-tmpdir
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Checking ${clang_tidy_file} ...")

            add_dependencies(check-clang-tidy check-clang-tidy-${counter})

            add_custom_target(
                clang-tidy-${counter}
                COMMAND
                    ${CLANG_TIDY_EXECUTABLE} -header-filter=.* -checks=${CLANG_TIDY_CHECKS}
                    -export-fixes=${CMAKE_BINARY_DIR}/clang-tidy/${counter}.yaml
                    -extra-arg=-Wno-unknown-warning-option -p ${CMAKE_SOURCE_DIR} ${clang_tidy_file}
                DEPENDS clang-tidy-tmpdir
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Formatting ${clang_tidy_file} ...")

            add_dependencies(clang-tidy clang-tidy-${counter})

            math(EXPR counter "${counter}+1")
        endforeach()

        add_dependencies(check check-clang-tidy)
        add_dependencies(format clang-tidy)
    else()
        message(FATAL_ERROR "clang-tidy or clang-apply-replacements executable not found")
    endif()
endif()
