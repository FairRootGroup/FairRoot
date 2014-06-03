 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libTutorial1" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${Boost_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/example/Tutorial1/src
${CMAKE_SOURCE_DIR}/example/mcstack
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(SRCS
#Put here your sourcefiles
FairTutorialDet1.cxx
FairTutorialDet1ContFact.cxx
FairTutorialDet1Geo.cxx
FairTutorialDet1GeoPar.cxx
FairTutorialDet1Point.cxx
)

Set(HEADERS )
Set(LINKDEF Tutorial1LinkDef.h)
Set(LIBRARY_NAME Tutorial1)
Set(DEPENDENCIES MCStack Base)

GENERATE_LIBRARY()

