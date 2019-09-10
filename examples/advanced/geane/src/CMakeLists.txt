 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libPixel" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/examples/advanced/geane/src
  ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/src
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
  ${CMAKE_SOURCE_DIR}/geane
  ${CMAKE_SOURCE_DIR}/trackbase
  ${FairLogger_INCDIR}
)


set(SYSTEM_INCLUDE_DIRECTORIES
  ${SYSTEM_INCLUDE_DIRECTORIES}
  ${Geant3_INCLUDE_DIRS}
)

include_directories( ${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
FairGeaneTr.cxx
)

Set(HEADERS
FairGeaneTr.h
)

Set(LINKDEF GeaneExampleLinkDef.h)
Set(LIBRARY_NAME GeaneExample)
Set(DEPENDENCIES
    Base
    GeoBase
    ParBase
    Geane
    Pixel
    MCStack
    Gen
    Passive
    TrkBase
)

GENERATE_LIBRARY()
