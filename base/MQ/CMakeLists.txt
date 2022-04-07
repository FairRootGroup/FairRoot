################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

### Wrapper around FairMQ::FairMQ to support API transition

set(target FairMQ)

set(headers FairMQ.h FairRunFairMQDevice.h)
add_library(${target} INTERFACE)
fairroot_compile_features(${target})
add_library(FairRoot::${target} ALIAS ${target})
target_link_libraries(${target} INTERFACE FairMQ::FairMQ)
target_include_directories(${target} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
unset(headers)

### BaseMQ lib

set(target BaseMQ)

set(sources
  tasks/FairMQProcessorTask.cxx
  tasks/FairMQSamplerTask.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

list(APPEND headers
  baseMQtools/baseMQtools.h
  devices/FairMQLmdSampler.h
  devices/FairMQProcessor.h
  devices/FairMQSampler.h
  devices/FairMQUnpacker.h
  policies/Sampler/FairMQFileSource.h
  policies/Sampler/FairSourceMQInterface.h
  policies/Sampler/SimpleTreeReader.h
  policies/Serialization/BinaryBaseClassSerializer.h
  policies/Serialization/BoostSerializer.h
  policies/Serialization/IOPolicy.h
  policies/Serialization/RootSerializer.h
  policies/Storage/BinaryOutFileManager.h
  policies/Storage/BoostDataSaver.h
  policies/Storage/RootOutFileManager.h
  policies/Storage/TriviallyCopyableDataSaver.h
)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tasks>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/baseMQtools>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Sampler>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Serialization>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Storage>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairTask, FairRunAna, FairRootFileSink, FairFileSource
  FairRoot::ParBase # FairParRootFileIo, FairRuntimeDb
  FairRoot::FairTools
  $<$<BOOL:${BUILD_MBS}>:FairRoot::MbsAPI>

  FairMQ::FairMQ

  Boost::serialization
  Boost::filesystem

  ROOT::Net # TMessage
  ROOT::Core # Rtypes, TClonesArray
  ROOT::RIO # TFile
  ROOT::Tree # TTree
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
