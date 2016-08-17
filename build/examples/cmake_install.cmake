# Install script for directory: /Users/turany/development/FairRoot/examples

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/turany/development/FairRoot/build/examples/common/passive/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/common/mcstack/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/simulation/Tutorial1/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/simulation/Tutorial4/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/advanced/Tutorial3/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/7-parameters/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/serialization/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/9-PixelDetector/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/simulation/rutherford/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/1-sampler-sink/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/2-sampler-processor-sink/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/4-copypush/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/5-req-rep/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/6-multiple-channels/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/8-multipart/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/LmdSampler/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/MQ/SharedMemory/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/advanced/GoTutorial/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/advanced/MbsTutorial/cmake_install.cmake")

endif()

