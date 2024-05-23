###############################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Test suite for the `FairRoot::GeoBase` library

set(suite GeoBase)

set(checks_lib "${suite}_checks")
add_library(${checks_lib} INTERFACE)
target_link_libraries(${checks_lib} INTERFACE FairRoot::GeoBase Catch2::Catch2 fmt::fmt Boost::filesystem)
target_include_directories(${checks_lib} INTERFACE ${CMAKE_SOURCE_DIR})
fairroot_library_settings(${checks_lib})

fairroot_add_catch2_test_suite(${suite}
  SOURCES
  tests_FairGeoShapes.cxx

# Compilation works but when running the test doesn't finish
# Disable for the time being 
#  FairTestGeo.cxx
#  tests_FairGeoSet.cxx

  DEPENDENCIES
  FairRoot::GeoBase
  FairRoot::GeoBase_checks
)

configure_File(${CMAKE_CURRENT_SOURCE_DIR}/data/testmedia.geo ${CMAKE_CURRENT_BINARY_DIR}/data/testmedia.geo @ONLY)
configure_File(${CMAKE_CURRENT_SOURCE_DIR}/data/testdet_brick.geo ${CMAKE_CURRENT_BINARY_DIR}/data/testdet_brick.geo @ONLY)
