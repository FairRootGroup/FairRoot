 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find PYTHIA8 instalation
# Once done this will define
#

MESSAGE(STATUS "Looking for PYTHIA8 ...")

FIND_PATH(PYTHIA8_INCLUDE_DIR NAMES Pythia.h PATHS
  ${PYTHIA8_DIR}/include/Pythia8
  ${AlFa_DIR}/include/Pythia8
  ${SIMPATH}/include/Pythia8
  ${SIMPATH}/include/pythia8  
  ${SIMPATH}/generators/include/pythia8  
  ${SIMPATH}/generators/pythia8/include  
  NO_DEFAULT_PATH
)

FIND_PATH(PYTHIA8_LIB_DIR  NAMES libpythia8.so PATHS
  ${PYTHIA8_DIR}/lib
  ${AlFa_DIR}/lib
  ${SIMPATH}/lib
  ${SIMPATH}/generators/lib
  NO_DEFAULT_PATH
)

Find_Path(PYTHIA8DATA NAMES MainProgramSettings.xml PATHS
  ${SIMPATH}/share/pythia8/xmldoc
)

If(NOT PYTHIA8DATA)
  Message(STATUS "Could not find Pythia8 data files")
EndIf()

if (PYTHIA8_INCLUDE_DIR AND PYTHIA8_LIB_DIR)
   set(PYTHIA8_FOUND TRUE)
endif (PYTHIA8_INCLUDE_DIR AND PYTHIA8_LIB_DIR)

if (PYTHIA8_FOUND)
  if (NOT PYTHIA8_FOUND_QUIETLY)
    MESSAGE(STATUS "Looking for PYTHIA8... - found ${PYTHIA8_LIB_DIR}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${PYTHIA8_LIB_DIR})
  endif (NOT PYTHIA8_FOUND_QUIETLY)
else (PYTHIA8_FOUND)
  if (PYTHIA8_FOUND_REQUIRED)
    message(FATAL_ERROR "Looking for PYTHIA8... - Not found")
  endif (PYTHIA8_FOUND_REQUIRED)
endif (PYTHIA8_FOUND)

