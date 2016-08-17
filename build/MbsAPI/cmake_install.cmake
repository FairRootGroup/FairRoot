# Install script for directory: /Users/turany/development/FairRoot/MbsAPI

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
    "/Users/turany/development/FairRoot/MbsAPI/fLmd.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_evhe.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_evhe_swap.h"
    "/Users/turany/development/FairRoot/MbsAPI/sMbs.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_ves10_1.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_ves10_1_swap.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_ve10_1.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_ve10_1_swap.h"
    "/Users/turany/development/FairRoot/MbsAPI/f_evt.h"
    "/Users/turany/development/FairRoot/MbsAPI/f_ut_utime.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_bufhe.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_bufhe_swap.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_filhe.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_filhe_swap.h"
    "/Users/turany/development/FairRoot/MbsAPI/portnum_def.h"
    "/Users/turany/development/FairRoot/MbsAPI/s_stdint.h"
    "/Users/turany/development/FairRoot/MbsAPI/typedefs.h"
    "/Users/turany/development/FairRoot/MbsAPI/f_stccomm.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/turany/development/FairRoot/build/lib/libMbsAPI.16.06.00.dylib"
    "/Users/turany/development/FairRoot/build/lib/libMbsAPI.16.dylib"
    "/Users/turany/development/FairRoot/build/lib/libMbsAPI.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMbsAPI.16.06.00.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMbsAPI.16.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMbsAPI.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

