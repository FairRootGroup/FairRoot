# Install script for directory: /Users/turany/development/FairRoot/parbase

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
    "/Users/turany/development/FairRoot/parbase/FairContFact.h"
    "/Users/turany/development/FairRoot/parbase/FairDetParAsciiFileIo.h"
    "/Users/turany/development/FairRoot/parbase/FairDetParIo.h"
    "/Users/turany/development/FairRoot/parbase/FairDetParRootFileIo.h"
    "/Users/turany/development/FairRoot/parbase/FairGenericParAsciiFileIo.h"
    "/Users/turany/development/FairRoot/parbase/FairGenericParRootFileIo.h"
    "/Users/turany/development/FairRoot/parbase/FairParAsciiFileIo.h"
    "/Users/turany/development/FairRoot/parbase/FairParGenericSet.h"
    "/Users/turany/development/FairRoot/parbase/FairParIo.h"
    "/Users/turany/development/FairRoot/parbase/FairParRootFileIo.h"
    "/Users/turany/development/FairRoot/parbase/FairParSet.h"
    "/Users/turany/development/FairRoot/parbase/FairParamList.h"
    "/Users/turany/development/FairRoot/parbase/FairRtdbRun.h"
    "/Users/turany/development/FairRoot/parbase/FairRuntimeDb.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/Users/turany/development/FairRoot/build/lib/G__ParBaseDict_rdict.pcm"
    "/Users/turany/development/FairRoot/build/lib/libParBase.rootmap"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/turany/development/FairRoot/build/lib/libParBase.16.06.00.dylib"
    "/Users/turany/development/FairRoot/build/lib/libParBase.16.dylib"
    "/Users/turany/development/FairRoot/build/lib/libParBase.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libParBase.16.06.00.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libParBase.16.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libParBase.dylib"
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

