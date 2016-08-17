# Install script for directory: /Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src

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
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/Pixel.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelContFact.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelDigitize.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelDigiPar.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelDigiSource.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelDigiBinSource.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelDigiWriteToFile.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelDigiWriteToBinFile.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelFindHits.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelFindTracks.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelFitTracks.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelGeo.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelGeoPar.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelEventHeader.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelPoint.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelDigi.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelHit.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelTrack.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/PixelPayload.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/Users/turany/development/FairRoot/build/lib/G__PixelDict_rdict.pcm"
    "/Users/turany/development/FairRoot/build/lib/libPixel.rootmap"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/turany/development/FairRoot/build/lib/libPixel.16.06.00.dylib"
    "/Users/turany/development/FairRoot/build/lib/libPixel.16.dylib"
    "/Users/turany/development/FairRoot/build/lib/libPixel.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPixel.16.06.00.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPixel.16.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPixel.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
        "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib64"
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9Sampler.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9SamplerBin.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9Processor.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/PixelFindHitsTask.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9Merger.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9FileSink.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9FileSinkBin.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9TaskProcessor.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9TaskProcessor.tpl"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9TaskProcessorBin.h"
    "/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices/FairMQEx9TaskProcessorBin.tpl"
    )
endif()

