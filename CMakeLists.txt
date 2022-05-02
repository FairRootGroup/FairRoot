 ################################################################################
 # Copyright (C) 2014-2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
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
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
cmake_policy(VERSION 3.15...3.20)

# Set project version
SET(FAIRROOT_MAJOR_VERSION 19)
SET(FAIRROOT_MINOR_VERSION 0)
SET(FAIRROOT_PATCH_VERSION 0)

set(PROJECT_MIN_CXX_STANDARD 17)

# Set name of our project to "FAIRROOT".
# Has to be done after check of cmake version
# This also sets ${FAIRROOT_VERSION} to the provided VERSION value, which would be empty if not set here explicitly
project(FAIRROOT VERSION ${FAIRROOT_MAJOR_VERSION}.${FAIRROOT_MINOR_VERSION}.${FAIRROOT_PATCH_VERSION})
# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/
# is checked
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/private")

# Generate compile_commands.json file (https://clang.llvm.org/docs/JSONCompilationDatabase.html)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define CMAKE_INSTALL_*DIR family of variables
include(GNUInstallDirs)
include(FairRootTargetRootDictionary)

# Define install dirs
set(PROJECT_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(PROJECT_INSTALL_DATADIR ${CMAKE_INSTALL_DATADIR}/fairbase) # TODO: change 'fairbase' to ${PROJECT_NAME_LOWER}

# https://cmake.org/Wiki/CMake_RPATH_handling
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../${PROJECT_INSTALL_LIBDIR}")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_INSTALL_RPATH "@loader_path/../${PROJECT_INSTALL_LIBDIR}")
  else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_LIBDIR}")
  endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-Wl,--enable-new-dtags")
  set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--enable-new-dtags")
  set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -z defs")
  set(CMAKE_MODULE_LINKER_FLAGS  "${CMAKE_MODULE_LINKER_FLAGS} -z defs")
  set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -z defs")
endif()

if(CMAKE_GENERATOR STREQUAL "Ninja" AND
  ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9) OR
   (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5)))
  # Force colored warnings in Ninja's output, if the compiler has -fdiagnostics-color support.
  # Rationale in https://github.com/ninja-build/ninja/issues/814
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif()

# Set a default if not specified by the user
if(NOT DEFINED BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
endif()
if(NOT DEFINED CMAKE_INSTALL_MESSAGE)
  set(CMAKE_INSTALL_MESSAGE LAZY)
endif()

SET(VMCWORKDIR ${CMAKE_SOURCE_DIR}/examples)

include(CheckSymbolExists)


if(DEFINED ENV{SIMPATH})
  set(SIMPATH $ENV{SIMPATH})
  list(PREPEND CMAKE_PREFIX_PATH ${SIMPATH})
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${SIMPATH}/lib)
endif()

# Load some basic macros which are needed later on
find_package(FairCMakeModules 0.2 QUIET REQUIRED)
include(FairFindPackage2)
include(FairFormattedOutput)
include(FairSummary)
include(FairRootTargets)
include(FairRootPackage)
include(FairRootSummary)
include(FairMacros)
include(WriteConfigFile)
include(Dart)
include(CheckCompiler)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")


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


# Set option(s)
option(BUILD_UNITTESTS "Build all unittests and add them as new tests" OFF)
option(ENABLE_GEANT3_TESTING "Enable tests utilizing Geant3" OFF)
option(BUILD_MBS "Build MBS" OFF)

# searches for needed packages
# REQUIRED means that cmake will stop if this packages are not found
# For example the framework can run without GEANT4, but ROOT is
# mandatory

# FairRoot only supports ROOT6, so check which version is available
list(APPEND required_root_components RIO)
if(BUILD_SIM)
  list(APPEND required_root_components pythia6 pythia8)
endif()
list(APPEND optional_root_components opengl)
list(APPEND optional_root_components gdml vmc)
find_package2(PUBLIC ROOT REQUIRED
  VERSION 6.18.00
  COMPONENTS ${required_root_components}
  OPTIONAL_COMPONENTS ${optional_root_components})
include(ROOTMacros)

#Check the compiler and set the compile and link flags
Check_Compiler()

fairroot_check_root_cxxstd_compatibility()

if(ROOT_vmc_FOUND)
  set(VMCLIB ROOT::VMC)
else()
  find_package2(PUBLIC VMC REQUIRED)
  set(VMCLIB VMCLibrary)
endif()
find_package2(PUBLIC Pythia6)
find_package2(PUBLIC Pythia8)
find_package2(PUBLIC Protobuf)
find_package2(PUBLIC msgpack)
find_package2(PUBLIC Flatbuffers)

find_package2(PUBLIC Geant3)
find_package2(PUBLIC Geant4)

Find_Package2(PUBLIC VGM)

find_package2(PUBLIC Geant4VMC)

find_package2(PUBLIC IWYU)

find_package2(PUBLIC GSL)
if(NOT DEFINED GTEST_ROOT)
  set(GTEST_ROOT ${SIMPATH})
endif()

find_package2(PUBLIC FairMQ VERSION 1.4.0)
find_package2(PUBLIC DDS)
find_package2(PUBLIC FairLogger VERSION 1.2.0 REQUIRED)

if(NOT DEFINED Boost_NO_SYSTEM_PATHS)
  Set(Boost_NO_SYSTEM_PATHS TRUE)
endif()
if(NOT DEFINED Boost_NO_BOOST_CMAKE AND CMAKE_VERSION VERSION_LESS 3.15)
  Set(Boost_NO_BOOST_CMAKE TRUE)
endif()
if(Boost_NO_BOOST_CMAKE)
  # If an older version of boost is found both of the variables below are
  # cached and in a second cmake run, a good boost version is found even
  # if the version is to old.
  # To overcome this problem both variables are cleared before checking
  # for boost.
  Unset(Boost_INCLUDE_DIR CACHE)
  Unset(Boost_LIBRARY_DIRS CACHE)
endif()

list(APPEND boost_dependencies filesystem serialization)

if(BUILD_UNITTESTS)
 list(APPEND boost_dependencies unit_test_framework)
endif()

find_package2(PUBLIC Boost
  VERSION 1.67
  COMPONENTS ${boost_dependencies}
)

If (Boost_FOUND)
  Set(Boost_Avail 1)
Else (Boost_FOUND)
  Set(Boost_Avail 0)
EndIf (Boost_FOUND)

set(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)
set(PROJECT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})

find_package2(PUBLIC yaml-cpp)
# Workaround missing exported include directories
# Upstream has fixed this in https://github.com/jbeder/yaml-cpp/commit/ab5f9259a4e67d3fe0e4832bd407a9e596e2d884 (since 0.6.3)
if(yaml-cpp_FOUND)
  get_filename_component(YAML_CPP_INCLUDE_DIR "${YAML_CPP_INCLUDE_DIR}" REALPATH BASE_DIR "/")
endif()
if(    yaml-cpp_FOUND
   AND TARGET yaml-cpp
   AND EXISTS YAML_CPP_INCLUDE_DIR
   AND yaml-cpp_VERSION VERSION_LESS 0.6.3
)
  set_target_properties(yaml-cpp PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${YAML_CPP_INCLUDE_DIR}"
  )
endif()

configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/FairRootConfigVersion.cmake.in "${CMAKE_BINARY_DIR}/FairRootConfigVersion.cmake" @ONLY)

# Load the macro to generate the needed version info at compile time
Generate_Version_Info()

# Set some useful variables
SetBasicVariables()

# Recurse into the given subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.
add_subdirectory(fairtools)
add_subdirectory(alignment)
add_subdirectory(base)
add_subdirectory(geobase)
add_subdirectory(parbase)
add_subdirectory(generators)
If(Geant3_FOUND)
 add_subdirectory(geane)
 add_subdirectory(trackbase)
EndIf ()

if(ROOT_opengl_FOUND)
  add_subdirectory(eventdisplay)
else()
  message(STATUS "eventdisplay will not be built, because ROOT has no opengl support.")
endif()

if(BUILD_MBS)
  add_subdirectory(MbsAPI)
endif()
add_subdirectory(datamatch)

add_subdirectory(templates)

If (FairMQ_FOUND AND Boost_FOUND)
  add_subdirectory(base/MQ)
  add_subdirectory(parmq)
Else ()
  Message(STATUS "base/MQ and parmq will not be built, because FairMQ and/or Boost was not found.")
EndIf ()

Option(BUILD_DOXYGEN "Build Doxygen" OFF)
if(BUILD_DOXYGEN)
  find_package2(PRIVATE Doxygen COMPONENTS dot)
  if (Doxygen_FOUND)
    if (NOT Doxygen_VERSION AND DOXYGEN_VERSION)
      set(Doxygen_VERSION "${DOXYGEN_VERSION}")
    endif()
    add_subdirectory(doxygen)
  else()
    message(WARNING "BUILD_DOXYGEN requested, but Doxygen not found")
  endif()
endif(BUILD_DOXYGEN)

Option(BUILD_EXAMPLES "Build Examples" ON)
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if(IWYU_FOUND)
  add_custom_target(checkHEADERS DEPENDS $ENV{ALL_HEADER_RULES})
endif(IWYU_FOUND)

find_package2(PRIVATE ClangFormat)
if(ClangFormat_FOUND)
  add_custom_target(FormatCheck
    ${CMAKE_COMMAND} -E env FAIRROOT_GIT_CLANG_FORMAT_BIN=${GIT_CLANG_FORMAT_BIN} ${CMAKE_SOURCE_DIR}/check-format.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
endif()

if(${CMAKE_BUILD_TYPE} MATCHES PROFILE)
  set(BUILD_UNITTESTS ON)
endif()
if(BUILD_UNITTESTS)
  find_package2(PRIVATE GTest REQUIRED VERSION 1.7.0)
  message(STATUS "Building the unit tests.")
  add_subdirectory(test)
endif()
add_subdirectory(test/tgeo)


find_package2_implicit_dependencies()

add_subdirectory(cmake)

install(FILES ${CMAKE_BINARY_DIR}/config.sh_install
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RENAME FairRootConfig.sh
)
install(FILES ${CMAKE_BINARY_DIR}/check_system.sh
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/FairVersion.h
  DESTINATION include
)
install(FILES ${CMAKE_BINARY_DIR}/config.csh_install
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RENAME FairRootConfig.csh
)
install(FILES ${CMAKE_BINARY_DIR}/check_system.csh
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)

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

install(PROGRAMS ${CMAKE_BINARY_DIR}/fairroot-config
  DESTINATION bin
)


WRITE_CONFIG_FILE(config.sh)
WRITE_CONFIG_FILE(config.csh)
SET(VMCWORKDIR ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples)
SET(ROOT_INCLUDE_PATH ${CMAKE_INSTALL_PREFIX}/include)
WRITE_CONFIG_FILE(config.sh_install)
WRITE_CONFIG_FILE(config.csh_install)

install_cmake_package()

# Summary ######################################################################
fairroot_summary_header()
fairroot_summary_install_prefix()
fair_summary_global_cxx_flags_standard()
fair_summary_build_types()
fairroot_summary_package_dependencies()
fairroot_summary_components()

message(STATUS "  ")
################################################################################
