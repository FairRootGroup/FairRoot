################################################################################
# Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

install(DIRECTORY
  modules
  scripts
  DESTINATION ${PROJECT_INSTALL_DATADIR}/cmake
)
set(PROJECT_CMAKE_MODULES_DIR ${PROJECT_INSTALL_DATADIR}/cmake/modules PARENT_SCOPE)
