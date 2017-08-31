################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(NOT DEFINED BUILD_MBS)
  set(BUILD_MBS TRUE)
endif()

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

  sink/FairSink.cxx
  sink/FairRootFileSink.cxx
)

set(root_dependencies
  ROOT::Proof
  ROOT::GeomPainter
  ROOT::Geom
  ROOT::VMC
  ROOT::EG
  ROOT::MathCore
  ROOT::Physics 
  ROOT::Matrix
  ROOT::Tree
  ROOT::Hist
  ROOT::RIO
  ROOT::RHTTP
  ROOT::Core
)

set(fairroot_dependencies
  FairTools 
  GeoBase
  ParBase
)

if(BUILD_MBS)
  set(sources
    ${sources}
    source/FairLmdSource.cxx
    source/FairRemoteSource.cxx
    source/FairMbsSource.cxx
    source/FairUnpack.cxx
    source/MRevBuffer.cxx
    source/FairMbsStreamSource.cxx
  )
  set(no_dict_srcs
    source/exitCli.c
    source/rclose.c
    source/swaplw.c
  )
  set(fairroot_dependencies MbsAPI ${fairroot_dependencies})

  set(defs ${defs} BUILD_MBS)
endif()

exec_program(${ROOT_CONFIG_EXECUTABLE} 
  ARGS "--has-gdml"
  OUTPUT_VARIABLE ROOT_HAS_GDML
)

if(ROOT_HAS_GDML STREQUAL yes)
  message(STATUS "Building Base with Gdml support")
  set(defs ${defs} ROOT_HAS_GDML)
  set(root_dependencies ${root_dependencies} ROOT::Gdml)
endif()

add_fairroot_library(Base
  SOURCES ${sources}
  LINKDEF FairLinkDef.h
  NO_DICT_SRCS ${no_dict_srcs}
  DEFINITIONS ${defs}

  DEPENDENCIES
  ${fairroot_dependencies}
  ${root_dependencies}
  Boost::serialization

  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/event
  ${CMAKE_CURRENT_SOURCE_DIR}/field
  ${CMAKE_CURRENT_SOURCE_DIR}/sim
  ${CMAKE_CURRENT_SOURCE_DIR}/source
  ${CMAKE_CURRENT_SOURCE_DIR}/steer
)
