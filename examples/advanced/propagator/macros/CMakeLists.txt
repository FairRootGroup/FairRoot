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

Set(MaxTestTime 60)

Add_Test(runPropagatorMC
         ${CMAKE_CURRENT_BINARY_DIR}/runMC.sh)
Set_Tests_Properties(runPropagatorMC PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(runPropagatorMC PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

Add_Test(runPropagator
         ${CMAKE_CURRENT_BINARY_DIR}/runProp.sh)
Set_Tests_Properties(runPropagator PROPERTIES DEPENDS runPropagatorMC)
Set_Tests_Properties(runPropagator PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(runPropagator PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

Add_Test(runPropagatorPull
         ${CMAKE_CURRENT_BINARY_DIR}/runPull.sh)
Set_Tests_Properties(runPropagatorPull PROPERTIES DEPENDS runPropagator)
Set_Tests_Properties(runPropagatorPull PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(runPropagatorPull PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

