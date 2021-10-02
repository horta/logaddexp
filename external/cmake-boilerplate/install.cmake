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
