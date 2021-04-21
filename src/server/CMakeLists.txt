ph_add_executable(
    NAME ph_server
    INCLUDE_DIRECTORIES PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    COMPILE_OPTIONS PRIVATE ${default_compile_options}
    SOURCES PRIVATE
            # application.cpp
            main.cpp
    LINK_LIBRARIES PRIVATE ph_common ph_vendor_libpqxx
    SANITIZERS ${default_sanitizers}
    INSTALL RUNTIME DESTINATION bin)
