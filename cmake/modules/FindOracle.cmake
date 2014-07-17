 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# TOra: Configure Oracle libraries
#
# ORACLE_FOUND - system has Oracle OCI
# ORACLE_INCLUDES - where to find oci.h
# ORACLE_LIBRARIES - the libraries to link against to use Oracle OCI
#
# copyright (c) 2007 Petr Vanek <petr@scribus.info>
# Redistribution and use is allowed according to the terms of the GPLv2 license.
#

SET(ORACLE_FOUND "NO")

MESSAGE(STATUS "Looking for Oracle preprocessor... ")


set(ORACLE_HOME $ENV{ORACLE_HOME})

FIND_PROGRAM(
    ORACLE_PREPROCESSOR
    proc
    PATHS ${ORACLE_HOME}/bin
    NO_DEFAULT_PATH
)

MESSAGE("CMAKE_SYSTEM_INCLUDE_PATH: ${CMAKE_SYSTEM_INCLUDE_PATH}")
MESSAGE("CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")


FIND_PATH(IOMANIP_INCLUDE_DIR iomanip
)

MESSAGE("IOMANIP: ${IOMANIP_INCLUDE_DIR}")

IF(ORACLE_PREPROCESSOR)
  SET(ORACLE_FOUND "YES")
ENDIF(ORACLE_PREPROCESSOR)


IF (ORACLE_FOUND)
    SET( ENV{ORA_USER} fairana/fair@db-hades-test)
    IF (NOT ORACLE_FIND_QUIETLY)
         MESSAGE(STATUS "Looking for Oracle preprocessor ... found ${ORACLE_PREPROCESSOR}")
         MESSAGE(STATUS "Using Oracle User: $ENV{ORA_USER} ")
    ENDIF (NOT ORACLE_FIND_QUIETLY)
ELSE (ORACLE_FOUND)
    MESSAGE(STATUS "Looking for Oracle preprocessor ... - Not found")
    MESSAGE(STATUS "Please define ORACLE_HOME environment variable")
    MESSAGE(STATUS "if you have an Oracle installation")
ENDIF (ORACLE_FOUND)

MACRO (PREPROCESS_ORACLE_FILES INFILES INCLUDE_DIRS_IN)
 
  set(SYS_INCLUDE "'sys_include=(/usr/include/,/usr/lib/gcc/i486-linux-gnu/4.1.2/include/,/usr/include/c++/4.1.2/backward/,/usr/include/c++/4.1.2,/usr/include/c++/4.1.2/i486-linux-gnu/)'")

#  set(INCLUDE_DIRS "
#      include=${ORACLE_HOME}/precomp/public
#      include=${ORACLE_HOME}/rdbms/public
#      include=${ORACLE_HOME}/rdbms/demo
#      include=${ORACLE_HOME}/plsql/public
#      include=${ORACLE_HOME}/network/public
#  ")

  set(INCLUDE_DIRS)

  foreach (_current_FILE ${INCLUDE_DIRS_IN})
    set(INCLUDE_DIRS ${INCLUDE_DIRS} include=${_current_FILE})   
  endforeach (_current_FILE ${INCLUDE_DIRS_IN})

  SET(PROCFLAGS oraca=yes code=cpp parse=partial sqlcheck=semantics ireclen=130 oreclen=130 ${SYS_INCLUDE} ${INCLUDE_DIRS})
 

#  MESSAGE("PROCFLAGS: ${PROCFLAGS}")
#  MESSAGE("INCLUDE_DIRS: ${INCLUDE_DIRS}")


  foreach (_current_FILE ${INFILES})
    GET_FILENAME_COMPONENT(OUTFILE_NAME ${_current_FILE} NAME_WE)
    set(OUTFILE "${OUTFILE_NAME}.cxx")
    ADD_CUSTOM_COMMAND(OUTPUT ${OUTFILE} 
     COMMAND $ENV{ORACLE_HOME}/bin/proc ARGS iname=${CMAKE_CURRENT_SOURCE_DIR}/${_current_FILE} oname=${CMAKE_CURRENT_BINARY_DIR}/${OUTFILE} ${PROCFLAGS} DEPENDS ${_current_FILE})
  endforeach (_current_FILE ${INFILES})

ENDMACRO (PREPROCESS_ORACLE_FILES)
