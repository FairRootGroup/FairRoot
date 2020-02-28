################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
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

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)
fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::MbsTutorial
  FairMQ::FairMQ

  ROOT::Core
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF LmdLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})

add_executable(ex-lmd-sampler runLmdSampler.cxx)
target_link_libraries(ex-lmd-sampler PRIVATE FairRoot::ExLmd FairRoot::BaseMQ FairMQ::FairMQ)

add_executable(ex-lmd-mbs-unpacker runMBSMQUnpacker.cxx)
target_link_libraries(ex-lmd-mbs-unpacker PRIVATE FairRoot::ExLmd FairRoot::BaseMQ FairMQ::FairMQ)

add_executable(ex-lmd-mbs-sink runMBSSink.cxx)
target_link_libraries(ex-lmd-mbs-sink PRIVATE FairRoot::ExLmd FairRoot::BaseMQ ROOT::Core FairRoot::MbsTutorial FairMQ::FairMQ)

install(TARGETS ex-lmd-sampler ex-lmd-mbs-unpacker ex-lmd-mbs-sink
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/Lmd/bin
)
