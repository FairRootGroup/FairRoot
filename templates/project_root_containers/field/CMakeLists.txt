# Create a library called "libField” which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES} 
${CMAKE_SOURCE_DIR}/field 
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${FAIRROOT_LIBRARY_DIR}

)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
MyConstField.cxx   
MyFieldCreator.cxx 
MyFieldPar.cxx
)

set(LINKDEF FieldLinkDef.h)
Set(LIBRARY_NAME Field)
Set(DEPENDENCIES
    FairRoot::Base
    FairRoot::ParBase
    FairLogger::FairLogger
    ROOT::Core
)

GENERATE_LIBRARY()
