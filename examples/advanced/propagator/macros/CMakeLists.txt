 ################################################################################
 #    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/runMC.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/runProp.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/runPull.C)

set(maxTestTime 60)

add_test(NAME runPropagatorMC
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runMC.sh)
set_tests_properties(runPropagatorMC PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_adv_propagator_sim
)

add_test(NAME runPropagator
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runProp.sh)
set_tests_properties(runPropagator PROPERTIES
  FIXTURES_REQUIRED fixtures.ex_adv_propagator_sim
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_adv_propagator_prop
)

add_test(NAME runPropagatorPull
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runPull.sh)
set_tests_properties(runPropagatorPull PROPERTIES
  FIXTURES_REQUIRED fixtures.ex_adv_propagator_prop
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)

