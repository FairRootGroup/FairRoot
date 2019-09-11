################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_subdirectory(macro)

set(target FairTestDetector)

set(sources
  data/FairTestDetectorDigi.cxx
  data/FairTestDetectorHit.cxx
  data/FairTestDetectorPoint.cxx

  digitization/FairTestDetectorDigiTask.cxx
  digitization/FairTestDetectorHitProducerSmearing.cxx

  reconstruction/FairTestDetectorRecoTask.cxx

  simulation/FairConstField.cxx
  simulation/FairConstPar.cxx
  simulation/FairMapPar.cxx
  simulation/FairTestDetector.cxx
  simulation/FairTestDetectorContFact.cxx
  simulation/FairTestDetectorGeo.cxx
  simulation/FairTestDetectorGeoPar.cxx

  timeBasedSimulation/FairTestDetectorDigiRingSorter.cxx
  timeBasedSimulation/FairTestDetectorDigiSorterTask.cxx
  timeBasedSimulation/FairTestDetectorDigiWriteoutBuffer.cxx
  timeBasedSimulation/FairTestDetectorTimeDigiTask.cxx
  timeBasedSimulation/FairTestDetectorTimeRecoTask.cxx

  $<$<BOOL:${Protobuf_FOUND}>:${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.cc>
  $<$<BOOL:${Flatbuffers_FOUND}>:${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadDigi_generated.h>
  $<$<BOOL:${Flatbuffers_FOUND}>:${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadHit_generated.h>
)

set(headers
  data/FairTestDetectorDigi.h
  data/FairTestDetectorHit.h
  data/FairTestDetectorPoint.h

  digitization/FairTestDetectorDigiTask.h
  digitization/FairTestDetectorHitProducerSmearing.h

  reconstruction/FairTestDetectorRecoTask.h

  simulation/FairConstField.h
  simulation/FairConstPar.h
  simulation/FairMapPar.h
  simulation/FairTestDetector.h
  simulation/FairTestDetectorContFact.h
  simulation/FairTestDetectorGeo.h
  simulation/FairTestDetectorGeoPar.h

  timeBasedSimulation/FairTestDetectorDigiRingSorter.h
  timeBasedSimulation/FairTestDetectorDigiSorterTask.h
  timeBasedSimulation/FairTestDetectorDigiWriteoutBuffer.h
  timeBasedSimulation/FairTestDetectorTimeDigiTask.h
  timeBasedSimulation/FairTestDetectorTimeRecoTask.h
)

# message(STATUS "Flatbuffers_FOUND: " ${Flatbuffers_FOUND})
# message(STATUS "Flatbuffers: " ${Flatbuffers_DIR})
# get_target_property(Flatbuffers_INCLUDEDIR flatbuffers::flatbuffers INTERFACE_INCLUDE_DIRECTORIES)
# message(STATUS "Flatbuffers: " ${Flatbuffers_INCLUDEDIR})
# message(STATUS "Flatbuffers: " ${SIMPATH})

if(Protobuf_FOUND)
  set(PROTOBUF_USED true)
  list(APPEND defs PROTOBUF)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.h ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.cc
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I=. --cpp_out=${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayload.proto
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/MQ/data
  )
else()
  set(PROTOBUF_USED false)
endif()

# TODO: fix paths here
if(Flatbuffers_FOUND)
  set(FLATBUFFERS_USED true)
  list(APPEND defs FLATBUFFERS)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadDigi_generated.h
    COMMAND $<TARGET_FILE:flatbuffers::flatc> -c -o ${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayloadDigi.fbs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/MQ/data
  )
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadHit_generated.h
    COMMAND $<TARGET_FILE:flatbuffers::flatc> -c -o ${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayloadHit.fbs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/MQ/data
  )
else()
  set(FLATBUFFERS_USED false)
endif()

if(msgpack_FOUND)
  set(MSGPACK_USED true)
  list(APPEND defs MSGPACK)
else()
  set(MSGPACK_USED false)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3Three.sh.in          ${CMAKE_CURRENT_BINARY_DIR}/startMQTut3Three.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3All.sh.in            ${CMAKE_CURRENT_BINARY_DIR}/startMQTut3All.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3AllProxy.sh.in       ${CMAKE_CURRENT_BINARY_DIR}/startMQTut3AllProxy.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3PushPull.sh.in       ${CMAKE_CURRENT_BINARY_DIR}/startMQTut3PushPull.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/run/startMQTut3ExtraProcessor.sh.in ${CMAKE_CURRENT_BINARY_DIR}/startMQTut3ExtraProcessor.sh)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_compile_definitions(${target} PUBLIC ${defs})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/digitization>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/MQ/data>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/MQ/fileSink>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/MQ/processorTask>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/MQ/run>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/MQ/samplerTask>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/reconstruction>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/simulation>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/timeBasedSimulation>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::MCStack
  FairRoot::ParBase # FairRuntimeDb, FairContFact, FairParamList
  FairRoot::GeoBase # FairGeoInterface, FairGeoLoader, FairGeoNode, FairGeoVolume
  FairMQ::FairMQ

  Boost::serialization

  $<$<BOOL:${Protobuf_FOUND}>:protobuf::libprotobuf>
  $<$<BOOL:${Flatbuffers_FOUND}>:flatbuffers::flatbuffers>
  $<$<BOOL:${msgpack_FOUND}>:msgpackc>

  # TODO: clean the following
  Core
  Physics
  MathCore
  VMC
  RIO
  Tree
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairTestDetectorLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(tut3-sampler MQ/run/runTestDetectorSampler.cxx)
target_link_libraries(tut3-sampler PRIVATE FairRoot::BaseMQ FairRoot::FairTestDetector FairMQ::FairMQ)
target_compile_definitions(tut3-sampler PRIVATE ${defs})
set_target_properties(tut3-sampler PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}") # TODO: delete me, use defaults

add_executable(tut3-processor MQ/run/runTestDetectorProcessor.cxx)
target_link_libraries(tut3-processor PRIVATE FairRoot::BaseMQ FairRoot::FairTestDetector FairMQ::FairMQ)
target_compile_definitions(tut3-processor PRIVATE ${defs})
set_target_properties(tut3-processor PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}") # TODO: delete me, use defaults

add_executable(tut3-sink MQ/run/runTestDetectorFileSink.cxx)
target_link_libraries(tut3-sink PRIVATE FairRoot::BaseMQ FairRoot::FairTestDetector FairMQ::FairMQ)
target_compile_definitions(tut3-sink PRIVATE ${defs})
set_target_properties(tut3-sink PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}") # TODO: delete me, use defaults

install(TARGETS tut3-sampler tut3-processor tut3-sink
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/parameters/bin
)
