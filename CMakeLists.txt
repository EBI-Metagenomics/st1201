cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

# Fetch version from header
set(VERSION_REGEX "#define ST1201_VERSION[ \t]+\"(.+)\"")
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/include/st1201/st1201.h"
  VERSION_STRING REGEX ${VERSION_REGEX})
string(REGEX REPLACE ${VERSION_REGEX} "\\1" VERSION_STRING "${VERSION_STRING}")

project(st1201 LANGUAGES C VERSION ${VERSION_STRING})
set(PROJECT_DESCRIPTION "MISB ST 1201: Floating Point to Integer Mapping.")

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(st1201 INTERFACE)
add_library(ST1201::st1201 ALIAS st1201)
target_include_directories(st1201
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(st1201 INTERFACE $<$<BOOL:${UNIX}>:m>)

install(TARGETS st1201 EXPORT st1201-targets)
install(DIRECTORY include/ DESTINATION include)

# Export the targets to a script
install(EXPORT st1201-targets
    FILE st1201-targets.cmake
    NAMESPACE ST1201::
    DESTINATION lib/cmake/st1201
)
include(CMakePackageConfigHelpers)
configure_package_config_file(st1201-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/st1201-config.cmake
    INSTALL_DESTINATION lib/cmake/st1201
    NO_SET_AND_CHECK_MACRO
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/st1201-config.cmake
    DESTINATION lib/cmake/st1201
)

enable_testing()
add_subdirectory(test)
