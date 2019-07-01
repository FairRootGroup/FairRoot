 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# The name of our project is "FairRoot".  CMakeLists files in this project can
# refer to the root source directory of the project as ${FAIRROOT_SOURCE_DIR} or
# as ${CMAKE_SOURCE_DIR} and to the root binary directory of the project as
# ${FAIRROOT_BINARY_DIR} or ${CMAKE_BINARY_DIR}.
# This difference is important for the base classes which are in FAIRROOT
# and the subproject (i.e: CbmRoot, Pandaroot,... etc).

# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_INSTALL_MESSAGE LAZY)
# Set project version
SET(FAIRROOT_MAJOR_VERSION 18)
SET(FAIRROOT_MINOR_VERSION 2)
SET(FAIRROOT_PATCH_VERSION 0)

# Set name of our project to "FAIRROOT".
# Has to be done after check of cmake version
# This also sets ${FAIRROOT_VERSION} to the provided VERSION value, which would be empty if not set here explicitly
project(FAIRROOT VERSION ${FAIRROOT_MAJOR_VERSION}.${FAIRROOT_MINOR_VERSION}.${FAIRROOT_PATCH_VERSION})
# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/
# is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

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
include(CheckSymbolExists)

# FairRoot only uses C++11 or later, so we need an compiler which supports C++11
# Check if the used compiler support C++11. If not stop with an error message
If(NOT _HAS_CXX11_FLAG)
  Message(FATAL_ERROR "The used C++ compiler (${CMAKE_CXX_COMPILER}) does not support C++11. CbmRoot can only be compiled with compilers supporting C++11. Please install such a compiler.")
EndIf()

# set cmake policies
include(FairRootCmakePolicies)
set_fairroot_cmake_policies()

# Load some basic macros which are needed later on
include(FairMacros)
include(WriteConfigFile)
include(Dart)
include(CheckCompiler)

#Check the compiler and set the compile and link flags
Check_Compiler()

# Check also if FairSoft has been compiled with C++11 or C++14 support
# If FairSoft is used the compiler flags provided by fairsoft-config
# are added to the variable CMAKE_CXX_FLAGS.
# If alibuild is used the compiler flags are passed on the command line
# and are also added to CMAKE_CXX_FLAGS.
# So check if CMAKE_CXX_FLAGS has the compiler flags -std=c++11 or -std=c++14
String(FIND "${CMAKE_CXX_FLAGS}" "-std=c++11" POS_C++11)
If(${POS_C++11} EQUAL -1)
  String(FIND "${CMAKE_CXX_FLAGS}" "-std=c++14" POS_C++11)
  If(${POS_C++11} EQUAL -1)
    String(FIND "${CMAKE_CXX_FLAGS}" "-std=c++17" POS_C++11)
    If(${POS_C++11} EQUAL -1)
      Message(FATAL_ERROR "FairSoft wasn't compiled with c++11, c++14 or c++17 support. Please recompile FairSoft with a compiler which supports at least c++11.")
    EndIf()
  EndIf()
EndIf()

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

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

if(SIMPATH)
  set(CMAKE_PREFIX_PATH ${SIMPATH} ${CMAKE_PREFIX_PATH})
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${SIMPATH}/lib)
endif()

# FairRoot only supports ROOT6, so check which version is available
find_package2(PUBLIC ROOT  VERSION 6.10.00  REQUIRED)
find_package2(PUBLIC FairLogger  VERSION 1.2.0 REQUIRED)
find_package2(PUBLIC Pythia6)
find_package2(PUBLIC Pythia8)
find_package2(PUBLIC Protobuf)
find_package2(PUBLIC msgpack)
find_package2(PUBLIC FlatBuffers)

find_package2(PUBLIC Geant3)
if(Geant3_FOUND)
  Set(Geant3_LIBRARY_DIR ${Geant3_DIR}/${Geant3_CMAKE_INSTALL_LIBDIR})
  FIND_PATH(Geant3_SYSTEM_DIR NAMES data PATHS
           ${Geant3_DIR}/../../share/geant3
           NO_DEFAULT_PATH)
endif()

find_package2(PUBLIC Geant4)

Find_Package2(PUBLIC VGM)

find_package2(PUBLIC Geant4VMC)
if(Geant4VMC_FOUND)
  Set(Geant4VMC_LIBRARY_DIR "${Geant4VMC_DIR}/${Geant4VMC_CMAKE_INSTALL_LIBDIR}")
  Set(Geant4VMC_SHARE_DIR "${Geant4VMC_DIR}/share")
  Find_Path(Geant4VMC_MACRO_DIR NAMES g4libs.C PATHS
    ${Geant4VMC_SHARE_DIR}/Geant4VMC-${Geant4VMC_VERSION}/examples/macro
    NO_DEFAULT_PATH
  )
Endif()

find_package2(PUBLIC IWYU)
if(WITH_GO_EXAMPLE)
  find_package2(PUBLIC Go VERSION 1.7)
  if(Go_FOUND)
    set(Go_VERSION "${GO_VERSION}")
  endif()
endif()

find_package2(PUBLIC GSL)
if(NOT DEFINED GTEST_ROOT)
  set(GTEST_ROOT ${SIMPATH})
endif()

find_package2(PUBLIC FairMQ VERSION 1.2.3)


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
#Message("-- Looking for Boost ...")
# If an older version of boost is found both of the variables below are
# cached and in a second cmake run, a good boost version is found even
# if the version is to old.
# To overcome this problem both variables are cleared before checking
# for boost.
Unset(Boost_INCLUDE_DIR CACHE)
Unset(Boost_LIBRARY_DIRS CACHE)

find_package2(PUBLIC Boost
  VERSION 1.67
  COMPONENTS thread system timer program_options random filesystem chrono exception regex serialization log log_setup atomic date_time signals
  ADD_REQUIREMENTS_OF FairMQ
)

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

find_package2(PUBLIC yaml-cpp)
if(yaml-cpp_FOUND AND TARGET yaml-cpp AND YAML_CPP_INCLUDE_DIR)
  set_target_properties(yaml-cpp PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${YAML_CPP_INCLUDE_DIR}
  )
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
add_subdirectory (alignment)
add_subdirectory (fairtools)
add_subdirectory (base)
add_subdirectory (geobase)
add_subdirectory (parbase)
add_subdirectory (generators)
If(Geant3_FOUND)
 add_subdirectory (geane)
 add_subdirectory (trackbase)
EndIf ()
add_subdirectory (eventdisplay)

add_subdirectory (MbsAPI)
add_subdirectory (datamatch)

add_subdirectory (templates)

If (FairMQ_FOUND)
  add_subdirectory (base/MQ)
  add_subdirectory (parmq)
Else ()
  Message(STATUS "base/MQ and parmq will not be built, because FairMQ was not found.")
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
#Message("Test_Model: ${CMAKE_BUILD_TYPE}")
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

find_package(Git)
set (Git_VERSION ${GIT_VERSION_STRING})
string(REPLACE "git" " " Git_ROOT ${GIT_EXECUTABLE} )
If(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
  Execute_Process(COMMAND ${GIT_EXECUTABLE} describe --tags
                  OUTPUT_VARIABLE FAIRROOT_GIT_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                 )
Else()
  Set(FAIRROOT_GIT_VERSION v${FAIRROOT_MAJOR_VERSION}.${FAIRROOT_MINOR_VERSION}.${FAIRROOT_PATCH_VERSION})
EndIf()
Configure_File(${CMAKE_SOURCE_DIR}/cmake/scripts/fairroot-config.in ${CMAKE_BINARY_DIR}/fairroot-config @ONLY)

Install(PROGRAMS ${CMAKE_BINARY_DIR}/fairroot-config
        DESTINATION bin
       )


WRITE_CONFIG_FILE(config.sh)
WRITE_CONFIG_FILE(config.csh)
SET(VMCWORKDIR ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples)
SET(ROOT_INCLUDE_PATH ${CMAKE_INSTALL_PREFIX}/include)
WRITE_CONFIG_FILE(config.sh_install)
WRITE_CONFIG_FILE(config.csh_install)

# Summary ######################################################################
if(CMAKE_CXX_FLAGS)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}GLOBAL CXX FLAGS${CR}  ${BGreen}${CMAKE_CXX_FLAGS}${CR}")
endif()
if(CMAKE_CONFIGURATION_TYPES)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}BUILD TYPE         CXX FLAGS${CR}")
  string(TOUPPER "${CMAKE_BUILD_TYPE}" selected_type)
  foreach(type IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${type}" type_upper)
    if(type_upper STREQUAL selected_type)
      pad("${type}" 18 " " type_padded)
      message(STATUS "${BGreen}* ${type_padded}${CMAKE_CXX_FLAGS_${type_upper}}${CR}")
    else()
      pad("${type}" 18 " " type_padded)
      message(STATUS "  ${BWhite}${type_padded}${CR}${CMAKE_CXX_FLAGS_${type_upper}}")
    endif()
    unset(type_padded)
    unset(type_upper)
  endforeach()
  message(STATUS "  ")
  message(STATUS "  (Change the build type with ${BMagenta}-DCMAKE_BUILD_TYPE=...${CR})")
endif()

################################################################################
if(PROJECT_PACKAGE_DEPENDENCIES)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}DEPENDENCY FOUND     VERSION                   PREFIX${CR}")
  foreach(dep IN LISTS PROJECT_PACKAGE_DEPENDENCIES)
    if(${dep}_VERSION)
      if(${dep} STREQUAL DDS)
        set(version_str "${BGreen}${${dep}_MAJOR_VERSION}.${${dep}_MINOR_VERSION}${CR}")
      elseif(${dep} STREQUAL Boost)
        if(Boost_VERSION_MAJOR)
          set(version_str "${BGreen}${${dep}_VERSION_MAJOR}.${${dep}_VERSION_MINOR}${CR}")
        else()
          set(version_str "${BGreen}${${dep}_MAJOR_VERSION}.${${dep}_MINOR_VERSION}${CR}")
        endif()
      else()
        set(version_str "${BGreen}${${dep}_VERSION}${CR}")
      endif()
    else()
      set(version_str "${BYellow}unknown${CR}")
    endif()
    if(PROJECT_${dep}_VERSION)
      set(version_req_str " (>= ${PROJECT_${dep}_VERSION})")
    endif()
    pad(${dep} 20 " " dep_padded)
    if(DISABLE_COLOR)
      pad("${version_str}${version_req_str}" 25 " " version_padded)
    else()
      pad("${version_str}${version_req_str}" 25 " " version_padded COLOR 1)
    endif()
    set(prefix ${${dep}_PREFIX})
    if(${dep} STREQUAL Boost)
      if(TARGET Boost::headers)
        get_target_property(boost_include Boost::headers INTERFACE_INCLUDE_DIRECTORIES)
      else()
        get_target_property(boost_include Boost::boost INTERFACE_INCLUDE_DIRECTORIES)
      endif()
      get_filename_component(prefix ${boost_include}/.. ABSOLUTE)
    elseif(${dep} STREQUAL Protobuf)
      get_filename_component(prefix ${Protobuf_INCLUDE_DIRS}/.. ABSOLUTE)
    elseif(${dep} STREQUAL msgpack)
      get_target_property(msgpack_include msgpackc INTERFACE_INCLUDE_DIRECTORIES)
      get_filename_component(prefix ${msgpack_include}/.. ABSOLUTE)
    elseif(${dep} STREQUAL Pythia6)
      get_filename_component(prefix ${PYTHIA6_LIBRARY_DIR}/.. ABSOLUTE)
    elseif(${dep} STREQUAL Pythia8)
      get_filename_component(prefix ${PYTHIA8_LIB_DIR}/.. ABSOLUTE)
    elseif(${dep} STREQUAL FairLogger)
      if(FairLogger_PREFIX)
        set(prefix ${FairLogger_PREFIX})
      else()
        set(prefix ${FairLogger_ROOT})
      endif()
    elseif(${dep} STREQUAL FairMQ)
      if(FairMQ_PREFIX)
        set(prefix ${FairMQ_PREFIX})
      else()
        set(prefix ${FairMQ_ROOT})
      endif()
    elseif(${dep} STREQUAL yaml-cpp)
      get_filename_component(prefix ${YAML_CPP_INCLUDE_DIR}/.. ABSOLUTE)
    elseif(${dep} STREQUAL Geant4VMC)
      string(REPLACE ":" ";" geant4vmc_include ${Geant4VMC_INCLUDE_DIRS})
      list(GET geant4vmc_include 0 geant4vmc_include)
      get_filename_component(prefix ${geant4vmc_include}/../.. ABSOLUTE)
    elseif(${dep} STREQUAL Geant3)
      string(REPLACE ":" ";" geant3_include ${Geant3_INCLUDE_DIRS})
      list(GET geant3_include 0 geant3_include)
      get_filename_component(prefix ${geant3_include}/../.. ABSOLUTE)
    elseif(${dep} STREQUAL Geant4)
      list(GET Geant4_INCLUDE_DIRS 0 geant4_include)
      get_filename_component(prefix ${geant4_include}/../.. ABSOLUTE)
    elseif(${dep} STREQUAL VGM)
      string(REPLACE ":" ";" vgm_include ${VGM_INCLUDE_DIRS})
      list(GET vgm_include 0 vgm_include)
      get_filename_component(prefix ${vgm_include}/.. ABSOLUTE)
    elseif(${dep} STREQUAL ROOT)
      set(prefix ${ROOT_INSTALL_DIR})
    elseif(${dep} STREQUAL IWYU)
      get_filename_component(prefix ${IWYU_BINARY}/.. ABSOLUTE)
    elseif(${dep} STREQUAL yaml-cpp)
      get_filename_component(prefix ${YAML_CPP_INCLUDE_DIR}/.. ABSOLUTE)
    endif()

    message(STATUS "  ${BWhite}${dep_padded}${CR}${version_padded}${prefix}")

    if(${dep} STREQUAL Geant3)
      message(STATUS "                                          G3SYS: ${Geant3_SYSTEM_DIR}")
    endif()
    if(${dep} STREQUAL Geant4)
      foreach(dataset IN LISTS Geant4_DATASETS)
        pad(${Geant4_DATASET_${dataset}_ENVVAR} 20 " " envvar_padded LEFT)
        message(STATUS "                          ${envvar_padded}: ${Geant4_DATASET_${dataset}_PATH}")
      endforeach()
    endif()

    unset(version_str)
    unset(version_padded)
    unset(version_req_str)
  endforeach()
endif()
message(STATUS "  ")

message(STATUS "  ${Cyan}COMPONENT           BUILT?  INFO${CR}")
if(BUILD_EXAMPLES)
  set(examples_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_EXAMPLES=OFF${CR})")
else()
  set(examples_summary "${BRed} NO${CR}    (enable with ${BMagenta}-DBBUILD_EXAMPLES=ON${CR})")
endif()
message(STATUS "  ${BWhite}Examples${CR}             ${examples_summary}")

if(BUILD_DOXYGEN)
  set(doxygen_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_DOXYGENS=OFF${CR})")
else()
  set(doxygen_summary "${BRed} NO${CR}     (enable with ${BMagenta}-DBUILD_DOXYGEN=ON${CR})")
endif()
message(STATUS "  ${BWhite}Doxygen${CR}             ${doxygen_summary}")

if(BUILD_UNITTESTS)
  set(unittests_summary "${BGreen} YES${CR}    (disable with ${BMagenta}-DBUILD_UNITTESTS=OFF${CR})")
else()
  set(unittests_summary "${BRed} NO${CR}     (default, enable with ${BMagenta}-DBUILD_UNITTESTS=ON${CR})")
endif()
message(STATUS "  ${BWhite}Unit-tests${CR}          ${unittests_summary}")

if(WITH_GO_EXAMPLE)
  set(Go_summary "${BGreen} YES${CR}    (disable with ${BMagenta}-DWITH_GO_EXAMPLE=OFF${CR})")
else()
   set(Go_summary "${BRed} NO${CR}     (default, enable with ${BMagenta}-DWITH_GO_EXAMPLE=ON${CR})")
endif()
message(STATUS "  ${BWhite}Go-Example ${CR}         ${Go_summary}")


message(STATUS "  ")
################################################################################
