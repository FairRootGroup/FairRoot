 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libLmdMQSamplerExample" 

set(INCLUDE_DIRECTORIES
    ${BASE_INCLUDE_DIRECTORIES}
    ${CMAKE_SOURCE_DIR}/fairmq
    ${CMAKE_SOURCE_DIR}/fairmq/devices
    ${CMAKE_SOURCE_DIR}/fairmq/options
    ${CMAKE_SOURCE_DIR}/fairmq/tools

    ${CMAKE_SOURCE_DIR}/base/MQ
    ${CMAKE_SOURCE_DIR}/base/MQ/devices
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Sampler
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Storage
    ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools

    ${CMAKE_SOURCE_DIR}/example/MQ/LmdSampler
    ${CMAKE_SOURCE_DIR}/example/MQ/LmdSampler/devices
    ${CMAKE_SOURCE_DIR}/example/MQ/LmdSampler/unpacker

    ${CMAKE_SOURCE_DIR}/example/Tutorial7/run/helper_functions
    
    ${CMAKE_SOURCE_DIR}/MbsAPI

    ${CMAKE_SOURCE_DIR}/example/Tutorial8
    ${CMAKE_SOURCE_DIR}/example/Tutorial8/src
    ${CMAKE_SOURCE_DIR}/example/Tutorial8/macro
    
)

Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZMQ_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

#configure_file( ${CMAKE_SOURCE_DIR}/example/MQ/LmdSampler/macro/startTuto7Sink.sh.in ${CMAKE_BINARY_DIR}/bin/startTuto7Sink.sh )
#configure_file( ${CMAKE_SOURCE_DIR}/example/MQ/LmdSampler/options/tuto7Config.cfg.in ${CMAKE_BINARY_DIR}/bin/config/tuto7Config.cfg)
configure_file( ${CMAKE_SOURCE_DIR}/example/MQ/LmdSampler/macro/startLmdMQChain.sh.in ${CMAKE_BINARY_DIR}/bin/startLmdMQChain.sh)


set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

if(DDS_PATH)
  set(LINK_DIRECTORIES
    ${LINK_DIRECTORIES}
    ${DDS_PATH}/lib
  )
endif(DDS_PATH)

link_directories(${LINK_DIRECTORIES})

Set(SRCS
    unpacker/FairTut8Unpacker.cxx
)

Set(DEPENDENCIES
    Base MbsAPI Tutorial8
)

Set(LINKDEF LmdSamplerLinkDef.h)
Set(LIBRARY_NAME LmdMQSampler)



GENERATE_LIBRARY()


Set(Exe_Names
    runLmdSampler
    runTut8MQUnpacker
    runTut8Sink
)

set(Exe_Source
    run/runLmdSampler.cxx
    run/runTut8MQUnpacker.cxx
    run/runTut8Sink.cxx
)



List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    #Set(DEPENDENCIES LmdMQSamplerExample ${UBUNTU_GREATERTHAN_v11_LINKER_FLAG})
    Set(DEPENDENCIES
        #Base 
        FairMQ 
        BaseMQ 
        boost_thread 
        boost_system 
        boost_serialization 
        boost_program_options 
        Tutorial8
        LmdMQSampler
    )
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})



