function(__target_compile_options target)
  set(args)

  foreach(arg IN LISTS ARGN)
    if(NOT
       (arg STREQUAL "BEFORE"
        OR arg STREQUAL "INTERFACE"
        OR arg STREQUAL "PUBLIC"
        OR arg STREQUAL "PRIVATE"))
      string(MAKE_C_IDENTIFIER ${arg} identifier)
      string(TOUPPER ${identifier} identifier)
      string(SHA1 hash ${arg})

      if(${arg} MATCHES "[-/][a-zA-Z0-9=:_-]+")
        string(
          REGEX
          REPLACE "^-Wno-"
                  "-W"
                  alt
                  ${CMAKE_MATCH_0})
        check_cxx_compiler_flag(${alt} PHANSAR_HAS_${identifier}_${hash})
        if(PHANSAR_HAS_${identifier}_${hash})
          list(APPEND args "SHELL:${arg}")
        endif()
      endif()
    else()
      list(APPEND args ${arg})
    endif()
  endforeach()

  target_compile_options(${target} ${args})
endfunction()

function(__target_link_libraries target)
  function(__get_link_libraries target outputs)
    set(_outputs)
    list(APPEND visited ${target})
    get_target_property(interface_link_libs ${target} INTERFACE_LINK_LIBRARIES)
    get_target_property(type ${target} TYPE)
    if(NOT
       type
       STREQUAL
       "INTERFACE_LIBRARY")
      get_target_property(link_libs ${target} LINK_LIBRARIES)
    endif()
    foreach(link_lib IN LISTS interface_link_libs link_libs)
      if(TARGET ${link_lib})
        list(
          FIND
          visited
          ${link_lib}
          result)
        if(result EQUAL -1)
          __get_link_libraries(${link_lib} __outputs)
          list(
            APPEND
            _outputs
            ${link_lib}
            ${__outputs})
        endif()
      endif()
    endforeach()

    set(visited
        ${visited}
        PARENT_SCOPE)
    set(${outputs}
        ${_outputs}
        PARENT_SCOPE)
  endfunction()

  set(args)
  list(
    GET
    ARGN
    0
    arg0)

  if(arg0 STREQUAL "SYSTEM")
    set(system ON)
  else()
    set(system OFF)
  endif()

  foreach(arg IN LISTS ARGN)
    if(arg STREQUAL "SYSTEM")
      continue()
    endif()

    if(NOT
       (arg STREQUAL "INTERFACE"
        OR arg STREQUAL "PUBLIC"
        OR arg STREQUAL "PRIVATE"))
      if(TARGET ${arg})
        if(system)
          __get_link_libraries(${arg} outputs)
          foreach(output IN LISTS outputs)
            get_target_property(interface_include_dirs ${output}
                                INTERFACE_INCLUDE_DIRECTORIES)
            if(interface_include_dirs)
              target_include_directories(${target} SYSTEM
                                         INTERFACE ${interface_include_dirs})
            endif()
          endforeach()
          get_target_property(interface_include_dirs ${arg}
                              INTERFACE_INCLUDE_DIRECTORIES)
          if(interface_include_dirs)
            target_include_directories(${target} SYSTEM
                                       INTERFACE ${interface_include_dirs})
          endif()
        endif()
      endif()
      list(APPEND args ${arg})
    else()
      list(APPEND args ${arg})
    endif()
  endforeach()

  target_link_libraries(${target} ${args})
endfunction()

function(__target_sanitizers target)
  foreach(arg IN LISTS ARGN)
    if(${arg} MATCHES "address|memory|thread|undefined")
      string(MAKE_C_IDENTIFIER ${arg} identifier)
      string(TOUPPER ${identifier} identifier)
      string(SHA1 hash ${arg})

      set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=${CMAKE_MATCH_0}")
      check_cxx_compiler_flag("-fsanitize=${CMAKE_MATCH_0}"
                              PHANSAR_HAS_${identifier}_${hash})
      if(PHANSAR_HAS_${identifier}_${hash})
        string(
          REPLACE ${CMAKE_MATCH_0}
                  "-fsanitize=${CMAKE_MATCH_0}"
                  arg
                  ${arg})
        target_compile_options(${target} PRIVATE "SHELL:${arg}")
        target_link_options(${target} PRIVATE "SHELL:${arg}")
      endif()
      unset(CMAKE_REQUIRED_LINK_OPTIONS)
    endif()
  endforeach()

  # /fsanitize=address
  # /INFERASANLIBS
endfunction()

function(ph_add_library)
  cmake_parse_arguments(
    ARG
    ""
    "NAME;TYPE"
    "INCLUDE_DIRECTORIES;COMPILE_DEFINITIONS;COMPILE_FEATURES;COMPILE_OPTIONS;PRECOMPILE_HEADERS;SOURCES;LINK_LIBRARIES;LINK_OPTIONS;LINK_DIRECTORIES;SANITIZERS;DEPENDENCIES;INSTALL"
    ${ARGN})

  if(ARG_UNPARSED_ARGUMENTS)
    message(
      FATAL_ERROR
        "called with unrecognized parameters: ${ARG_UNPARSED_ARGUMENTS}")
  endif()

  add_library(${ARG_NAME} ${ARG_TYPE})

  if(ARG_INCLUDE_DIRECTORIES)
    target_include_directories(${ARG_NAME} ${ARG_INCLUDE_DIRECTORIES})
  endif()

  if(ARG_COMPILE_DEFINITIONS)
    target_compile_definitions(${ARG_NAME} ${ARG_COMPILE_DEFINITIONS})
  endif()

  if(ARG_COMPILE_FEATURES)
    target_compile_features(${ARG_NAME} ${ARG_COMPILE_FEATURES})
  endif()

  if(ARG_COMPILE_OPTIONS)
    __target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
  endif()

  if(ARG_PRECOMPILE_HEADERS)
    target_precompile_headers(${ARG_NAME} ${ARG_PRECOMPILE_HEADERS})
  endif()

  if(ARG_SOURCES)
    target_sources(${ARG_NAME} ${ARG_SOURCES})
  endif()

  if(ARG_LINK_LIBRARIES)
    __target_link_libraries(${ARG_NAME} ${ARG_LINK_LIBRARIES})
  endif()

  if(ARG_LINK_OPTIONS)
    target_link_options(${ARG_NAME} ${ARG_LINK_OPTIONS})
  endif()

  if(ARG_LINK_DIRECTORIES)
    target_link_directories(${ARG_NAME} ${ARG_LINK_DIRECTORIES})
  endif()

  if(ARG_SANITIZERS)
    __target_sanitizers(${ARG_NAME} ${ARG_SANITIZERS})
  endif()

  if(ARG_DEPENDENCIES)
    add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
  endif()

  if(ARG_INSTALL)
    install(TARGETS ${ARG_NAME} ${ARG_INSTALL})
  endif()
endfunction()

function(ph_add_executable)
  cmake_parse_arguments(
    ARG
    ""
    "NAME"
    "INCLUDE_DIRECTORIES;COMPILE_DEFINITIONS;COMPILE_FEATURES;COMPILE_OPTIONS;PRECOMPILE_HEADERS;SOURCES;LINK_LIBRARIES;LINK_OPTIONS;LINK_DIRECTORIES;SANITIZERS;DEPENDENCIES;INSTALL;DISCOVER_TESTS"
    ${ARGN})

  if(ARG_UNPARSED_ARGUMENTS)
    message(
      FATAL_ERROR
        "called with unrecognized parameters: ${ARG_UNPARSED_ARGUMENTS}")
  endif()

  add_executable(${ARG_NAME})

  if(ARG_INCLUDE_DIRECTORIES)
    target_include_directories(${ARG_NAME} ${ARG_INCLUDE_DIRECTORIES})
  endif()

  if(ARG_COMPILE_DEFINITIONS)
    target_compile_definitions(${ARG_NAME} ${ARG_COMPILE_DEFINITIONS})
  endif()

  if(ARG_COMPILE_FEATURES)
    target_compile_features(${ARG_NAME} ${ARG_COMPILE_FEATURES})
  endif()

  if(ARG_COMPILE_OPTIONS)
    __target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
  endif()

  if(ARG_PRECOMPILE_HEADERS)
    target_precompile_headers(${ARG_NAME} ${ARG_PRECOMPILE_HEADERS})
  endif()

  if(ARG_SOURCES)
    target_sources(${ARG_NAME} ${ARG_SOURCES})
  endif()

  if(ARG_LINK_LIBRARIES)
    __target_link_libraries(${ARG_NAME} ${ARG_LINK_LIBRARIES})
  endif()

  if(ARG_LINK_OPTIONS)
    target_link_options(${ARG_NAME} ${ARG_LINK_OPTIONS})
  endif()

  if(ARG_LINK_DIRECTORIES)
    target_link_directories(${ARG_NAME} ${ARG_LINK_DIRECTORIES})
  endif()

  if(ARG_SANITIZERS)
    __target_sanitizers(${ARG_NAME} ${ARG_SANITIZERS})
  endif()

  if(ARG_DEPENDENCIES)
    add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
  endif()

  if(ARG_INSTALL)
    install(TARGETS ${ARG_NAME} ${ARG_INSTALL})
  endif()

  if(ARG_DISCOVER_TESTS)
    catch_discover_tests(${ARG_NAME} ${ARG_DISCOVER_TESTS})
  endif()
endfunction()
