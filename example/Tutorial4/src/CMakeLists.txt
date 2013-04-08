# Create a library called "libTutorial1" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src/mc
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src/param
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src/data
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src/reco
${FAIRROOT_SOURCE_DIR}/example/Tutorial4/src/tools
${FAIRROOT_SOURCE_DIR}/example/mcstack
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
param/FairTutorialDetMisalignPar.cxx

data/FairTutorialDetPoint.cxx
data/FairTutorialDetHit.cxx

reco/FairTutorialDetHitProducerIdealMisalign.cxx
reco/FairTutorialDetStraightLineFitter.cxx
reco/FairTutorialDetMilleWriter.cxx

tools/FairTutorialDetGeoHandler.cxx
)

set(NO_DICT_SRCS tools/Mille.cc)
Set(HEADERS )
Set(LINKDEF Tutorial4LinkDef.h)
Set(LIBRARY_NAME Tutorial4)
Set(DEPENDENCIES Base MCStack GeoBase ParBase VMC Physics Cint Core)

GENERATE_LIBRARY()

