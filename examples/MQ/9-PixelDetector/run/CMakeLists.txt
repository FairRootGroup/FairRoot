 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(MaxTestTime 30)

GENERATE_TEST_SCRIPT(${CMAKE_BINARY_DIR}/bin/startFairMQEx9_Static.sh ${CMAKE_CURRENT_BINARY_DIR})

Add_Test(ex9_static
	${CMAKE_CURRENT_BINARY_DIR}/startFairMQEx9_Static.sh)
Set_Tests_Properties(ex9_static PROPERTIES DEPENDS ex9_digi_TGeant3)
Set_Tests_Properties(ex9_static PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(ex9_static PROPERTIES PASS_REGULAR_EXPRESSION "Shell script finished successfully")


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

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})


set(EXAMPLE9_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(EXAMPLE9_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9New.sh.in                
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9New.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_2Levels.sh.in           
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9_2Levels.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_3Levels.sh.in           
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9_3Levels.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin.sh.in                
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9Bin.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin_2Samplers.sh.in      
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9Bin_2Samplers.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9BinProxy.sh.in 
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9Bin_2Samplers.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger.sh.in      
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9Merger.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger2Levels.sh.in      
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9Merger2Levels.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/ex9-dds-topology.xml
		${CMAKE_BINARY_DIR}/bin/ex9-dds-topology.xml )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_Static.sh.in
		${CMAKE_BINARY_DIR}/bin/startFairMQEx9_Static.sh )

set(EXAMPLE9_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(EXAMPLE9_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/bin)
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9New.sh.in      
		${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9New.sh_install )
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

Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9New.sh_install
        DESTINATION bin
        RENAME startFairMQEx9New.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_2Levels.sh_install
        DESTINATION bin
        RENAME startFairMQEx9_2Levels.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_3Levels.sh_install
        DESTINATION bin
        RENAME startFairMQEx9_3Levels.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin.sh_install
        DESTINATION bin
        RENAME startFairMQEx9Bin.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Bin_2Samplers.sh_install
        DESTINATION bin
        RENAME startFairMQEx9Bin_2Samplers.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9BinProxy.sh_install
        DESTINATION bin
        RENAME startFairMQEx9BinProxy.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger.sh_install
        DESTINATION bin
        RENAME startFairMQEx9Merger.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9Merger2Levels.sh_install
        DESTINATION bin
        RENAME startFairMQEx9Merger2Levels.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/ex9-dds-topology.xml_install
        DESTINATION bin
        RENAME ex9-dds-topology.xml PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_Static.sh_install
        DESTINATION bin
        RENAME startFairMQEx9_Static.sh PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)

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

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES Pixel)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})

If(DDS_FOUND)
  Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${CMAKE_SOURCE_DIR}/parmq
    ${DDS_INCLUDE_DIR}
  )

  Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

  Set(LINK_DIRECTORIES
    ${LINK_DIRECTORIES}
    ${DDS_LIBRARY_DIR}
  )

  Link_Directories(${LINK_DIRECTORIES})

  Set(DEPENDENCIES
    ${DEPENDENCIES}
    dds_intercom_lib
  )

  Set(Dds_Names
      ex9-dds-sampler
      ex9-dds-processor
      ex9-dds-sink

      dds-parmq-server
  )

  set(Dds_Source
      ddsEx9Sampler.cxx
      ddsEx9TaskProcessor.cxx
      ddsEx9FileSink.cxx

      ddsParameterMQServer.cxx
  )


  List(LENGTH Dds_Names _length)
  Math(EXPR _length ${_length}-1)

  ForEach(_file RANGE 0 ${_length})
      List(GET Dds_Names ${_file} _name)
      List(GET Dds_Source ${_file} _src)
      Set(EXE_NAME ${_name})
      Set(SRCS ${_src})
      Set(DEPENDENCIES Pixel ParMQ dds_intercom_lib)
      GENERATE_EXECUTABLE()
  EndForEach(_file RANGE 0 ${_length})
EndIf(DDS_FOUND)





