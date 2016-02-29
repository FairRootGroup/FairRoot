 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libPixel" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/fairmq
  ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
  ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/src
  ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/src/devices
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
)


Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZMQ_INCLUDE_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${Boost_LIBRARY_DIRS}
) 

link_directories( ${LINK_DIRECTORIES})

Set(NO_DICT_SRCS
devices/FairMQEx9Processor.cxx
)

set(SRCS
Pixel.cxx
PixelContFact.cxx
PixelGeo.cxx
PixelGeoPar.cxx
PixelDigi.cxx
PixelDigitize.cxx
PixelDigiPar.cxx
PixelFindHits.cxx
PixelHit.cxx
PixelPoint.cxx
)
Set(HEADERS )
Set(LINKDEF PixelLinkDef.h)
Set(LIBRARY_NAME Pixel)
Set(DEPENDENCIES
    Base 
    GeoBase
    ParBase
    MCStack
    FairMQ 
    BaseMQ 
    Gen
    Passive
    boost_thread 
    boost_system 
    boost_serialization 
    boost_program_options
)

GENERATE_LIBRARY()
