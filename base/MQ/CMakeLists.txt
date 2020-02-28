################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target BaseMQ)

set(sources
  tasks/FairMQProcessorTask.cxx
  tasks/FairMQSamplerTask.cxx
)

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

list(APPEND headers
  baseMQtools/baseMQtools.h
  devices/BaseMQFileSink.h
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

fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
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

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
