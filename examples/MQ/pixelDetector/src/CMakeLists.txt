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
  ${FairMQ_INCDIR}/fairmq/options
  ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
  ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/src
  ${CMAKE_SOURCE_DIR}/examples/MQ/pixelDetector/src/devices
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
  ${FairLogger_INCDIR}
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
devices/FairMQPixelSampler.cxx
devices/FairMQPixelSamplerBin.cxx
devices/PixelFindHitsTask.cxx
devices/FairMQPixelMerger.cxx
devices/FairMQPixelFileSink.cxx
devices/FairMQPixelFileSinkBin.cxx
devices/FairMQSimDevice.cxx
FairOnlineSink.cxx
)

Set(NO_DICT_HEADERS
devices/FairMQPixelSampler.h
devices/FairMQPixelSamplerBin.h
devices/PixelFindHitsTask.h
devices/FairMQPixelMerger.h
devices/FairMQPixelFileSink.h
devices/FairMQPixelFileSinkBin.h
devices/FairMQPixelTaskProcessor.h
devices/FairMQPixelTaskProcessor.tpl
devices/FairMQPixelTaskProcessorBin.h
devices/FairMQPixelTaskProcessorBin.tpl
devices/FairMQSimDevice.h
FairOnlineSink.h
)

set(SRCS
Pixel.cxx
PixelContFact.cxx
PixelDigitize.cxx
PixelDigiPar.cxx
PixelDigiSource.cxx
PixelDigiBinSource.cxx
PixelDigiWriteToFile.cxx
PixelDigiWriteToBinFile.cxx
PixelFindHits.cxx
PixelFindTracks.cxx
PixelFitTracks.cxx
PixelGeo.cxx
PixelGeoPar.cxx

PixelEventHeader.cxx
PixelPoint.cxx
PixelDigi.cxx
PixelHit.cxx
PixelTrack.cxx
)

Set(HEADERS 
Pixel.h
PixelContFact.h
PixelDigitize.h
PixelDigiPar.h
PixelDigiSource.h
PixelDigiBinSource.h
PixelDigiWriteToFile.h
PixelDigiWriteToBinFile.h
PixelFindHits.h
PixelFindTracks.h
PixelFitTracks.h
PixelGeo.h
PixelGeoPar.h

PixelEventHeader.h
PixelPoint.h
PixelDigi.h
PixelHit.h
PixelTrack.h

PixelPayload.h
)

Set(LINKDEF PixelLinkDef.h)
Set(LIBRARY_NAME Pixel)
Set(DEPENDENCIES
    Base 
    GeoBase
    ParBase
    MCStack
    FairMQ::FairMQ
    BaseMQ 
    Gen
    Passive
    ${Boost_THREAD_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY} 
    ${Boost_SERIALIZATION_LIBRARY} 
   ${Boost_PROGRAM_OPTIONS_LIBRARY}
)

GENERATE_LIBRARY()

Install(FILES ${NO_DICT_HEADERS} DESTINATION include)
