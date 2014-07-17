 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/rutherford/macros/run_rutherford.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/rutherford/macros/run_rad.C)

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_rutherford_${_mcEngine}
            ${CMAKE_BINARY_DIR}/example/rutherford/macros/run_rutherford.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_rutherford_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_rutherford_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

  Add_Test(run_rad_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/example/rutherford/macros/run_rad.sh 100 \"${_mcEngine}\")
  Set_Tests_Properties(run_rad_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_rad_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")
EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 



Install(FILES run_rutherford.C run_rad.C eventDisplay.C
        DESTINATION share/fairbase/example/rutherford
       )
