################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

################################################################################
#Sets CMake policies.
MACRO(set_fairroot_cmake_policies)
#Find more details to each policy with cmake-- help - policy CMPXXXX
    foreach(policy
      CMP0025 # Compiler id for Apple Clang is now AppleClang.
      CMP0028 # Double colon in target name means ALIAS or IMPORTED target.
      CMP0042 # MACOSX_RPATH is enabled by default.
      CMP0048 # The ``project()`` command manages VERSION variables.
      CMP0054 # Only interpret ``if()`` arguments as variables or keywords when unquoted.
      CMP0074 # searches prefixes specified by the <PackageName>_ROOT
    )
      if(POLICY ${policy})
        cmake_policy(SET ${policy} NEW)
      endif()
    endforeach()
ENDMACRO()

