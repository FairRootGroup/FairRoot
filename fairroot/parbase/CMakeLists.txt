################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
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

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target}
  PUBLIC
  ROOT::Core
  ROOT::RIO

  PRIVATE
  FairRoot::Tools

  FairLogger::FairLogger
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF LinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
