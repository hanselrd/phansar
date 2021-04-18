ph_add_executable(
    NAME ph_server
    INCLUDE_DIRECTORIES PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_FEATURES PRIVATE cxx_std_20 c_std_99
    SOURCES PRIVATE application.cpp main.cpp
    LINK_LIBRARIES PRIVATE ph_common ph_vendor_libpqxx
    INSTALL RUNTIME DESTINATION bin)
