 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Find ROOT instalation
# This module tries to find the ROOT installation on your system.
# It tries to find the root-config script which gives you all the needed 
# information.
# If the system variable ROOTSYS is set this is straight forward.
# If not the module uses the pathes given in ROOT_CONFIG_SEARCHPATH.
# If you need an other path you should add this path to this varaible.  
# The root-config script is then used to detect basically everything else.
# This module defines a number of key variables and macros.
#
# Variables defined by this module:
#
#   ROOT_FOUND               System has ROOT, this means the root-config 
#                            executable was found.
#
#   ROOT_INCLUDE_DIR         ROOT include directories: not cached
#
#   ROOT_INCLUDES            Same as above,
#
#   ROOT_LIBRARIESS          Link to these to use the ROOT libraries, not cached
#
#   ROOT_LIBRARY_DIR         The path to where the ROOT library files are.
#
#   ROOT_VERSION_STRING      The version string of the ROOT libraries which
#                            is reported by root-config
#
#   ROOT_VERSION_MAJOR       Major version number of ROOT
#   ROOT_VERSION_MINOR       Minor version number of ROOT
#   ROOT_VERSION_PATCH       Patch version number of ROOT
#
#   ROOT_VERSION_NUMBER      A unique version number which is calculated from 
#                            major, minor and patch version found
#
#   ROOT_CINT_EXECUTABLE     The rootcint executable.
#
#   RLIBMAP_EXECUTABLE       The rlibmap executable.

Message(STATUS "Looking for Root...")

Set(ROOT_CONFIG_SEARCHPATH
  ${SIMPATH}/bin
  ${SIMPATH}/tools/root/bin
  $ENV{ROOTSYS}/bin
)

Set(ROOT_FOUND FALSE)
Set(ROOT_DEFINITIONS "")
Set(ROOT_INSTALLED_VERSION_TOO_OLD FALSE)
Set(ROOT_CONFIG_EXECUTABLE ROOT_CONFIG_EXECUTABLE-NOTFOUND)

Find_Program(ROOT_CONFIG_EXECUTABLE NAMES root-config 
             PATHS ${ROOT_CONFIG_SEARCHPATH}
             NO_DEFAULT_PATH
            )
     
If(ROOT_CONFIG_EXECUTABLE)
   
  String(REGEX REPLACE "(^.*)/bin/root-config" "\\1" test ${ROOT_CONFIG_EXECUTABLE}) 
  Set(ENV{ROOTSYS} ${test})
  Set(ROOTSYS ${test})

  Execute_Process(COMMAND ${ROOT_CONFIG_EXECUTABLE} --version 
                  OUTPUT_VARIABLE ROOT_VERSION_STRING
                 )
  Execute_Process(COMMAND ${ROOT_CONFIG_EXECUTABLE} --prefix
                  OUTPUT_VARIABLE ROOT_INSTALL_DIR
                 )
  String(STRIP ${ROOT_VERSION_STRING} ROOT_VERSION_STRING)
  String(STRIP ${ROOT_INSTALL_DIR} ROOT_INSTALL_DIR)


  MESSAGE(STATUS "Looking for Root... - Found ${ROOT_INSTALL_DIR}/bin/root")
  MESSAGE(STATUS "Looking for Root... - Found version is ${ROOT_VERSION_STRING} ")   
   
  # extract major, minor, and patch versions from
  # the version string given by root-config
  String(REGEX REPLACE "^([0-9]+)\\.[0-9][0-9]+\\/[0-9][0-9]+.*" "\\1" ROOT_VERSION_MAJOR "${ROOT_VERSION_STRING}")
  String(REGEX REPLACE "^[0-9]+\\.([0-9][0-9])+\\/[0-9][0-9]+.*" "\\1" ROOT_VERSION_MINOR "${ROOT_VERSION_STRING}")
  String(REGEX REPLACE "^[0-9]+\\.[0-9][0-9]+\\/([0-9][0-9]+).*" "\\1" ROOT_VERSION_PATCH "${ROOT_VERSION_STRING}")

  # compute overall version numbers which can be compared at once
  Math(EXPR req_vers "${ROOT_FIND_VERSION_MAJOR}*10000 + ${ROOT_FIND_VERSION_MINOR}*100 + ${ROOT_FIND_VERSION_PATCH}")
  Math(EXPR found_vers "${ROOT_VERSION_MAJOR}*10000 + ${ROOT_VERSION_MINOR}*100 + ${ROOT_VERSION_PATCH}")

  Set(ROOT_Version ${found_vers})
  Set(ROOT_VERSION_NUMBER ${found_vers})

  If(found_vers LESS req_vers)
    Set(ROOT_FOUND FALSE)
    Set(ROOT_INSTALLED_VERSION_TOO_OLD TRUE)
  Else(found_vers LESS req_vers)
    Set(ROOT_FOUND TRUE)
  EndIf(found_vers LESS req_vers)

Else(ROOT_CONFIG_EXECUTABLE)
  Message(STATUS "Looking for Root... - Not found")
  Message(FATAL_ERROR "ROOT not installed in the searchpath and ROOTSYS is not set. Please set ROOTSYS or add the path to your ROOT installation in the Macro FindROOT.cmake in the subdirectory cmake/modules.")
Endif(ROOT_CONFIG_EXECUTABLE)


If(ROOT_FOUND)

  # ask root-config for the library dir
  # Set ROOT_LIBRARY_DIR
  Execute_Process(COMMAND ${ROOT_CONFIG_EXECUTABLE} --libdir
                  OUTPUT_VARIABLE ROOT_LIBRARY_DIR
                 )
  String(STRIP ${ROOT_LIBRARY_DIR} ROOT_LIBRARY_DIR)

  # ask root-config for the binary dir
  Execute_Process(COMMAND ${ROOT_CONFIG_EXECUTABLE} --bindir
                  OUTPUT_VARIABLE ROOT_BINARY_DIR
                 )
  String(STRIP ${ROOT_BINARY_DIR} ROOT_BINARY_DIR)

  # ask root-config for the include dir
  Execute_Process(COMMAND ${ROOT_CONFIG_EXECUTABLE} --incdir
                  OUTPUT_VARIABLE ROOT_INCLUDE_DIR
                 )
  String(STRIP ${ROOT_INCLUDE_DIR} ROOT_INCLUDE_DIR)

  # ask root-config for the library varaibles
  Execute_Process(COMMAND ${ROOT_CONFIG_EXECUTABLE} --glibs
                  OUTPUT_VARIABLE ROOT_LIBRARIES
                 )
  String(STRIP ${ROOT_LIBRARIES} ROOT_LIBRARIES)

  # Make variables changeble to the advanced user
  Mark_As_Advanced(ROOT_LIBRARY_DIR ROOT_INCLUDE_DIR ROOT_DEFINITIONS)

  # Set ROOT_INCLUDES
  Set(ROOT_INCLUDES ${ROOT_INCLUDE_DIR})

  Set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${ROOT_LIBRARY_DIR})

  #######################################
  #
  #       Check the executables of ROOT 
  #          ( rootcint ) 
  #
  #######################################

  Find_Program(ROOT_CINT_EXECUTABLE
    NAMES rootcint
    PATHS ${ROOT_BINARY_DIR}
    NO_DEFAULT_PATH
    )

  Find_Program(RLIBMAP_EXECUTABLE
    NAMES rlibmap
    PATHS ${ROOT_BINARY_DIR}
    NO_DEFAULT_PATH
    )

    Include(ROOTMacros)

Else(ROOT_FOUND)

  If(ROOT_FIND_REQUIRED)
    Message(STATUS "Looking for ROOT... - Found version to old.")
    Message(STATUS "Looking for ROOT... - Minimum required version is ${ROOT_FIND_VERSION}")
    Message(FATAL_ERROR "Stop here because of a wrong Root version.")
  EndIf(ROOT_FIND_REQUIRED)

Endif(ROOT_FOUND)
