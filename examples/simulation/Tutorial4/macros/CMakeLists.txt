 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial4/macros/run_tutorial4_createMatrices.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial4/macros/run_tutorial4_createGeometryFile.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial4/macros/run_tutorial4_createParameterFile.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial4/macros/run_tutorial4.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial4/macros/run_reco.C)

Set(MaxTestTime 60)

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_tutorial4_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial4/macros/run_tutorial4.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_tutorial4_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_tutorial4_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")


  Add_Test(run_reco_tut4_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial4/macros/run_reco.sh \"${_mcEngine}\")
  Set_Tests_Properties(run_reco_tut4_${_mcEngine} PROPERTIES DEPENDS run_tutorial4_${_mcEngine})
  Set_Tests_Properties(run_reco_tut4_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_reco_tut4_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")
EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 

Install(FILES eventDisplay.C run_reco.C Create_Tutorial4_Geometry.C
              run_tutorial4.C plots.C
        DESTINATION share/fairbase/examples/simulation/Tutorial4
       )


