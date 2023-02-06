################################################################################
# Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

### BaseMQ lib

set(target BaseMQ)

list(APPEND headers
  devices/FairMQLmdSampler.h
  devices/FairMQProcessor.h
  devices/FairMQSampler.h
  devices/FairMQUnpacker.h
  policies/Serialization/BoostSerializer.h
  policies/Serialization/RootSerializer.h
  FairBoostSerializationSupport.h
  FairHitBoostSerializationSupport.h
  FairMCPointBoostSerializationSupport.h
  FairTimeStampBoostSerializationSupport.h
  tasks/FairMQProcessorTask.h
  tasks/FairMQSamplerTask.h
)

add_library(${target} INTERFACE)
fairroot_library_settings(${target})

target_include_directories(${target} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tasks>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/baseMQtools>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Sampler>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Serialization>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Storage>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target}
  INTERFACE
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
