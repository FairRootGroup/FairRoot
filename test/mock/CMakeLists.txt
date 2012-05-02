# Create a library called "libFairTest" which includes the source files
# given in
# the array .
# The extension is already found.  Any number of sources could be listed
# here.

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/fairtools
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
)

link_directories( ${LINK_DIRECTORIES})

Set(Sources 
    FairMockMCApplication.cxx
    FairMockVirtualMC.cxx
)

CHANGE_FILE_EXTENSION(*.cxx *.h HDRS "${Sources}")
set(LINKDEF MockLinkDef.h)
set(DICTIONARY FairMockDict.cxx)
ROOT_GENERATE_DICTIONARY()

set(Sources ${Sources} ${DICTIONARY})

############### build the library #####################
add_library(FairMock SHARED ${Sources})

