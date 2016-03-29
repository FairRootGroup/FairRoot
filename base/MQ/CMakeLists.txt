 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/base/MQ
  ${CMAKE_SOURCE_DIR}/base/MQ/devices
  ${CMAKE_SOURCE_DIR}/base/MQ/tasks
  ${CMAKE_SOURCE_DIR}/fairmq
  ${CMAKE_SOURCE_DIR}/MbsAPI
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  ${Boost_LIBRARY_DIRS}
)

if(DDS_PATH)
  set(LINK_DIRECTORIES
    ${LINK_DIRECTORIES}
    ${DDS_PATH}/lib
  )
endif(DDS_PATH)

Link_Directories(${LINK_DIRECTORIES})

Set(SRCS
  devices/FairMQProcessor.cxx
  tasks/FairMQSamplerTask.cxx
  tasks/FairMQProcessorTask.cxx
  devices/FairMQLmdSampler.cxx
)

# to copy src that are header-only files (e.g. c++ template) for FairRoot external installation
# manual install (globbing add not recommended)
Set(BaseMQHDRFiles
  baseMQtools/baseMQtools.h
  devices/FairMQSampler.h
  devices/FairMQSampler.tpl
  devices/FairMQUnpacker.h
  policies/Sampler/SimpleTreeReader.h
  policies/Sampler/FairSourceMQInterface.h
  policies/Sampler/FairMQFileSource.h
  policies/Serialization/BinaryBaseClassSerializer.h
  policies/Serialization/BoostSerializer.h
  policies/Serialization/RootSerializer.h
  policies/Serialization/NoInputMethod.h
  policies/Storage/RootOutFileManager.h
  policies/Storage/RootOutFileManager.tpl
  policies/Storage/BinaryOutFileManager.h
  policies/Storage/BoostDataSaver.h
  policies/Storage/TriviallyCopyableDataSaver.h
)
install(FILES ${BaseMQHDRFiles} DESTINATION include)

set(DEPENDENCIES
  Base
  ParBase
  FairTools
  GeoBase
  ${Boost_THREAD_LIBRARY}
  ${Boost_TIMER_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  FairMQ
)

set(LIBRARY_NAME BaseMQ)

GENERATE_LIBRARY()
