################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target Gen)

set(sources
  FairAsciiGenerator.cxx
  FairBoxGenerator.cxx
  FairEvtGenGenerator.cxx
  FairIonGenerator.cxx
  FairParticleGenerator.cxx
  FairShieldGenerator.cxx
  FairUrqmdGenerator.cxx
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
  FairRoot::Base # FairPrimaryGenerator, FairGenerator, FairIon, FairParticle, FairRunSim
  FairRoot::FairTools

  ROOT::Core
  ROOT::EG
  ROOT::MathCore
  ROOT::Hist
  ROOT::Physics
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF GenLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
