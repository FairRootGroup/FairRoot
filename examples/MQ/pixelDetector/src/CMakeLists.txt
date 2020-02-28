################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target Pixel)

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

fairroot_change_extensions_if_exists(.cxx .h FILES "${no_dict_sources}" OUTVAR no_dict_headers)

list(APPEND no_dict_headers
  devices/FairMQPixelTaskProcessor.h
  devices/FairMQPixelTaskProcessorBin.h
)
fairroot_copy(HEADERS ${no_dict_headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

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

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

list(APPEND headers
  PixelPayload.h
)

fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${no_dict_sources} ${headers} ${no_dict_headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::BaseMQ # Serialization policies
  FairRoot::FairTools # FairLogger
  FairRoot::Gen # FairBoxGenerator
  FairRoot::GeoBase
  FairRoot::MCStack
  FairRoot::ParBase # FairParGenericSet
  FairRoot::Passive # FairCave

  Boost::serialization

  FairMQ::FairMQ

  ROOT::Core
  ROOT::MathCore
  ROOT::RIO
  ROOT::Tree
  ROOT::Physics
  ROOT::Geom
  ROOT::Hist
  ${VMC_LIB} # TVirtualMC
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF PixelLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
