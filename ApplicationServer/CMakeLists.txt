cmake_minimum_required(VERSION 3.5)


  set(CMAKE_AUTOMOC ON)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-D_QX_ENABLE_QT_NETWORK)

add_executable(${CMAKE_PROJECT_NAME} main.cpp main.rc)
find_package(Qt5Core REQUIRED)
qt5_use_modules(${CMAKE_PROJECT_NAME} Core)
target_link_libraries(${CMAKE_PROJECT_NAME} ApplicationServerCore ApplicationServerInterface)
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION "${EXEC_FOLDER}")
