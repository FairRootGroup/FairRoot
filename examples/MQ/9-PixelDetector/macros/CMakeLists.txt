 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/macros/run_sim.C)

Set(MaxTestTime 60)

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(run_sim_${_mcEngine} 
           ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/macros/run_sim.sh 10 \"${_mcEngine}\")
  Set_Tests_Properties(run_sim_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(run_sim_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 

Install(FILES run_sim.C
        DESTINATION share/fairbase/examples/MQ/9-PixelDetector/macros/
       )


