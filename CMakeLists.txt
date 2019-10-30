cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Fetch version from header
set(VERSION_REGEX "#define LOGADDEXP_VERSION[ \t]+\"(.+)\"")
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/include/logaddexp.h"
  VERSION_STRING REGEX ${VERSION_REGEX})
string(REGEX REPLACE ${VERSION_REGEX} "\\1" VERSION_STRING "${VERSION_STRING}")

project(logaddexp LANGUAGES C VERSION ${VERSION_STRING})

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(logaddexp INTERFACE)
add_library(LOGADDEXP::logaddexp ALIAS logaddexp)
target_compile_features (logaddexp INTERFACE c_std_11)
target_include_directories(logaddexp
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(logaddexp INTERFACE $<$<BOOL:${UNIX}>:m>)

install(TARGETS logaddexp EXPORT logaddexp-targets)
install(DIRECTORY include/ DESTINATION include)

# Export the targets to a script
install(EXPORT logaddexp-targets
    FILE logaddexp-config.cmake
    NAMESPACE LOGADDEXP::
    DESTINATION lib/cmake/logaddexp
)

enable_testing()
add_subdirectory(test)
