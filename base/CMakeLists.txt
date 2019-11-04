 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

If(Geant4_FOUND AND Geant4VMC_FOUND)
  add_subdirectory (sim/fastsim)
EndIf()

If(NOT DEFINED BUILD_MBS)
  Set(BUILD_MBS TRUE)
EndIf(NOT DEFINED BUILD_MBS)

Set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/logger
  ${CMAKE_SOURCE_DIR}/fairtools
  ${CMAKE_SOURCE_DIR}/geobase
  ${CMAKE_SOURCE_DIR}/parbase
  ${CMAKE_SOURCE_DIR}/trackbase
  ${CMAKE_SOURCE_DIR}/base
  ${CMAKE_SOURCE_DIR}/base/steer
  ${CMAKE_SOURCE_DIR}/base/event
  ${CMAKE_SOURCE_DIR}/base/field
  ${CMAKE_SOURCE_DIR}/base/sim
  ${CMAKE_SOURCE_DIR}/base/source
  ${CMAKE_SOURCE_DIR}/base/sink
  ${CMAKE_SOURCE_DIR}/alignment
  ${FairLogger_INCDIR}
)

if(BUILD_MBS)
  list(APPEND sources
    source/exitCli.c
    source/FairLmdSource.cxx
    source/FairMbsSource.cxx
    source/FairMbsStreamSource.cxx
    source/FairRemoteSource.cxx
    source/FairUnpack.cxx
    source/MRevBuffer.cxx
    source/rclose.c
    source/swaplw.c
  )
endif()

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/steer>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sim>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/event>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/field>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sink>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Alignment
  FairRoot::FairTools
  FairRoot::ParBase
  FairRoot::GeoBase
  Boost::serialization
  $<$<BOOL:${BUILD_MBS}>:FairRoot::MbsAPI>

  RHTTP # THttpServer
  Core
  EG
  Geom
  GeomPainter # TGeoTrack
  Hist
  MathCore
  Matrix
  Net # TSocket
  Physics
  Proof
  RIO
  Tree
  VMC
  $<$<BOOL:${ROOT_GDML_FOUND}>:Gdml>
)

target_compile_definitions(${target} PRIVATE
  $<$<BOOL:${BUILD_MBS}>:BUILD_MBS>
  $<$<BOOL:${ROOT_GDML_FOUND}>:ROOT_HAS_GDML>
  # $<$<PLATFORM_ID:Linux>:Linux>
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
