################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ExHistogramServer)

set(sources
  FairMQExHistoCanvasDrawer.cxx
  FairMQExHistoCanvasDrawerExample.cxx
  FairMQExHistoDevice.cxx
  FairMQExHistoServer.cxx
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
  FairRoot::ParBase
  FairMQ::FairMQ

  ROOT::Core
  ROOT::Gpad
  ROOT::Hist
  ROOT::MathCore
  ROOT::RHTTP
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairMQExHistoLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})

add_executable(ex-histo-device runExHistoDevice.cxx)
target_link_libraries(ex-histo-device PRIVATE FairRoot::ExHistogramServer FairMQ::FairMQ)

add_executable(ex-histo-server runExHistoCanvasDrawer.cxx)
target_link_libraries(ex-histo-server PRIVATE FairRoot::ExHistogramServer FairMQ::FairMQ)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-histo.sh.in ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-histo.sh)

install(TARGETS ex-histo-device ex-histo-server
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/histogramServer/bin
)
