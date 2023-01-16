cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(
  logaddexp
  LANGUAGES C
  VERSION 2.1.12)

set(LOGADDEXP_MAIN_PROJECT OFF)
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(LOGADDEXP_MAIN_PROJECT ON)
endif()

if(LOGADDEXP_MAIN_PROJECT)
  set(LOGADDEXP_BUILD_TESTS_DEFAULT ON)
else()
  set(LOGADDEXP_BUILD_TESTS_DEFAULT OFF)
endif()

option(LOGADDEXP_BUILD_TESTS "Build the unit tests"
       ${LOGADDEXP_BUILD_TESTS_DEFAULT})
message(STATUS "LOGADDEXP_MAIN_PROJECT: " ${LOGADDEXP_MAIN_PROJECT})
message(STATUS "LOGADDEXP_BUILD_TESTS: " ${LOGADDEXP_BUILD_TESTS})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

include(cmake/sanitizers.cmake)
include(cmake/warnings.cmake)

add_library(logaddexp INTERFACE)
add_library(LOGADDEXP::logaddexp ALIAS logaddexp)

target_include_directories(
  logaddexp
  INTERFACE $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(logaddexp INTERFACE $<$<BOOL:${UNIX}>:m>)
target_compile_features(logaddexp INTERFACE c_std_11)

install(TARGETS logaddexp EXPORT logaddexp-targets)

install(DIRECTORY include/logaddexp/ DESTINATION include/logaddexp)

install(
  EXPORT logaddexp-targets
  FILE logaddexp-targets.cmake
  NAMESPACE LOGADDEXP::
  DESTINATION lib/cmake/logaddexp)

include(CMakePackageConfigHelpers)

set(CMAKE_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/logaddexp-config.cmake)
configure_package_config_file(
  logaddexp-config.cmake.in ${CMAKE_CONFIG_FILE}
  INSTALL_DESTINATION lib/cmake/logaddexp)

set(CMAKE_VERSION_FILE ${CMAKE_CURRENT_BINARY_DIR}/logaddexp-config-version.cmake)
write_basic_package_version_file(${CMAKE_VERSION_FILE}
                                 COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CONFIG_FILE}
              ${CMAKE_VERSION_FILE}
        DESTINATION lib/cmake/logaddexp)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md
              ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md
        DESTINATION share/docs/logaddexp)

if(LOGADDEXP_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
