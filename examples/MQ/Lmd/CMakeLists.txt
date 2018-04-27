 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

set(INCLUDE_DIRECTORIES
    ${BASE_INCLUDE_DIRECTORIES}
    ${FairMQ_INCDIR}
    ${FairMQ_INCDIR}/fairmq

    ${CMAKE_SOURCE_DIR}/base/MQ/devices
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Storage
    ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools

    ${CMAKE_SOURCE_DIR}/examples/MQ/Lmd
    ${CMAKE_SOURCE_DIR}/examples/MQ/Lmd/unpacker

    ${CMAKE_SOURCE_DIR}/MbsAPI

    ${CMAKE_SOURCE_DIR}/examples/advanced/MbsTutorial/src
)

Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZeroMQ_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/Lmd/run/startMQExLmd.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/Lmd/startMQExLmd.sh)
configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/Lmd/run/ex-lmd.json
               ${CMAKE_BINARY_DIR}/bin/config/ex-lmd.json)

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})

Set(SRCS
    unpacker/FairMBSUnpacker.cxx
)

Set(DEPENDENCIES
  Base MbsAPI MbsTutorial FairMQ::FairMQ
)

Set(LINKDEF LmdLinkDef.h)
Set(LIBRARY_NAME ExLmd)

GENERATE_LIBRARY()

Set(Exe_Names
    ex-lmd-sampler
    ex-lmd-mbs-unpacker
    ex-lmd-mbs-sink
)

set(Exe_Source
    run/runLmdSampler.cxx
    run/runMBSMQUnpacker.cxx
    run/runMBSSink.cxx
)

List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)

set(BIN_DESTINATION share/fairbase/examples/MQ/Lmd/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/Lmd")

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES
        FairMQ::FairMQ
        BaseMQ
        ${Boost_THREAD_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_SERIALIZATION_LIBRARY}
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        MbsTutorial
        ExLmd
    )
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})
