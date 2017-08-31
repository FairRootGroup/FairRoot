################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

find_path(Pythia6_LIBRARY_DIR
  NAMES libPythia6.so libPythia6.dylib
  HINTS ${PYTHIA6_ROOT} $ENV{PYTHIA6_ROOT} ${SIMPATH}
  PATH_SUFFIXES lib generators/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Pythia6
  REQUIRED_VARS Pythia6_LIBRARY_DIR
)
