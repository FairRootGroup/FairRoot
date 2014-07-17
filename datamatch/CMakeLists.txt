 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairDataMatch" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/base/steer
${CMAKE_SOURCE_DIR}/base/event
${CMAKE_SOURCE_DIR}/base/field
${CMAKE_SOURCE_DIR}/base/sim
${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

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
Set(DEPENDENCIES Base)
#    FairTools ParBase GeoBase 
#    Proof GeomPainter Geom VMC EG MathCore Physics 
#    Matrix Tree Hist RIO Cint Core
#)

GENERATE_LIBRARY()

