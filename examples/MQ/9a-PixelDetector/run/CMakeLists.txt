 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(MaxTestTime 30)

set(INCLUDE_DIRECTORIES
    ${BASE_INCLUDE_DIRECTORIES}
    ${CMAKE_SOURCE_DIR}/fairmq
    ${CMAKE_SOURCE_DIR}/fairmq/deployment
    ${CMAKE_SOURCE_DIR}/fairmq/devices
    ${CMAKE_SOURCE_DIR}/fairmq/options
    ${CMAKE_SOURCE_DIR}/fairmq/tools
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Sampler
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Storage
    ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools
    ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector
    ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/src
    ${CMAKE_SOURCE_DIR}/examples/MQ/9a-PixelDetector/src
    ${CMAKE_SOURCE_DIR}/examples/MQ/9a-PixelDetector/src/devices
)

Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZMQ_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(NETWORK_INTERFACE eth0)
If(APPLE)
  set(NETWORK_INTERFACE lo0)
EndIf(APPLE)

set(EXAMPLE9_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(EXAMPLE9_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector)
set(EXAMPLE9a_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(EXAMPLE9a_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/9a-PixelDetector)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9a-PixelDetector/run/scripts/startFairMQEx9Bin.sh.in                
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9a-PixelDetector/startFairMQEx9Bin.sh )

set(EXAMPLE9_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(EXAMPLE9_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/9-PixelDetector/bin)
set(EXAMPLE9a_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(EXAMPLE9a_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/9a-PixelDetector/bin)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9a-PixelDetector/run/scripts/startFairMQEx9Bin.sh.in      
		${CMAKE_BINARY_DIR}/examples/MQ/9a-PixelDetector/run/scripts/startFairMQEx9Bin.sh_install )

set(EXAMPLE9_INSTALL_BIN share/fairbase/examples/MQ/9a-PixelDetector/bin)
set(EXAMPLE9a_INSTALL_BIN share/fairbase/examples/MQ/9a-PixelDetector/bin)

Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9a-PixelDetector/run/scripts/startFairMQEx9Bin.sh_install
        DESTINATION ${EXAMPLE9a_INSTALL_BIN}
        RENAME startFairMQEx9Bin.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)


set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})


Set(Exe_Names
    ex9a-processorBin
)

set(Exe_Source
    runEx9TaskProcessorBin.cxx
)


List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)


set(BIN_DESTINATION share/fairbase/examples/MQ/9a-PixelDetector/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/9a-PixelDetector")

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES Pixel PixelAlt)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})
