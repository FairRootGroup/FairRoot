 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libSerializationExample"

set(INCLUDE_DIRECTORIES
    ${BASE_INCLUDE_DIRECTORIES}
    ${FairMQ_INCDIR}
    ${FairMQ_INCDIR}/fairmq
    ${CMAKE_SOURCE_DIR}/base/MQ
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Storage
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
    ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data_generator
    ${CMAKE_CURRENT_SOURCE_DIR}/data_struct
    ${CMAKE_CURRENT_SOURCE_DIR}/1-simple/
    ${CMAKE_CURRENT_SOURCE_DIR}/2-multipart/
)

set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

# Data generator
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data_generator/startSerializationGenerateData.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startSerializationGenerateData.sh)

# start MQ chains
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/1-simple/startSerializationEx1.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startSerializationEx1.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/2-multipart/startSerializationEx2.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startSerializationEx2.sh)

# test scripts
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/1-simple/testSerializationEx1.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/testSerializationEx1.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/2-multipart/testSerializationEx2.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/testSerializationEx2.sh)

# Create a default directory that will hold root input/output data file
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/data_io)

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})

set(SRCS
    data_struct/MyDigi.cxx
    data_struct/MyHit.cxx
    data_struct/MyPodData.cxx
)

set(LINKDEF SerializationExampleLinkDef.h)
set(LIBRARY_NAME SerializationExample)

set(DEPENDENCIES
    Base
    FairMQ::FairMQ
    BaseMQ
    ${Boost_SERIALIZATION_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    Minuit
    XMLIO
    MathMore
)

GENERATE_LIBRARY()

set(Exe_Names
    ex-serialization1-sampler
    ex-serialization1-processor
    ex-serialization1-sink

    ex-serialization2-sampler
    ex-serialization2-processor
    ex-serialization2-sink
)

set(Exe_Source
    1-simple/runEx1Sampler.cxx
    1-simple/runEx1Processor.cxx
    1-simple/runEx1Sink.cxx

    2-multipart/runEx2Sampler.cxx
    2-multipart/runEx2Processor.cxx
    2-multipart/runEx2Sink.cxx
)

List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)

set(BIN_DESTINATION share/fairbase/examples/MQ/serialization/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/serialization")

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    set(EXE_NAME ${_name})
    set(SRCS ${_src})
    # set(DEPENDENCIES SerializationExample ${UBUNTU_GREATERTHAN_v11_LINKER_FLAG})
    set(DEPENDENCIES SerializationExample)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})

set(EXE_NAME ex-serialization-generate-data)
set(SRCS data_generator/runGenerateData.cxx)
set(DEPENDENCIES SerializationExample RooFitCore RooFit Foam)
GENERATE_EXECUTABLE()

add_test(NAME MQ.ex-serialization1 COMMAND ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/testSerializationEx1.sh)
set_tests_properties(MQ.ex-serialization1 PROPERTIES TIMEOUT "30")
set_tests_properties(MQ.ex-serialization1 PROPERTIES
    PASS_REGULAR_EXPRESSION "Data generation successful"
    PASS_REGULAR_EXPRESSION "Sent 100 messages!"
    PASS_REGULAR_EXPRESSION "Received 100 and sent 100 messages!"
    PASS_REGULAR_EXPRESSION "Received 100 messages!"
    )

add_test(NAME MQ.ex-serialization2 COMMAND ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/testSerializationEx2.sh)
set_tests_properties(MQ.ex-serialization2 PROPERTIES DEPENDS MQ.ex-serialization1)
set_tests_properties(MQ.ex-serialization2 PROPERTIES TIMEOUT "30")
set_tests_properties(MQ.ex-serialization2 PROPERTIES
    PASS_REGULAR_EXPRESSION "Data generation successful"
    PASS_REGULAR_EXPRESSION "Sent 100 messages!"
    PASS_REGULAR_EXPRESSION "Received 100 and sent 100 messages!"
    PASS_REGULAR_EXPRESSION "Received 100 messages!"
    )
