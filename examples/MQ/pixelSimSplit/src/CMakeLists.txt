################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target SimMQ)

set(sources
  devices/FairMQChunkMerger.cxx
  devices/FairMQPrimaryGeneratorDevice.cxx
  devices/FairMQTransportDevice.cxx

  FairMCSplitEventHeader.cxx
)

set(no_dict_headers
  devices/FairMQChunkMerger.h
  devices/FairMQPrimaryGeneratorDevice.h
  devices/FairMQTransportDevice.h
)

set(headers
  FairMCSplitEventHeader.h
)

add_library(${target} SHARED ${sources} ${headers} ${no_dict_headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::MCStack
  FairRoot::ParBase
  FairRoot::Pixel

  FairMQ::FairMQ

  Core
  VMC
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF SimMQLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} ${no_dict_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
