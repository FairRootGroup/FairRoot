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
  steer/FairAnaSelector.cxx
  steer/FairRadGridManager.cxx
  steer/FairRadLenManager.cxx
  steer/FairRadMapManager.cxx
  steer/FairRingSorter.cxx
  steer/FairRingSorterTask.cxx
  steer/FairRootManager.cxx
  steer/FairRun.cxx
  steer/FairRunAna.cxx
  steer/FairRunAnaProof.cxx
  steer/FairRunSim.cxx
  steer/FairTSBufferFunctional.cxx
  steer/FairTask.cxx
  steer/FairTrajFilter.cxx
  steer/FairWriteoutBuffer.cxx
  steer/FairRunOnline.cxx
  steer/FairLinkManager.cxx

  sim/FairBaseContFact.cxx
  sim/FairBaseParSet.cxx
  sim/FairGeoParSet.cxx
  sim/FairDetector.cxx
  sim/FairGeaneApplication.cxx
  sim/FairGenerator.cxx
  sim/FairGenericStack.cxx
  sim/FairIon.cxx
  sim/FairMCApplication.cxx
  sim/FairModule.cxx
  sim/FairParticle.cxx
  sim/FairPrimaryGenerator.cxx
  sim/FairRunIdGenerator.cxx
  sim/FairGenericVMCConfig.cxx
  sim/FairVolume.cxx
  sim/FairVolumeList.cxx

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
  event/FairMultiLinkedData.cxx
  event/FairMultiLinkedData_Interface.cxx
  event/FairRadLenPoint.cxx
  event/FairRadMapPoint.cxx
  event/FairRecoEventHeader.cxx
  event/FairRunInfo.cxx
  event/FairTimeStamp.cxx
  event/FairTrackParam.cxx
  event/FairPrintFairLinks.cxx

  field/FairField.cxx
  field/FairFieldFactory.cxx
  field/FairPropagator.cxx
  field/FairRKPropagator.cxx

  source/FairSource.cxx
  source/FairFileSource.cxx
  source/FairMixedSource.cxx
  source/FairOnlineSource.cxx

  $<$<BOOL:${BUILD_MBS}>:source/FairLmdSource.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/FairRemoteSource.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/FairMbsSource.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/FairUnpack.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/MRevBuffer.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/FairMbsStreamSource.cxx>
  $<$<BOOL:${BUILD_MBS}>:source/exitCli.c>
  $<$<BOOL:${BUILD_MBS}>:source/rclose.c>
  $<$<BOOL:${BUILD_MBS}>:source/swaplw.c>

  sink/FairSink.cxx
  sink/FairRootFileSink.cxx
)

set(headers
  event/FairMCPoint.h
  event/FairTrackParam.h
  event/FairRadLenPoint.h
  event/FairTimeStamp.h
  event/FairMCEventHeader.h
  event/FairEventHeader.h
  event/FairRadMapPoint.h
  event/FairMultiLinkedData_Interface.h
  event/FairMesh.h
  event/FairHit.h
  event/FairFileHeader.h
  event/FairFileInfo.h
  event/FairMultiLinkedData.h
  event/FairLink.h
  event/FairEventBuilderManager.h
  event/FairRecoEventHeader.h
  event/FairEventBuilder.h
  event/FairRunInfo.h
  event/FairPrintFairLinks.h

  steer/FairWriteoutBuffer.h
  steer/FairRadMapManager.h
  steer/FairRunAnaProof.h
  steer/FairAnaSelector.h
  steer/FairTask.h
  steer/FairRunOnline.h
  steer/FairRadGridManager.h
  steer/FairWriteoutBufferAbsBasis.h
  steer/FairLinkManager.h
  steer/FairRingSorter.h
  steer/FairRunAna.h
  steer/FairRootManager.h
  steer/FairRingSorterTask.h
  steer/FairTrajFilter.h
  steer/FairRun.h
  steer/FairRunSim.h
  steer/FairTSBufferFunctional.h
  steer/FairRadLenManager.h

  field/FairFieldFactory.h
  field/FairPropagator.h
  field/FairField.h
  field/FairRKPropagator.h

  sink/FairRootFileSink.h
  sink/FairSink.h

  source/ptrevmbsdef.h
  source/FairMixedSource.h
  source/FairUnpack.h
  source/FairMbsSource.h
  source/FairLmdSource.h
  source/FairFileSource.h
  source/FairMbsStreamSource.h
  source/FairOnlineSource.h
  source/MRevBuffer.h
  source/FairRemoteSource.h
  source/ptrevcomm.h
  source/FairSource.h

  sim/FairGeoParSet.h
  sim/FairGeaneApplication.h
  sim/FairParticle.h
  sim/FairVolume.h
  sim/FairGenericVMCConfig.h
  sim/FairPrimaryGenerator.h
  sim/FairBaseContFact.h
  sim/FairVolumeList.h
  sim/FairMCApplication.h
  sim/FairModule.h
  sim/FairGenericStack.h
  sim/FairRunIdGenerator.h
  sim/FairBaseParSet.h
  sim/FairGenerator.h
  sim/FairIon.h
  sim/FairDoubleHit.h
  sim/FairDetector.h
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
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/alignment>
  $<$<BOOL:${BUILD_MBS}>:$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/MbsAPI>>
  # DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)
target_link_libraries(${target} PUBLIC
  Alignment
  ParBase
  GeoBase
  FairTools
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
