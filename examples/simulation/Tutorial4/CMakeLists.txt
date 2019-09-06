################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_subdirectory(src)
add_subdirectory(macros)

install(DIRECTORY gconfig parameters macros/analysis
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial4
)
