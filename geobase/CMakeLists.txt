################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target GeoBase)

set(sources
  FairGeoAsciiIo.cxx
  FairGeoAssembly.cxx
  FairGeoBasicShape.cxx
  FairGeoBrik.cxx
  FairGeoBuilder.cxx
  FairGeoCompositeVolume.cxx
  FairGeoCone.cxx
  FairGeoCons.cxx
  FairGeoEltu.cxx
  FairGeoInterface.cxx
  FairGeoIo.cxx
  FairGeoLoader.cxx
  FairGeoMatrix.cxx
  FairGeoMedia.cxx
  FairGeoMedium.cxx
  FairGeoNode.cxx
  FairGeoOldAsciiIo.cxx
  FairGeoPcon.cxx
  FairGeoPgon.cxx
  FairGeoRootBuilder.cxx
  FairGeoRotation.cxx
  FairGeoSet.cxx
  FairGeoShapes.cxx
  FairGeoSphe.cxx
  FairGeoTorus.cxx
  FairGeoTransform.cxx
  FairGeoTrap.cxx
  FairGeoTrd1.cxx
  FairGeoTube.cxx
  FairGeoTubs.cxx
  FairGeoVector.cxx
  FairGeoVolume.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::FairTools

  ROOT::Core
  ROOT::MathCore
  ROOT::Geom
  ROOT::Graf3d # TRotMatrix
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF GeoBaseLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
