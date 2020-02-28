 ################################################################################
 #    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

set(target PropagatorExample)

set(sources
  FairTutPropContFact.cxx
  FairTutPropDet.cxx
  FairTutPropGeo.cxx
  FairTutPropGeoPar.cxx
  FairTutPropPoint.cxx
  FairTutPropTr.cxx
)

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)
fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_compile_definitions(${target} PUBLIC ${defs})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::GeoBase # FairGeoSet
  FairRoot::MCStack
  FairRoot::ParBase # FairRuntimeDb, FairContFact, FairParamList
  FairRoot::TrkBase # FairPropagator

  ROOT::Core # Rtypes
  ROOT::MathCore # TRandom
  ROOT::Physics # TVector3, TLorentzVector
  ROOT::RIO # TFile
  ROOT::Tree # TTree
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF TutPropLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
