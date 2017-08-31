################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(dependencies
  Base
  MCStack
  FairMQ::FairMQ
  BaseMQ
  Boost::system
  Boost::serialization
)

if(Protobuf_FOUND)
  set(defs ${defs} PROTOBUF)
  add_custom_command(
    OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.h
    ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.cc
    COMMAND protobuf::protoc
    ARGS -I=. --cpp_out=${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayload.proto
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/MQ/data
  )
  set(NO_DICT_SRCS ${NO_DICT_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.cc)
  set(dependencies ${dependencies} protobuf::libprotobuf)
endif()

if(MSGPACK_FOUND)
  set(defs ${defs} MSGPACK)
  set(dependencies ${dependencies} Msgpack)
endif()

if(FLATBUFFERS_FOUND)
  set(defs ${defs} FLATBUFFERS)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadDigi_generated.h
    COMMAND FlatBuffers::flatc
    ARGS -c -o ${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayloadDigi.fbs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/MQ/data
  )
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadHit_generated.h
    COMMAND FlatBuffers::flatc
    ARGS -c -o ${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayloadHit.fbs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/MQ/data
  )
  Set(NO_DICT_SRCS ${NO_DICT_SRCS}
    ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadDigi_generated.h
    ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadHit_generated.h
  )
  set(dependencies ${dependencies} FlatBuffers)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3Three.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/advanced/Tutorial3/startMQTut3Three.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3All.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/advanced/Tutorial3/startMQTut3All.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3AllProxy.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/advanced/Tutorial3/startMQTut3AllProxy.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3PushPull.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/advanced/Tutorial3/startMQTut3PushPull.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3ExtraProcessor.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/advanced/Tutorial3/startMQTut3ExtraProcessor.sh)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/tut3-all-proxy.json
               ${CMAKE_BINARY_DIR}/bin/config/tut3-all-proxy.json)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/tut3-all.json
               ${CMAKE_BINARY_DIR}/bin/config/tut3-all.json)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/tut3-extra-processor.json
               ${CMAKE_BINARY_DIR}/bin/config/tut3-extra-processor.json)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/tut3-push-pull.json
               ${CMAKE_BINARY_DIR}/bin/config/tut3-push-pull.json)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/tut3-three.json
               ${CMAKE_BINARY_DIR}/bin/config/tut3-three.json)

add_fairroot_library(FairTestDetector
  SOURCES
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

  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${CMAKE_CURRENT_SOURCE_DIR}/simulation
  ${CMAKE_CURRENT_SOURCE_DIR}/digitization
  ${CMAKE_CURRENT_SOURCE_DIR}/reconstruction
  ${CMAKE_CURRENT_SOURCE_DIR}/timeBasedSimulation
  ${CMAKE_CURRENT_SOURCE_DIR}/MQ/samplerTask
  ${CMAKE_CURRENT_SOURCE_DIR}/MQ/processorTask
  ${CMAKE_CURRENT_SOURCE_DIR}/MQ/fileSink
  ${CMAKE_CURRENT_SOURCE_DIR}/MQ/run
  ${CMAKE_CURRENT_SOURCE_DIR}/MQ/data

  DEPENDENCIES ${dependencies}
  LINKDEF FairTestDetectorLinkDef.h
)

add_subdirectory(macro)

add_fairroot_multiple_executables(
  NAMES
  tut3-sampler
  tut3-processor
  tut3-sink

  SOURCES
  MQ/run/runTestDetectorSampler.cxx
  MQ/run/runTestDetectorProcessor.cxx
  MQ/run/runTestDetectorFileSink.cxx

  BIN_DESTINATION share/fairbase/examples/advanced/Tutorial3/bin
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/advanced/Tutorial3
  DEPENDENCIES FairTestDetector
)
