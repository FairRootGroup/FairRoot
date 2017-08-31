################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(NOT PYTHIA8DATA)
  set(PYTHIA8DATA $ENV{PYTHIA8DATA})
endif()

find_path(PYTHIA8DATA
  NAMES MainProgramSettings.xml

  HINTS
  ${PYTHIA8DATA}
  ${PYTHIA_ROOT}/share/Pythia8/xmldoc
  ${SIMPATH}/share/pythia8/xmldoc
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Pythia8Data
  REQUIRED_VARS PYTHIA8DATA
)
