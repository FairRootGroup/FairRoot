################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ParBase)

set(sources
  FairContFact.cxx
  FairDetParAsciiFileIo.cxx
  FairDetParIo.cxx
  FairDetParRootFileIo.cxx
  FairGenericParAsciiFileIo.cxx
  FairGenericParRootFileIo.cxx
  FairParamList.cxx
  FairParAsciiFileIo.cxx
  FairParGenericSet.cxx
  FairParIo.cxx
  FairParRootFileIo.cxx
  FairParSet.cxx
  FairRtdbRun.cxx
  FairRuntimeDb.cxx
)

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)
fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::FairTools

  ROOT::Core
  ROOT::RIO
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF ParBaseLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
