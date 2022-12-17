 # Create a library called "libMyProjData" 

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_SOURCE_DIR}/MyProjData
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${FAIRROOT_LIBRARY_DIR}
${CMAKE_SOURCE_DIR}/MyProjData

)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
MyProjStack.cxx 
MyProjMCTrack.cxx
)

Set(HEADERS )
Set(LINKDEF MCStackLinkDef.h)
Set(LIBRARY_NAME MyProjData)
Set(DEPENDENCIES
    FairRoot::Base
    FairLogger::FairLogger
    ${VMCLIB}
    ROOT::EG
    ROOT::Physics
    ROOT::Core)

GENERATE_LIBRARY()
