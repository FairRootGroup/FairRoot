################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

find_path(PYTHIA8_INCLUDE_DIR
  NAMES Pythia.h
  HINTS ${PYTHIA_ROOT} $ENV{PYTHIA_ROOT} ${SIMPATH}
  PATH_SUFFIXES include/Pythia8 generators/include/pythia8 generators/pythia8/include  
)

find_path(PYTHIA8_LIB_DIR
  NAMES libpythia8.so libpythia8.dylib
  HINTS ${PYTHIA_ROOT} $ENV{PYTHIA_ROOT} ${SIMPATH}
  PATH_SUFFIXES lib generators/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Pythia8
  REQUIRED_VARS PYTHIA8_LIB_DIR PYTHIA8_INCLUDE_DIR
)
