# Install script for directory: /Users/turany/development/FairRoot/geobase

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
    "/Users/turany/development/FairRoot/geobase/FairGeoAssembly.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoCone.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoCons.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoEltu.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoBuilder.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoInterface.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoIo.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoLoader.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoMatrix.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoMedia.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoMedium.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoNode.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoOldAsciiIo.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoPcon.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoPgon.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoRootBuilder.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoRotation.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoSet.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoShapes.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoSphe.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoTransform.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoTrap.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoTrd1.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoTube.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoTubs.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoTorus.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoVector.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoVolume.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoCompositeVolume.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoAsciiIo.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoBrik.h"
    "/Users/turany/development/FairRoot/geobase/FairGeoBasicShape.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/Users/turany/development/FairRoot/build/lib/G__GeoBaseDict_rdict.pcm"
    "/Users/turany/development/FairRoot/build/lib/libGeoBase.rootmap"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/turany/development/FairRoot/build/lib/libGeoBase.16.06.00.dylib"
    "/Users/turany/development/FairRoot/build/lib/libGeoBase.16.dylib"
    "/Users/turany/development/FairRoot/build/lib/libGeoBase.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libGeoBase.16.06.00.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libGeoBase.16.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libGeoBase.dylib"
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

