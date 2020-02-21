
if(NOT CMAKE_PROJECT_NAME)
project("ApplicationServer" LANGUAGES CXX)
endif()
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

if(${PACKAGE})
include("Package.cmake")
endif()


install(
  EXPORT ApplicationServer
  DESTINATION ${LIB_FOLDER}
  )
