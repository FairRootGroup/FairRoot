 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
If(Geant4_FOUND AND Geant4VMC_FOUND)
  add_subdirectory (sim/fastsim)
EndIf()

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

  sim/FairBaseContFact.cxx
  sim/FairBaseParSet.cxx
  sim/FairDetector.cxx
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

if(BUILD_MBS)
  list(APPEND sources
    source/exitCli.c
    source/FairLmdSource.cxx
    source/FairMbsSource.cxx
    source/FairMbsStreamSource.cxx
    source/FairRemoteSource.cxx
    source/FairUnpack.cxx
    source/MRevBuffer.cxx
    source/rclose.c
    source/swaplw.c
  )
endif()

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/steer>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sim>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/event>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/field>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sink>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Alignment
  FairRoot::FairTools
  FairRoot::ParBase
  FairRoot::GeoBase
  Boost::serialization
  $<$<BOOL:${BUILD_MBS}>:FairRoot::MbsAPI>

  RHTTP # THttpServer
  Core
  EG
  Geom
  GeomPainter # TGeoTrack
  Hist
  MathCore
  Matrix
  Net # TSocket
  Physics
  Proof
  RIO
  Tree
  ${VMCLIB}
  $<$<BOOL:${ROOT_GDML_FOUND}>:Gdml>
)

target_compile_definitions(${target} PRIVATE
  $<$<BOOL:${BUILD_MBS}>:BUILD_MBS>
  $<$<BOOL:${ROOT_GDML_FOUND}>:ROOT_HAS_GDML>
  # $<$<PLATFORM_ID:Linux>:Linux>
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
