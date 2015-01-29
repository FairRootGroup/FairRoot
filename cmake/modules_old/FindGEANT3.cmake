 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find GEANT3
# Once done this will define
#
#  GEANT3_FOUND - system has GEANT3
#  GEANT3_INCLUDE_DIR - the GEANT3 include directory
#  GEANT_LIBRARIES - The libraries needed to use GEANT3
#  GEANT_DEFINITIONS - Compiler switches required for using GEANT3
#  GEANT3_SYSTEM_DIR - Base directory of the GEANT3 installation, needed for GCALOR

INCLUDE(CheckCXXSourceCompiles)

MACRO (TEST_GEANT3_VERSION)

# Check if SetCUTS from TGeant3 has 11 or 16 parameters
# According to this test the g3Config file is choosen
# As a test cmake tries to compile a small program with
# a function only present in the new Geant3 version.
# If the compilation succed the library has the new version,
# if not the library has the old version.

SET(CMAKE_REQUIRED_INCLUDES ${GEANT3_INCLUDE_DIR} ${ROOT_INCLUDE_DIR}) 
SET(CMAKE_REQUIRED_LIBRARIES 
    ${GEANT3_LIB} 
    ${ROOT_LIBRARY_DIR}/libCore.so 
    Cint 
    Hist 
    RIO
    Net
    Graf 
    Graf3d 
    Gpad 
    Tree 
    Rint 
    Postscript 
    Matrix 
    Physics 
    Gui 
    EG 
    ${Pythia6_LIBRARY_DIR}/libPythia6.so 
    EGPythia6 
    VMC 
    Geom 
    dl   
)

check_cxx_source_compiles("
  #include \"TGeant3.h\"
  int main(){
    TGeant3* geant3= new TGeant3(\"\");
    float cut = 1.e-3;
    float usrcuts[5]={0.,0.,0.,0.,0};
    geant3->SetCUTS(cut, cut, cut, cut ,cut, cut, cut, cut, cut, cut, cut,usrcuts); 
    return 0;
  }
" TGEANT3_SETCUTS )

IF (TGEANT3_SETCUTS)
  MESSAGE(STATUS "New Version of GEANT3 with full GEANE support found.")
ELSE (TGEANT3_SETCUTS)
  MESSAGE(STATUS "Old Version of GEANT3 without GEANE support found.")
  ADD_DEFINITIONS(-DHAVE_OLD_GEANT3)
ENDIF (TGEANT3_SETCUTS)

ENDMACRO (TEST_GEANT3_VERSION)


if (GEANT3_INCLUDE_DIR AND GEANT3_LIBRARIES)
  SET (GEANT3_INCLUDE_DIR GEANT3_INCLUDE_DIR-NOTFOUND)
  SET (GEANT3_LIB GEANT3_LIB-NOTFOUND)
  SET (GEANT3_DUMMY_LIB GEANT3_DUMMY_LIB-NOTFOUND)
  SET (GEANT3_SYSTEM_DIR GEANT3_SYSTEM_DIR-NOTFOUND)
endif (GEANT3_INCLUDE_DIR AND GEANT3_LIBRARIES)

MESSAGE(STATUS "Looking for GEANT3...")

FIND_PATH(GEANT3_SYSTEM_DIR NAMES data PATHS
  ${SIMPATH}/share/geant3
  ${SIMPATH}/transport/geant3
  NO_DEFAULT_PATH
)

FIND_PATH(GEANT3_INCLUDE_DIR NAMES TGeant3.h PATHS
  ${SIMPATH}/include/TGeant3
  ${SIMPATH}/transport/geant3/TGeant3
  NO_DEFAULT_PATH
)

FIND_PATH(GEANT3_LIBRARY_DIR NAMES libgeant321.so PATHS
  ${SIMPATH}/lib
  ${SIMPATH}/transport/geant3/lib/tgt_linux
  ${SIMPATH}/transport/geant3/lib/tgt_linuxicc
  ${SIMPATH}/transport/geant3/lib/tgt_linuxx8664gcc
  ${SIMPATH}/transport/geant3/lib
  NO_DEFAULT_PATH
)

FIND_LIBRARY(GEANT3_LIB NAMES geant321 PATHS
  ${SIMPATH}/lib
  ${SIMPATH}/transport/geant3/lib/tgt_linux
  ${SIMPATH}/transport/geant3/lib/tgt_linuxicc
  ${SIMPATH}/transport/geant3/lib/tgt_linuxx8664gcc
  ${SIMPATH}/transport/geant3/lib
  NO_DEFAULT_PATH
)

SET(GEANT3_LIBRARIES ${GEANT3_LIB})

if (GEANT3_INCLUDE_DIR AND GEANT3_LIBRARIES)
   set(GEANT3_FOUND TRUE)
endif (GEANT3_INCLUDE_DIR AND GEANT3_LIBRARIES)

if (GEANT3_FOUND)
  if (NOT GEANT3_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for GEANT3... - found ${GEANT3_LIBRARIES}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${GEANT3_LIBRARY_DIR})
  endif (NOT GEANT3_FIND_QUIETLY)

#  TEST_GEANT3_VERSION()

else (GEANT3_FOUND)
  if (GEANT3_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for GEANT3... - Not found ")
  endif (GEANT3_FIND_REQUIRED)
endif (GEANT3_FOUND)

