################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ExPixel)

set(no_dict_sources
  devices/FairMQPixelFileSink.cxx
  devices/FairMQPixelFileSinkBin.cxx
  devices/FairMQPixelMerger.cxx
  devices/FairMQPixelSampler.cxx
  devices/FairMQPixelSamplerBin.cxx
  devices/FairMQRunDevice.cxx
  devices/FairMQSimDevice.cxx
  devices/PixelFindHitsTask.cxx
  FairOnlineSink.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${no_dict_sources}" OUTVAR no_dict_headers)

list(APPEND no_dict_headers
  devices/FairMQPixelTaskProcessor.h
  devices/FairMQPixelTaskProcessorBin.h
)

set(sources
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

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

list(APPEND headers
  PixelPayload.h
)

add_library(${target} SHARED ${sources} ${no_dict_sources} ${headers} ${no_dict_headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::Tools # FairLogger
  FairRoot::Generators # FairBoxGenerator
  FairRoot::GeoBase
  FairRoot::ParBase # FairParGenericSet
  FairRoot::ExMCStack
  FairRoot::ExPassive # FairCave
  FairRoot::FairMQ

  Boost::serialization

  ROOT::Core
  ROOT::MathCore
  ROOT::RIO
  ROOT::Tree
  ROOT::Physics
  ROOT::Geom
  ROOT::Hist
  ${VMCLIB}
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF PixelLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} ${no_dict_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
