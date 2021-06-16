cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

# Fetch version from header
set(VERSION_REGEX "#define LOGADDEXP_VERSION[ \t]+\"(.+)\"")
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/include/logaddexp/logaddexp.h"
  VERSION_STRING REGEX ${VERSION_REGEX})
string(REGEX REPLACE ${VERSION_REGEX} "\\1" VERSION_STRING "${VERSION_STRING}")

project(logaddexp LANGUAGES C VERSION ${VERSION_STRING})
set(PROJECT_DESCRIPTION "Implements the logarithm of the sum of exponentiations.")

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${CMAKE_C_COMPILER_ID} MATCHES "MSVC")
    # /wd5105: https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5105?view=msvc-160
    set(WARNING_FLAGS /W3 /wd5105)
else()
    set(WARNING_FLAGS -Wall -Wextra -pedantic -Wstrict-prototypes -Wshadow
        -Wconversion -Wmissing-prototypes -Wno-unused-parameter -Wsign-conversion
        -Wno-unused-function # TODO: added only to please clangd for now
        -Wno-empty-translation-unit # TODO: added only to please clangd for now
    )
endif()

add_library(logaddexp INTERFACE)
add_library(LOGADDEXP::logaddexp ALIAS logaddexp)
target_include_directories(logaddexp
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(logaddexp INTERFACE $<$<BOOL:${UNIX}>:m>)
target_compile_features(logaddexp INTERFACE c_std_11)

install(TARGETS logaddexp EXPORT logaddexp-targets)
install(DIRECTORY include/ DESTINATION include)

# Export the targets to a script
install(EXPORT logaddexp-targets
    FILE logaddexp-targets.cmake
    NAMESPACE LOGADDEXP::
    DESTINATION lib/cmake/logaddexp
)
include(CMakePackageConfigHelpers)
configure_package_config_file(logaddexp-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/logaddexp-config.cmake
    INSTALL_DESTINATION lib/cmake/logaddexp
    NO_SET_AND_CHECK_MACRO
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/logaddexp-config.cmake
    DESTINATION lib/cmake/logaddexp
)

enable_testing()
add_subdirectory(test)
