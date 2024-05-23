################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ExSerialization)

set(headers
  data/MyDigi.h
  data/MyHit.h
)

add_library(${target} SHARED ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies

  Boost::serialization

  ROOT::Core
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF SerializationExampleLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(ex-serialization-sampler sampler.cxx)
target_link_libraries(ex-serialization-sampler PRIVATE FairRoot::ExSerialization FairRoot::FairMQ)

add_executable(ex-serialization-processor processor.cxx)
target_link_libraries(ex-serialization-processor PRIVATE FairRoot::ExSerialization FairRoot::FairMQ)

add_executable(ex-serialization-sink sink.cxx)
target_link_libraries(ex-serialization-sink PRIVATE FairRoot::ExSerialization FairRoot::FairMQ)

add_executable(ex-serialization-data-generator data_generator/dataGenerator.cxx)
target_link_libraries(ex-serialization-data-generator
  PRIVATE
  FairRoot::ExSerialization
  FairRoot::FairMQ
  ROOT::Gpad
  ROOT::RooFit
  ROOT::RooFitCore
)

# Create a directory that will hold root input/output data file
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data_io)

# Data generator
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data_generator/startDataGenerator.sh.in ${CMAKE_CURRENT_BINARY_DIR}/startDataGenerator.sh)

# launch script
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/startSerializationEx.sh.in ${CMAKE_CURRENT_BINARY_DIR}/startSerializationEx.sh)

# test script
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/testSerializationEx.sh.in ${CMAKE_CURRENT_BINARY_DIR}/testSerializationEx.sh)

install(TARGETS
  ex-serialization-sampler
  ex-serialization-processor
  ex-serialization-sink
  ex-serialization-data-generator
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/serialization/bin
)

add_test(NAME ex_MQ_serialization COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSerializationEx.sh)
set_tests_properties(ex_MQ_serialization PROPERTIES TIMEOUT "30" PASS_REGULAR_EXPRESSION "Received 100 messages!")
