cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project(
  logaddexp
  LANGUAGES C
  VERSION 2.1.14)
set(PROJECT_DESCRIPTION "Logarithm of the sum of exponentiations.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

include(cmake/sanitizers.cmake)
include(cmake/warnings.cmake)

add_library(logaddexp INTERFACE)
add_library(LOGADDEXP::logaddexp ALIAS logaddexp)

target_include_directories(
  logaddexp INTERFACE $<INSTALL_INTERFACE:include>
                      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

target_link_libraries(logaddexp INTERFACE $<$<BOOL:${UNIX}>:m>)
set_target_properties(logaddexp PROPERTIES VERSION ${PROJECT_VERSION})
target_compile_options(logaddexp PRIVATE ${WARNING_FLAGS})

install(TARGETS logaddexp EXPORT logaddexp-targets)
install(DIRECTORY include/logaddexp/ DESTINATION include/logaddexp)

export(
  TARGETS logaddexp
  NAMESPACE LOGADDEXP::
  FILE logaddexp-targets.cmake)
install(
  EXPORT logaddexp-targets
  NAMESPACE LOGADDEXP::
  DESTINATION lib/cmake/logaddexp)

install(FILES ${PROJECT_SOURCE_DIR}/README.md ${PROJECT_SOURCE_DIR}/LICENSE.md
        DESTINATION share/docs/logaddexp)

include(CMakePackageConfigHelpers)

set(project_config ${PROJECT_BINARY_DIR}/logaddexp-config.cmake)
set(version_config ${PROJECT_BINARY_DIR}/logaddexp-config-version.cmake)

configure_package_config_file(logaddexp-config.cmake.in ${project_config}
                              INSTALL_DESTINATION lib/cmake/logaddexp)

write_basic_package_version_file(${version_config}
                                 COMPATIBILITY SameMajorVersion)

install(FILES ${project_config} ${version_config}
        DESTINATION lib/cmake/logaddexp)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  enable_testing()
  add_subdirectory(test)
endif()
