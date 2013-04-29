# Create a library called "libFairTestDetector" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_SOURCE_DIR}/example/mcstack
${CMAKE_SOURCE_DIR}/example/Tutorial3
${CMAKE_SOURCE_DIR}/example/Tutorial3/data
${CMAKE_SOURCE_DIR}/example/Tutorial3/simulation
${CMAKE_SOURCE_DIR}/example/Tutorial3/digitization
${CMAKE_SOURCE_DIR}/example/Tutorial3/reconstruction
${CMAKE_SOURCE_DIR}/example/Tutorial3/timeBasedSimulation
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

Set(SRCS
  simulation/FairTestDetector.cxx
  simulation/FairTestDetectorContFact.cxx
  simulation/FairTestDetectorGeo.cxx
  simulation/FairTestDetectorGeoPar.cxx
  simulation/FairConstField.cxx
  simulation/FairConstPar.cxx
  simulation/FairMapPar.cxx
  data/FairTestDetectorPoint.cxx
  data/FairTestDetectorHit.cxx
  data/FairTestDetectorDigi.cxx
  digitization/FairTestDetectorHitProducerSmearing.cxx
  digitization/FairTestDetectorDigiTask.cxx
  reconstruction/FairTestDetectorRecoTask.cxx
  timeBasedSimulation/FairTestDetectorDigiRingSorter.cxx
  timeBasedSimulation/FairTestDetectorDigiSorterTask.cxx
  timeBasedSimulation/FairTestDetectorDigiWriteoutBuffer.cxx
  timeBasedSimulation/FairTestDetectorTimeDigiTask.cxx
  timeBasedSimulation/FairTestDetectorTimeRecoTask.cxx
)

Set(HEADERS )
Set(LINKDEF FairTestDetectorLinkDef.h)
Set(LIBRARY_NAME FairTestDetector)
Set(DEPENDENCIES Base)

GENERATE_LIBRARY()

Add_Subdirectory(macro)
