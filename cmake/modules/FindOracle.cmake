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
 
  set(SYS_INCLUDE "'sys_include=(${ORACLE_HOME}/precomp/public,/usr/include/,/usr/local/gcc3.2.3/lib/gcc-lib/i686-pc-linux-gnu/3.2.3/include,/usr/local/gcc3.2.3/lib/gcc-lib/i686-pc-linux-gnu,/usr/include/g++-3,/usr/include/c++/3.2/backward,/usr/include/c++/3.2)'")

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

  SET(PROCFLAGS oraca=yes code=cpp parse=partial sqlcheck=semantics ireclen=130 oreclen=130 ${INCLUDE_DIRS})
# ${SYS_INCLUDE} ${INCLUDE_DIRS})
 

#  MESSAGE("PROCFLAGS: ${PROCFLAGS}")
#  MESSAGE("INCLUDE_DIRS: ${INCLUDE_DIRS}")


  foreach (_current_FILE ${INFILES})
    GET_FILENAME_COMPONENT(OUTFILE_NAME ${_current_FILE} NAME_WE)
    set(OUTFILE "${OUTFILE_NAME}.cxx")
    ADD_CUSTOM_COMMAND(OUTPUT ${OUTFILE} 
     COMMAND $ENV{ORACLE_HOME}/bin/proc ARGS iname=${CMAKE_CURRENT_SOURCE_DIR}/${_current_FILE} oname=${CMAKE_CURRENT_BINARY_DIR}/${OUTFILE} ${PROCFLAGS} DEPENDS ${_current_FILE})
  endforeach (_current_FILE ${INFILES})

ENDMACRO (PREPROCESS_ORACLE_FILES)
