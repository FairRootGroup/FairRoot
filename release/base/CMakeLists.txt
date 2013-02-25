# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

# List of source files
set(SRCS
FairBaseContFact.cxx 
FairBaseParSet.cxx
FairLink.cxx
FairMultiLinkedData.cxx 
FairDetector.cxx 
FairEventHeader.cxx 
FairFileHeader.cxx 
FairGenerator.cxx 
FairHit.cxx 
FairIon.cxx 
FairMCApplication.cxx 
FairGeaneApplication.cxx 
FairMCEventHeader.cxx 
FairMCPoint.cxx 
FairModule.cxx 
FairParticle.cxx 
FairPrimaryGenerator.cxx 
FairRootManager.cxx 
FairRun.cxx 
FairRunAna.cxx 
FairRunIdGenerator.cxx 
FairRunSim.cxx 
FairGenericStack.cxx 
FairTask.cxx 
FairTrackParam.cxx 
FairTrajFilter.cxx 
FairVolume.cxx 
FairVolumeList.cxx 
FairField.cxx
FairFieldFactory.cxx
FairRadLenPoint.cxx
FairRadMapManager.cxx
FairRadMapPoint.cxx
FairRadLenManager.cxx
FairRadGridManager.cxx
FairMesh.cxx
FairRKPropagator.cxx
FairTimeStamp.cxx
FairTSBufferFunctional.cxx
FairFileInfo.cxx
FairRunInfo.cxx
FairWriteoutBuffer.cxx
FairRingSorter.cxx
FairRingSorterTask.cxx
FairAnaSelector.cxx
)

Set(HEADERS )
Set(LINKDEF FairLinkDef.h)
Set(LIBRARY_NAME Base)
Set(DEPENDENCIES 
    FairTools ParBase GeoBase 
    Proof GeomPainter Geom VMC EG MathCore Physics 
    Matrix Tree Hist RIO Cint Core
)

GENERATE_LIBRARY()

 
