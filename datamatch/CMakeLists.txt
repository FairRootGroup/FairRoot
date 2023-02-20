################################################################################
# Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target DataMatch)

set(sources
  FairMCDataCrawler.cxx
  FairMCEntry.cxx
  FairMCList.cxx
  FairMCMatch.cxx
  FairMCMatchCreatorTask.cxx
  FairMCMatchLoaderTask.cxx
  FairMCMatchSelectorTask.cxx
  FairMCObject.cxx
  FairMCResult.cxx
  FairMCStage.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})
# Keep old filesystem name
set_target_properties(${target} PROPERTIES OUTPUT_NAME FairDataMatch)

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# TODO: DELETE ME ONCE USING root targets
target_include_directories(${target} SYSTEM PUBLIC
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairMultiLinkedData, FairRootManager, FairLink

  ROOT::Core
)

target_compile_definitions(${target} PRIVATE
  FAIR_SILENCE_DATAMATCH_DEPRECATION
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF LinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
