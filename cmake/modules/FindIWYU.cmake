################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(NOT IWYU_ROOT)
    set(IWYU_ROOT $ENV{IWYU_ROOT})
endif()

find_file(IWYU_BINARY
  NAMES include-what-you-use
  HINTS ${IWYU_ROOT} $ENV{IWYU_ROOT}
  PATH_SUFFIXES bin
  PATHS ENV PATH
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IWYU
  REQUIRED_VARS IWYU_BINARY
)

if(IWYU_FOUND)
  add_custom_target(checkHEADERS DEPENDS $ENV{ALL_HEADER_RULES})
endif(IWYU_FOUND)

Macro(CHECK_HEADERS INFILES INCLUDE_DIRS_IN HEADER_RULE_NAME)

#  Message("Create Header Checker for ${HEADER_RULE_NAME}")

  Set(_INCLUDE_DIRS)
  Set(_all_files)

  ForEach(_current_FILE ${INCLUDE_DIRS_IN})
    Set(_INCLUDE_DIRS ${_INCLUDE_DIRS} -I${_current_FILE})   
  EndForEach(_current_FILE ${INCLUDE_DIRS_IN})

  ForEach (_current_FILE ${INFILES})

    Get_Filename_Component(file_name ${_current_FILE} NAME_WE)
    Get_Filename_Component(path ${_current_FILE} PATH)
    
    Set(_current_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${_current_FILE}")
    Set(headerfile "${CMAKE_CURRENT_SOURCE_DIR}/${path}/${file_name}.h")
   
    If(NOT EXISTS ${headerfile})
      Set(headerfile)
    EndIf(NOT EXISTS ${headerfile})
  
    Set(outfile "${CMAKE_CURRENT_BINARY_DIR}/${file_name}.iwyu")

    ADD_CUSTOM_COMMAND(OUTPUT ${outfile} 
      COMMAND ${IWYU_BINARY} ${_current_FILE} ${_INCLUDE_DIRS} 2> ${outfile}
 #     COMMAND /bin/bash ${CMAKE_CURRENT_SOURCE_DIR}/cmake/scripts/iwyu.sh ${outfile} ${_current_FILE} ${headerfile} 
      DEPENDS  ${_current_FILE} ${headerfile}
   )

    set(_all_files ${_all_files}  ${outfile})

  endforeach (_current_FILE ${INFILES})

  Add_CUSTOM_TARGET(${HEADER_RULE_NAME} 
     COMMAND touch ${CMAKE_BINARY_DIR}/${RULE_NAME}
     DEPENDS ${_all_files}
  )

  SET(BLA $ENV{ALL_HEADER_RULES})
  SET(BLA ${BLA} ${HEADER_RULE_NAME})
  SET(ENV{ALL_HEADER_RULES} "${BLA}")

EndMacro(CHECK_HEADERS INFILES INCLUDE_DIRS_IN HEADER_RULE_NAME)
