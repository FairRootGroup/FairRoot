################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(FairDataMatch
  SOURCES
  FairMCMatch.cxx
  FairMCMatchCreatorTask.cxx
  FairMCMatchLoaderTask.cxx
  FairMCMatchSelectorTask.cxx
  FairMCObject.cxx
  FairMCStage.cxx
  FairMCResult.cxx
  FairMCEntry.cxx
  FairMCList.cxx
  FairMCDataCrawler.cxx

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDENCIES Base ROOT::Core
  LINKDEF FairMCMatchLinkDef.h
)
