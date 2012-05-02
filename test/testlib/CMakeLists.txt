# Create a library called "libFairTest" which includes the source files
# given in
# the array .
# The extension is already found.  Any number of sources could be listed
# here.

set(INCLUDE_DIRECTORIES
 ${CMAKE_SOURCE_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
)

link_directories( ${LINK_DIRECTORIES})

############### build the library #####################
add_library(FairTest SHARED FairCaptureOutput.cxx FairTestOutputHandler.cxx)

