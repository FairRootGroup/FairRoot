################################################################################
# Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(Geant3_FOUND AND Geant4VMC_FOUND AND yaml-cpp_FOUND)
  add_subdirectory(mcconfigurator)
endif()

add_subdirectory(datamatch)
