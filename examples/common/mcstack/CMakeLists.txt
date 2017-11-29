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
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM  ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)
 
Link_Directories(${LINK_DIRECTORIES})

Set(HEADERS
  FairDetectorList.h
  FairMCTrack.h
  FairStack.h
)

Set(SRCS
  FairStack.cxx 
  FairMCTrack.cxx
)

Set(LINKDEF MCStackLinkDef.h)
Set(LIBRARY_NAME MCStack)
Set(DEPENDENCIES Base EG Physics Core)

GENERATE_LIBRARY()
