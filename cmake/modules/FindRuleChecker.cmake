 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Find IRST Code Analysis Tool (RuleChecker)
# This module finds if the RuleChecker is installed
#   
# This code sets the following variables:
#
# RULE_CHECKER_FOUND = Boolean defining if Rule Checker is available
# RULE_CHECKER_PATH  = Path to the java class containing the FAIR Rule Checker
# RULE_CHECKER       = Java class to executed
# RULE_CHECKER_PERL  = Perl script to be executed to patch preprocessor files



# Check if Java and Perl are available. Both are nedded for the Rule
# checker.

MESSAGE(STATUS "Looking for Java...")
find_package(Java)
IF(JAVA_RUNTIME)
  MESSAGE(STATUS "Looking for Java... - found ${JAVA_RUNTIME} ")
ELSE(JAVA_RUNTIME)
  MESSAGE(STATUS "Looking for Java... - not found")
ENDIF(JAVA_RUNTIME)

MESSAGE(STATUS "Looking for Perl...")
find_package(Perl)
IF(PERL_FOUND)
  MESSAGE(STATUS "Looking for Perl... - found ${PERL_EXECUTABLE} ")
ELSE(PERL_FOUND)
  MESSAGE(STATUS "Looking for Perl... - not found")
ENDIF(PERL_FOUND)

if (JAVA_RUNTIME AND PERL_FOUND)

  MESSAGE(STATUS "Looking for Rule Checker...")
  
  SET(PATH1)
  IF($ENV{CLASSPATH})
    STRING(REGEX MATCHALL "[^:]+" PATH1 $ENV{CLASSPATH})
  ENDIF($ENV{CLASSPATH})
  SET(CHECK_DIRECTORIES ${SIMPATH}/tools/RuleChecker "${PATH1}")
  
  IF(CBMROOT_SOURCE_DIR)
    SET(RULE_CHECKER_LIBRARY_DIRECTORIES)
    FOREACH(dir ${CHECK_DIRECTORIES})
      SET(RULE_CHECKER_LIBRARY_DIRECTORIES
        ${RULE_CHECKER_LIBRARY_DIRECTORIES}
        ${dir}/rules/CBM
        )
    ENDFOREACH(dir)
    FIND_PATH(RULE_CHECKER_PATH CBMRuleChecker.class PATHS
       ${RULE_CHECKER_LIBRARY_DIRECTORIES}
    )
    SET(RULE_CHECKER rules.CBM.CBMRuleChecker)
  ELSE(CBMROOT_SOURCE_DIR)
    IF(PANDAROOT_SOURCE_DIR)
        SET(RULE_CHECKER_LIBRARY_DIRECTORIES)
      FOREACH(dir ${CHECK_DIRECTORIES})
        SET(RULE_CHECKER_LIBRARY_DIRECTORIES
          ${RULE_CHECKER_LIBRARY_DIRECTORIES}
          ${dir}/rules/PANDA
        )
      ENDFOREACH(dir)
      FIND_PATH(RULE_CHECKER_PATH PANDARuleChecker.class PATHS
         ${RULE_CHECKER_LIBRARY_DIRECTORIES}
      )
      SET(RULE_CHECKER rules.PANDA.PANDARuleChecker)
    ELSE(PANDAROOT_SOURCE_DIR)
      MESSAGE(STATUS "Looking for Rule Checker... - No Rules found")
    ENDIF(PANDAROOT_SOURCE_DIR)
  ENDIF(CBMROOT_SOURCE_DIR)
  
  SET(RULE_CHECKER_PERL_DIRECTORIES)
  FOREACH(dir ${CHECK_DIRECTORIES})
    SET(RULE_CHECKER_PERL_DIRECTORIES
      ${RULE_CHECKER_PERL_DIRECTORIES}
      ${dir}/patch
      )
  ENDFOREACH(dir)
    
  FIND_PATH(RULE_CHECKER_PERL_PATH patch4alice.prl PATHS
      ${RULE_CHECKER_PERL_DIRECTORIES}
  )

 
  IF (NOT RULE_CHECKER_PATH)
    MESSAGE(STATUS "Looking for Rule Checker... - Not found ")
    SET(RULE_CHECKER_FOUND "NO")
  ELSE (NOT RULE_CHECKER_PATH)
    MESSAGE(STATUS "Looking for Rule Checker... - found ${RULE_CHECKER_PATH}") 
    SET(RULE_CHECKER_FOUND "YES")
    SET(RULE_CHECKER_PERL ${RULE_CHECKER_PERL_PATH}/patch4alice.prl)
    FIND_PATH(RULE_CHECKER_PATH1 rules  PATHS
        ${CHECK_DIRECTORIES}
    )
    SET(RULE_CHECKER_SCRIPT_PATH ${RULE_CHECKER_PATH1}/scripts)
    IF(CBMROOT_SOURCE_DIR)
      SET(RULE_CHECKER_SCRIPT ${RULE_CHECKER_SCRIPT_PATH}/createCbmViolationTable.sh)
      SET(RULE_CHECKER_SCRIPT1 ${RULE_CHECKER_SCRIPT_PATH}/createCbmViolationTable_html.sh)
    ELSE(CBMROOT_SOURCE_DIR)
      IF(PANDAROOT_SOURCE_DIR)
        SET(RULE_CHECKER_SCRIPT ${RULE_CHECKER_SCRIPT_PATH}/createPandaViolationTable.sh)
        SET(RULE_CHECKER_SCRIPT1 ${RULE_CHECKER_SCRIPT_PATH}/createPandaViolationTable_html.sh)
      ELSE(PANDAROOT_SOURCE_DIR)
      ENDIF(PANDAROOT_SOURCE_DIR)
    ENDIF(CBMROOT_SOURCE_DIR)

    SET(NEW_CLASSPATH "${PATH1}" ${RULE_CHECKER_PATH1})
    UNIQUE(BLA "${NEW_CLASSPATH}")
    SET(ENV{NEW_CLASSPATH} ${BLA})
    SET(ENV{CLASSPATH} ${BLA})
  ENDIF (NOT RULE_CHECKER_PATH)

  SET(ENV{ALL_RULES} "")
endif (JAVA_RUNTIME AND PERL_FOUND)


###########################################################################

MACRO(CHECK_RULES INFILES INCLUDE_DIRS_IN RULE_NAME) # _special_inc_dir)

  SET(_special_inc_dir "${ARGV3}")
#  IF(${ARGC} EQUAL "4")
#    MESSAGE("Arguments: ${ARGC}")
#    MESSAGE("SPECIAL: ${_special_inc_dir}")
#  ENDIF(${ARGC} EQUAL "4")

  SET(BLA $ENV{ALL_RULES})
  SET(BLA ${BLA} ${RULE_NAME})
  SET(ENV{ALL_RULES} "${BLA}")

#  MESSAGE("Create Rule Checker for ${RULE_NAME}")

  set(_INCLUDE_DIRS)
  set(_all_files)

  foreach (_current_FILE ${INCLUDE_DIRS_IN})
    set(_INCLUDE_DIRS ${_INCLUDE_DIRS} -I${_current_FILE})   
  endforeach (_current_FILE ${INCLUDE_DIRS_IN})

#  MESSAGE("RULE_CHECKER: ${RULE_CHECKER}")  

  foreach (_current_FILE ${INFILES})

    STRING(REGEX REPLACE "^(.*)\\.(.*)$" "\\1.i" OUTFILE "${_current_FILE}")
    STRING(REGEX REPLACE "^(.*)\\.(.*)$" "\\1.ii" OUTFILE1 "${_current_FILE}")
    STRING(REGEX REPLACE "^(.*)\\.(.*)$" "\\1.h" HFILE "${_current_FILE}")
    STRING(REGEX REPLACE "^(.*)\\.(.*)$" "\\1.viol" VIOLFILE "${_current_FILE}")
    STRING(REGEX REPLACE "^(.*)\\/(.*)$" "\\1" RELPATH "${_current_FILE}")
 
    IF(NOT ${RELPATH} STREQUAL ${_current_FILE})
#      MESSAGE("RELPATH: ${RELPATH}")
      SET(HEADERDIR ${CMAKE_CURRENT_SOURCE_DIR}/${RELPATH})
      STRING(REGEX REPLACE "^(.*)\\/(.*)$" "\\2" HFILE2 "${HFILE}")
#      SET(HFILE ${HFILE2})
      STRING(REGEX REPLACE "^(.*)\\/(.*)$" "\\2" OUTFILE2 "${OUTFILE}")
      SET(OUTFILE ${OUTFILE2})
      STRING(REGEX REPLACE "^(.*)\\/(.*)$" "\\2" OUTFILE2 "${OUTFILE1}")
      SET(OUTFILE1 ${OUTFILE2})
      STRING(REGEX REPLACE "^(.*)\\/(.*)$" "\\2" VIOLFILE2 "${VIOLFILE}")
      SET(VIOLFILE ${VIOLFILE2})
      IF(${ARGC} EQUAL "4")
        SET(HEADERDIR ${CMAKE_CURRENT_SOURCE_DIR}/${RELPATH}/${_special_inc_dir})
        SET(HFILE ${CMAKE_CURRENT_SOURCE_DIR}/${RELPATH}/${_special_inc_dir}/${HFILE2})
#        MESSAGE(HEADERDIR: ${HEADERDIR})
      ENDIF(${ARGC} EQUAL "4")
    ELSE(NOT ${RELPATH} STREQUAL ${_current_FILE})
      SET(HEADERDIR ${CMAKE_CURRENT_SOURCE_DIR})
    ENDIF(NOT ${RELPATH} STREQUAL ${_current_FILE})

    SET(_current_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${_current_FILE}")

# The RuleChecker does not work with files generated by g++ 4.4 and g++4.3.
# So the file is changed and the g++-4.1 is hardcoded. 
    ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${OUTFILE} ${CMAKE_CURRENT_BINARY_DIR}/${OUTFILE1} ${CMAKE_CURRENT_BINARY_DIR}/${VIOLFILE} 
     COMMAND g++-4.1 -E ${_INCLUDE_DIRS}  -o  ${OUTFILE} ${_current_FILE}
     COMMAND ${RULE_CHECKER_PERL} ${OUTFILE}
     COMMAND ${JAVA_RUNTIME} ${RULE_CHECKER} ${OUTFILE} ${HEADERDIR} > ${VIOLFILE}
     DEPENDS  ${_current_FILE}  ${HFILE})
 
    set(_all_files ${_all_files}  ${CMAKE_CURRENT_BINARY_DIR}/${VIOLFILE})

  endforeach (_current_FILE ${INFILES})

  ADD_CUSTOM_TARGET(${RULE_NAME} 
     COMMAND touch ${CMAKE_BINARY_DIR}/${RULE_NAME}
     DEPENDS ${_all_files})

ENDMACRO(CHECK_RULES)
 

