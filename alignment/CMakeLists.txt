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
  ${CMAKE_SOURCE_DIR}/fairtools
  ${FairLogger_INCDIR}
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)

Include_Directories(${INCLUDE_DIRECTORIES})

Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

# List of source files
Set(SRCS
FairAlignmentHandler.cxx
)

Set(DEPENDENCIES
      Geom Matrix
)

Set(LIBRARY_NAME Alignment)

GENERATE_LIBRARY()
