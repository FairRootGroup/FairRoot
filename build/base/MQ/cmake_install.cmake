# Install script for directory: /Users/turany/development/FairRoot/base/MQ

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
    "/Users/turany/development/FairRoot/base/MQ/baseMQtools/baseMQtools.h"
    "/Users/turany/development/FairRoot/base/MQ/devices/FairMQSampler.h"
    "/Users/turany/development/FairRoot/base/MQ/devices/FairMQSampler.tpl"
    "/Users/turany/development/FairRoot/base/MQ/devices/FairMQUnpacker.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Sampler/SimpleTreeReader.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Sampler/FairSourceMQInterface.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Sampler/FairMQFileSource.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Serialization/BinaryBaseClassSerializer.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Serialization/BoostSerializer.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Serialization/RootSerializer.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Serialization/MQPolicyDef.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Storage/RootOutFileManager.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Storage/RootOutFileManager.tpl"
    "/Users/turany/development/FairRoot/base/MQ/policies/Storage/BinaryOutFileManager.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Storage/BoostDataSaver.h"
    "/Users/turany/development/FairRoot/base/MQ/policies/Storage/TriviallyCopyableDataSaver.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/turany/development/FairRoot/base/MQ/devices/FairMQProcessor.h"
    "/Users/turany/development/FairRoot/base/MQ/tasks/FairMQSamplerTask.h"
    "/Users/turany/development/FairRoot/base/MQ/tasks/FairMQProcessorTask.h"
    "/Users/turany/development/FairRoot/base/MQ/devices/FairMQLmdSampler.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/turany/development/FairRoot/build/lib/libBaseMQ.16.06.00.dylib"
    "/Users/turany/development/FairRoot/build/lib/libBaseMQ.16.dylib"
    "/Users/turany/development/FairRoot/build/lib/libBaseMQ.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBaseMQ.16.06.00.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBaseMQ.16.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBaseMQ.dylib"
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

