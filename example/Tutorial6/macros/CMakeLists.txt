 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial6/macros/run_sim.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial6/macros/run_digi.C)

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_sim_Tut6_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/example/Tutorial6/macros/run_sim.sh 100 \"${_mcEngine}\")
  Set_Tests_Properties(run_sim_Tut6_${_mcEngine} PROPERTIES TIMEOUT "180")
  Set_Tests_Properties(run_sim_Tut6_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

  Add_Test(run_digi_Tut6_${_mcEngine} ${CMAKE_BINARY_DIR}/example/Tutorial6/macros/run_digi.sh \"${_mcEngine}\")
  Set_Tests_Properties(run_digi_Tut6_${_mcEngine} PROPERTIES DEPENDS run_sim_Tut6_${_mcEngine})
  Set_Tests_Properties(run_digi_Tut6_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_digi_Tut6_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")

  EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 


Install(FILES run_sim.C run_digi.C 
        DESTINATION share/fairbase/example/Tutorial6
       )

