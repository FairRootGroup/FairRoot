################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(TrkBase
  SOURCES
  FairTrackPar.cxx
  FairTrackParP.cxx
  FairTrackParH.cxx 
  FairGeaneUtil.cxx

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  LINKDEF TrackBaseLinkDef.h
  DEPENDENCIES Base Boost::serialization
)
