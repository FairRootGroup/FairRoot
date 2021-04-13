################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_sim.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_digi.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_digiToBin.C)

set(maxTestTime 30)

add_test(NAME ex_pixel_sim_TGeant3
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_sim.sh 10000 \"TGeant3\")
math(EXPR testTime 4*${maxTestTime})
set_tests_properties(ex_pixel_sim_TGeant3 PROPERTIES
  TIMEOUT ${testTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)

add_test(NAME ex_pixel_digi_TGeant3
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_digi.sh \"TGeant3\")
set_tests_properties(ex_pixel_digi_TGeant3 PROPERTIES
  DEPENDS ex_pixel_sim_TGeant3
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)

add_test(NAME ex_pixel_digi_to_bin_TGeant3
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_digiToBin.sh 0 \"TGeant3\")
set_tests_properties(ex_pixel_digi_to_bin_TGeant3 PROPERTIES
  DEPENDS ex_pixel_digi_TGeant3
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)

install(FILES run_sim.C run_digi.C run_tracks.C run_reco.C run_digiToAscii.C run_digiToBin.C run_dAsciiSource.C run_dBinSource.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelDetector/macros/
)
