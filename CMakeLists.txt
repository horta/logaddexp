cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(
  logaddexp
  LANGUAGES C
  VERSION 2.1.6
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(external/cmake-boilerplate/cbp.cmake)
cbp_set_warning_flags()
cbp_ci_build_option()

add_library(logaddexp INTERFACE)
add_library(LOGADDEXP::logaddexp ALIAS logaddexp)
target_include_directories(
  logaddexp INTERFACE $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(logaddexp INTERFACE $<$<BOOL:${UNIX}>:m>)
target_compile_features(logaddexp INTERFACE c_std_11)

cbp_install(logaddexp SEPARATE)

enable_testing()
add_subdirectory(test)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Danilo Horta")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C library that implements the logarithm of the sum of exponentiations")
set(CPACK_PACKAGE_CONTACT "Danilo Horta")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/package)
set(CPACK_VERBATIM_VARIABLES YES)
set(CPACK_PACKAGE_RELOCATABLE YES)
set(CPACK_MONOLITHIC_INSTALL YES)
include(CPack)
