################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target SimMQ)

set(no_dict_sources
  devices/FairMQChunkMerger.cxx
  devices/FairMQPrimaryGeneratorDevice.cxx
  devices/FairMQTransportDevice.cxx
)

fairroot_change_extensions_if_exists(.cxx .h FILES "${no_dict_sources}" OUTVAR no_dict_headers)

list(APPEND no_dict_sources
  devices/FairMQTransportDevice.h
)

fairroot_copy(HEADERS ${no_dict_headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

set(sources
  FairMCSplitEventHeader.cxx
)

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)
fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${no_dict_sources} ${headers} ${no_dict_headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::MCStack
  FairRoot::ParBase
  FairRoot::Pixel

  FairMQ::FairMQ

  ROOT::Core
  ${VMC_LIB} # TVirtualMC
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF SimMQLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
