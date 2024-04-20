################################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

fairroot_add_catch2_test_suite(ExSimulation4
  SOURCES
  test_FairTutorialDet4Geo.cxx

  DEPENDENCIES
  FairRoot::ExSimulation4
  FairRoot::GeoBase_checks
)
