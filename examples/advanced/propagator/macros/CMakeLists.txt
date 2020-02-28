################################################################################
# Copyright (C) 2019-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(run "source ${CMAKE_BINARY_DIR}/config.sh && root -b -q -l ${CMAKE_CURRENT_SOURCE_DIR}/run")
set(prop "runPropagator")

add_test(NAME ${prop}MC COMMAND bash -c "${run}MC.C")

add_test(NAME ${prop} COMMAND bash -c "${run}Prop.C")
set_tests_properties(${prop} PROPERTIES DEPENDS ${prop}MC)

add_test(NAME ${prop}Pull COMMAND bash -c "${run}Pull.C")
set_tests_properties(${prop}Pull PROPERTIES DEPENDS ${prop})

set_tests_properties(${prop}MC ${prop} ${prop}Pull PROPERTIES
  TIMEOUT 60
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)
