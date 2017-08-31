################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run/startMQExLmd.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/Lmd/startMQExLmd.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run/ex-lmd.json
               ${CMAKE_BINARY_DIR}/bin/config/ex-lmd.json)

add_fairroot_library(ExLmd
  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/unpacker

  SOURCES unpacker/FairMBSUnpacker.cxx

  DEPENDENCIES Base FairMQ MbsAPI MbsTutorial
  LINKDEF LmdLinkDef.h
)

set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/Lmd")
add_fairroot_multiple_executables(
  NAMES
  ex-lmd-sampler
  ex-lmd-mbs-unpacker
  ex-lmd-mbs-sink

  SOURCES
  run/runLmdSampler.cxx
  run/runMBSMQUnpacker.cxx
  run/runMBSSink.cxx

  BIN_DESTINATION ${FAIRROOT_INSTALL_DATADIR}/examples/MQ/Lmd/bin

  DEPENDENCIES
  FairMQ::FairMQ
  BaseMQ
  MbsTutorial
  ExLmd
)
