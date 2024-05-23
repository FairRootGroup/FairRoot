################################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

fairroot_add_catch2_test_suite(ExPropagator
  SOURCES
  test_FairTutPropGeo.cxx

  DEPENDENCIES
  FairRoot::ExPropagator
  FairRoot::GeoBase_checks
)
