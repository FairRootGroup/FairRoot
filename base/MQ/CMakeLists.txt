################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(BaseMQ
  SOURCES
  tasks/FairMQSamplerTask.cxx
  tasks/FairMQProcessorTask.cxx

  HEADERS
  baseMQtools/baseMQtools.h
  devices/FairMQSampler.h
  devices/FairMQProcessor.h
  devices/FairMQUnpacker.h
  devices/FairMQLmdSampler.h
  tasks/FairMQSamplerTask.h
  tasks/FairMQProcessorTask.h
  policies/Sampler/SimpleTreeReader.h
  policies/Sampler/FairSourceMQInterface.h
  policies/Sampler/FairMQFileSource.h
  policies/Serialization/BinaryBaseClassSerializer.h
  policies/Serialization/BoostSerializer.h
  policies/Serialization/RootSerializer.h
  policies/Serialization/MQPolicyDef.h
  policies/Storage/RootOutFileManager.h
  policies/Storage/BinaryOutFileManager.h
  policies/Storage/BoostDataSaver.h
  policies/Storage/TriviallyCopyableDataSaver.h

  DEPENDENCIES
  Base
  ParBase
  FairTools
  GeoBase
  Boost::thread
  Boost::timer
  Boost::system
  Boost::filesystem
  FairMQ

  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/baseMQtools
  ${CMAKE_CURRENT_SOURCE_DIR}/devices
  ${CMAKE_CURRENT_SOURCE_DIR}/policies
  ${CMAKE_CURRENT_SOURCE_DIR}/policies/Sampler
  ${CMAKE_CURRENT_SOURCE_DIR}/policies/Serialization
  ${CMAKE_CURRENT_SOURCE_DIR}/policies/Storage
  ${CMAKE_CURRENT_SOURCE_DIR}/tasks
)
