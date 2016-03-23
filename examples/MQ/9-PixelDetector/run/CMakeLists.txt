 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

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


configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9.sh.in         ${CMAKE_BINARY_DIR}/bin/startFairMQEx9.sh )

set(EXAMPLE9_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(EXAMPLE9_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9New.sh.in      ${CMAKE_BINARY_DIR}/bin/startFairMQEx9New.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_2Levels.sh.in ${CMAKE_BINARY_DIR}/bin/startFairMQEx9_2Levels.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_3Levels.sh.in ${CMAKE_BINARY_DIR}/bin/startFairMQEx9_3Levels.sh )

set(EXAMPLE9_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(EXAMPLE9_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/bin)
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9New.sh.in      ${CMAKE_BINARY_DIR}/bin/startFairMQEx9New.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_2Levels.sh.in ${CMAKE_BINARY_DIR}/bin/startFairMQEx9_2Levels.sh_install )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/run/scripts/startFairMQEx9_3Levels.sh.in ${CMAKE_BINARY_DIR}/bin/startFairMQEx9_3Levels.sh_install )

Install(FILES ${CMAKE_BINARY_DIR}/bin/startFairMQEx9New.sh_install
        DESTINATION bin
        RENAME startFairMQEx9New.sh)
Install(FILES ${CMAKE_BINARY_DIR}/bin/startFairMQEx9_2Levels.sh_install
        DESTINATION bin
        RENAME startFairMQEx9_2Levels.sh)
Install(FILES ${CMAKE_BINARY_DIR}/bin/startFairMQEx9_3Levels.sh_install
        DESTINATION bin
        RENAME startFairMQEx9_3Levels.sh)

Install(FILES options/Pixel9MQConfig_Multipart.json options/Pixel9MQConfig_2Levels.json options/Pixel9MQConfig_3Levels.json
        DESTINATION share/fairbase/examples/MQ/9-PixelDetector/run/options/
       )


set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})


Set(Exe_Names
    FairMQEx9Splitter
    FairMQEx9Merger

    FairMQEx9Sampler
    FairMQEx9TaskProcessor
    FairMQEx9FileSink
)

set(Exe_Source
    runSplitterT9.cxx
    runMergerT9.cxx

    runEx9Sampler.cxx
    runEx9TaskProcessor.cxx
    runEx9FileSink.cxx
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







