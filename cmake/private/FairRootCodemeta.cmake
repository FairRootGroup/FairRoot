################################################################################
#    Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

function(get_codemeta_version)
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
    file(READ "${CMAKE_SOURCE_DIR}/codemeta.json" codemeta_content)
    string(JSON codemeta_version ERROR_VARIABLE json_error
           GET "${codemeta_content}" "softwareVersion")
    if(NOT "${json_error}" STREQUAL "NOTFOUND")
      string(JSON codemeta_version ERROR_VARIABLE json_error
             GET "${codemeta_content}" "version")
    endif()
    if(NOT "${json_error}" STREQUAL "NOTFOUND")
      return()
    endif()
    string(REGEX REPLACE "^v" "" codemeta_version "${codemeta_version}")
    set(PROJECT_CODEMETA_VERSION "${codemeta_version}" PARENT_SCOPE)
  endif()
endfunction()
