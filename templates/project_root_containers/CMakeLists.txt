# The name of our project is “MYPROJ”.  CMakeLists files in this project can
# refer to the root source directory of the project as ${MYPROJ_SOURCE_DIR}
# or as ${CMAKE_SOURCE_DIR} and to the root binary directory of the project as
# ${MYPROJ_BINARY_DIR} or ${CMAKE_BINARY_DIR}.
# This difference is important for the base classes which are in FAIRROOT
# and the experiment part.

# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.11.0 FATAL_ERROR)
cmake_policy(VERSION 3.11...3.14)

# Set name of our project to “MYPROJ". Has to be done
# after check of cmake version since this is a new feature
project(MYPROJ VERSION 1.0.0)

#In case you need Fortran
#ENABLE_LANGUAGE(Fortran)

# Check for needed environment variables
IF(NOT DEFINED ENV{FAIRROOTPATH})
  MESSAGE(FATAL_ERROR "You did not define the environment variable FAIRROOTPATH which is needed to find FairRoot. Please set this variable and execute cmake again.")
ENDIF(NOT DEFINED ENV{FAIRROOTPATH})

SET(SIMPATH $ENV{SIMPATH})
SET(FAIRROOTPATH $ENV{FAIRROOTPATH})

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/
# is checked
  set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules"  ${CMAKE_MODULE_PATH})
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
if(SIMPATH)
  set(CMAKE_PREFIX_PATH ${SIMPATH} ${CMAKE_PREFIX_PATH})
endif()

find_package(FairCMakeModules 0.2 QUIET REQUIRED)
include(FairFindPackage2)
include(FairSummary)

find_package2(PUBLIC FairRoot VERSION 19.0 REQUIRED)

# Load some basic macros which are needed later on
include(FairMacros)
include(WriteConfigFile)
include(CTest)
include(CheckCompiler)
#include(CheckFortran)

#Check the compiler and set the compile and link flags
If(NOT CMAKE_BUILD_TYPE)
  Message("Set BuildType DEBUG")
  set(CMAKE_BUILD_TYPE Debug)
EndIf(NOT CMAKE_BUILD_TYPE)
Check_Compiler()


set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(INCLUDE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/include")
Set(VMCWORKDIR ${CMAKE_SOURCE_DIR})


# Check if the user wants to build the project in the source
# directory
CHECK_OUT_OF_SOURCE_BUILD()

# Check if we are on an UNIX system. If not stop with an error
# message
IF(NOT UNIX)
  MESSAGE(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
ENDIF(NOT UNIX)

# searches for needed packages
# REQUIRED means that cmake will stop if this packages are not found
# For example the framework can run without GEANT4, but ROOT is
# mandatory

if(SIMPATH)
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${SIMPATH}/lib)
endif()

find_package2(PUBLIC ROOT REQUIRED)
include(ROOTMacros)
fairroot_check_root_cxxstd_compatibility()
if(ROOT_vmc_FOUND)
  set(VMCLIB ROOT::VMC)
else()
  find_package2(PUBLIC VMC REQUIRED)
  set(VMCLIB VMCLibrary)
endif()
find_package2(PUBLIC FairLogger  VERSION 1.2.0 REQUIRED)
find_package2(PUBLIC Pythia6)
find_package2(PUBLIC Pythia8)
find_package2(PUBLIC Geant3)
find_package2(PUBLIC Geant4)
Find_Package2(PUBLIC VGM)
find_package2(PUBLIC Geant4VMC)
find_package2(PUBLIC HEPMC)

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

find_package2(PUBLIC Boost
  VERSION 1.67
)

If (Boost_FOUND)
  Set(Boost_Avail 1)
Else (Boost_FOUND)
  Set(Boost_Avail 0)
EndIf (Boost_FOUND)

find_package2_implicit_dependencies()

# set a variable which should be used in all CMakeLists.txt
# Defines all basic include directories from fairbase
SetBasicVariables()

set(PROJECT_LIBRARY_PROPERTIES VERSION "${PROJECT_VERSION}")

SET(_LIBDIR ${CMAKE_BINARY_DIR}/lib)
SET(LD_LIBRARY_PATH  ${_LIBDIR} ${LD_LIBRARY_PATH})


# Recurse into the given subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.

add_subdirectory (MyProjData)
if(TARGET pythia8 AND TARGET Pythia6)
  add_subdirectory (MyProjGenerators)
endif()
add_subdirectory (NewDetector)
add_subdirectory (passive)
add_subdirectory (field)

WRITE_CONFIG_FILE(config.sh)

configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake
               ${CMAKE_BINARY_DIR}/CTestCustom.cmake
              )
# Summary ######################################################################
fair_summary_global_cxx_flags_standard()
fair_summary_build_types()
fair_summary_package_dependencies()

   ################################################################################
