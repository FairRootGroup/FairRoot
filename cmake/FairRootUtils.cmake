################################################################################
# Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

################################################################################
# Exchange file extention of file in list from ext1 to ext2,
# only if the resulting file exists in CMAKE_CURRENT_SOURCE_DIR,
# and assign the newly created list to 'output'.
# The input list is not changed at all
# Ex: fair_change_file_extension_ifexists(*.cxx *.h "${TRD_SRCS}" TRD_HEADERS)
################################################################################
function(fairroot_change_extensions_if_exists ext1 ext2)
  cmake_parse_arguments(ARGS "" "OUTVAR" "FILES" ${ARGN})

  set(required_args "FILES;OUTVAR")
  foreach(required_arg IN LISTS required_args)
    if(NOT ARGS_${required_arg})
      message(FATAL_ERROR "fair_change_extensions_if_exists is missing a required argument: ${required_arg}")
    endif()
  endforeach()

  if(${ext1} MATCHES "^[*][.]+.*$")
    string(REGEX REPLACE "^[*]+([.].*)$" "\\1" ext1new ${ext1})
  else()
    set(ext1new ${ext1})
  endif()
  if(${ext2} MATCHES "^[*][.]+.*$")
    string(REGEX REPLACE "^[*]+([.].*)$" "\\1" ext2new ${ext2})
  else()
    set(ext2new ${ext2})
  endif()
  foreach(file ${ARGS_FILES})
    set(newFile "")
    string(REGEX REPLACE "^(.*)${ext1new}$" "\\1${ext2new}" newFile ${file})
    if(NOT ${file} STREQUAL ${newFile} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${newFile})
      list(APPEND result ${newFile})
    endif()
  endforeach()
  set(${ARGS_OUTVAR} ${result} PARENT_SCOPE)
endfunction()

