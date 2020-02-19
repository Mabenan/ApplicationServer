cmake_minimum_required(VERSION 3.5)

project("ApplicationServer" LANGUAGES CXX)
enable_testing()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXEC_FOLDER "bin")

if(WIN32)
set(LIB_FOLDER "bin")
else()
set(LIB_FOLDER "lib")
endif()
set(INCLUDE_FOLDER "include")
set(PLUGIN_FOLDER "${EXEC_FOLDER}/plugins")
add_subdirectory(ApplicationServerCore)
add_subdirectory(ApplicationServerInterface)
add_subdirectory(ApplicationServer)

  export(PACKAGE ${CMAKE_PROJECT_NAME})

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "${CMAKE_PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${LIB_FOLDER}
  PATH_VARS
    LIB_FOLDER
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )
  
  export(EXPORT ${CMAKE_PROJECT_NAME}
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.cmake"
)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.cmake"
)

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${LIB_FOLDER}"
  )
install(
  EXPORT ${CMAKE_PROJECT_NAME}
  DESTINATION ${LIB_FOLDER}
  )
