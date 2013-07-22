# Create a library called "libFairTestDetector" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${ROOT_INCLUDE_DIR}
${ZMQ_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/fairmq
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
  data/FairMQFileSink.cxx
  digitization/FairTestDetectorHitProducerSmearing.cxx
  digitization/FairTestDetectorDigiTask.cxx
  digitization/TestDetectorMQSampler.cxx
  digitization/TestDetectorDigiLoader.cxx
  reconstruction/FairTestDetectorRecoTask.cxx
  reconstruction/FairTestDetectorMQRecoTask.cxx
  reconstruction/FairTestDetectorMQRecoTask.h
  timeBasedSimulation/FairTestDetectorDigiRingSorter.cxx
  timeBasedSimulation/FairTestDetectorDigiSorterTask.cxx
  timeBasedSimulation/FairTestDetectorDigiWriteoutBuffer.cxx
  timeBasedSimulation/FairTestDetectorTimeDigiTask.cxx
  timeBasedSimulation/FairTestDetectorTimeRecoTask.cxx
  )

Set(HEADERS)
Set(${HEADERS} data/TestDetectorPayload.h ) 
Set(LINKDEF FairTestDetectorLinkDef.h)
Set(LIBRARY_NAME FairTestDetector)
Set(DEPENDENCIES Base MCStack FairMQ)

GENERATE_LIBRARY()

Add_Subdirectory(macro)


Set(Exe_Names testDetectorProcessor testDetectorSampler fileSink)
Set(Exe_Source reconstruction/runTestDetectorProcessor.cxx digitization/runTestDetectorSampler.cxx reconstruction/runFileSink.cxx)

List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)

ForEach(_file RANGE 0 ${_length})
  List(GET Exe_Names ${_file} _name)
  List(GET Exe_Source ${_file} _src)
  Set(EXE_NAME ${_name})
  Set(SRCS ${_src})
  Set(DEPENDENCIES FairMQ FairTestDetector)
  GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})
