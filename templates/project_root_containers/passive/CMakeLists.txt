# Create a library called "libPassive" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_SOURCE_DIR}/passive
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${FAIRROOT_LIBRARY_DIR}

)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
MyCave.cxx           
MyPipe.cxx 
MyGeoCave.cxx        
MyMagnet.cxx         
MyPassiveContFact.cxx
)

Set(HEADERS )
Set(LINKDEF PassiveLinkDef.h)
Set(LIBRARY_NAME Passive)
Set(DEPENDENCIES
    FairRoot::Base
    FairRoot::GeoBase
    FairRoot::ParBase
    FairLogger::FairLogger
    ROOT::Geom
    ROOT::Core)

GENERATE_LIBRARY()
