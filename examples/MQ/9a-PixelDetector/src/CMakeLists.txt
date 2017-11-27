 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #             GNU Lesser General Public Licence (LGPL) version 3,              #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libPixel" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/fairmq
  ${CMAKE_SOURCE_DIR}/fairmq/options
  ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
  ${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/src
  ${CMAKE_SOURCE_DIR}/examples/MQ/9a-PixelDetector/src
  ${CMAKE_SOURCE_DIR}/examples/MQ/9a-PixelDetector/src/devices
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
)


Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZeroMQ_INCLUDE_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${Boost_LIBRARY_DIRS}
) 

link_directories( ${LINK_DIRECTORIES})

Set(NO_DICT_SRCS
devices/FairMQEx9aSamplerBin.cxx
devices/FairMQEx9aFileSinkBin.cxx
)

Set(NO_DICT_HEADERS
devices/FairMQEx9aSamplerBin.h
devices/FairMQEx9aFileSinkBin.h
devices/FairMQEx9aTaskProcessorBin.h
devices/FairMQEx9aTaskProcessorBin.tpl
)

set(SRCS
PixelAltFindHits.cxx
PixelAltDigiWriteToRootVector.cxx
)

Set(HEADERS 
PixelAltFindHits.h
PixelAltDigiWriteToRootVector.h
)

Set(LINKDEF PixelAltLinkDef.h)
Set(LIBRARY_NAME PixelAlt)
Set(DEPENDENCIES
    Base 
    GeoBase
    ParBase
    MCStack
    FairMQ 
    BaseMQ 
    Gen
    Passive
    Pixel
    ${Boost_THREAD_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY} 
    ${Boost_SERIALIZATION_LIBRARY} 
   ${Boost_PROGRAM_OPTIONS_LIBRARY}
)

GENERATE_LIBRARY()

Install(FILES ${NO_DICT_HEADERS} DESTINATION include)
