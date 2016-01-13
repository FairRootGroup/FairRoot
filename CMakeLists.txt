 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# The name of our project is "FairBase".  CMakeLists files in this project can
# refer to the root source directory of the project as ${FAIRROOT_SOURCE_DIR} or
# as ${CMAKE_SOURCE_DIR} and to the root binary directory of the project as 
# ${FAIRROOT_BINARY_DIR} or ${CMAKE_BINARY_DIR}.
# This difference is is important for the base classes which are in FAIRROOT 
# and PANDAROOT.

# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION  2.8.2 FATAL_ERROR)

### CMP0025   Compiler id for Apple Clang is now AppleClang.
### CMP0042   MACOSX_RPATH is enabled by default.

foreach(p
  CMP0025 # CMake 3.0
  CMP0042 # CMake 3.0
  )
  if(POLICY ${p})
  cmake_policy(SET ${p} NEW)
  endif()
endforeach()


# Set name of our project to "FAIRROOT". Has to be done
# after check of cmake version                        
project(FAIRROOT)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ 
# is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/cuda" ${CMAKE_MODULE_PATH})

SET(VMCWORKDIR ${CMAKE_SOURCE_DIR}/examples)

# Check if the compiler support specific C++11 features
# Up to now this is only a check since the code does not use
# any of the features of the new standard
Set(CheckSrcDir "${CMAKE_SOURCE_DIR}/cmake/checks")
include(CheckCXX11Features)

# Load some basic macros which are needed later on
include(FairMacros)
include(WriteConfigFile)
include(Dart)
include(CheckCompiler)

#Check the compiler and set the compile and link flags
Check_Compiler()

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

Option(WITH_DBASE "Switch off the building of FairDB." OFF)
If(WITH_DBASE)
  Add_Definitions(-DWITH_DBASE)
EndIf()

Option(USE_PATH_INFO "Information from PATH and LD_LIBRARY_PATH are used." OFF)

If(USE_PATH_INFO)
  Set(PATH $ENV{PATH})
  If (APPLE)
    Set(LD_LIBRARY_PATH $ENV{DYLD_LIBRARY_PATH})
  Else (APPLE)
    Set(LD_LIBRARY_PATH $ENV{LD_LIBRARY_PATH})
  EndIf (APPLE)
EndIf(USE_PATH_INFO)

# Check if the user wants to build the project in the source
# directory and if the install directory is different from the build
# directory
CHECK_OUT_OF_SOURCE_BUILD()
CHECK_INSTALL_DIRECTORY()

# Check if we are on an UNIX system. If not stop with an error
# message
IF(NOT UNIX)
  MESSAGE(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
ENDIF(NOT UNIX)  


#Check if necessary environment variables are set
#If not stop execution unless modular build is activated
Option(FAIRROOT_MODULAR_BUILD "Modular build without environment variables" OFF)
IF(NOT FAIRROOT_MODULAR_BUILD)
  IF(NOT DEFINED ENV{SIMPATH})
    MESSAGE(FATAL_ERROR "You did not define the environment variable SIMPATH which is nedded to find the external packages. Please set this variable and execute cmake again.")
  ENDIF(NOT DEFINED ENV{SIMPATH})
  STRING(REGEX MATCHALL "[^:]+" PATH $ENV{PATH})
  SET(SIMPATH $ENV{SIMPATH})
endif(NOT FAIRROOT_MODULAR_BUILD)

# Check if the external packages are installed into a separate install
# directory
CHECK_EXTERNAL_PACKAGE_INSTALL_DIR()

# searches for needed packages
# REQUIRED means that cmake will stop if this packages are not found
# For example the framework can run without GEANT4, but ROOT is
# mandatory

find_package(ROOT 5.32.00 REQUIRED)
find_package(Pythia6)

if(FAIRROOT_MODULAR_BUILD)
  # Geant3, Geant4 installed via cmake
  find_package(Geant3)
  find_package(Geant4)
else(FAIRROOT_MODULAR_BUILD)
  # For old versions of VMC packages (to be removed)
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules_old" ${CMAKE_MODULE_PATH})
  find_package(GEANT3)
  find_package(GEANT4)
  find_package(GEANT4DATA)
  find_package(GEANT4VMC)
  find_package(CLHEP)
  find_package(GEANT4DATA)
  find_package(GEANT4VMC)
  find_package(CLHEP)
endif(FAIRROOT_MODULAR_BUILD)

find_package(CUDA)
find_package(IWYU)
find_package(ZeroMQ)
find_package(nanomsg)
find_package(Protobuf)
find_package(DDS)

If(WITH_DBASE)
  find_package(MYSQL)
  find_package(PGSQL)
  find_package(SQLITE)
EndIf(WITH_DBASE)

If(FAIRSOFT_EXTERN)
  set(BOOST_ROOT ${SIMPATH})
  set(GSL_DIR ${SIMPATH})
Else(FAIRSOFT_EXTERN)
  set(BOOST_ROOT ${SIMPATH}/basics/boost)
  set(GSL_DIR ${SIMPATH}/basics/gsl)
EndIf(FAIRSOFT_EXTERN)

Set(Boost_NO_SYSTEM_PATHS TRUE)
Set(Boost_NO_BOOST_CMAKE TRUE)
Message("-- Looking for Boost ...")
# If an older version of boost is found both of the variables below are
# cached and in a second cmake run, a good boost version is found even
# if the version is to old.
# To overcome this problem both variables are cleared before checking
# for boost.
Unset(Boost_INCLUDE_DIR CACHE)
Unset(Boost_LIBRARY_DIRS CACHE)
find_package(Boost 1.41 COMPONENTS thread system timer program_options random filesystem chrono exception regex)
If (Boost_FOUND)
  Set(Boost_Avail 1)
  Set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${Boost_LIBRARY_DIR})
Else (Boost_FOUND)
  Set(Boost_Avail 0)
EndIf (Boost_FOUND)

# Set the library version in the main CMakeLists.txt
SET(FAIRROOT_MAJOR_VERSION 15)
SET(FAIRROOT_MINOR_VERSION 11)
SET(FAIRROOT_PATCH_VERSION 0)
SET(FAIRROOT_VERSION "${FAIRROOT_MAJOR_VERSION}.${FAIRROOT_MINOR_VERSION}.${FAIRROOT_PATCH_VERSION}")
  
If(ROOT_FOUND_VERSION LESS 59999)
  SET(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
      VERSION "${FAIRROOT_VERSION}"
      SOVERSION "${FAIRROOT_MAJOR_VERSION}"
      SUFFIX ".so"
  )
Else()
  SET(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
      VERSION "${FAIRROOT_VERSION}"
      SOVERSION "${FAIRROOT_MAJOR_VERSION}"
  )
EndIf()

# Load the macro to generate the needed version info at compile time
Generate_Version_Info()

# Set some useful variables
SetBasicVariables()

# Check C++11 availability
If(NOT CMAKE_CXX_FLAGS)
  Message(STATUS "No C++11 support found.")
Else()
  String(FIND " ${CMAKE_CXX_FLAGS} " "-std=c++11" POS_C++11)
  If(POS_C++11)
    Message(STATUS "C++11 support found.")
  Else()
    Message(STATUS "No C++11 support found.")
  EndIf()
EndIf()


# Recurse into the given subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.
add_subdirectory (fairtools)
add_subdirectory (base)
If(WITH_DBASE)
  add_subdirectory (dbase)
EndIf()
add_subdirectory (geobase)
add_subdirectory (parbase)
add_subdirectory (generators)
If(GEANT3_FOUND)
 add_subdirectory (geane)
 add_subdirectory (trackbase)
 add_subdirectory (eventdisplay)
EndIf ()

add_subdirectory (MbsAPI)
add_subdirectory (datamatch)

If (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
  Message(STATUS "C++11, boost and ZeroMQ libraries found. FairMQ will be built.")
  add_subdirectory (fairmq)
  add_subdirectory (base/MQ)
  add_subdirectory (parmq)
Else ()
  Message(STATUS "Building of the FairMQ library is switched off since C++11, ZeroMQ or the necessary boost libraries couldn't be found on the system")
EndIf ()

Option(BUILD_DOXYGEN "Build Doxygen" OFF)
if(BUILD_DOXYGEN)
  MESSAGE(STATUS "*** Building the Doxygen documentaion ***")
  ADD_SUBDIRECTORY(doxygen)
endif(BUILD_DOXYGEN)


add_subdirectory (examples)

if(IWYU_FOUND)

  ADD_CUSTOM_TARGET(checkHEADERS 
     DEPENDS $ENV{ALL_HEADER_RULES}
  )

endif(IWYU_FOUND)


Option(BUILD_UNITTESTS "Build all unittests and add them as new tests" OFF)
If(BUILD_UNITTESTS)

  Message("Build the unit tests.")

  Set(GTEST_ROOT ${SIMPATH})
  Find_Package(GTest)

  If(GTEST_FOUND)
    Message("Add tests library and tests.")
    add_subdirectory(test)
  EndIf(GTEST_FOUND)
EndIf(BUILD_UNITTESTS)

Install(DIRECTORY examples/common/gconfig examples/common/geometry
        DESTINATION share/fairbase/examples/common
        PATTERN ".svn" EXCLUDE)

Install(FILES ${CMAKE_BINARY_DIR}/config.sh_install
        DESTINATION bin
        RENAME FairRootConfig.sh
       )

Install(FILES ${CMAKE_BINARY_DIR}/check_system.sh
        DESTINATION bin
       )

Install(FILES ${CMAKE_BINARY_DIR}/FairVersion.h
        DESTINATION include
       )

Install(FILES ${CMAKE_BINARY_DIR}/config.csh_install
        DESTINATION bin
        RENAME FairRootConfig.csh
       )

Install(FILES ${CMAKE_BINARY_DIR}/check_system.csh
        DESTINATION bin
       )

Install(DIRECTORY cmake 
        DESTINATION share/fairbase
        PATTERN ".svn" EXCLUDE)

Find_Package(Git)

If(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
  Execute_Process(COMMAND ${GIT_EXECUTABLE} describe --tags
                  OUTPUT_VARIABLE FAIRROOT_GIT_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                 )
Else()
  Set(FAIRROOT_GIT_VERSION v-15.11a) 
EndIf()
Configure_File(${CMAKE_SOURCE_DIR}/cmake/scripts/fairroot-config.in ${CMAKE_BINARY_DIR}/fairroot-config @ONLY)

Install(PROGRAMS ${CMAKE_BINARY_DIR}/fairroot-config
        DESTINATION bin
       )

if(NOT FAIRROOT_MINIMAL)

  WRITE_CONFIG_FILE(config.sh)
  WRITE_CONFIG_FILE(config.csh)

  SET(VMCWORKDIR ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples)
  SET(ROOT_INCLUDE_PATH ${CMAKE_INSTALL_PREFIX}/include)
  WRITE_CONFIG_FILE(config.sh_install)
  WRITE_CONFIG_FILE(config.csh_install)

else(NOT FAIRROOT_MINIMAL)
  WRITE_MINIMAL_CONFIG_FILE(config.sh)
endif(NOT FAIRROOT_MINIMAL)
