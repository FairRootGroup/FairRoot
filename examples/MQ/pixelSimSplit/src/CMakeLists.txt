################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ExSimMQ)

set(no_dict_sources
  devices/FairMQChunkMerger.cxx
  devices/FairMQPrimaryGeneratorDevice.cxx
  devices/FairMQTransportDevice.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${no_dict_sources}" OUTVAR no_dict_headers)

list(APPEND no_dict_sources
  devices/FairMQTransportDevice.h
)

set(sources
  FairMCSplitEventHeader.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${no_dict_sources} ${headers} ${no_dict_headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::ParBase
  FairRoot::ExMCStack
  FairRoot::ExPixel
  FairRoot::FairMQ

  ROOT::Core
  ${VMCLIB}
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF SimMQLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} ${no_dict_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
