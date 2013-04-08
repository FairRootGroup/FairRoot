# Create a library called "libTutorial1" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${FAIRROOT_SOURCE_DIR}/example/Tutorial1/src
${FAIRROOT_SOURCE_DIR}/example/mcstack
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(SRCS
#Put here your sourcefiles
FairTutorialDet.cxx
FairTutorialDetContFact.cxx
FairTutorialDetGeo.cxx
FairTutorialDetGeoPar.cxx
FairTutorialDetPoint.cxx
)

Set(HEADERS )
Set(LINKDEF Tutorial1LinkDef.h)
Set(LIBRARY_NAME Tutorial1)
Set(DEPENDENCIES Base MCStack GeoBase ParBase VMC Physics Cint Core)

GENERATE_LIBRARY()

