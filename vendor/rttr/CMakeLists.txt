CPMAddPackage(
    NAME rttr
    GITHUB_REPOSITORY rttrorg/rttr # master
    GIT_TAG 7edbd580cfad509a3253c733e70144e36f02ecd4
    OPTIONS "BUILD_RTTR_DYNAMIC OFF"
            "BUILD_UNIT_TESTS OFF"
            "BUILD_STATIC ON"
            "BUILD_EXAMPLES OFF"
            "BUILD_DOCUMENTATION OFF"
            "BUILD_INSTALLER OFF"
            "BUILD_PACKAGE OFF"
    EXCLUDE_FROM_ALL YES)

if(rttr_ADDED)
    set_target_properties(rttr_core_lib PROPERTIES COMPILE_OPTIONS "")
endif()

ph_add_library(
    NAME ph_vendor_rttr
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE rttr_core_lib)
