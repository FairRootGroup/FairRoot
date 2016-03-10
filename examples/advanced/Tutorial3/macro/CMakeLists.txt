 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################


Set(MaxTestTime 60)

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/macro/run_sim.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/macro/run_digi.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/macro/run_reco.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/macro/run_digi_timebased.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/macro/run_reco_timebased.C)

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_sim_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/examples/advanced/Tutorial3/macro/run_sim.sh 100 \"${_mcEngine}\")
  Math(EXPR TestTime 3*${MaxTestTime})
  Set_Tests_Properties(run_sim_${_mcEngine} PROPERTIES TIMEOUT ${TestTime})
  Set_Tests_Properties(run_sim_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  Add_Test(run_digi_${_mcEngine} ${CMAKE_BINARY_DIR}/examples/advanced/Tutorial3/macro/run_digi.sh \"${_mcEngine}\")
  Set_Tests_Properties(run_digi_${_mcEngine} PROPERTIES DEPENDS run_sim_${_mcEngine})
  Set_Tests_Properties(run_digi_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_digi_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")


  Add_Test(run_reco_${_mcEngine} ${CMAKE_BINARY_DIR}/examples/advanced/Tutorial3/macro/run_reco.sh \"${_mcEngine}\")
  Set_Tests_Properties(run_reco_${_mcEngine} PROPERTIES DEPENDS run_digi_${_mcEngine})
  Set_Tests_Properties(run_reco_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_reco_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")


  Add_Test(run_digi_timebased_${_mcEngine} ${CMAKE_BINARY_DIR}/examples/advanced/Tutorial3/macro/run_digi_timebased.sh \"${_mcEngine}\")
  Set_Tests_Properties(run_digi_timebased_${_mcEngine} PROPERTIES DEPENDS run_sim_${_mcEngine})
  Set_Tests_Properties(run_digi_timebased_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_digi_timebased_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")


  Add_Test(run_reco_timebased_${_mcEngine} ${CMAKE_BINARY_DIR}/examples/advanced/Tutorial3/macro/run_reco_timebased.sh \"${_mcEngine}\")
  Set_Tests_Properties(run_reco_timebased_${_mcEngine} PROPERTIES DEPENDS run_digi_timebased_${_mcEngine})
  Set_Tests_Properties(run_reco_timebased_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_reco_timebased_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")
EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 


Install(FILES run_sim.C run_digi.C run_reco.C eventDisplay.C
              run_digi_timebased.C run_reco_timebased.C
        DESTINATION share/fairbase/examples/advanced/Tutorial3
       )

Install(FILES data/dummy.txt
        DESTINATION share/fairbase/examples/advanced/Tutorial3/macro/data
       )
