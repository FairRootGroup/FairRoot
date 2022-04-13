################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/startMQExLmd.sh.in ${CMAKE_CURRENT_BINARY_DIR}/startMQExLmd.sh)

set(target ExLmd)

set(sources
  FairMBSUnpacker.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
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
  FairRoot::ExMbs
  FairRoot::FairMQ

  Core
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF LmdLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(ex-lmd-sampler runLmdSampler.cxx)
target_link_libraries(ex-lmd-sampler PRIVATE FairRoot::ExLmd FairRoot::BaseMQ FairRoot::FairMQ)

add_executable(ex-lmd-mbs-unpacker runMBSMQUnpacker.cxx)
target_link_libraries(ex-lmd-mbs-unpacker PRIVATE FairRoot::ExLmd FairRoot::BaseMQ FairRoot::FairMQ)

add_executable(ex-lmd-mbs-sink runMBSSink.cxx)
target_link_libraries(ex-lmd-mbs-sink PRIVATE FairRoot::ExLmd FairRoot::BaseMQ Core FairRoot::ExMbs FairRoot::FairMQ)

install(TARGETS ex-lmd-sampler ex-lmd-mbs-unpacker ex-lmd-mbs-sink
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/Lmd/bin
)
