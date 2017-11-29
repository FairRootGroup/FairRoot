 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairTest" which includes the source files
# given in
# the array .
# The extension is already found.  Any number of sources could be listed
# here.

set(INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/fairtools
)

include_directories( ${INCLUDE_DIRECTORIES})

set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
)

include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

Set(SRCS
    FairMockMCApplication.cxx
    FairMockVirtualMC.cxx
)

Set(HEADERS )
Set(LINKDEF MockLinkDef.h)
Set(LIBRARY_NAME FairMock)
Set(DEPENDENCIES Core VMC)

GENERATE_LIBRARY()
