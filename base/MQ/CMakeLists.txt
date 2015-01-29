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
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  ${Boost_LIBRARY_DIRS}
)

Link_Directories(${LINK_DIRECTORIES})

Set(SRCS
  devices/FairMQProcessor.cxx
  tasks/FairMQSamplerTask.cxx
  tasks/FairMQProcessorTask.cxx
)

# to copy src that are header-only files (e.g. c++ template) for FairRoot external installation
# manual install (globbing add not recommended)
Set(BaseMQHDRFiles
   baseMQtools/baseMQtools.h
   devices/FairMQSampler.h
   devices/FairMQSampler.tpl
   policies/Sampler/SimpleTreeReader.h
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
  Base ParBase FairTools GeoBase boost_thread boost_timer boost_system FairMQ
)


set(LIBRARY_NAME BaseMQ)


GENERATE_LIBRARY()
