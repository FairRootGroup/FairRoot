################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parameter-server.json ${CMAKE_BINARY_DIR}/bin/config/parameter-server.json)

add_fairroot_library(ParMQ
  SOURCES ParameterMQServer.cxx
  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDENCIES FairMQ::FairMQ ParBase Base
)

add_fairroot_executable(parmq-server
  SOURCES runParameterMQServer.cxx
  DEPENDENCIES ParMQ
)
