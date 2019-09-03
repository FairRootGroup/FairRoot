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

set(headers
  FairAsciiGenerator.h
  FairBoxGenerator.h
  FairEvtGenGenerator.h
  FairIonGenerator.h
  FairParticleGenerator.h
  FairShieldGenerator.h
  FairUrqmdGenerator.h
)

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

target_link_libraries(${target} PUBLIC
  FairRoot::FairTools
  FairRoot::Base # FairPrimaryGenerator, FairGenerator, FairIon, FairParticle, FairRunSim
  # TODO: clean the following
  # needed: Rtypes, TRandom, TParticlePDG, TDatabasePDG, TMath, TF1, TParticle, TObjArray, TVector3, TLorentzVector
  Core
  EG
  MathCore
  Physics
  RIO
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF GenLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
