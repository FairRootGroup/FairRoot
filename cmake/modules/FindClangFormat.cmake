################################################################################
# Copyright (C) 2020-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Defines the following variables:
#
#   ClangFormat_FOUND - Found clang-format and git-clang-format
#   CLANG_FORMAT_BIN - clang-format executable 
#   GIT_CLANG_FORMAT_BIN - git-clang-format executable 

find_program(CLANG_FORMAT_BIN
  NAMES clang-format
        clang-format-11
        clang-format-9
        clang-format-8
        clang-format-7
        clang-format-6.0
        clang-format-5.0
        clang-format-4.0
        clang-format-3.9
        clang-format-3.8
        clang-format-3.7
        clang-format-3.6
        clang-format-3.5
        clang-format-3.4
)

find_program(GIT_CLANG_FORMAT_BIN
  NAMES git-clang-format
        git-clang-format-11
        git-clang-format-9
        git-clang-format-8
        git-clang-format-7
        git-clang-format-6.0
        git-clang-format-5.0
        git-clang-format-4.0
        git-clang-format-3.9
        git-clang-format-3.8
        git-clang-format-3.7
        git-clang-format-3.6
        git-clang-format-3.5
        git-clang-format-3.4
)

if (CLANG_FORMAT_BIN)
  execute_process(COMMAND ${CLANG_FORMAT_BIN} --version
    OUTPUT_VARIABLE CLANG_FORMAT_VERSION_STRING)
  string(REGEX MATCH "clang-format version ([0-9.]+)" ClangFormat_VERSION
    "${CLANG_FORMAT_VERSION_STRING}")
  unset(CLANG_FORMAT_VERSION_STRING)
  set(ClangFormat_VERSION "${CMAKE_MATCH_1}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ClangFormat
  REQUIRED_VARS CLANG_FORMAT_BIN GIT_CLANG_FORMAT_BIN
  VERSION_VAR ClangFormat_VERSION
)
