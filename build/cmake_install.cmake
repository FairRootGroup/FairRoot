# Install script for directory: /Users/turany/development/FairRoot

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/common" TYPE DIRECTORY FILES
    "/Users/turany/development/FairRoot/examples/common/gconfig"
    "/Users/turany/development/FairRoot/examples/common/geometry"
    REGEX "/\\.svn$" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE RENAME "FairRootConfig.sh" FILES "/Users/turany/development/FairRoot/build/config.sh_install")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "/Users/turany/development/FairRoot/build/check_system.sh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/Users/turany/development/FairRoot/build/FairVersion.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE RENAME "FairRootConfig.csh" FILES "/Users/turany/development/FairRoot/build/config.csh_install")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "/Users/turany/development/FairRoot/build/check_system.csh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fairbase" TYPE DIRECTORY FILES "/Users/turany/development/FairRoot/cmake" REGEX "/\\.svn$" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/Users/turany/development/FairRoot/build/fairroot-config")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/turany/development/FairRoot/build/fairtools/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/base/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/geobase/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/parbase/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/generators/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/geane/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/trackbase/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/eventdisplay/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/MbsAPI/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/datamatch/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/fairmq/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/base/MQ/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/parmq/cmake_install.cmake")
  include("/Users/turany/development/FairRoot/build/examples/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/turany/development/FairRoot/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
