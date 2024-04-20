################################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

fairroot_add_catch2_test_suite(ExTestDetector
  SOURCES
  test_FairTestDetectorGeo.cxx

  DEPENDENCIES
  FairRoot::ExTestDetector
  FairRoot::GeoBase_checks
)
