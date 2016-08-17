# Install script for directory: /Users/turany/development/FairRoot/base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/turany/development/install/FairRoot_dev_R6")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/turany/development/FairRoot/base/steer/FairAnaSelector.h"
    "/Users/turany/development/FairRoot/base/steer/FairRadGridManager.h"
    "/Users/turany/development/FairRoot/base/steer/FairRadLenManager.h"
    "/Users/turany/development/FairRoot/base/steer/FairRadMapManager.h"
    "/Users/turany/development/FairRoot/base/steer/FairRingSorter.h"
    "/Users/turany/development/FairRoot/base/steer/FairRingSorterTask.h"
    "/Users/turany/development/FairRoot/base/steer/FairRootManager.h"
    "/Users/turany/development/FairRoot/base/steer/FairRun.h"
    "/Users/turany/development/FairRoot/base/steer/FairRunAna.h"
    "/Users/turany/development/FairRoot/base/steer/FairRunAnaProof.h"
    "/Users/turany/development/FairRoot/base/steer/FairRunSim.h"
    "/Users/turany/development/FairRoot/base/steer/FairTSBufferFunctional.h"
    "/Users/turany/development/FairRoot/base/steer/FairTask.h"
    "/Users/turany/development/FairRoot/base/steer/FairTrajFilter.h"
    "/Users/turany/development/FairRoot/base/steer/FairWriteoutBuffer.h"
    "/Users/turany/development/FairRoot/base/steer/FairRunOnline.h"
    "/Users/turany/development/FairRoot/base/steer/FairLinkManager.h"
    "/Users/turany/development/FairRoot/base/sim/FairBaseContFact.h"
    "/Users/turany/development/FairRoot/base/sim/FairBaseParSet.h"
    "/Users/turany/development/FairRoot/base/sim/FairGeoParSet.h"
    "/Users/turany/development/FairRoot/base/sim/FairDetector.h"
    "/Users/turany/development/FairRoot/base/sim/FairGeaneApplication.h"
    "/Users/turany/development/FairRoot/base/sim/FairGenerator.h"
    "/Users/turany/development/FairRoot/base/sim/FairGenericStack.h"
    "/Users/turany/development/FairRoot/base/sim/FairIon.h"
    "/Users/turany/development/FairRoot/base/sim/FairMCApplication.h"
    "/Users/turany/development/FairRoot/base/sim/FairModule.h"
    "/Users/turany/development/FairRoot/base/sim/FairParticle.h"
    "/Users/turany/development/FairRoot/base/sim/FairPrimaryGenerator.h"
    "/Users/turany/development/FairRoot/base/sim/FairRunIdGenerator.h"
    "/Users/turany/development/FairRoot/base/sim/FairVolume.h"
    "/Users/turany/development/FairRoot/base/sim/FairVolumeList.h"
    "/Users/turany/development/FairRoot/base/event/FairEventBuilder.h"
    "/Users/turany/development/FairRoot/base/event/FairEventBuilderManager.h"
    "/Users/turany/development/FairRoot/base/event/FairEventHeader.h"
    "/Users/turany/development/FairRoot/base/event/FairFileHeader.h"
    "/Users/turany/development/FairRoot/base/event/FairFileInfo.h"
    "/Users/turany/development/FairRoot/base/event/FairHit.h"
    "/Users/turany/development/FairRoot/base/event/FairLink.h"
    "/Users/turany/development/FairRoot/base/event/FairMCEventHeader.h"
    "/Users/turany/development/FairRoot/base/event/FairMCPoint.h"
    "/Users/turany/development/FairRoot/base/event/FairMesh.h"
    "/Users/turany/development/FairRoot/base/event/FairMultiLinkedData.h"
    "/Users/turany/development/FairRoot/base/event/FairMultiLinkedData_Interface.h"
    "/Users/turany/development/FairRoot/base/event/FairRadLenPoint.h"
    "/Users/turany/development/FairRoot/base/event/FairRadMapPoint.h"
    "/Users/turany/development/FairRoot/base/event/FairRecoEventHeader.h"
    "/Users/turany/development/FairRoot/base/event/FairRunInfo.h"
    "/Users/turany/development/FairRoot/base/event/FairTimeStamp.h"
    "/Users/turany/development/FairRoot/base/event/FairTrackParam.h"
    "/Users/turany/development/FairRoot/base/field/FairField.h"
    "/Users/turany/development/FairRoot/base/field/FairFieldFactory.h"
    "/Users/turany/development/FairRoot/base/field/FairRKPropagator.h"
    "/Users/turany/development/FairRoot/base/source/FairSource.h"
    "/Users/turany/development/FairRoot/base/source/FairFileSource.h"
    "/Users/turany/development/FairRoot/base/source/FairMixedSource.h"
    "/Users/turany/development/FairRoot/base/source/FairOnlineSource.h"
    "/Users/turany/development/FairRoot/base/source/FairLmdSource.h"
    "/Users/turany/development/FairRoot/base/source/FairRemoteSource.h"
    "/Users/turany/development/FairRoot/base/source/FairMbsSource.h"
    "/Users/turany/development/FairRoot/base/source/FairUnpack.h"
    "/Users/turany/development/FairRoot/base/source/MRevBuffer.h"
    "/Users/turany/development/FairRoot/base/source/FairMbsStreamSource.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/Users/turany/development/FairRoot/build/lib/G__BaseDict_rdict.pcm"
    "/Users/turany/development/FairRoot/build/lib/libBase.rootmap"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/turany/development/FairRoot/build/lib/libBase.16.06.00.dylib"
    "/Users/turany/development/FairRoot/build/lib/libBase.16.dylib"
    "/Users/turany/development/FairRoot/build/lib/libBase.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBase.16.06.00.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBase.16.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBase.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
        "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/turany/development/FairRoot/build/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

