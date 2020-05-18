include(../../../QxOrm/QxOrm.cmake)
add_definitions(-DAPPLICATIONSERVERCORE_LIBRARY)
add_definitions(-D_QX_ENABLE_QT_NETWORK)
file(GLOB SRCl
    "*.cpp"
)
file(GLOB HEADERl
    "*.h"
    "*.hpp"
)
set(SRC ${SRC} ${SRCl} PARENT_SCOPE)
set(HEADER ${HEADER} ${HEADERl} PARENT_SCOPE)