################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
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
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
)

# Geant4 uses namespace since 10.5
if(${Geant4_VERSION} VERSION_LESS "10.6")
  set(targetG4processes G4processes)
else()
  set(targetG4processes Geant4::G4processes)
endif()

target_link_libraries(${target} PUBLIC
  FairRoot::FairTools
  FairRoot::Base # FairDetector,
  FairRoot::GeoBase

  ${targetG4processes}
  geant4vmc

  Geom # TGeoManager
  Core # Rtypes
  ${VMCLIB} # TVirtualMC
  EG # TParticle
  Physics # TVector
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FastSimLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
