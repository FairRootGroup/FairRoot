 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(MaxTestTime 30)

GENERATE_TEST_SCRIPT(${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9_Static.sh ${CMAKE_CURRENT_BINARY_DIR})

Add_Test(ex9_static
	${CMAKE_CURRENT_BINARY_DIR}/startFairMQEx9_Static.sh --work-dir ${CMAKE_BINARY_DIR})
Set_Tests_Properties(ex9_static PROPERTIES DEPENDS ex9_digi_TGeant3)
Set_Tests_Properties(ex9_static PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(ex9_static PROPERTIES PASS_REGULAR_EXPRESSION "Shell script finished successfully")

If(DDS_FOUND)
  add_definitions(-DDDS_FOUND)	
EndIf(DDS_FOUND)

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
    ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/src/devices
)

Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZMQ_INCLUDE_DIR}
)

If(DDS_FOUND)
  Set(SYSTEM_INCLUDE_DIRECTORIES
      ${SYSTEM_INCLUDE_DIRECTORIES}
      ${DDS_INCLUDE_DIR}
  )
EndIf(DDS_FOUND)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(NETWORK_INTERFACE eth0)
If(APPLE)
  set(NETWORK_INTERFACE lo0)
EndIf(APPLE)

set(EXAMPLE9_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(EXAMPLE9_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9.sh.in                
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_2Levels.sh.in           
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9_2Levels.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_3Levels.sh.in           
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9_3Levels.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin.sh.in                
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9Bin.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin_2Samplers.sh.in      
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9Bin_2Samplers.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9BinProxy.sh.in 
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9Bin_2Samplers.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger.sh.in      
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9Merger.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger2Levels.sh.in      
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9Merger2Levels.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/ex9-dds-topology.xml
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/ex9-dds-topology.xml )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_Static.sh.in
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/startFairMQEx9_Static.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/param/pixel_digi.par
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/param/pixel_digi.par )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/options/Pixel9MQConfig_Multipart.json
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/options/Pixel9MQConfig_Multipart.json )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/controlDDS.sh.in
		${CMAKE_BINARY_DIR}/bin/examples/MQ/9-PixelDetector/controlDDS.sh @ONLY)

set(EXAMPLE9_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(EXAMPLE9_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/9-PixelDetector/bin)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9.sh.in      
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_2Levels.sh.in 
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_2Levels.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_3Levels.sh.in 
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_3Levels.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin.sh.in      
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin_2Samplers.sh.in      
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin_2Samplers.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9BinProxy.sh.in 
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9BinProxy.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger.sh.in
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger2Levels.sh.in
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger2Levels.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/ex9-dds-topology.xml
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/ex9-dds-topology.xml_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_Static.sh.in
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_Static.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/controlDDS.sh.in
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/controlDDS.sh_install @ONLY)

set(EXAMPLE9_INSTALL_BIN share/fairbase/examples/MQ/9-PixelDetector/bin)

Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_2Levels.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9_2Levels.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_3Levels.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9_3Levels.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9Bin.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin_2Samplers.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9Bin_2Samplers.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9BinProxy.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9BinProxy.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9Merger.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger2Levels.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9Merger2Levels.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/ex9-dds-topology.xml_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME ex9-dds-topology.xml PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_Static.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME startFairMQEx9_Static.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/controlDDS.sh_install
        DESTINATION ${EXAMPLE9_INSTALL_BIN}
        RENAME controlDDS.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)

Install(FILES options/Pixel9MQConfig_Multipart.json options/Pixel9MQConfig_2Levels.json options/Pixel9MQConfig_3Levels.json options/Pixel9MQConfig_Proxy.json options/Pixel9MQConfig_2Samplers.json options/Pixel9MQConfig_Merger.json options/Pixel9MQConfig_Merger2Levels.json options/ex9-dds.json
        DESTINATION share/fairbase/examples/MQ/9-PixelDetector/run/options/
       )


set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})


Set(Exe_Names
    ex9-sampler
    ex9-processor
    ex9-sink

    ex9-samplerBin
    ex9-processorBin
    ex9-sinkBin

    ex9-merger
)

set(Exe_Source
    runEx9Sampler.cxx
    runEx9TaskProcessor.cxx
    runEx9FileSink.cxx

    runEx9SamplerBin.cxx
    runEx9TaskProcessorBin.cxx
    runEx9FileSinkBin.cxx

    runEx9Merger.cxx
)


List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)


set(BIN_DESTINATION share/fairbase/examples/MQ/9-PixelDetector/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/9-PixelDetector")

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES Pixel)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})
