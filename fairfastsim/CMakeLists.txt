################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target FairFastSim)

set(sources
  FairFastSimDetector.cxx
  FairFastSimModel.cxx
  FairFastSimRunConfiguration.cxx
  FairFastSimulation.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCLUDEDIR}>
)

# Geant4 uses namespace since 10.5
if(${Geant4_VERSION} VERSION_LESS "10.6")
  set(targetG4processes G4processes)
else()
  set(targetG4processes Geant4::G4processes)
endif()

target_link_libraries(${target} PUBLIC
  FairRoot::Tools
  FairRoot::Base # FairDetector,
  FairRoot::GeoBase

  ${targetG4processes}
  geant4vmc

  ROOT::Geom # TGeoManager
  ROOT::Core # Rtypes
  ${VMCLIB} # TVirtualMC
  ROOT::EG # TParticle
  ROOT::Physics # TVector
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FastSimLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${PROJECT_INSTALL_INCLUDEDIR})
