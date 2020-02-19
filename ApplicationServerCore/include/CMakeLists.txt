
add_definitions(-DAPPLICATIONSERVERCORE_LIBRARY)
file(GLOB SRCl
    "*.cpp"
)
file(GLOB HEADERl
    "*.h"
    "*.hpp"
    "ApplicationServerCore"
)
set(SRC ${SRC} ${SRCl} PARENT_SCOPE)
set(HEADER ${HEADER} ${HEADERl} PARENT_SCOPE)