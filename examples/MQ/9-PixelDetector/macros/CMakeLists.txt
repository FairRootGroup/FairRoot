 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/macros/run_sim.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/macros/run_digi.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/MQ/9-PixelDetector/macros/run_digiToBin.C)

Set(MaxTestTime 30)

Add_Test(ex9_sim_TGeant3
         ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/macros/run_sim.sh 10000 \"TGeant3\")
Math(EXPR TestTime 4*${MaxTestTime})
Set_Tests_Properties(ex9_sim_TGeant3 PROPERTIES TIMEOUT ${TestTime})
Set_Tests_Properties(ex9_sim_TGeant3 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

Add_Test(ex9_digi_TGeant3
         ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/macros/run_digi.sh \"TGeant3\")
Set_Tests_Properties(ex9_digi_TGeant3 PROPERTIES DEPENDS ex9_sim_TGeant3)
Set_Tests_Properties(ex9_digi_TGeant3 PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(ex9_digi_TGeant3 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

Add_Test(ex9_dbin_TGeant3
         ${CMAKE_BINARY_DIR}/examples/MQ/9-PixelDetector/macros/run_digiToBin.sh 0 \"TGeant3\")
Set_Tests_Properties(ex9_dbin_TGeant3 PROPERTIES DEPENDS ex9_digi_TGeant3)
Set_Tests_Properties(ex9_dbin_TGeant3 PROPERTIES TIMEOUT ${MaxTestTime})
Set_Tests_Properties(ex9_dbin_TGeant3 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

Install(FILES run_sim.C run_digi.C run_tracks.C run_reco.C run_digiToAscii.C run_digiToBin.C run_dAsciiSource.C run_dBinSource.C
        DESTINATION share/fairbase/examples/MQ/9-PixelDetector/macros/
       )


