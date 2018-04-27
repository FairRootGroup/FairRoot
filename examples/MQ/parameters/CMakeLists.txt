 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start-mq-ex-params.sh.in ${CMAKE_BINARY_DIR}/bin/examples/MQ/parameters/start-mq-ex-params.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test-mq-ex-params.sh.in ${CMAKE_BINARY_DIR}/bin/examples/MQ/parameters/test-mq-ex-params.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mq_ex_params.root ${CMAKE_BINARY_DIR}/examples/MQ/parameters/mq_ex_params.root COPYONLY)

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${FairMQ_INCDIR}
  ${FairMQ_INCDIR}/fairmq
  ${CMAKE_SOURCE_DIR}/examples/MQ/parameters
  ${CMAKE_CURRENT_BINARY_DIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${Boost_LIBRARY_DIRS}
  ${ROOT_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

set(SRCS
  "FairMQExParamsParOne.cxx"
  "FairMQExParamsContFact.cxx"
)

Set(NO_DICT_SRCS
  "FairMQExParamsClient.cxx"
)

set(DEPENDENCIES
  ${DEPENDENCIES}
  FairMQ::FairMQ
  Base
  MCStack
)

set(LINKDEF "FairMQExParamsLinkDef.h")

set(LIBRARY_NAME FairMQExParameters)

GENERATE_LIBRARY()

set(Exe_Names
  ex-params-client
)

set(Exe_Source
  runExParamsClient.cxx
)

list(LENGTH Exe_Names _length)
math(EXPR _length ${_length}-1)

set(BIN_DESTINATION share/fairbase/examples/MQ/parameters/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/parameters")

ForEach(_file RANGE 0 ${_length})
  list(GET Exe_Names ${_file} _name)
  list(GET Exe_Source ${_file} _src)
  set(EXE_NAME ${_name})
  set(SRCS ${_src})
  set(DEPENDENCIES FairMQExParameters)
  GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})

add_test(NAME MQ.ex-parameterss COMMAND ${CMAKE_BINARY_DIR}/bin/examples/MQ/parameters/test-mq-ex-params.sh)
set_tests_properties(MQ.ex-parameterss PROPERTIES
    TIMEOUT "30"
    RUN_SERIAL true
    PASS_REGULAR_EXPRESSION "Received parameter from the server:"
)
