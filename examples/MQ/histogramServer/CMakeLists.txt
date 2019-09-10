################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target FairMQExHistogramServer)

set(sources
  FairMQExHistoCanvasDrawer.cxx
  FairMQExHistoCanvasDrawerExample.cxx
  FairMQExHistoDevice.cxx
  FairMQExHistoServer.cxx
)

set(headers
  FairMQExHistoCanvasDrawer.h
  FairMQExHistoCanvasDrawerExample.h
  FairMQExHistoDevice.h
  FairMQExHistoServer.h
)

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
  FairRoot::ParBase
  FairMQ::FairMQ
  # TODO: clean the following
  Core
  Gpad
  RHTTP
  Hist
  MathCore
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairMQExHistoLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(ex-histo-device runExHistoDevice.cxx)
target_link_libraries(ex-histo-device PRIVATE FairRoot::FairMQExHistogramServer)
set_target_properties(ex-histo-device PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}") # TODO: delete me, use defaults

add_executable(ex-histo-server runExHistoCanvasDrawer.cxx)
target_link_libraries(ex-histo-server PRIVATE FairRoot::FairMQExHistogramServer)
set_target_properties(ex-histo-server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}") # TODO: delete me, use defaults

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-histo.sh.in ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-histo.sh)

install(TARGETS ex-histo-device ex-histo-server
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/histogramServer/bin
)
