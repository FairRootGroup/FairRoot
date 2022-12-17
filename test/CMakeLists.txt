################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(dependencies
  FairRoot::Tools
  GTest::GTest
  GTest::Main
)

add_executable(FairLoggerFatal FairLoggerFatal.cxx)
target_link_libraries(FairLoggerFatal ${dependencies})
add_test(NAME FairLoggerFatal COMMAND ${CMAKE_CURRENT_BINARY_DIR}/FairLoggerFatal)
