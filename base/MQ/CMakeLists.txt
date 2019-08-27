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

set(headers
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
  tasks/FairMQProcessorTask.h
  tasks/FairMQSamplerTask.h
)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tasks>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/baseMQtools>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Sampler>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Serialization>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/policies/Storage>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/MbsAPI>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR} # TClonesArray, TMessage, etc
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR} # Net
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairTask
  FairRoot::FairTools
  FairMQ::FairMQ
  Boost::boost
  Boost::serialization
  Boost::filesystem
  # TODO: clean the following
  Net # TMessage
)

install(TARGETS ${target}
  LIBRARY DESTINATION lib
  # TODO: change to?:
  # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
)

install(FILES ${headers}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
