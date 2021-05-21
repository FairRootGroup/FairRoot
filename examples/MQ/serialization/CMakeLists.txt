################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ExSerialization)

set(sources
  data/MyDigi.cxx
  data/MyHit.cxx
  data/MyPodData.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/1-simple>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/2-multipart>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data_generator>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::ParBase

  FairMQ::FairMQ
  Boost::serialization

  ROOT::Core
  ROOT::MathCore
  ROOT::RIO
  ROOT::Tree
  ROOT::RooFit
  ROOT::RooFitCore
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF SerializationExampleLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(ex-serialization1-sampler 1-simple/runEx1Sampler.cxx)
target_link_libraries(ex-serialization1-sampler PRIVATE FairRoot::ExSerialization FairMQ::FairMQ)

add_executable(ex-serialization1-processor 1-simple/runEx1Processor.cxx)
target_link_libraries(ex-serialization1-processor PRIVATE FairRoot::ExSerialization FairMQ::FairMQ)

add_executable(ex-serialization1-sink 1-simple/runEx1Sink.cxx)
target_link_libraries(ex-serialization1-sink PRIVATE FairRoot::ExSerialization FairMQ::FairMQ)

add_executable(ex-serialization2-sampler 2-multipart/runEx2Sampler.cxx)
target_link_libraries(ex-serialization2-sampler PRIVATE FairRoot::ExSerialization FairMQ::FairMQ)

add_executable(ex-serialization2-processor 2-multipart/runEx2Processor.cxx)
target_link_libraries(ex-serialization2-processor PRIVATE FairRoot::ExSerialization FairMQ::FairMQ)

add_executable(ex-serialization2-sink 2-multipart/runEx2Sink.cxx)
target_link_libraries(ex-serialization2-sink PRIVATE FairRoot::ExSerialization FairMQ::FairMQ)

add_executable(ex-serialization-generate-data data_generator/runGenerateData.cxx)
target_link_libraries(ex-serialization-generate-data PRIVATE FairRoot::ExSerialization FairMQ::FairMQ)

# Create a directory that will hold root input/output data file
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data_io)

# Data generator
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data_generator/startSerializationGenerateData.sh.in ${CMAKE_CURRENT_BINARY_DIR}/startSerializationGenerateData.sh)

# start MQ chains
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/1-simple/startSerializationEx1.sh.in    ${CMAKE_CURRENT_BINARY_DIR}/startSerializationEx1.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/2-multipart/startSerializationEx2.sh.in ${CMAKE_CURRENT_BINARY_DIR}/startSerializationEx2.sh)

# test scripts
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/1-simple/testSerializationEx1.sh.in    ${CMAKE_CURRENT_BINARY_DIR}/testSerializationEx1.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/2-multipart/testSerializationEx2.sh.in ${CMAKE_CURRENT_BINARY_DIR}/testSerializationEx2.sh)

install(TARGETS
  ex-serialization1-sampler
  ex-serialization1-processor
  ex-serialization1-sink
  ex-serialization2-sampler
  ex-serialization2-processor
  ex-serialization2-sink
  ex-serialization-generate-data
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/serialization/bin
)

add_test(NAME ex_MQ_serialization1 COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSerializationEx1.sh)
set_tests_properties(ex_MQ_serialization1 PROPERTIES
  TIMEOUT "30"
  PASS_REGULAR_EXPRESSION "Received 100 messages!"
)

add_test(NAME ex_MQ_serialization2 COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSerializationEx2.sh)
set_tests_properties(ex_MQ_serialization2 PROPERTIES
  DEPENDS ex_MQ_serialization1
  TIMEOUT "30"
  PASS_REGULAR_EXPRESSION "Received 100 messages!"
)
