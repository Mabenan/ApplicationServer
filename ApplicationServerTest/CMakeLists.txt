cmake_minimum_required(VERSION 3.5)

project("ApplicationServerTest" LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  add_executable(ApplicationServerTest tst_findsplugins.cpp)
find_package(Qt5Core REQUIRED)
qt5_use_modules(ApplicationServerTest Core)
  qt5_use_modules(ApplicationServerTest Test)
target_link_libraries(ApplicationServerTest ApplicationServerCore ApplicationServerInterface)