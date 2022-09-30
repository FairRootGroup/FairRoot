################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target TrkBase)

set(sources
  FairGeaneUtil.cxx
  FairTrackPar.cxx
  FairTrackParH.cxx
  FairTrackParP.cxx

  FairPropagator.cxx
  FairRKPropagator.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::FairTools
  FairRoot::Base # FairRunAna, FairField

  ROOT::Core
  ROOT::Physics
  ROOT::MathCore
  ROOT::Matrix
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF TrackBaseLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${PROJECT_INSTALL_INCLUDEDIR})
