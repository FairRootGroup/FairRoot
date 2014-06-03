 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial4/macros/run_tutorial4.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial4/macros/run_reco.C)


ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_tutorial4_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/example/Tutorial4/macros/run_tutorial4.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial4_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_tutorial4_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")


  Add_Test(run_reco_tut4_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/example/Tutorial4/macros/run_reco.sh \"${_mcEngine}\")
  Set_Tests_Properties(run_reco_tut4_${_mcEngine} PROPERTIES DEPENDS run_tutorial4_${_mcEngine})
  Set_Tests_Properties(run_reco_tut4_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_reco_tut4_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")
EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 

Install(FILES eventDisplay.C run_reco.C Create_Tutorial4_Geometry.C
              run_tutorial4.C plots.C
        DESTINATION share/fairbase/example/Tutorial4
       )


