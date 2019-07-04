 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairDataMatch" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})

set(SRCS
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
)

Set(HEADERS )
Set(LINKDEF FairMCMatchLinkDef.h)
Set(LIBRARY_NAME FairDataMatch)
Set(DEPENDENCIES Base Core)
#    FairTools ParBase GeoBase 
#    Proof GeomPainter Geom VMC EG MathCore Physics 
#    Matrix Tree Hist RIO Core
#)

GENERATE_LIBRARY()

