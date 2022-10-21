 ################################################################################
 #    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

set(target Online)

set(sources
  source/FairOnlineSource.cxx
  source/FairUnpack.cxx

  steer/FairRunOnline.cxx
)

if(BUILD_MBS)
  list(APPEND sources
    source/exitCli.c
    source/FairLmdSource.cxx
    source/FairMbsSource.cxx
    source/FairMbsStreamSource.cxx
    source/FairRemoteSource.cxx
    source/MRevBuffer.cxx
    source/rclose.c
    source/swaplw.c
  )
endif()
fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/steer>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::FairTools
  FairRoot::Base
  FairRoot::ParBase
  $<$<BOOL:${BUILD_MBS}>:FairRoot::MbsAPI>

  ROOT::RHTTP # THttpServer
  ROOT::Core
  ROOT::Geom
  ROOT::Net # TSocket
)

target_compile_definitions(${target} PRIVATE
  $<$<BOOL:${BUILD_MBS}>:BUILD_MBS>
  $<$<BOOL:${ROOT_gdml_FOUND}>:ROOT_HAS_GDML>
  # $<$<PLATFORM_ID:Linux>:Linux>
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF LinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
