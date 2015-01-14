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
  FairMQSampler.cxx
  FairMQSamplerTask.cxx
  FairMQProcessor.cxx
  FairMQProcessorTask.cxx
)

set(DEPENDENCIES
  Base ParBase FairTools GeoBase boost_thread boost_timer boost_system FairMQ
)


set(LIBRARY_NAME FairMQSampler)

install(FILES "FairMQSampler.tpl" DESTINATION include)

GENERATE_LIBRARY()
