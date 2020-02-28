################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target MCStack)

set(sources
  FairMCTrack.cxx
  FairStack.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

list(APPEND headers
  FairDetectorList.h
)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::FairTools # FairLogger

  ROOT::Core
  ROOT::Physics # TLorentzVector, TVector3
  ROOT::MathCore # TMath
  ROOT::EG # TDatabasePDG, TParticle
  ${VMC_LIB} # TVirtualMC
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF MCStackLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
