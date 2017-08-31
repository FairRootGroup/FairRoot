################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(NOT VGM_ROOT)
  set(VGM_ROOT $ENV{VGM_ROOT})
endif()

find_package(VGM QUIET CONFIG
  HINTS ${VGM_ROOT} ${SIMPATH}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(VGM CONFIG_MODE)
