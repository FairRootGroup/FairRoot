# Create a library called "libTutorial1" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
#put here all directories where header files are located

${FAIRROOT_SOURCE_DIR}/fairtools
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src/mc
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src/param
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src/data
${FAIRROOT_SOURCE_DIR}/base
${FAIRROOT_SOURCE_DIR}/example/mcstack
${FAIRROOT_SOURCE_DIR}/parbase
${FAIRROOT_SOURCE_DIR}/geobase
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(SRCS
#Put here your sourcefiles
mc/FairTutorialDet.cxx
mc/FairTutorialDetGeo.cxx

param/FairTutorialDetContFact.cxx
param/FairTutorialDetGeoPar.cxx

data/FairTutorialDetPoint.cxx
)

Set(HEADERS )
Set(LINKDEF Tutorial4LinkDef.h)
Set(LIBRARY_NAME Tutorial4)
Set(DEPENDENCIES Base MCStack GeoBase ParBase VMC Physics Cint Core)

GENERATE_LIBRARY()

