 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/macros/run_sim.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/macros/run_digi.C)

Set(MaxTestTime 30)

ForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 
  Add_Test(ex9_sim_${_mcEngine}
           ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/macros/run_sim.sh 10000 \"${_mcEngine}\")
  Math(EXPR TestTime 4*${MaxTestTime})
  Set_Tests_Properties(ex9_sim_${_mcEngine} PROPERTIES TIMEOUT ${TestTime})
  Set_Tests_Properties(ex9_sim_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  Add_Test(ex9_digi_${_mcEngine}
           ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/macros/run_digi.sh \"${_mcEngine}\")
  Set_Tests_Properties(ex9_digi_${_mcEngine} PROPERTIES DEPENDS ex9_sim_${_mcEngine})
  Set_Tests_Properties(ex9_digi_${_mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  Set_Tests_Properties(ex9_digi_${_mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

EndForEach(_mcEngine IN ITEMS TGeant3 TGeant4) 

Install(FILES run_sim.C run_digi.C run_tracks.C run_reco.C run_digiToAscii.C run_digiToBin.C run_dAsciiSource.C run_dBinSource.C
        DESTINATION share/fairbase/examples/MQ/9-PixelDetector/macros/
       )


