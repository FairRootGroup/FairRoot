# Ora: Configure Oracle libraries
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


# If we have the preprocessor, extract information from cpp and ggc
# to build up the system include pathes needed by the oracle preprocessor
IF(ORACLE_PREPROCESSOR)
  SET(ORACLE_FOUND "YES")

  # extract version and target from gcc
  EXEC_PROGRAM( gcc ARGS "-dumpversion" OUTPUT_VARIABLE GCC_VERSION )
  EXEC_PROGRAM( gcc ARGS "-dumpmachine" OUTPUT_VARIABLE TARGET )

  # set default part of path
  SET(GCC_PATH "${ORACLE_HOME}/precomp/public,/usr/include") 

  # get other include directories from the preprocessor
  # the file is needed since i don't find any other good way
  # to extract the necessary info. contents is a list each entry
  # containing one line of the output
  EXEC_PROGRAM( cpp ARGS "-v </dev/null >${CMAKE_BINARY_DIR}/gcc_path.txt" OUTPUT_VARIABLE BLA )
  FILE(READ "${CMAKE_BINARY_DIR}/gcc_path.txt" contents)
  STRING(REGEX REPLACE "\n" ";" contents "${contents}")
  
  # only put relevat info to the path
  set(is_active "NO")
  set(is_end "NO")
  FOREACH(_actual_contents ${contents})
  
    # check if still in interseting part of output
    # search for the last line after the include section
    IF(is_active AND NOT is_end)
      STRING(COMPARE EQUAL "End of search list." ${_actual_contents} is_end)
    ENDIF(is_active AND NOT is_end)
  
    # if in interesting part remove blanks from directory string 
    # and add directory to the path 
    IF(is_active AND NOT is_end)
      STRING(REGEX REPLACE " " "" BLA2 ${_actual_contents})
      SET(GCC_PATH "${GCC_PATH},${BLA2}")
    ENDIF(is_active AND NOT is_end)
  
    # search for the start of the include section
    # set active flag to process next line
    IF(NOT is_active)
      STRING(COMPARE EQUAL "#include <...> search starts here:" ${_actual_contents} is_active)
    ENDIF(NOT is_active)

    # extract build target from the info
#    STRING(REGEX REPLACE "(^Target:)(.*)$" "\\1" BLA3 ${_actual_contents})
#    STRING(COMPARE EQUAL "Target:" ${BLA3} is_line)
#    IF(is_line)
#      STRING(REGEX REPLACE "^Target:[ ](.*)$" "\\1" TARGET ${_actual_contents})
#    ENDIF(is_line)
    
  ENDFOREACH(_actual_contents ${contents})
 
  # Look for the include directories
  # c++ headers are in version specific directories
  # Add this libraries to the path
  SET(GCC_PATH "${GCC_PATH},/usr/include/c++/${GCC_VERSION}/${TARGET},/usr/include/c++/${GCC_VERSION},/usr/include/c++/${GCC_VERSION}/backward")

ENDIF(ORACLE_PREPROCESSOR)


IF (ORACLE_FOUND)
    SET( ENV{ORA_USER} fairana/fair@db-hades-test)
    SET( ORACLE_LIBRARY_DIR ${ORACLE_HOME}/lib)
    EXEC_PROGRAM( cat ARGS "${ORACLE_HOME}/lib/sysliblist" OUTPUT_VARIABLE ORACLE_LIBRARIES )
    set(ORACLE_LIBRARIES "${ORACLE_LIBRARIES} -lclntsh")
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
 
  set(SYS_INCLUDE "'sys_include=(${GCC_PATH})'")
  IF(EXISTS /usr/include/c++/3.3/)
    set(SYS_INCLUDE "'sys_include=(/usr/local/oracle/product/10.2.0.1client/precomp/public,/usr/include,/usr/local/include,/usr/lib/gcc-lib/i486-linux/3.3.5/include,/usr/include,/usr/include/c++/3.3/i486-linux,/usr/include/c++/3.3,/usr/include/c++/3.3/backward)'") 
  ENDIF(EXISTS /usr/include/c++/3.3/)

  set(INCLUDE_DIRS)

  foreach (_current_FILE ${INCLUDE_DIRS_IN})
    set(INCLUDE_DIRS ${INCLUDE_DIRS} include=${_current_FILE})   
  endforeach (_current_FILE ${INCLUDE_DIRS_IN})

  SET(PROCFLAGS oraca=yes code=cpp parse=partial sqlcheck=semantics ireclen=130 oreclen=130 userid=$ENV{ORA_USER}  ${SYS_INCLUDE} ${INCLUDE_DIRS})
 
  foreach (_current_FILE ${INFILES})
    GET_FILENAME_COMPONENT(OUTFILE_NAME ${_current_FILE} NAME_WE)
    set(OUTFILE "${CMAKE_CURRENT_BINARY_DIR}/${OUTFILE_NAME}.cxx")
    ADD_CUSTOM_COMMAND(OUTPUT ${OUTFILE} 
     COMMAND $ENV{ORACLE_HOME}/bin/proc ARGS iname=${CMAKE_CURRENT_SOURCE_DIR}/${_current_FILE} oname=${OUTFILE} ${PROCFLAGS} > /dev/null DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${_current_FILE})
  endforeach (_current_FILE ${INFILES})

ENDMACRO (PREPROCESS_ORACLE_FILES)
