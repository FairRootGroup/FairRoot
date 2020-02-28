################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start-mq-ex-params.sh.in ${CMAKE_CURRENT_BINARY_DIR}/start-mq-ex-params.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test-mq-ex-params.sh.in  ${CMAKE_CURRENT_BINARY_DIR}/test-mq-ex-params.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mq_ex_params.root        ${CMAKE_CURRENT_BINARY_DIR}/mq_ex_params.root COPYONLY)

set(target ExParameters)

set(sources
  FairMQExParamsClient.cxx
  FairMQExParamsContFact.cxx
  FairMQExParamsParOne.cxx
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
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairMQExParamsLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})

add_executable(ex-params-client runExParamsClient.cxx)
target_link_libraries(ex-params-client PRIVATE FairRoot::ExParameters FairMQ::FairMQ)

install(TARGETS ex-params-client
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/parameters/bin
)

add_test(ex_MQ_parameters ${CMAKE_CURRENT_BINARY_DIR}/test-mq-ex-params.sh)
set_tests_properties(ex_MQ_parameters PROPERTIES
  TIMEOUT "30"
  RUN_SERIAL true
  PASS_REGULAR_EXPRESSION "Received parameter from the server:"
)
