 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

add_fairroot_library(Pixel
  SOURCES
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

  HEADERS 
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

  NO_DICT_SRCS
  devices/FairMQEx9Sampler.cxx
  devices/FairMQEx9SamplerBin.cxx
  devices/PixelFindHitsTask.cxx
  devices/FairMQEx9Merger.cxx
  devices/FairMQEx9FileSink.cxx
  devices/FairMQEx9FileSinkBin.cxx
  devices/FairMQSimDevice.cxx
  FairOnlineSink.cxx

  NO_DICT_HEADERS
  devices/FairMQEx9Sampler.h
  devices/FairMQEx9SamplerBin.h
  devices/PixelFindHitsTask.h
  devices/FairMQEx9Merger.h
  devices/FairMQEx9FileSink.h
  devices/FairMQEx9FileSinkBin.h
  devices/FairMQEx9TaskProcessor.h
  devices/FairMQEx9TaskProcessor.tpl
  devices/FairMQEx9TaskProcessorBin.h
  devices/FairMQEx9TaskProcessorBin.tpl
  devices/FairMQSimDevice.h
  FairOnlineSink.h

  LINKDEF PixelLinkDef.h

  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/devices

  DEPENDENCIES
  Base 
  GeoBase
  ParBase
  MCStack
  FairMQ::FairMQ 
  BaseMQ 
  Gen
  Passive
  Boost::thread
  Boost::system 
  Boost::serialization 
  Boost::program_options
)
