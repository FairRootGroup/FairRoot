################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target Pixel)

set(sources
  devices/FairMQPixelFileSink.cxx
  devices/FairMQPixelFileSinkBin.cxx
  devices/FairMQPixelMerger.cxx
  devices/FairMQPixelSampler.cxx
  devices/FairMQPixelSamplerBin.cxx
  devices/FairMQRunDevice.cxx
  devices/FairMQSimDevice.cxx
  devices/PixelFindHitsTask.cxx
  FairOnlineSink.cxx

  Pixel.cxx
  PixelContFact.cxx
  PixelDigi.cxx
  PixelDigiBinSource.cxx
  PixelDigiPar.cxx
  PixelDigiSource.cxx
  PixelDigitize.cxx
  PixelDigiWriteToBinFile.cxx
  PixelDigiWriteToFile.cxx
  PixelEventHeader.cxx
  PixelFindHits.cxx
  PixelFindTracks.cxx
  PixelFitTracks.cxx
  PixelGeo.cxx
  PixelGeoPar.cxx
  PixelHit.cxx
  PixelPoint.cxx
  PixelTrack.cxx
)

set(no_dict_headers
  devices/FairMQPixelFileSink.h
  devices/FairMQPixelFileSinkBin.h
  devices/FairMQPixelMerger.h
  devices/FairMQPixelSampler.h
  devices/FairMQPixelSamplerBin.h
  devices/FairMQPixelTaskProcessor.h
  devices/FairMQPixelTaskProcessorBin.h
  devices/FairMQRunDevice.h
  devices/FairMQSimDevice.h
  devices/PixelFindHitsTask.h
  FairOnlineSink.h
)

set(headers
  Pixel.h
  PixelContFact.h
  PixelDigi.h
  PixelDigiBinSource.h
  PixelDigiPar.h
  PixelDigiSource.h
  PixelDigitize.h
  PixelDigiWriteToBinFile.h
  PixelDigiWriteToFile.h
  PixelEventHeader.h
  PixelFindHits.h
  PixelFindTracks.h
  PixelFitTracks.h
  PixelGeo.h
  PixelGeoPar.h
  PixelHit.h
  PixelPayload.h
  PixelPoint.h
  PixelTrack.h
)

add_library(${target} SHARED ${sources} ${headers} ${no_dict_headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::ParBase
  FairRoot::GeoBase
  FairRoot::MCStack
  FairMQ::FairMQ
  FairRoot::Passive

  # TODO: clean the following
  Gen
  Core
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF PixelLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} ${no_dict_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
