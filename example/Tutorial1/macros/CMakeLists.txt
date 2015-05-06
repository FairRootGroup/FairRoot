 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial1/macros/run_tutorial1.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial1/macros/run_tutorial1_mesh.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial1/macros/run_tutorial1_urqmd.C)

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_tutorial1_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/example/Tutorial1/macros/run_tutorial1.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial1_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_tutorial1_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

  Add_Test(run_tutorial1_mesh_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/example/Tutorial1/macros/run_tutorial1_mesh.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial1_mesh_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_tutorial1_mesh_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

  Add_Test(run_tutorial1_urqmd_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/example/Tutorial1/macros/run_tutorial1_urqmd.sh 2 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial1_urqmd_${_mcEngine} PROPERTIES TIMEOUT "30")
  Set_Tests_Properties(run_tutorial1_urqmd_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")
EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 

Install(FILES run_tutorial1.C run_tutorial1_urqmd.C run_tutorial1_mesh.C
        DESTINATION share/fairbase/example/Tutorial1
       )


