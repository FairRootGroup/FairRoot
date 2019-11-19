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

add_test(runPropagatorMC
         ${CMAKE_CURRENT_BINARY_DIR}/runMC.sh)
set_tests_properties(runPropagatorMC PROPERTIES TIMEOUT ${maxTestTime})
set_tests_properties(runPropagatorMC PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

add_test(runPropagator
         ${CMAKE_CURRENT_BINARY_DIR}/runProp.sh)
set_tests_properties(runPropagator PROPERTIES DEPENDS runPropagatorMC)
set_tests_properties(runPropagator PROPERTIES TIMEOUT ${maxTestTime})
set_tests_properties(runPropagator PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

add_test(runPropagatorPull
         ${CMAKE_CURRENT_BINARY_DIR}/runPull.sh)
set_tests_properties(runPropagatorPull PROPERTIES DEPENDS runPropagator)
set_tests_properties(runPropagatorPull PROPERTIES TIMEOUT ${maxTestTime})
set_tests_properties(runPropagatorPull PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

