################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target Tutorial4)

set(sources
  data/FairTutorialDet4Point.cxx
  data/FairTutorialDet4Hit.cxx

  mc/FairTutorialDet4.cxx
  mc/FairTutorialDet4Geo.cxx

  param/FairTutorialDet4ContFact.cxx
  param/FairTutorialDet4GeoPar.cxx
  param/FairTutorialDet4MisalignPar.cxx

  reco/FairTutorialDet4HitProducerIdealMisalign.cxx
  reco/FairTutorialDet4StraightLineFitter.cxx
  reco/FairTutorialDet4MilleWriter.cxx

  tools/FairTutorialDet4GeoHandler.cxx
  tools/Mille.cc
)

if(${ROOT_HAS_OPENGL})
  list(APPEND sources
    display/FairTutorialDet4PointDraw.cxx
  )
endif()

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)
list(APPEND headers tools/Mille.h)
fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::FairTools # FairLogger
  FairRoot::MCStack
  FairRoot::GeoBase
  FairRoot::ParBase
  FairRoot::Gen
  $<$<BOOL:${BUILD_EVENTDISPLAY}>:FairRoot::EventDisplay>

  ROOT::Core
  ROOT::Physics
  ROOT::Geom
  ${VMC_LIB} # TVirtualMC
  ROOT::MathCore
  ROOT::Hist
  $<$<BOOL:${BUILD_EVENTDISPLAY}>:ROOT::Eve>
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF Tutorial4LinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
