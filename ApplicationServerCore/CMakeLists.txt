include(../../QxOrm/QxOrm.cmake)
set(target "ApplicationServerCore")

add_definitions(-DAPPLICATIONSERVERCORE_LIBRARY)
add_definitions(-D_QX_ENABLE_QT_NETWORK)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${curdir}/${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()

FOREACH(src ${SRC})
  message(${src})
ENDFOREACH()
add_library(${target} SHARED ${SRC})

if(COMMAND target_precompile_headers)
target_precompile_headers(${target}
 PUBLIC
  "ApplicationServerCore_global.h"
 )
 endif()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
find_package(Qt5Core REQUIRED)
qt5_use_modules(${target} Core)
target_link_libraries(${target} ApplicationServerInterface QxOrm)
target_include_directories(${target}
 PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${INCLUDE_FOLDER}>
 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)    
set_property(TARGET ${target} APPEND PROPERTY PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )
install(TARGETS ${target}
LIBRARY DESTINATION "${LIB_FOLDER}"
    ARCHIVE DESTINATION "${LIB_FOLDER}"
    RUNTIME DESTINATION "${EXEC_FOLDER}"
    INCLUDES DESTINATION "${INCLUDE_FOLDER}")
install(FILES ${HEADER} DESTINATION "${INCLUDE_FOLDER}")