################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

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
  FairBoostSerializationSupport.h
  FairHitBoostSerializationSupport.h
  FairMCPointBoostSerializationSupport.h
  FairTimeStampBoostSerializationSupport.h
)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tasks>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/baseMQtools>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Sampler>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Serialization>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Storage>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR} # TClonesArray, TMessage, etc
)

target_link_libraries(${target}
  PUBLIC
  FairRoot::Base # FairTask, FairRunAna, FairRootFileSink, FairFileSource
  FairRoot::FairMQ

  INTERFACE
  FairRoot::ParBase # FairParRootFileIo, FairRuntimeDb
  FairRoot::Tools
  $<$<BOOL:${BUILD_MBS}>:FairRoot::MbsAPI>

  Boost::serialization
  Boost::filesystem

  ROOT::Net # TMessage
  ROOT::Core # Rtypes, TClonesArray
  ROOT::RIO # TFile
  ROOT::Tree # TTree
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
