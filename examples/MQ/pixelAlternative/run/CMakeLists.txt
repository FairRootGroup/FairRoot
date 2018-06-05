 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(MaxTestTime 30)

GENERATE_TEST_SCRIPT(${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelAlternative/startFairMQPixAlt.sh ${CMAKE_CURRENT_BINARY_DIR})

Add_Test(pixalt_static
	${CMAKE_CURRENT_BINARY_DIR}/startFairMQPixAlt.sh --work-dir ${CMAKE_BINARY_DIR} --max-index 10000 --aggregate 100 --processors 5 --command static --force-kill true)
Set_Tests_Properties(pixalt_static PROPERTIES DEPENDS pixel_static)
Set_Tests_Properties(pixalt_static PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(pixalt_static PROPERTIES PASS_REGULAR_EXPRESSION "Shell script finished successfully")

set(INCLUDE_DIRECTORIES
    ${BASE_INCLUDE_DIRECTORIES}
    ${CMAKE_SOURCE_DIR}/fairmq
    ${CMAKE_SOURCE_DIR}/fairmq/devices
    ${CMAKE_SOURCE_DIR}/fairmq/options
    ${CMAKE_SOURCE_DIR}/fairmq/tools
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Sampler
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Storage
    ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/src
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelAlternative/src
    ${CMAKE_SOURCE_DIR}/examples/MQ/pixelAlternative/src/devices
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

set(PIXEL_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(PIXEL_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector)
set(PIXALT_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(PIXALT_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelAlternative)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelAlternative/run/scripts/startFairMQPixAlt.sh.in
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelAlternative/startFairMQPixAlt.sh @ONLY )

set(PIXEL_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(PIXEL_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/pixelDetector/bin)
set(PIXALT_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(PIXALT_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/pixelAlternative/bin)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelAlternative/run/scripts/startFairMQPixAlt.sh.in
		${CMAKE_BINARY_DIR}/examples/MQ/pixelAlternative/run/scripts/startFairMQPixAlt.sh_install @ONLY )

set(PIXEL_INSTALL_BIN share/fairbase/examples/MQ/pixelAlternative/bin)
set(PIXALT_INSTALL_BIN share/fairbase/examples/MQ/pixelAlternative/bin)

Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelAlternative/run/scripts/startFairMQPixAlt.sh_install
        DESTINATION ${PIXALT_INSTALL_BIN}
        RENAME startFairMQPixAlt.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)


set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})


Set(Exe_Names
    pixalt-samplerBin
    pixalt-sinkBin
    pixalt-processorBin
)

set(Exe_Source
    runPixAltSamplerBin.cxx
    runPixAltFileSinkBin.cxx
    runPixAltTaskProcessorBin.cxx
)


List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)


set(BIN_DESTINATION share/fairbase/examples/MQ/pixelAlternative/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/pixelAlternative")

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES Pixel PixelAlt)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})
