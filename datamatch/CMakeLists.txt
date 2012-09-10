# Create a library called "libMCMatch" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base 
#${CMAKE_SOURCE_DIR}/pndbase 
#${CMAKE_SOURCE_DIR}/pnddata
#${CMAKE_SOURCE_DIR}/pnddata/SdsData
#${CMAKE_SOURCE_DIR}/pnddata/SttData
#${CMAKE_SOURCE_DIR}/pnddata/GemData
#${CMAKE_SOURCE_DIR}/pnddata/FtsData
#${CMAKE_SOURCE_DIR}/pnddata/TrackData
#${CMAKE_SOURCE_DIR}/pndbase/PndStdUtils
#${CMAKE_SOURCE_DIR}/field 
#${CMAKE_SOURCE_DIR}/trackrep
#${CMAKE_SOURCE_DIR}/trackbase
#${CMAKE_SOURCE_DIR}/geane
#${CMAKE_SOURCE_DIR}/genfit
#${CMAKE_SOURCE_DIR}/PndTools/riemannfit
#${CMAKE_SOURCE_DIR}/emc/EmcData
#${CMAKE_SOURCE_DIR}/emc/EmcReco
#${CMAKE_SOURCE_DIR}/tpc
${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
FairMCMatch.cxx
FairMCMatchCreatorTask.cxx
FairMCMatchLoaderTask.cxx
FairMCMatchSelectorTask.cxx
FairMCObject.cxx
FairMCStage.cxx
FairMCResult.cxx
FairMCEntry.cxx
FairMCList.cxx
FairMCDataCrawler.cxx
)

Set(HEADERS )
Set(LINKDEF FairMCMatchLinkDef.h)
Set(LIBRARY_NAME MCMatch)
#Set(DEPENDENCIES 
#    FairTools ParBase GeoBase 
#    Proof GeomPainter Geom VMC EG MathCore Physics 
#    Matrix Tree Hist RIO Cint Core
#)

GENERATE_LIBRARY()

########################### create libMCMatchExamples ##################################

#set(SRCS
#examples/FairMCTestMomentumCompare.cxx
#examples/FairMCTestHitCompare.cxx
#examples/FairMCIdealTrackFinder.cxx
#examples/FairMCTestEmcClusterCompare.cxx
#examples/FairMCTestPatternRecoQuality.cxx
#examples/FairMCTestDataCrawler.cxx
#)

#Set(HEADERS )
#Set(LINKDEF FairMCMatchLinkDef.h)
#Set(LIBRARY_NAME MCMatch)
#Set(DEPENDENCIES 
#    FairTools ParBase GeoBase 
#    Proof GeomPainter Geom VMC EG MathCore Physics 
#    Matrix Tree Hist RIO Cint Core
#)

#GENERATE_LIBRARY()

