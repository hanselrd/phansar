ph_add_library(
  NAME ph_server_lib
  TYPE STATIC
  INCLUDE_DIRECTORIES PUBLIC ${CMAKE_SOURCE_DIR}/include
  COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
  COMPILE_FEATURES PRIVATE ${default_compile_features}
  COMPILE_OPTIONS PRIVATE ${default_compile_options}
  SOURCES PRIVATE test.cpp # TODO: remove
  LINK_LIBRARIES PUBLIC ph_common ph_vendor_libpqxx
  SANITIZERS ${default_sanitizers})

ph_add_executable(
  NAME ph_server
  INCLUDE_DIRECTORIES PRIVATE ${CMAKE_SOURCE_DIR}/include
  COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
  COMPILE_FEATURES PRIVATE ${default_compile_features}
  COMPILE_OPTIONS PRIVATE ${default_compile_options}
  SOURCES PRIVATE main.cpp
  LINK_LIBRARIES PRIVATE ph_server_lib
  SANITIZERS ${default_sanitizers}
  DEPENDENCIES assets
  INSTALL RUNTIME DESTINATION bin)
