 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
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

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)
fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Alignment
  FairRoot::FairTools
  FairRoot::ParBase
  FairRoot::GeoBase
  Boost::serialization
  $<$<BOOL:${BUILD_MBS}>:FairRoot::MbsAPI>

  ROOT::RHTTP # THttpServer
  ROOT::Core
  ROOT::EG
  ROOT::Geom
  ROOT::GeomPainter # TGeoTrack
  ROOT::Hist
  ROOT::MathCore
  ROOT::Matrix
  ROOT::Net # TSocket
  ROOT::Physics
  ROOT::Proof
  ROOT::RIO
  ROOT::Tree
  ${VMC_LIB}
  $<$<BOOL:${ROOT_gdml_FOUND}>:ROOT::Gdml>
)

target_compile_definitions(${target} PRIVATE
  $<$<BOOL:${BUILD_MBS}>:BUILD_MBS>
  $<$<BOOL:${ROOT_gdml_FOUND}>:ROOT_HAS_GDML>
  # $<$<PLATFORM_ID:Linux>:Linux>
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF FairLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
