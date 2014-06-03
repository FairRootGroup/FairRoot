 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_sim.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_digi.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_reco.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_digi_timebased.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_reco_timebased.C)

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_sim_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_sim.sh 100 \"${_mcEngine}\")
  Set_Tests_Properties(run_sim_${_mcEngine} PROPERTIES TIMEOUT "180")
  Set_Tests_Properties(run_sim_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

  Add_Test(run_digi_${_mcEngine} ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_digi.sh)
  Set_Tests_Properties(run_digi_${_mcEngine} PROPERTIES DEPENDS run_sim_${_mcEngine})
  Set_Tests_Properties(run_digi_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_digi_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")


  Add_Test(run_reco_${_mcEngine} ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_reco.sh)
  Set_Tests_Properties(run_reco_${_mcEngine} PROPERTIES DEPENDS run_digi_${_mcEngine})
  Set_Tests_Properties(run_reco_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_reco_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")


  Add_Test(run_digi_timebased_${_mcEngine} ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_digi_timebased.sh)
  Set_Tests_Properties(run_digi_timebased_${_mcEngine} PROPERTIES DEPENDS run_sim_${_mcEngine})
  Set_Tests_Properties(run_digi_timebased_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_digi_timebased_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")


  Add_Test(run_reco_timebased_${_mcEngine} ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_reco_timebased.sh)
  Set_Tests_Properties(run_reco_timebased_${_mcEngine} PROPERTIES DEPENDS run_digi_timebased_${_mcEngine})
  Set_Tests_Properties(run_reco_timebased_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_reco_timebased_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")
EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 


Install(FILES run_sim.C run_digi.C run_reco.C eventDisplay.C
              run_digi_timebased.C run_reco_timebased.C
        DESTINATION share/fairbase/example/Tutorial3
       )

