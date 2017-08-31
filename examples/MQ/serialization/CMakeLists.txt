################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Create a default directory that will hold root input/output data file
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data_io)

# Data generator
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data_generator/startMQSerializationGenerateData.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startMQSerializationGenerateData.sh )

# start MQ chains
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/startMQSerializationEx1.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startMQSerializationEx1.sh )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/startMQSerializationEx2.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startMQSerializationEx2.sh )

# test scripts
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test/startTestSerializationEx1.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startTestSerializationEx1.sh )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test/startTestSerializationEx2.sh.in
               ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startTestSerializationEx2.sh )

if(Protobuf_FOUND)
  add_custom_command(
    OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/Tuto7Payload.pb.h
    ${CMAKE_CURRENT_BINARY_DIR}/Tuto7Payload.pb.cc
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I=. --cpp_out=${CMAKE_CURRENT_BINARY_DIR} Tuto7Payload.proto
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/data_struct
  )

  set(no_dict_srcs ${CMAKE_CURRENT_BINARY_DIR}/Tuto7Payload.pb.cc)
endif()

set(dependencies
  Base
  FairMQ::FairMQ
  BaseMQ
  Boost::serialization
  # Minuit
  # XMLIO
  # MathMore
)

if(Protobuf_FOUND)
  list(APPEND dependencies protobuf::libprotobuf)
endif()

add_fairroot_library(SerializationExample
  DEPENDENCIES ${dependencies}
  LINKDEF SerializationExampleLinkDef.h
  NO_DICT_SRCS ${no_dict_srcs}

  SOURCES
  data_struct/MyDigi.cxx
  data_struct/MyHit.cxx
  data_struct/MyPodData.cxx

  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/data_generator
  ${CMAKE_CURRENT_SOURCE_DIR}/data_struct
  ${CMAKE_CURRENT_SOURCE_DIR}/src/1-simple/devices
  ${CMAKE_CURRENT_SOURCE_DIR}/src/2-multi-part/devices
)

set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/serialization")
add_fairroot_multiple_executables(
  NAMES
  serialization-Ex1-Sampler
  serialization-Ex1-Processor
  serialization-Ex1-Sink

  serialization-Ex2-Sampler
  serialization-Ex2-Processor
  serialization-Ex2-Sink

  SOURCES
  src/1-simple/run/runEx1Sampler.cxx
  src/1-simple/run/runEx1Processor.cxx
  src/1-simple/run/runEx1Sink.cxx

  src/2-multi-part/run/runEx2Sampler.cxx
  src/2-multi-part/run/runEx2Processor.cxx
  src/2-multi-part/run/runEx2Sink.cxx

  BIN_DESTINATION ${FAIRROOT_INSTALL_DATADIR}/examples/MQ/serialization/bin
  DEPENDENCIES SerializationExample
)

add_fairroot_executable(serialization-Ex-generate-data
  SOURCES data_generator/runGenerateData.cxx
  DEPENDENCIES SerializationExample RooFitCore RooFit Foam
)

add_test(NAME run_serialization_ex1 COMMAND ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startTestSerializationEx1.sh)
set_tests_properties(run_serialization_ex1 PROPERTIES TIMEOUT "30")
set_tests_properties(run_serialization_ex1 PROPERTIES
  PASS_REGULAR_EXPRESSION "Data generation successful"
  PASS_REGULAR_EXPRESSION "Sent 100 messages!"
  PASS_REGULAR_EXPRESSION "Received 100 and sent 100 messages!"
  PASS_REGULAR_EXPRESSION "Received 100 messages!"
)

add_test(NAME MQ.ex-serialization2 COMMAND ${CMAKE_BINARY_DIR}/bin/examples/MQ/serialization/startTestSerializationEx2.sh)
set_tests_properties(MQ.ex-serialization2 PROPERTIES DEPENDS MQ.ex-serialization1)
set_tests_properties(MQ.ex-serialization2 PROPERTIES TIMEOUT "30")
set_tests_properties(MQ.ex-serialization2 PROPERTIES
  PASS_REGULAR_EXPRESSION "Data generation successful"
  PASS_REGULAR_EXPRESSION "Sent 100 messages!"
  PASS_REGULAR_EXPRESSION "Received 100 and sent 100 messages!"
  PASS_REGULAR_EXPRESSION "Received 100 messages!"
)
