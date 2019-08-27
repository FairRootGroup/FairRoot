################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(Geant4_FOUND AND Geant4VMC_FOUND)
  add_subdirectory(sim/fastsim)
endif()

set(target Base)

set(sources
  event/FairEventBuilder.cxx
  event/FairEventBuilderManager.cxx
  event/FairEventHeader.cxx
  event/FairFileHeader.cxx
  event/FairFileInfo.cxx
  event/FairHit.cxx
  event/FairLink.cxx
  event/FairMCEventHeader.cxx
  event/FairMCPoint.cxx
  event/FairMesh.cxx
  event/FairMultiLinkedData_Interface.cxx
  event/FairMultiLinkedData.cxx
  event/FairPrintFairLinks.cxx
  event/FairRadLenPoint.cxx
  event/FairRadMapPoint.cxx
  event/FairRecoEventHeader.cxx
  event/FairRunInfo.cxx
  event/FairTimeStamp.cxx
  event/FairTrackParam.cxx

  field/FairField.cxx
  field/FairFieldFactory.cxx
  field/FairPropagator.cxx
  field/FairRKPropagator.cxx

  sim/FairBaseContFact.cxx
  sim/FairBaseParSet.cxx
  sim/FairDetector.cxx
  # sim/FairDoubleHit.cxx # TODO: should this be added?
  sim/FairGeaneApplication.cxx
  sim/FairGenerator.cxx
  sim/FairGenericStack.cxx
  sim/FairGenericVMCConfig.cxx
  sim/FairGeoParSet.cxx
  sim/FairIon.cxx
  sim/FairMCApplication.cxx
  sim/FairModule.cxx
  sim/FairParticle.cxx
  sim/FairPrimaryGenerator.cxx
  sim/FairRunIdGenerator.cxx
  sim/FairVolume.cxx
  sim/FairVolumeList.cxx

  sink/FairRootFileSink.cxx
  sink/FairSink.cxx

  source/FairFileSource.cxx
  source/FairMixedSource.cxx
  source/FairOnlineSource.cxx
  source/FairSource.cxx
  $<$<BOOL:${BUILD_MBS}>:source/exitCli.c>
  $<$<BOOL:${BUILD_MBS}>:source/FairLmdSource.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/FairMbsSource.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/FairMbsStreamSource.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/FairRemoteSource.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/FairUnpack.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/MRevBuffer.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/rclose.c>
  $<$<BOOL:${BUILD_MBS}>:source/swaplw.c>

  steer/FairAnaSelector.cxx
  steer/FairLinkManager.cxx
  steer/FairRadGridManager.cxx
  steer/FairRadLenManager.cxx
  steer/FairRadMapManager.cxx
  steer/FairRingSorter.cxx
  steer/FairRingSorterTask.cxx
  steer/FairRootManager.cxx
  steer/FairRun.cxx
  steer/FairRunAna.cxx
  steer/FairRunAnaProof.cxx
  steer/FairRunOnline.cxx
  steer/FairRunSim.cxx
  steer/FairTask.cxx
  steer/FairTrajFilter.cxx
  steer/FairTSBufferFunctional.cxx
  steer/FairWriteoutBuffer.cxx
)

set(headers
  event/FairEventBuilder.h
  event/FairEventBuilderManager.h
  event/FairEventHeader.h
  event/FairFileHeader.h
  event/FairFileInfo.h
  event/FairHit.h
  event/FairLink.h
  event/FairMCEventHeader.h
  event/FairMCPoint.h
  event/FairMesh.h
  event/FairMultiLinkedData_Interface.h
  event/FairMultiLinkedData.h
  event/FairPrintFairLinks.h
  event/FairRadLenPoint.h
  event/FairRadMapPoint.h
  event/FairRecoEventHeader.h
  event/FairRunInfo.h
  event/FairTimeStamp.h
  event/FairTrackParam.h

  field/FairField.h
  field/FairFieldFactory.h
  field/FairPropagator.h
  field/FairRKPropagator.h

  sim/FairBaseContFact.h
  sim/FairBaseParSet.h
  sim/FairDetector.h
  sim/FairDoubleHit.h
  sim/FairGeaneApplication.h
  sim/FairGenerator.h
  sim/FairGenericStack.h
  sim/FairGenericVMCConfig.h
  sim/FairGeoParSet.h
  sim/FairIon.h
  sim/FairMCApplication.h
  sim/FairModule.h
  sim/FairParticle.h
  sim/FairPrimaryGenerator.h
  sim/FairRunIdGenerator.h
  sim/FairVolume.h
  sim/FairVolumeList.h

  sink/FairRootFileSink.h
  sink/FairSink.h

  source/FairFileSource.h
  source/FairMixedSource.h
  source/FairOnlineSource.h
  source/FairSource.h
  source/FairLmdSource.h
  source/FairMbsSource.h
  source/FairMbsStreamSource.h
  source/FairRemoteSource.h
  source/FairUnpack.h
  source/MRevBuffer.h
  source/ptrevcomm.h
  source/ptrevmbsdef.h

  steer/FairAnaSelector.h
  steer/FairLinkManager.h
  steer/FairRadGridManager.h
  steer/FairRadLenManager.h
  steer/FairRadMapManager.h
  steer/FairRingSorter.h
  steer/FairRingSorterTask.h
  steer/FairRootManager.h
  steer/FairRun.h
  steer/FairRunAna.h
  steer/FairRunAnaProof.h
  steer/FairRunOnline.h
  steer/FairRunSim.h
  steer/FairTask.h
  steer/FairTrajFilter.h
  steer/FairTSBufferFunctional.h
  steer/FairWriteoutBuffer.h
  steer/FairWriteoutBufferAbsBasis.h
)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/steer>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sim>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/event>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/field>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sink>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # DELETE US ONCE MODERNIZED TARGETS
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/fairtools>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/geobase>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/parbase>
  $<$<BOOL:${BUILD_MBS}>:$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/MbsAPI>>
  # DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Alignment
  ParBase
  GeoBase
  FairTools
  Boost::serialization
  $<$<BOOL:${BUILD_MBS}>:MbsAPI>

  Proof
  GeomPainter
  Geom
  VMC
  EG
  MathCore
  Physics
  Matrix
  Tree
  Hist
  RIO
  RHTTP
  Core
  $<$<BOOL:${ROOT_GDML_FOUND}>:Gdml>
)

target_compile_definitions(${target} PRIVATE
  $<$<BOOL:${BUILD_MBS}>:BUILD_MBS>
  $<$<BOOL:${ROOT_GDML_FOUND}>:ROOT_HAS_GDML>
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairLinkDef.h
)

install(TARGETS ${target}
  LIBRARY DESTINATION lib
  #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
)

install(FILES ${headers}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
