 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(MaxTestTime 60)

GENERATE_TEST_SCRIPT(${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/startFairMQPixelSimulation.sh ${CMAKE_CURRENT_BINARY_DIR})

Add_Test(pixel_simulation
       ${CMAKE_CURRENT_BINARY_DIR}/startFairMQPixelSimulation.sh --work-dir ${CMAKE_BINARY_DIR} -n 1000 -g TGeant3 -c static -s 6 --force-kill true -m 20)
Set_Tests_Properties(pixel_simulation PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(pixel_simulation PROPERTIES PASS_REGULAR_EXPRESSION "Shell script finished successfully")

GENERATE_TEST_SCRIPT(${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/startFairMQPixel.sh ${CMAKE_CURRENT_BINARY_DIR})

Add_Test(pixel_static
	${CMAKE_CURRENT_BINARY_DIR}/startFairMQPixel.sh --work-dir ${CMAKE_BINARY_DIR} -p 3 --command static --force-kill true)
Set_Tests_Properties(pixel_static PROPERTIES DEPENDS pixel_dbin_TGeant3)
Set_Tests_Properties(pixel_static PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(pixel_static PROPERTIES PASS_REGULAR_EXPRESSION "Shell script finished successfully")

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
set(FAIRROOT_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixel.sh.in                
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/startFairMQPixel.sh @ONLY )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelSimulation.sh.in
                ${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/startFairMQPixelSimulation.sh @ONLY )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixel_3Levels.sh.in           
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/startFairMQPixel_3Levels.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelBin.sh.in                
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/startFairMQPixelBin.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelBinProxy.sh.in 
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/startFairMQPixelBinProxy.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelMerger.sh.in      
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/startFairMQPixelMerger.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-topology.xml
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/pixel-dds-topology.xml )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-simulation.xml
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/pixel-dds-simulation.xml )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-chain.xml
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/pixel-dds-chain.xml )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/param/pixel_digi.par
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/param/pixel_digi.par )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/controlDDS.sh.in
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/controlDDS.sh @ONLY)
set(DDS_LOCATION $ENV{DDS_LOCATION})
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/run_pixel_dds_chain.sh.in
		${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector/run_pixel_dds_chain.sh @ONLY)

set(PIXEL_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(PIXEL_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/pixelDetector/bin)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixel.sh.in      
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixel.sh_install @ONLY )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelSimulation.sh.in
                ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelSimulation.sh_install @ONLY )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixel_3Levels.sh.in 
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixel_3Levels.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelBin.sh.in      
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelBin.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelBinProxy.sh.in 
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelBinProxy.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelMerger.sh.in
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelMerger.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-topology.xml
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-topology.xml_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-simulation.xml
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-simulation.xml_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-chain.xml
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-chain.xml_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/controlDDS.sh.in
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/controlDDS.sh_install @ONLY)
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/run/scripts/run_pixel_dds_chain.sh.in
		${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/run_pixel_dds_chain.sh_install @ONLY)

set(PIXEL_INSTALL_BIN share/fairbase/examples/MQ/pixelDetector/bin)

Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixel.sh_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME startFairMQPixel.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelSimulation.sh_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME startFairMQPixelSimulation.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixel_3Levels.sh_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME startFairMQPixel_3Levels.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelBin.sh_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME startFairMQPixelBin.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelBinProxy.sh_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME startFairMQPixelBinProxy.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/startFairMQPixelMerger.sh_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME startFairMQPixelMerger.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-topology.xml_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME pixel-dds-topology.xml PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-simulation.xml_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME pixel-dds-simulation.xml PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/pixel-dds-chain.xml_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME pixel-dds-chain.xml PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/controlDDS.sh_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME controlDDS.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run/scripts/run_pixel_dds_chain.sh_install
        DESTINATION ${PIXEL_INSTALL_BIN}
        RENAME run_pixel_dds_chain.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})


Set(Exe_Names
    pixel-sampler
    pixel-processor
    pixel-sink

    pixel-samplerBin
    pixel-processorBin
    pixel-sinkBin

    pixel-merger

    run-sim
)

set(Exe_Source
    runPixelSampler.cxx
    runPixelTaskProcessor.cxx
    runPixelFileSink.cxx

    runPixelSamplerBin.cxx
    runPixelTaskProcessorBin.cxx
    runPixelFileSinkBin.cxx

    runPixelMerger.cxx

    runMQSim.cxx
)


List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)


set(BIN_DESTINATION share/fairbase/examples/MQ/pixelDetector/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/pixelDetector")

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES Pixel)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})
