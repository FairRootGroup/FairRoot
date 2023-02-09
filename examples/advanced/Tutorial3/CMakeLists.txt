################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_subdirectory(macro)

set(target ExTestDetector)

set(sources
  data/FairTestDetectorDigi.cxx
  data/FairTestDetectorHit.cxx
  data/FairTestDetectorPoint.cxx

  digitization/FairTestDetectorDigiTask.cxx
  digitization/FairTestDetectorHitProducerSmearing.cxx

  reconstruction/FairTestDetectorRecoTask.cxx

  simulation/FairConstField.cxx
  simulation/FairConstPar.cxx
  simulation/FairConstFieldCreator.cxx
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

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

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

  if(TARGET flatbuffers::flatbuffers_shared)
    set(flatbuffers_lib flatbuffers::flatbuffers_shared)
  else()
    set(flatbuffers_lib flatbuffers::flatbuffers)
  endif()
else()
  set(FLATBUFFERS_USED false)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MQ/start.sh.in ${CMAKE_CURRENT_BINARY_DIR}/start.sh)

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
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::GeoBase # FairGeoSet
  FairRoot::ParBase # FairRuntimeDb, FairContFact, FairParamList
  FairRoot::FairMQ

  FairLogger::FairLogger

  Boost::serialization

  $<$<BOOL:${Protobuf_FOUND}>:protobuf::libprotobuf>
  $<$<BOOL:${Flatbuffers_FOUND}>:${flatbuffers_lib}>

  ROOT::Physics # TVector3, TLorentzVector
  ROOT::Core # Rtypes
  ROOT::RIO # TFile

  PRIVATE
  FairRoot::ExMCStack
  FairRoot::Tools # FairLogger

  ROOT::MathCore # TRandom
  ${VMCLIB}
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairTestDetectorLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(tut3-sampler MQ/sampler.cxx)
target_link_libraries(tut3-sampler PRIVATE FairRoot::BaseMQ FairRoot::ExTestDetector FairRoot::FairMQ)
target_compile_definitions(tut3-sampler PRIVATE ${defs})

add_executable(tut3-processor MQ/processor.cxx)
target_link_libraries(tut3-processor PRIVATE FairRoot::BaseMQ FairRoot::ExTestDetector FairRoot::FairMQ)
target_compile_definitions(tut3-processor PRIVATE ${defs})

add_executable(tut3-sink MQ/sink.cxx)
target_link_libraries(tut3-sink PRIVATE FairRoot::BaseMQ FairRoot::ExTestDetector FairRoot::FairMQ)
target_compile_definitions(tut3-sink PRIVATE ${defs})

install(TARGETS tut3-sampler tut3-processor tut3-sink
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/advanced/Tutorial3/bin
)
