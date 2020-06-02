cmake_minimum_required(VERSION 3.5)


  set(CMAKE_AUTOMOC ON)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-D_QX_ENABLE_QT_NETWORK)

add_executable(ApplicationServer main.cpp main.rc)
find_package(Qt5Core REQUIRED)
qt5_use_modules(ApplicationServer Core)
target_link_libraries(ApplicationServer ApplicationServerCore ApplicationServerInterface)
install(TARGETS ApplicationServer DESTINATION "${EXEC_FOLDER}")
