################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ParMQ)

set(sources
  ParameterMQServer.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::ParBase # FairRuntimeDb, ...
  FairRoot::Tools # FairLogger
  FairRoot::FairMQ

  ROOT::Core
  ROOT::Geom
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${PROJECT_INSTALL_INCLUDEDIR})

add_executable(parmq-server runParameterMQServer.cxx)
target_link_libraries(parmq-server PRIVATE FairRoot::ParMQ FairRoot::FairMQ)
set_target_properties(parmq-server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

install(TARGETS parmq-server
  RUNTIME DESTINATION bin
)
