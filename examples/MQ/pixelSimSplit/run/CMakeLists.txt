 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(MaxTestTime 90)

GENERATE_TEST_SCRIPT(${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelSimSplit/test-splitMC.sh ${CMAKE_CURRENT_BINARY_DIR})
GENERATE_TEST_SCRIPT(${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelSimSplit/test-splitMQ.sh ${CMAKE_CURRENT_BINARY_DIR})

#Add_Test(pixelSplitDDS
#       ${CMAKE_CURRENT_BINARY_DIR}/test-splitMC.sh)
#Set_Tests_Properties(pixelSplitDDS PROPERTIES TIMEOUT ${MaxTestTime})
#Set_Tests_Properties(pixelSplitDDS PROPERTIES PASS_REGULAR_EXPRESSION "Shell script finished successfully")

Add_Test(pixelSplitMQ
         ${CMAKE_CURRENT_BINARY_DIR}/test-splitMQ.sh)
Set_Tests_Properties(pixelSplitMQ PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(pixelSplitMQ PROPERTIES PASS_REGULAR_EXPRESSION "Shell script finished successfully")

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
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelSimSplit/src
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelSimSplit/src/devices
)

Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZeroMQ_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(EXAMPLE_LIBRARY_EXTENSION so)
If(APPLE)
  set(EXAMPLE_LIBRARY_EXTENSION dylib)
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


set(BIN_DESTINATION share/fairbase/examples/MQ/pixelSimSplit/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/pixelSimSplit")

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES Pixel SimMQ)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})

Message(STATUS "Looking for DDS!!!")
find_package(DDS)
set(DDS_LOCATION ${DDS_INCLUDE_DIR}/../)
MESSAGE(STATUS "Set ${DDS_LOCATION} as place to look for DDS_env.sh")

set(SPLITMC_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelSimSplit)
set(SPLITMC_FILE_LOCATION ${CMAKE_SOURCE_DIR}/examples/MQ/pixelSimSplit/run/scripts/)
set(PIXEL_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelSimSplit/run/scripts/splitMC-topology.xml
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelSimSplit/splitMC-topology.xml )

set(SPLITMC_FILE_LOCATION ${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelSimSplit)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelSimSplit/run/scripts/splitMC-topology.xml
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelSimSplit/test-splitMC.xml )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelSimSplit/run/scripts/test-splitMC.sh.in
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelSimSplit/test-splitMC.sh)
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelSimSplit/run/scripts/test-splitMQ.sh.in
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelSimSplit/test-splitMQ.sh)
