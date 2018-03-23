 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# The name of our project is "FairBase".  CMakeLists files in this project can
# refer to the root source directory of the project as ${FAIRROOT_SOURCE_DIR} or
# as ${CMAKE_SOURCE_DIR} and to the root binary directory of the project as
# ${FAIRROOT_BINARY_DIR} or ${CMAKE_BINARY_DIR}.
# This difference is important for the base classes which are in FAIRROOT
# and PANDAROOT.

# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.9.4 FATAL_ERROR)

### CMP0025   Compiler id for Apple Clang is now AppleClang.
### CMP0042   MACOSX_RPATH is enabled by default.

foreach(p
  CMP0025 # CMake 3.0
  CMP0028 # double colon for imported and alias targets
  CMP0042 # CMake 3.0
  CMP0054 # Only interpret ``if()`` arguments as variables or keywords when unquoted.
  )
  if(POLICY ${p})
  cmake_policy(SET ${p} NEW)
  endif()
endforeach()

# Set project version
SET(FAIRROOT_MAJOR_VERSION 17)
SET(FAIRROOT_MINOR_VERSION 10)
SET(FAIRROOT_PATCH_VERSION 02)

# Set name of our project to "FAIRROOT".
# Has to be done after check of cmake version
# This also sets ${FAIRROOT_VERSION} to the provided VERSION value, which would be empty if not set here explicitly
project(FAIRROOT VERSION ${FAIRROOT_MAJOR_VERSION}.${FAIRROOT_MINOR_VERSION}.${FAIRROOT_PATCH_VERSION})

option(BUILD_OFI_TRANSPORT "Build FairMQ OFI transport" OFF)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/
# is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/cuda" ${CMAKE_MODULE_PATH})

if(APPLE)
  # Configure RPATH entries on macOS
  # https://cmake.org/Wiki/CMake_RPATH_handling#Always_full_RPATH
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
  if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  endif()
endif()

if(CMAKE_GENERATOR STREQUAL "Ninja" AND
  ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9) OR
   (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5)))
  # Force colored warnings in Ninja's output, if the compiler has -fdiagnostics-color support.
  # Rationale in https://github.com/ninja-build/ninja/issues/814
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif()

SET(VMCWORKDIR ${CMAKE_SOURCE_DIR}/examples)

# Check if the compiler support specific C++11 features
# Up to now this is only a check since the code does not use
# any of the features of the new standard
Set(CheckSrcDir "${CMAKE_SOURCE_DIR}/cmake/checks")
include(CheckCXX11Features)

# FairRoot only uses C++11 or later, so we need an compiler which supports C++11
# Check if the used compiler support C++11. If not stop with an error message
If(NOT _HAS_CXX11_FLAG)
  Message(FATAL_ERROR "The used C++ compiler (${CMAKE_CXX_COMPILER}) does not support C++11. CbmRoot can only be compiled with compilers supporting C++11. Please install such a compiler.")
EndIf()


# Load some basic macros which are needed later on
include(FairMacros)
include(WriteConfigFile)
include(Dart)
include(CheckCompiler)

# COmpile TIme REducer helper
include(cotire)

#Check the compiler and set the compile and link flags
Check_Compiler()

# Check also if FairSoft has been compiled with C++11 or C++14 support
# If FairSoft is used the compiler flags provided by fairsoft-config
# are added to the variable CMAKE_CXX_FLAGS.
# If alibuild is used the compiler flags are passed on the command line
# and are also added to CMAKE_CXX_FLAGS.
# So check if CMAKE_CXX_FLAGS has the compiler flags -std=c++11 or -std=c++14
String(FIND ${CMAKE_CXX_FLAGS} "-std=c++11" POS_C++11)
If(${POS_C++11} EQUAL -1)
  String(FIND ${CMAKE_CXX_FLAGS} "-std=c++14" POS_C++11)
  If(${POS_C++11} EQUAL -1)
    Message(FATAL_ERROR "FairSoft wasn't compiled with c++11 or c++14 support. Please recompile FairSoft with a compiler which supports at least c++11.")
  EndIf()
EndIf()

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
#Option(FAIRROOT_MODULAR_BUILD "Modular build without environment variables" OFF)
#IF(NOT FAIRROOT_MODULAR_BUILD)
If(FAIRSOFT_CONFIG)
  IF(NOT DEFINED ENV{SIMPATH})
    MESSAGE(FATAL_ERROR "You did not define the environment variable SIMPATH which is nedded to find the external packages. Please set this variable and execute cmake again.")
  ENDIF(NOT DEFINED ENV{SIMPATH})
  STRING(REGEX MATCHALL "[^:]+" PATH $ENV{PATH})
  SET(SIMPATH $ENV{SIMPATH})
endif()

# Check if the external packages are installed into a separate install
# directory
CHECK_EXTERNAL_PACKAGE_INSTALL_DIR()

# searches for needed packages
# REQUIRED means that cmake will stop if this packages are not found
# For example the framework can run without GEANT4, but ROOT is
# mandatory

# FairRoot only supports ROOT6, so check which version is available
find_package(ROOT 6.10.00 REQUIRED)
find_package(Pythia6)
find_package(Pythia8)

if(FAIRROOT_MODULAR_BUILD)
  # Geant3, Geant4 installed via cmake
  Message(STATUS "Looking for GEANT3...")
  Find_Package(Geant3)
  # Fill the variables needed to create the config script
  If(Geant3_DIR)
    Set(GEANT3_INCLUDE_DIR ${Geant3_INCLUDE_DIRS})
    Set(GEANT3_LIBRARIES ${Geant3_LIBRARIES})
    Set(GEANT3_LIBRARY_DIR ${Geant3_DIR}/..)
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${GEANT3_LIBRARY_DIR})
    FIND_PATH(GEANT3_SYSTEM_DIR NAMES data PATHS
              ${Geant3_DIR}/../../share/geant3
              NO_DEFAULT_PATH
             )
    Set(GEANT3_FOUND TRUE)
    Message(STATUS "Looking for GEANT3... - found ${GEANT3_LIBRARIES}")
  Else()
    Set(GEANT3_FOUND FALSE)
    Message(Status "Looking for GEANT3... - Not found ")
  EndIf()
  Message(STATUS "Looking for GEANT4...")
  Find_Package(Geant4)
  If(Geant4_DIR)
    Set(GEANT4_INCLUDE_DIR ${Geant4_INCLUDE_DIRS})
    Set(GEANT4_LIBRARY_DIR "${Geant4_DIR}/..")
    Set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${GEANT4_LIBRARY_DIR})
    Set(GEANT4_SHARE_DIR "${Geant4_DIR}/../../share")
    Set(GEANT4_FOUND TRUE)
    Message(STATUS "Looking for GEANT4... - found ${GEANT4_LIBRARY_DIR}")
    Set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules_old" ${CMAKE_MODULE_PATH})
    Find_Package(GEANT4DATA)
  Else()
    Set(GEANT4_FOUND FALSE)
    Message(Status "Looking for GEANT4... - Not found ")
  EndIf()
  # Checking for Genat4VMC has to be done in a better way.
  # In the moment the Geant4VMC version is hardcoded
  Message(STATUS "Looking for GEANT4VMC...")
  Find_Package(Geant4VMC)
  If(Geant4VMC_DIR)
    Set(GEANT4VMC_INCLUDE_DIR ${Geant4VMC_INCLUDE_DIRS})
    Set(GEANT4VMC_LIBRARY_DIR "${Geant4VMC_DIR}/..")
    Set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${GEANT4VMC_LIBRARY_DIR})
    Set(GEANT4VMC_SHARE_DIR "${Geant4VMC_DIR}/../../share")
    Find_Path(GEANT4VMC_MACRO_DIR NAMES g4libs.C PATHS
       ${GEANT4VMC_SHARE_DIR}/Geant4VMC-${Geant4VMC_VERSION}/examples/macro
       NO_DEFAULT_PATH
    )
    Set(GEANT4VMC_FOUND TRUE)
    Message(STATUS "Looking for GEANT4VMC... - found ${GEANT4VMC_LIBRARY_DIR}")
  EndIf()
  Message(STATUS "Looking for VGM...")
  Find_Package(VGM)
  If(VGM_DIR)
    Set(VGM_INCLUDE_DIR ${VGM_INCLUDE_DIRS})
    Set(VGM_LIBRARY_DIR "${VGM_DIR}/..")
    Set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${VGM_LIBRARY_DIR})
    Set(VGM_FOUND TRUE)
    Message(STATUS "Looking for VGM... - found ${VGM_LIBRARY_DIR}")
  EndIf()
else(FAIRROOT_MODULAR_BUILD)
  # For old versions of VMC packages (to be removed)
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules_old" ${CMAKE_MODULE_PATH})
  find_package(GEANT3)
  find_package(GEANT4)
  find_package(GEANT4DATA)
  find_package(GEANT4VMC)
  find_package(CLHEP)
endif(FAIRROOT_MODULAR_BUILD)

find_package(CUDA)
find_package(IWYU)
find_package(ZeroMQ 4.1.3)
find_package(nanomsg)
if(SIMPATH)
  set(CMAKE_PREFIX_PATH ${SIMPATH} ${CMAKE_PREFIX_PATH})
endif()
find_package(Protobuf)
find_package(Msgpack)
find_package(FlatBuffers)
find_package(DDS)
if(NOT DISABLE_GO)
  find_package(Go 1.7)
endif()
find_package(GSL)
if(NOT DEFINED GTEST_ROOT)
  set(GTEST_ROOT ${SIMPATH})
endif()
find_package(GTest)


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

if(NOT DEFINED Boost_NO_SYSTEM_PATHS)
  Set(Boost_NO_SYSTEM_PATHS TRUE)
endif()
Set(Boost_NO_BOOST_CMAKE TRUE)
Message("-- Looking for Boost ...")
# If an older version of boost is found both of the variables below are
# cached and in a second cmake run, a good boost version is found even
# if the version is to old.
# To overcome this problem both variables are cleared before checking
# for boost.
Unset(Boost_INCLUDE_DIR CACHE)
Unset(Boost_LIBRARY_DIRS CACHE)
find_package(Boost 1.64 COMPONENTS thread system timer program_options random filesystem chrono exception regex
    serialization log log_setup atomic date_time signals)
If (Boost_FOUND)
  Set(Boost_Avail 1)
  Set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${Boost_LIBRARY_DIR})
Else (Boost_FOUND)
  Set(Boost_Avail 0)
EndIf (Boost_FOUND)

If(ROOT_FOUND_VERSION LESS 59999)
#  If(FAIRROOT_MODULAR_BUILD)
#    SET(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
#        VERSION "${FAIRROOT_VERSION}"
#        SOVERSION "${FAIRROOT_MAJOR_VERSION}"
#    )
#  Else()
    SET(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
        VERSION "${FAIRROOT_VERSION}"
        SOVERSION "${FAIRROOT_MAJOR_VERSION}"
        SUFFIX ".so"
    )
#  EndIf()
Else()
  SET(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
      VERSION "${FAIRROOT_VERSION}"
      SOVERSION "${FAIRROOT_MAJOR_VERSION}"
  )
EndIf()

if(BUILD_OFI_TRANSPORT)
  find_package(OFI REQUIRED COMPONENTS fi_sockets)
endif()

configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/FairRootConfigVersion.cmake.in "${CMAKE_BINARY_DIR}/FairRootConfigVersion.cmake" @ONLY)

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
add_subdirectory (logger)
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

If (Boost_FOUND AND POS_C++11 AND ZeroMQ_FOUND AND HAS_CXX11_PATTERN1)
  Message(STATUS "Required C++11 feature(s), boost and ZeroMQ libraries found. FairMQ will be built.")
  add_subdirectory (fairmq)
  add_subdirectory (base/MQ)
  add_subdirectory (parmq)
Else ()
  Message(STATUS "Building of the FairMQ library is switched off due to at least one of the following reasons : one or more C++11 feature(s), ZeroMQ or the necessary boost libraries couldn't be found on the system.")
EndIf ()

Option(BUILD_DOXYGEN "Build Doxygen" OFF)
if(BUILD_DOXYGEN)
  MESSAGE(STATUS "*** Building the Doxygen documentation ***")
  ADD_SUBDIRECTORY(doxygen)
endif(BUILD_DOXYGEN)

Option(BUILD_EXAMPLES "Build Examples" ON)
if(BUILD_EXAMPLES)
  add_subdirectory (examples)
endif(BUILD_EXAMPLES)

if(IWYU_FOUND)

  ADD_CUSTOM_TARGET(checkHEADERS
     DEPENDS $ENV{ALL_HEADER_RULES}
  )

endif(IWYU_FOUND)


Option(BUILD_UNITTESTS "Build all unittests and add them as new tests" OFF)
Message("Test_Model: ${CMAKE_BUILD_TYPE}")
If(${CMAKE_BUILD_TYPE} MATCHES PROFILE)
  Set(BUILD_UNITTESTS ON)
EndIf()
If(BUILD_UNITTESTS)

  Message("Build the unit tests.")

  If(GTEST_FOUND)
    Message("Add tests library and tests.")
    add_subdirectory(test)
  EndIf(GTEST_FOUND)
EndIf(BUILD_UNITTESTS)

if(BUILD_EXAMPLES)
  Install(DIRECTORY examples/common/gconfig examples/common/geometry
          DESTINATION share/fairbase/examples/common
          PATTERN ".svn" EXCLUDE)
endif(BUILD_EXAMPLES)

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
  Set(FAIRROOT_GIT_VERSION v-17.10)
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
