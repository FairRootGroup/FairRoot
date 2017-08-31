################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(FairTools
  SOURCES
  FairLogger.cxx
  FairMonitor.cxx
  FairSystemInfo.cxx

  DEPENDENCIES
  FairLogger::FairLogger
  ROOT::Core
  ROOT::Graf
  ROOT::Gpad

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  LINKDEF FairToolsLinkDef.h
)
