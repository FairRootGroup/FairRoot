# Create a library called "libTutorial2" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${FAIRROOT_SOURCE_DIR}/example/Tutorial2/src
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
FairTutorialDetDigiPar.cxx
FairTutorialDetDigitizer.cxx
)

Set(HEADERS )
Set(LINKDEF Tutorial2LinkDef.h)
Set(LIBRARY_NAME Tutorial2)
Set(DEPENDENCIES Base MCStack GeoBase ParBase VMC Physics Cint Core)

GENERATE_LIBRARY()
