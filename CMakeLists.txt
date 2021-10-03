cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(
  logaddexp
  LANGUAGES C
  VERSION 2.1.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(external/cmake-boilerplate/cbp.cmake)
cbp_set_warning_flags()
cbp_ci_build_option()

add_library(logaddexp INTERFACE)
add_library(LOGADDEXP::logaddexp ALIAS logaddexp)
target_include_directories(
  logaddexp INTERFACE $<INSTALL_INTERFACE:include>
                      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(logaddexp INTERFACE $<$<BOOL:${UNIX}>:m>)
target_compile_features(logaddexp INTERFACE c_std_11)
target_compile_definitions(logaddexp INTERFACE _XOPEN_SOURCE=1)

cbp_install(logaddexp SEPARATE)

enable_testing()
add_subdirectory(test)
