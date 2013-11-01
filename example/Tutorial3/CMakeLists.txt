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

If (Boost_FOUND)
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startAll.sh.in ${CMAKE_BINARY_DIR}/bin/startAll.sh ) 
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startAllProxy.sh.in ${CMAKE_BINARY_DIR}/bin/startAllProxy.sh ) 
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startPushPull.sh.in ${CMAKE_BINARY_DIR}/bin/startPushPull.sh ) 

  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startFileSink.sh.in ${CMAKE_BINARY_DIR}/bin/startFileSink.sh ) 
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startSink.sh.in ${CMAKE_BINARY_DIR}/bin/startSink.sh ) 
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startTestDetectorProcessor1.sh.in ${CMAKE_BINARY_DIR}/bin/startTestDetectorProcessor1.sh ) 
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startTestDetectorProcessor2.sh.in ${CMAKE_BINARY_DIR}/bin/startTestDetectorProcessor2.sh ) 
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startExtraProcessor.sh.in ${CMAKE_BINARY_DIR}/bin/startExtraProcessor.sh ) 
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startTestDetectorSampler.sh.in ${CMAKE_BINARY_DIR}/bin/startTestDetectorSampler.sh )
EndIf (Boost_FOUND)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${Boost_LIBRARY_DIRS}
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

If (Boost_FOUND)
  Set(SRCS 
      ${SRCS} 
      reconstruction/FairTestDetectorMQRecoTask.cxx
      digitization/FairTestDetectorDigiLoader.cxx
  )

  Set(NO_DICT_SRCS
    data/FairMQFileSink.cxx
    digitization/FairTestDetectorMQSampler.cxx
  )
EndIf (Boost_FOUND)

Set(HEADERS)
Set(${HEADERS} data/FairTestDetectorPayload.h ) 
Set(LINKDEF FairTestDetectorLinkDef.h)
Set(LIBRARY_NAME FairTestDetector)

If (Boost_FOUND)
  Set(DEPENDENCIES Base MCStack FairMQ boost_thread boost_system)
Else (Boost_FOUND)
  Set(DEPENDENCIES Base MCStack)
EndIf (Boost_FOUND)

GENERATE_LIBRARY()

Add_Subdirectory(macro)


If (Boost_FOUND)
  Set(Exe_Names testDetectorProcessor testDetectorSampler fileSink)
  Set(Exe_Source reconstruction/runTestDetectorProcessor.cxx digitization/runTestDetectorSampler.cxx reconstruction/runFileSink.cxx)

  List(LENGTH Exe_Names _length)
  Math(EXPR _length ${_length}-1)

  ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES FairTestDetector)
    GENERATE_EXECUTABLE()
  EndForEach(_file RANGE 0 ${_length})
EndIf (Boost_FOUND)
