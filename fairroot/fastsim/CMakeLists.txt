################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target FastSim)

set(sources
  FairFastSimDetector.cxx
  FairFastSimModel.cxx
  FairFastSimRunConfiguration.cxx
  FairFastSimulation.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})
# Keep old filesystem name
set_target_properties(${target} PROPERTIES OUTPUT_NAME FairFastSim)

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Geant4 uses namespace since 10.5
if(${Geant4_VERSION} VERSION_LESS "10.6")
  set(targetG4processes G4processes)
else()
  set(targetG4processes Geant4::G4processes)
endif()

target_link_libraries(${target}
  PUBLIC
  FairRoot::Base # FairDetector,

  ROOT::Core # Rtypes

  ${targetG4processes}
  geant4vmc

  PRIVATE
  FairRoot::Tools
  FairRoot::GeoBase
  ROOT::Geom # TGeoManager
  ${VMCLIB} # TVirtualMC
  ROOT::EG # TParticle
  ROOT::Physics # TVector
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF LinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

# exchange linker flag --enable-new-dtags by --disable-new-dtags
# to use RPATH instead of RUNPATH in the generated library. When using
# RUNPATH on many Linux systems the indirect library dependencies are not
# found when linking an executable which uses the FairFastSim library and
# such that the linking fails. This bug somehow depends on the Linux system
# and the linker version.
# No better solution was found so far. In principle there should be a way
# such that also when using RUNPATH the indirect dependencies are properly
# found.
# Send patches to upstrean such that that geant4, geant4_vmc and vgm
# correctly build libraries with RPATH information.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(new_linker_flags ${CMAKE_SHARED_LINKER_FLAGS})
  string(REGEX REPLACE "--enable-new-dtags" "--disable-new-dtags" CMAKE_SHARED_LINKER_FLAGS ${new_linker_flags})
endif()

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
