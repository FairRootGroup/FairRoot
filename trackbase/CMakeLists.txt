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

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/field 
  ${CMAKE_SOURCE_DIR}/passive
  ${CMAKE_SOURCE_DIR}/trackbase
)

Include_Directories(${INCLUDE_DIRECTORIES})

Set(SRCS
  FairTrackPar.cxx
  FairTrackParP.cxx
  FairTrackParH.cxx 
  FairGeaneUtil.cxx
)

Set(HEADERS )
Set(LINKDEF TrackBaseLinkDef.h)
Set(LIBRARY_NAME TrkBase)
Set(DEPENDENCIES Base Boost::serialization)
#Set(DEPENDENCIES Base Physics Matrix Core)

GENERATE_LIBRARY()
