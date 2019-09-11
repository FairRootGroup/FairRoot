 ################################################################################
 #    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/geane/macros/runMC.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/geane/macros/runGeane.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/geane/macros/runPull.C)

Set(MaxTestTime 60)

Add_Test(runGeaneMC
         ${CMAKE_BINARY_DIR}/examples/advanced/geane/macros/runMC.sh)
Set_Tests_Properties(runGeaneMC PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(runGeaneMC PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

Add_Test(runGeane
         ${CMAKE_BINARY_DIR}/examples/advanced/geane/macros/runGeane.sh)
Set_Tests_Properties(runGeane PROPERTIES DEPENDS runGeaneMC)
Set_Tests_Properties(runGeane PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(runGeane PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

Add_Test(runGeanePull
         ${CMAKE_BINARY_DIR}/examples/advanced/geane/macros/runPull.sh)
Set_Tests_Properties(runGeanePull PROPERTIES DEPENDS runGeane)
Set_Tests_Properties(runGeanePull PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(runGeanePull PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

