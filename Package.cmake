

export(PACKAGE "ApplicationServer")
include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "ApplicationServerConfig.cmake"
  INSTALL_DESTINATION ${LIB_FOLDER}
  PATH_VARS
    LIB_FOLDER
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/ApplicationServerConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )
  
  export(EXPORT ApplicationServer
  FILE "${CMAKE_CURRENT_BINARY_DIR}/ApplicationServer.cmake"
)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/ApplicationServerConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/ApplicationServer.cmake"
)

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/ApplicationServerConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/ApplicationServerConfigVersion.cmake"
  DESTINATION "${LIB_FOLDER}"
  )