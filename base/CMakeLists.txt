 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.


If(NOT DEFINED BUILD_MBS)
  Set(BUILD_MBS TRUE)
EndIf(NOT DEFINED BUILD_MBS)

Set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/logger
  ${CMAKE_SOURCE_DIR}/fairtools
  ${CMAKE_SOURCE_DIR}/geobase
  ${CMAKE_SOURCE_DIR}/parbase
  ${CMAKE_SOURCE_DIR}/base
  ${CMAKE_SOURCE_DIR}/base/steer
  ${CMAKE_SOURCE_DIR}/base/event
  ${CMAKE_SOURCE_DIR}/base/field
  ${CMAKE_SOURCE_DIR}/base/sim
  ${CMAKE_SOURCE_DIR}/base/source
)


If(WITH_DBASE)
  Set(INCLUDE_DIRECTORIES
     ${INCLUDE_DIRECTORIES}
     ${CMAKE_SOURCE_DIR}/dbase/dbInterface
     ${CMAKE_SOURCE_DIR}/dbase/dbValidation
     ${CMAKE_SOURCE_DIR}/dbase/dbUtils
     ${CMAKE_SOURCE_DIR}/input/db
     ${CMAKE_SOURCE_DIR}/dbase/dbInput
   )
EndIf(WITH_DBASE)


If(BUILD_MBS)
  Set(INCLUDE_DIRECTORIES
     ${INCLUDE_DIRECTORIES}
     ${CMAKE_SOURCE_DIR}/MbsAPI
  )
EndIf(BUILD_MBS)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)


Include_Directories(${INCLUDE_DIRECTORIES})

Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

# List of source files
set(SRCS

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
field/FairRKPropagator.cxx

source/FairSource.cxx
source/FairFileSource.cxx
source/FairMixedSource.cxx
source/FairOnlineSource.cxx
)

If(BUILD_MBS)
  Set(SRCS
      ${SRCS}
      source/FairLmdSource.cxx
      source/FairRemoteSource.cxx
      source/FairMbsSource.cxx
      source/FairUnpack.cxx
      source/MRevBuffer.cxx
      source/FairMbsStreamSource.cxx
   )

  Set(NO_DICT_SRCS
      source/exitCli.c
      source/rclose.c
      source/swaplw.c
  )

  Set(DEPENDENCIES
      ParBase GeoBase FairTools MbsAPI
      Proof GeomPainter Geom VMC EG MathCore Physics
      Matrix Tree Hist RIO RHTTP Core
  )

  Set(DEFINITIONS BUILD_MBS)
Else(BUILD_MBS)
  Set(DEPENDENCIES
      ParBase GeoBase FairTools
      Proof GeomPainter Geom VMC EG MathCore Physics
      Matrix Tree Hist RIO RHTTP Core
  )
EndIf(BUILD_MBS)

EXEC_PROGRAM( ${ROOT_CONFIG_EXECUTABLE}
    ARGS "--has-gdml"
    OUTPUT_VARIABLE ROOT_HAS_GDML )

If ( ${ROOT_HAS_GDML} STREQUAL yes )
  Message(STATUS "Build CbmModule with Gdml support")
  Add_Definitions(-DROOT_HAS_GDML)
EndIf ( ${ROOT_HAS_GDML} STREQUAL yes )

If ( ${ROOT_HAS_GDML} STREQUAL yes )
 Set (DEPENDENCIES ${DEPENDENCIES} Gdml)
EndIf ( ${ROOT_HAS_GDML} STREQUAL yes )

Set(LINKDEF FairLinkDef.h)
Set(LIBRARY_NAME Base)

GENERATE_LIBRARY()
