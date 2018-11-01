 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(MaxTestTime 60)

set(INCLUDE_DIRECTORIES
    ${BASE_INCLUDE_DIRECTORIES}
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Sampler
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Storage
    ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools
    ${CMAKE_SOURCE_DIR}/generators
    ${CMAKE_SOURCE_DIR}/examples/common/passive
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/src
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/src/devices
    ${CMAKE_SOURCE_DIR}/examples/MQ/simulation_split/src
    ${CMAKE_SOURCE_DIR}/examples/MQ/simulation_split/src/devices
)

Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZeroMQ_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(NETWORK_INTERFACE eth0)
If(APPLE)
  set(NETWORK_INTERFACE lo0)
EndIf(APPLE)

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})


Set(Exe_Names
    runMQGen
    runMQTrans
    runMQChMer
)

set(Exe_Source
    runMQGen.cxx
    runMQTrans.cxx
    runMQChunkMerger.cxx
)


List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)


set(BIN_DESTINATION share/fairbase/examples/MQ/simulation_split/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/simulation_split")

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES Pixel SimMQ)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})

set(SPLITMC_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/simulation_split)
set(SPLITMC_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(PIXEL_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/simulation_split/run/scripts/splitMC-topology.xml
		${CMAKE_BINARY_DIR}/bin/examples/MQ/simulation_split/splitMC-topology.xml )
