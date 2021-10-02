function(cbp_install tgt hdr_place)
  install(TARGETS ${tgt} EXPORT ${tgt}-targets)

  if(hdr_place STREQUAL "SEPARATE")
    install(DIRECTORY include/ DESTINATION include)
  elseif(hdr_place STREQUAL "MERGED")
    install(DIRECTORY src/${tgt}/ DESTINATION include/${tgt})
  else()
    message(FATAL_ERROR "Wrong header placement.")
  endif()

  string(TOUPPER ${tgt} TGT)
  set(dst lib/cmake/${tgt})
  install(
    EXPORT ${tgt}-targets
    FILE ${tgt}-targets.cmake
    NAMESPACE ${TGT}::
    DESTINATION ${dst})

  include(CMakePackageConfigHelpers)

  set(cfg ${CMAKE_CURRENT_BINARY_DIR}/${tgt}-config.cmake)
  configure_package_config_file(${tgt}-config.cmake.in ${cfg}
                                INSTALL_DESTINATION ${dst})

  set(ver ${CMAKE_CURRENT_BINARY_DIR}/${tgt}-config-version.cmake)
  write_basic_package_version_file(${ver} COMPATIBILITY SameMajorVersion)

  install(FILES ${cfg} ${ver} DESTINATION ${dst})
endfunction()

macro(cbp_set_warning_flags)
  if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # /wd5105:
    # https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5105?view=msvc-160
    set(WARNING_FLAGS /W3 /wd5105)
  else()
    set(WARNING_FLAGS
        -Wall
        -Wextra
        -Wstrict-prototypes
        -Wshadow
        -Wconversion
        -Wmissing-prototypes
        -Wno-unused-parameter
        -Wsign-conversion
        -Wno-unused-function)

    if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
      list(APPEND WARNING_FLAGS -Wno-gnu-designator -Wno-empty-translation-unit
           -Wno-gnu-statement-expression -Wno-nullability-extension)
    endif()
  endif()
endmacro()

macro(cbp_ci_build_option)
  option(CI_BUILD "CI, extra flags will be set" OFF)
  if(CI_BUILD)
    message(STATUS "CI build enabled")
    if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
      add_compile_options(/WX)
    else()
      add_compile_options(-Werror)
    endif()
  endif()
endmacro()
