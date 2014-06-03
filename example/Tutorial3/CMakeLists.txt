 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairTestDetector" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${ROOT_INCLUDE_DIR}
${ZMQ_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/fairmq
${CMAKE_SOURCE_DIR}/base/MQ
${CMAKE_SOURCE_DIR}/example/mcstack
${CMAKE_SOURCE_DIR}/example/Tutorial3
${CMAKE_SOURCE_DIR}/example/Tutorial3/data
${CMAKE_SOURCE_DIR}/example/Tutorial3/simulation
${CMAKE_SOURCE_DIR}/example/Tutorial3/digitization
${CMAKE_SOURCE_DIR}/example/Tutorial3/reconstruction
${CMAKE_SOURCE_DIR}/example/Tutorial3/timeBasedSimulation
)

include_directories(${INCLUDE_DIRECTORIES})

If (Boost_FOUND)
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startAll.sh.in ${CMAKE_BINARY_DIR}/bin/startAll.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startAllProxy.sh.in ${CMAKE_BINARY_DIR}/bin/startAllProxy.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startPushPull.sh.in ${CMAKE_BINARY_DIR}/bin/startPushPull.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startThree.sh.in ${CMAKE_BINARY_DIR}/bin/startThree.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startFileSink.sh.in ${CMAKE_BINARY_DIR}/bin/startFileSink.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startSink.sh.in ${CMAKE_BINARY_DIR}/bin/startSink.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startTestDetectorProcessor1.sh.in ${CMAKE_BINARY_DIR}/bin/startTestDetectorProcessor1.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startTestDetectorProcessor2.sh.in ${CMAKE_BINARY_DIR}/bin/startTestDetectorProcessor2.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startExtraProcessor.sh.in ${CMAKE_BINARY_DIR}/bin/startExtraProcessor.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startTestDetectorSampler.sh.in ${CMAKE_BINARY_DIR}/bin/startTestDetectorSampler.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startBenchmark.sh.in ${CMAKE_BINARY_DIR}/bin/startBenchmark.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startBin.sh.in ${CMAKE_BINARY_DIR}/bin/startBin.sh )
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/startProto.sh.in ${CMAKE_BINARY_DIR}/bin/startProto.sh )
EndIf (Boost_FOUND)

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${Boost_LIBRARY_DIRS}
) 

link_directories(${LINK_DIRECTORIES})

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
    data/FairTestDetectorDigi.cxx
    
  )


  Set(NO_DICT_SRCS
    data/FairMQFileSink.cxx
    #data/has_BoostSerialization.cxx
  )

  If(HAS_CXX11_AUTO AND HAS_CXX11_AUTO_RET_TYPE AND HAS_CXX11_CONSTEXPR AND HAS_CXX11_LAMBDA AND HAS_CXX11_DECLTYPE)
    Set(NO_DICT_SRCS
    ${NO_DICT_SRCS} data/has_BoostSerialization.cxx
    )
  Endif(HAS_CXX11_AUTO AND HAS_CXX11_AUTO_RET_TYPE AND HAS_CXX11_CONSTEXPR AND HAS_CXX11_LAMBDA AND HAS_CXX11_DECLTYPE)



  If(PROTOBUF_FOUND)
    Set(NO_DICT_SRCS
      ${NO_DICT_SRCS}
      data/FairTestDetectorPayload.pb.cc
    )
  Endif(PROTOBUF_FOUND)
EndIf (Boost_FOUND)

Set(LINKDEF FairTestDetectorLinkDef.h)
Set(LIBRARY_NAME FairTestDetector)

If (Boost_FOUND)
  Set(DEPENDENCIES
    Base MCStack FairMQ FairMQSampler boost_thread boost_system boost_serialization)
Else (Boost_FOUND)
  Set(DEPENDENCIES Base MCStack)
EndIf (Boost_FOUND)

GENERATE_LIBRARY()

Add_Subdirectory(macro)


If (Boost_FOUND)
  Set(Exe_Names
    testDetectorSamplerBin
    testDetectorProcessorBin
    fileSinkBin # todo: make this consistent with the others
    testDetectorSamplerBoost
    testDetectorProcessorBoost
    fileSinkBoost # todo: make this consistent with the others
    testDetectorSamplerRoot
    testDetectorProcessorRoot
    fileSinkRoot # todo: make this consistent with the others
  )

  If(PROTOBUF_FOUND)
    Set(Exe_Names
      ${Exe_Names}
      testDetectorSamplerProto
      testDetectorProcessorProto
      fileSinkProto # todo: make this consistent with the others
    )
  EndIf(PROTOBUF_FOUND)

  set(Exe_Source
    run/runTestDetectorSamplerBin.cxx
    run/runTestDetectorProcessorBin.cxx
    run/runFileSinkBin.cxx
    run/runTestDetectorSamplerBoost.cxx
    run/runTestDetectorProcessorBoost.cxx
    run/runFileSinkBoost.cxx
    run/runTestDetectorSamplerRoot.cxx
    run/runTestDetectorProcessorRoot.cxx
    run/runFileSinkRoot.cxx
    )

  If(PROTOBUF_FOUND)
    Set(Exe_Source
      ${Exe_Source}
      run/runTestDetectorSamplerProto.cxx
      run/runTestDetectorProcessorProto.cxx
      run/runFileSinkProto.cxx
    )
  EndIf(PROTOBUF_FOUND)

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
