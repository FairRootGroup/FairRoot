# Install script for directory: /Users/turany/development/FairRoot/examples/MQ/LmdSampler

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/Users/turany/development/FairRoot/examples/MQ/LmdSampler/unpacker/FairTut8Unpacker.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/Users/turany/development/FairRoot/build/lib/G__LmdMQSamplerDict_rdict.pcm"
    "/Users/turany/development/FairRoot/build/lib/libLmdMQSampler.rootmap"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/turany/development/FairRoot/build/lib/libLmdMQSampler.16.06.00.dylib"
    "/Users/turany/development/FairRoot/build/lib/libLmdMQSampler.16.dylib"
    "/Users/turany/development/FairRoot/build/lib/libLmdMQSampler.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libLmdMQSampler.16.06.00.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libLmdMQSampler.16.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libLmdMQSampler.dylib"
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin" TYPE EXECUTABLE FILES "/Users/turany/development/FairRoot/build/bin/examples/MQ/LmdSampler/runLmdSampler")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runLmdSampler" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runLmdSampler")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runLmdSampler")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib64"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runLmdSampler")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/FairRoot/build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runLmdSampler")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runLmdSampler")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin" TYPE EXECUTABLE FILES "/Users/turany/development/FairRoot/build/bin/examples/MQ/LmdSampler/runTut8MQUnpacker")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8MQUnpacker" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8MQUnpacker")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8MQUnpacker")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib64"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8MQUnpacker")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/FairRoot/build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8MQUnpacker")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8MQUnpacker")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin" TYPE EXECUTABLE FILES "/Users/turany/development/FairRoot/build/bin/examples/MQ/LmdSampler/runTut8Sink")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8Sink" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8Sink")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib/root"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8Sink")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/install/RC_may16_R6/lib64"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8Sink")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/turany/development/FairRoot/build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8Sink")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/LmdSampler/bin/runTut8Sink")
    endif()
  endif()
endif()

