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

  $<$<BOOL:${ROOT_HAS_OPENGL}>:display/FairTutorialDet4PointDraw.cxx>

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

set(headers
  data/FairTutorialDet4Point.h
  data/FairTutorialDet4Hit.h

  display/FairTutorialDet4PointDraw.h

  mc/FairTutorialDet4.h
  mc/FairTutorialDet4Geo.h

  param/FairTutorialDet4ContFact.h
  param/FairTutorialDet4GeoPar.h
  param/FairTutorialDet4MisalignPar.h

  reco/FairTutorialDet4HitProducerIdealMisalign.h
  reco/FairTutorialDet4StraightLineFitter.h
  reco/FairTutorialDet4MilleWriter.h

  tools/FairTutorialDet4GeoHandler.h
  tools/Mille.h
)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mc>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/param>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/reco>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::FairTools # FairLogger
  FairRoot::MCStack
  FairRoot::GeoBase
  FairRoot::ParBase
  FairRoot::Gen
  FairRoot::EventDisplay

  Core
  Physics
  Geom
  VMC
  MathCore
  Hist
  $<$<BOOL:${ROOT_HAS_OPENGL}>:Eve>
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF Tutorial4LinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
