################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parameter-server.json ${CMAKE_BINARY_DIR}/bin/config/parameter-server.json)

set(target ParMQ)

set(sources
  ParameterMQServer.cxx
)

set(headers
  ParameterMQServer.cxx
)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR} # Net
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::ParBase # FairRuntimeDb, ...
  FairRoot::FairTools # FairLogger
  FairMQ::FairMQ
  # TODO: clean the following
  # which ROOT libs for TGeoManager, TClass, RTypes
)

install(TARGETS ${target}
  LIBRARY DESTINATION lib
  # TODO: change to?:
  # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
)

install(FILES ${headers}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

add_executable(parmq-server runParameterMQServer.cxx)
target_link_libraries(parmq-server PRIVATE ParMQ)

install(TARGETS parmq-server
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  # TODO: change to?:
  # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
)
