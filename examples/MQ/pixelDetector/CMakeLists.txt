################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_subdirectory(param)
add_subdirectory(src)
if(ENABLE_GEANT3_TESTING)
  add_subdirectory(macros)
endif()
add_subdirectory(run)
