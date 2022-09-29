################################################################################
#    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Wrapper around FairMQ::FairMQ to support API transition

set(target FairMQ)

set(headers
  FairMQ.h
  FairRunFairMQDevice.h
)

add_library(${target} INTERFACE ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} INTERFACE
  FairMQ::FairMQ
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
