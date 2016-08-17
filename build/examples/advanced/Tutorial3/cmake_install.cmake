# Install script for directory: /Users/turany/development/FairRoot/examples/advanced/Tutorial3

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
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/simulation/FairTestDetector.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/simulation/FairTestDetectorContFact.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/simulation/FairTestDetectorGeo.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/simulation/FairTestDetectorGeoPar.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/simulation/FairConstField.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/simulation/FairConstPar.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/simulation/FairMapPar.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/data/FairTestDetectorPoint.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/data/FairTestDetectorHit.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/digitization/FairTestDetectorHitProducerSmearing.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/digitization/FairTestDetectorDigiTask.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/reconstruction/FairTestDetectorRecoTask.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/timeBasedSimulation/FairTestDetectorDigiRingSorter.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/timeBasedSimulation/FairTestDetectorDigiSorterTask.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/timeBasedSimulation/FairTestDetectorDigiWriteoutBuffer.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/timeBasedSimulation/FairTestDetectorTimeDigiTask.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/timeBasedSimulation/FairTestDetectorTimeRecoTask.h"
    "/Users/turany/development/FairRoot/examples/advanced/Tutorial3/data/FairTestDetectorDigi.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/Users/turany/development/FairRoot/build/lib/G__FairTestDetectorDict_rdict.pcm"
    "/Users/turany/development/FairRoot/build/lib/libFairTestDetector.rootmap"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/turany/development/FairRoot/build/lib/libFairTestDetector.16.06.00.dylib"
    "/Users/turany/development/FairRoot/build/lib/libFairTestDetector.16.dylib"
    "/Users/turany/development/FairRoot/build/lib/libFairTestDetector.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libFairTestDetector.16.06.00.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libFairTestDetector.16.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libFairTestDetector.dylib"
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
        -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib"
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin" TYPE EXECUTABLE FILES "/Users/turany/development/FairRoot/build/bin/examples/advanced/Tutorial3/tut3-sampler")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sampler" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sampler")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sampler")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib64"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sampler")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sampler")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/FairRoot/build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sampler")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sampler")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin" TYPE EXECUTABLE FILES "/Users/turany/development/FairRoot/build/bin/examples/advanced/Tutorial3/tut3-processor")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-processor" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-processor")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-processor")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib64"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-processor")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-processor")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/FairRoot/build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-processor")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-processor")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin" TYPE EXECUTABLE FILES "/Users/turany/development/FairRoot/build/bin/examples/advanced/Tutorial3/tut3-sink")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sink" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sink")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sink")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib64"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sink")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sink")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/FairRoot/build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sink")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/advanced/Tutorial3/bin/tut3-sink")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/turany/development/FairRoot/build/examples/advanced/Tutorial3/macro/cmake_install.cmake")

endif()

