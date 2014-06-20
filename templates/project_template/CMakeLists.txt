# The name of our project is “MyProj”.  CMakeLists files in this project can
# refer to the root source directory of the project as ${MYPROJ_SOURCE_DIR} 
# or as ${CMAKE_SOURCE_DIR} and to the root binary directory of the project as 
# ${MYPROJ_BINARY_DIR} or ${CMAKE_BINARY_DIR}.
# This difference is important for the base classes which are in FAIRROOT 
# and the experiment part.

# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0 FATAL_ERROR)

# Set name of our project to “M”yProj. Has to be done
# after check of cmake version since this is a new feature                  
project(MyProj)

#In case you need Fortran 
#ENABLE_LANGUAGE(Fortran)

FIND_PATH(FAIRBASE NAMES FairRun.h  PATHS
  ${CMAKE_SOURCE_DIR}/base/steer
  NO_DEFAULT_PATH
)

If (FAIRBASE)
  Message(STATUS "Found FAIRBASE")
  SET(FAIRBASE ${FAIRBASE})
Else (FAIRBASE)
  Message(STATUS "NOT Found FAIRBASE")
  IF(NOT DEFINED ENV{FAIRROOTPATH})
     MESSAGE(FATAL_ERROR "You did not define the environment variable FAIRROOTPATH which is needed to find FairRoot. Please set this variable and execute cmake again.")
  ENDIF(NOT DEFINED ENV{FAIRROOTPATH})
  SET(FAIRROOTPATH $ENV{FAIRROOTPATH})

EndIf (FAIRBASE)


# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ 
# is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules"  ${CMAKE_MODULE_PATH})

IF(FAIRROOTPATH)
  Set(CheckSrcDir "${FAIRROOTPATH}/share/fairbase/cmake/checks")
ELSE(FAIRROOTPATH)
  Set(CheckSrcDir "${CMAKE_SOURCE_DIR}/cmake/checks")
ENDIF(FAIRROOTPATH)

if(FAIRROOTPATH)
  find_package(FairRoot)
endif(FAIRROOTPATH)


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
Option(USE_PATH_INFO "Information from PATH and LD_LIBRARY_PATH are
used."OFF)
If(USE_PATH_INFO)
  Set(PATH "$PATH")
  If (APPLE)
    Set(LD_LIBRARY_PATH $ENV{DYLD_LIBRARY_PATH})
  Else (APPLE)
    Set(LD_LIBRARY_PATH $ENV{LD_LIBRARY_PATH})
  EndIf (APPLE)
Else(USE_PATH_INFO)
  STRING(REGEX MATCHALL "[^:]+" PATH $ENV{PATH})
EndIf(USE_PATH_INFO)


# Check if the user wants to build the project in the source
# directory
CHECK_OUT_OF_SOURCE_BUILD()

# Check if we are on an UNIX system. If not stop with an error
# message
IF(NOT UNIX)
  MESSAGE(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
ENDIF(NOT UNIX)  

# Check if we are at GSI
# If we are GSI set some variables
IF(NOT DEFINED ENV{SIMPATH})
   MESSAGE(FATAL_ERROR "You did not define the environment variable SIMPATH which is nedded to find the external packages. Please set this variable and execute cmake again.") 
ENDIF(NOT DEFINED ENV{SIMPATH})

SET(SIMPATH $ENV{SIMPATH})

# Check if the external packages are installed into a separate install
# directory
CHECK_EXTERNAL_PACKAGE_INSTALL_DIR()

# Set the build type. Possibilities are None, Debug, Release, 
# RelWithDebInfo and MinSizeRel 
#SET(CMAKE_BUILD_TYPE Debug)

# searches for needed packages
# REQUIRED means that cmake will stop if this packages are not found
# For example the framework can run without GEANT4, but ROOT is
# mandatory

find_package(ROOT 5.32.00 REQUIRED)
find_package(Pythia8)
find_package(GENERATORS REQUIRED)
find_package(GEANT3 REQUIRED)
find_package(GEANT4)
find_package(GEANT4DATA)
find_package(GEANT4VMC)
find_package(CLHEP)
find_package(CERNLIB)
find_package(HEPMC)

find_package(RuleChecker)
  Set(Boost_NO_SYSTEM_PATHS TRUE)
  Set(Boost_NO_BOOST_CMAKE TRUE)
#  set(Boost_DEBUG TRUE)
  If(${ROOT_LIBRARY_DIR} MATCHES /lib/root)
    set(BOOST_ROOT ${SIMPATH})
    set(GSL_DIR ${SIMPATH})
  Else(${ROOT_LIBRARY_DIR} MATCHES /lib/root)
    set(BOOST_ROOT ${SIMPATH}/basics/boost)
    set(GSL_DIR ${SIMPATH}/basics/gsl)
  EndIf(${ROOT_LIBRARY_DIR} MATCHES /lib/root)
  Message("-- Looking for Boost ...")
  # If an older version of boost is found both of the variables below are
  # cached and in a second cmake run, a good boost version is found even 
  # if the version is to old. 
  # To overcome this problem both variables are cleared before checking
  # for boost.
  Unset(Boost_INCLUDE_DIR CACHE)
  Unset(Boost_LIBRARY_DIRS CACHE)
  find_package(Boost 1.41)
  If (Boost_FOUND)
    Set(Boost_Avail 1)
  Else (Boost_FOUND)
    Set(Boost_Avail 0)
  EndIf (Boost_FOUND)


# set a variable which should be used in all CMakeLists.txt
# Defines all basic include directories from fairbase
SetBasicVariables()


# Set the library version in the main CMakeLists.txt
SET(FAIRROOT_MAJOR_VERSION 0)
SET(FAIRROOT_MINOR_VERSION 0)
SET(FAIRROOT_PATCH_VERSION 0)
SET(FAIRROOT_VERSION "${FAIRROOT_MAJOR_VERSION}.${FAIRROOT_MINOR_VERSION}.${FAIRROOT_PATCH_VERSION}")
SET(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
    VERSION "${FAIRROOT_VERSION}"
    SOVERSION "${FAIRROOT_MAJOR_VERSION}"
    SUFFIX ".so"
)

Generate_Version_Info()

SET(CBMLIBDIR ${CMAKE_BINARY_DIR}/lib)
SET(LD_LIBRARY_PATH  ${CBMLIBDIR} ${LD_LIBRARY_PATH})


#IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#  SET(CMAKE_INSTALL_PREFIX "./install" CACHE PATH "FOO install prefix" FORCE)
#  Message("Set default install path ...")
#ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

install(DIRECTORY geometry DESTINATION pnd_install 
          PATTERN ".svn" EXCLUDE
          )


# Check if the compiler support specific C++11 features
# Up to now this is only a check since the code does not use
# any of the features of the new standard

IF(FAIRROOT_FOUND)
 Set(CheckSrcDir "${FAIRROOTPATH}/share/fairbase/cmake/checks")
ELSE(FAIRROOT_FOUND)
 Set(CheckSrcDir "${CMAKE_SOURCE_DIR}/cmake/checks")
ENDIF(FAIRROOT_FOUND)

include(CheckCXX11Features)

IF(HAS_CXX11_SHAREDPOINTER)
  Add_Definitions(-DHAS_SHAREDPOINTER)
ENDIF(HAS_CXX11_SHAREDPOINTER)



# Recurse into the given subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.

IF(NOT FAIRROOT_FOUND)

add_subdirectory (fairtools)
add_subdirectory (base)
add_subdirectory (geobase)
add_subdirectory (parbase)
add_subdirectory (dbase)
add_subdirectory (MbsAPI)
add_subdirectory (trackbase)
add_subdirectory (geane)
add_subdirectory (generators)
ENDIF (NOT FAIRROOT_FOUND)

add_subdirectory (MyProjData)
add_subdirectory (MyProjGenerators)
add_subdirectory (NewDetector)
add_subdirectory (passive)
add_subdirectory (field)  

FIND_PATH(TEvePath NAMES TEveEventManager.h PATHS
  ${SIMPATH}/tools/root/include
  ${SIMPATH}/include/root
  NO_DEFAULT_PATH
)

If(TEvePath)
#find_package(OpenGL)
#If (OPENGL_FOUND AND OPENGL_GLU_FOUND)
  Message("Found TEve, so the eventdisplay will be compiled.")

IF(NOT FAIRROOT_FOUND)
  add_subdirectory (eventdisplay)
ENDIF(NOT FAIRROOT_FOUND)
# In case you have your own event display add it here

EndIf(TEvePath)

if(RULE_CHECKER_FOUND)

  ADD_CUSTOM_TARGET(RULES 
     COMMAND ${RULE_CHECKER_SCRIPT1} ${CMAKE_BINARY_DIR} viol > violations.html
     DEPENDS $ENV{ALL_RULES})

endif(RULE_CHECKER_FOUND)

WRITE_CONFIG_FILE(config.sh)
 
configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake 
               ${CMAKE_BINARY_DIR}/CTestCustom.cmake
              )


