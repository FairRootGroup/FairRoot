 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${FairMQ_INCDIR}
  ${FairMQ_INCDIR}/fairmq
  ${CMAKE_SOURCE_DIR}/examples/MQ/histogramServer
  ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
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
)

Set(NO_DICT_SRCS
  "FairMQExHistoDevice.cxx"
  "FairMQExHistoServer.cxx"
  "FairMQExHistoCanvasDrawer.cxx"
  "FairMQExHistoCanvasDrawerExample.cxx"
)

set(DEPENDENCIES
  ${DEPENDENCIES}
  FairMQ::FairMQ
  Base
)

set(LINKDEF "FairMQExHistoLinkDef.h")

set(LIBRARY_NAME FairMQExHistogramServer)

GENERATE_LIBRARY()

set(Exe_Names
  ex-histo-device
  ex-histo-server
)

set(Exe_Source
  runExHistoDevice.cxx
  runExHistoCanvasDrawer.cxx
)

list(LENGTH Exe_Names _length)
math(EXPR _length ${_length}-1)

set(BIN_DESTINATION share/fairbase/examples/MQ/histogramServer/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/histogramServer")

ForEach(_file RANGE 0 ${_length})
  list(GET Exe_Names ${_file} _name)
  list(GET Exe_Source ${_file} _src)
  set(EXE_NAME ${_name})
  set(SRCS ${_src})
  set(DEPENDENCIES FairMQExHistogramServer)
  GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})

set(EX_BIN_DIR ${EXECUTABLE_OUTPUT_PATH})
set(MAIN_BINARY_DIR ${CMAKE_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-histo.sh.in ${EXECUTABLE_OUTPUT_PATH}/fairmq-start-ex-histo.sh)

