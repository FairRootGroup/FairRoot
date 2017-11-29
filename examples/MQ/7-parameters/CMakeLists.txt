 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/7-parameters/ex7-client.json ${CMAKE_BINARY_DIR}/bin/config/ex7-client.json)
configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/7-parameters/startMQEx7.sh.in ${CMAKE_BINARY_DIR}/bin/examples/MQ/7-parameters/startMQEx7.sh)
configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/7-parameters/testMQEx7.sh.in ${CMAKE_BINARY_DIR}/bin/examples/MQ/7-parameters/testMQEx7.sh)
configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/7-parameters/mqexample7_param.root ${CMAKE_BINARY_DIR}/examples/MQ/7-parameters/mqexample7_param.root COPYONLY)

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/fairmq
  ${CMAKE_SOURCE_DIR}/fairmq/devices
  ${CMAKE_SOURCE_DIR}/fairmq/tools
  ${CMAKE_SOURCE_DIR}/fairmq/options
  ${CMAKE_SOURCE_DIR}/examples/MQ/7-parameters
  ${CMAKE_CURRENT_BINARY_DIR}
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${SYSTEM_INCLUDE_DIRECTORIES}
  ${Boost_INCLUDE_DIR}
  ${ZeroMQ_INCLUDE_DIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${Boost_LIBRARY_DIRS}
  ${ROOT_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

set(SRCS
  "FairMQExample7ParOne.cxx"
  "FairMQExample7ContFact.cxx"
)

Set(NO_DICT_SRCS
  "FairMQExample7Client.cxx"
)

set(DEPENDENCIES
  ${DEPENDENCIES}
  FairMQ
  Base
  MCStack
)

set(LINKDEF "FairMQExample7LinkDef.h")

set(LIBRARY_NAME FairMQExample7)

GENERATE_LIBRARY()

set(Exe_Names
  ex7-client
)

set(Exe_Source
  runExample7Client.cxx
)

list(LENGTH Exe_Names _length)
math(EXPR _length ${_length}-1)

set(BIN_DESTINATION share/fairbase/examples/MQ/7-parameters/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/7-parameters")

ForEach(_file RANGE 0 ${_length})
  list(GET Exe_Names ${_file} _name)
  list(GET Exe_Source ${_file} _src)
  set(EXE_NAME ${_name})
  set(SRCS ${_src})
  set(DEPENDENCIES FairMQExample7)
  GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})

add_test(NAME MQ.ex7-parameters COMMAND ${CMAKE_BINARY_DIR}/bin/examples/MQ/7-parameters/testMQEx7.sh)
set_tests_properties(MQ.ex7-parameters PROPERTIES TIMEOUT "30")
set_tests_properties(MQ.ex7-parameters PROPERTIES RUN_SERIAL true)
set_tests_properties(MQ.ex7-parameters PROPERTIES PASS_REGULAR_EXPRESSION "Received parameter from the server:")

Install(
  FILES ex7-client.json
  DESTINATION share/fairbase/examples/MQ/7-parameters/config/
)
