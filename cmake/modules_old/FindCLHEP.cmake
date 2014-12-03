 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find CLHEP
# Once done this will define
#
#  CLHEP_FOUND - system has CLHEP
#  CLHEP_INCLUDE_DIR - the CLHEP include directory
#  CLHEP_LIBRARIES - The libraries needed to use CLHEP
#  CLHEP_DEFINITIONS - Compiler switches required for using CLHEP
#

if (CLHEP_INCLUDE_DIR AND CLHEP_LIBRARY_DIR)
  SET (CLHEP_INCLUDE_DIR CLHEP_INCLUDE_DIR-NOTFOUND)
  SET (CLHEP_LIB_DIR CLHEP_LIB_DIR-NOTFOUND)
  SET (CLHEP_PLISTS_LIB_DIR CLHEP_PLISTS_LIB_DIR-NOTFOUND)
endif (CLHEP_INCLUDE_DIR AND CLHEP_LIBRARY_DIR)

MESSAGE(STATUS "Looking for CLHEP...")

# If we find the new clhep-config executable use it, otherwise search in the path
Find_Program(CLHEP_CONFIG_EXE NAMES clhep-config PATHS
  ${SIMPATH}/cern/clhep/bin
  ${SIMPATH}/cern/clhep/
  ${SIMPATH}/bin
  NO_DEFAULT_PATH
)

If(CLHEP_CONFIG_EXE)

  # Use clhep-config to find libs and includes
  execute_process(COMMAND ${CLHEP_CONFIG_EXE} --libs OUTPUT_VARIABLE CLHEP_CONFIG_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND ${CLHEP_CONFIG_EXE} --include OUTPUT_VARIABLE CLHEP_CONFIG_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND ${CLHEP_CONFIG_EXE} --prefix OUTPUT_VARIABLE CLHEP_BASE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)

  # clean the variables because they are of the form -I/<dir> or -L/<dir> -l<lib>
  String (REGEX MATCHALL "((-L|-l|-Wl)([^\" ]+|\"[^\"]+\")|/[^\" ]+(a|so|dll))" _all_tokens "${CLHEP_CONFIG_LIBS}")
  Set(_directory_list)
  ForEach (token ${_all_tokens})
    If (token MATCHES "-L([^\" ]+|\"[^\"]+\")")
       # If it's a library path, add it to the list
       string (REGEX REPLACE "^-L" "" token ${token})
       string (REGEX REPLACE "//" "/" token ${token})
       list (APPEND _directory_list ${token})
    EndIf (token MATCHES "-L([^\" ]+|\"[^\"]+\")")
  EndForEach (token ${_all_tokens})
  Set(CLHEP_LIBRARY_DIR ${_directory_list})

  String (REGEX MATCHALL "-I([^\" ]+|\"[^\"]+\")" _all_tokens "${CLHEP_CONFIG_INCLUDE_DIR}")
  Set (_incs_found)
  ForEach (token ${_all_tokens})
    String (REGEX REPLACE "^-I" "" token ${token})
    String (REGEX REPLACE "//" "/" token ${token})
    If (EXISTS ${token})
      List (APPEND _incs_found ${token})
    EndIf (EXISTS ${token})
  EndForEach (token)
  List (LENGTH _incs_found _length)
  If (_length GREATER 1)
    List (REMOVE_DUPLICATES _incs_found)
  EndIf (_length GREATER 1)
  Set (CLHEP_INCLUDE_DIR ${_incs_found})
  set(CLHEP_LIBRARIES "-L${CLHEP_LIBRARY_DIR} -lCLHEP")  

Else(CLHEP_CONFIG_EXE)

  # check if clhep is available in Geant4
  If (GEANT4_FOUND)

    find_path(CLHEP_LIBRARY_DIR NAMES libG4clhep.so PATHS
      ${GEANT4_LIBRARY_DIR}
    )
    set(CLHEP_LIBRARIES "-L${CLHEP_LIBRARY_DIR} -lG4clhep")  

    FIND_PATH(CLHEP_INCLUDE_DIR NAMES CLHEP PATHS
      ${GEANT4_INCLUDE_DIR}
      ${SIMPATH}/cern/clhep/include
      ${SIMPATH}/include
      NO_DEFAULT_PATH
    )

  Else (GEANT4_FOUND)
  
    FIND_PATH(CLHEP_INCLUDE_DIR NAMES CLHEP PATHS
      ${SIMPATH}/cern/clhep/include
      ${SIMPATH}/include
      NO_DEFAULT_PATH
    )

    FIND_PATH(CLHEP_BASE_DIR NAMES ClhepVersion.h PATHS
      ${SIMPATH}/cern/clhep
      ${SIMPATH}/include
      NO_DEFAULT_PATH
    )

    FIND_PATH(CLHEP_LIBRARY_DIR NAMES libCLHEP.so libCLHEP.dylib PATHS
      ${SIMPATH}/cern/clhep/lib
      ${SIMPATH}/lib
      NO_DEFAULT_PATH
    )
    set(CLHEP_LIBRARIES "-L${CLHEP_LIBRARY_DIR} -lCLHEP")  
  EndIf (GEANT4_FOUND)

EndIf(CLHEP_CONFIG_EXE)

If (CLHEP_INCLUDE_DIR AND CLHEP_LIBRARY_DIR)
   set(CLHEP_FOUND TRUE)
EndIf (CLHEP_INCLUDE_DIR AND CLHEP_LIBRARY_DIR)

If (CLHEP_FOUND)
  if (NOT CLHEP_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for CLHEP... - found ${CLHEP_LIBRARY_DIR}")
#    message(STATUS "Found CLHEP: ${CLHEP_LIBRARY_DIR}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${CLHEP_LIBRARY_DIR})
  endif (NOT CLHEP_FIND_QUIETLY)
Else (CLHEP_FOUND)
  if (CLHEP_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for CLHEP... - Not found")
  endif (CLHEP_FIND_REQUIRED)
EndIf (CLHEP_FOUND)

