 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1_pythia6.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1_pythia8.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1_mesh.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1_urqmd.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial1/macros/load_all_libs.C)

Set(MaxTestTime 60)

Add_Test(load_all_libs ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial1/macros/load_all_libs.sh)
Set_Tests_Properties(load_all_libs PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(load_all_libs PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_tutorial1_${_mcEngine}
           ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial1_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_tutorial1_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  Add_Test(run_tutorial1_pythia6_${_mcEngine}
           ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1_pythia6.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial1_pythia6_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_tutorial1_pythia6_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  Add_Test(run_tutorial1_pythia8_${_mcEngine}
           ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1_pythia8.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial1_pythia8_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_tutorial1_pythia8_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  Add_Test(run_tutorial1_mesh_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1_mesh.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial1_mesh_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_tutorial1_mesh_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  Add_Test(run_tutorial1_urqmd_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial1/macros/run_tutorial1_urqmd.sh 2 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial1_urqmd_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_tutorial1_urqmd_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")
EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 

Install(FILES run_tutorial1.C run_tutorial1_pythia6.C run_tutorial1_pythia8.C run_tutorial1_urqmd.C run_tutorial1_mesh.C
        DESTINATION share/fairbase/examples/simulation/Tutorial1
       )


