################################################################################
# Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(prefix ex_pixel)

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_sim.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_digi.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_digiToBin.C)

# Try to compile the macros as normal files
add_library(${prefix}_check_compile OBJECT
    run_dAsciiSource.C
    run_dBinSource.C)
target_link_libraries(${prefix}_check_compile PRIVATE
    FairRoot::ExPixel)

set(maxTestTime 30)

add_test(NAME ex_pixel_sim_${pixel_simulation_engine}
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_sim.sh 1000 \"${pixel_simulation_engine}\")
math(EXPR testTime 4*${maxTestTime})
set_tests_properties(ex_pixel_sim_${pixel_simulation_engine} PROPERTIES
  TIMEOUT ${testTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_pixel_sim_${pixel_simulation_engine}
)

add_test(NAME ex_pixel_digi_${pixel_simulation_engine}
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_digi.sh \"${pixel_simulation_engine}\")
set_tests_properties(ex_pixel_digi_${pixel_simulation_engine} PROPERTIES
  FIXTURES_REQUIRED fixtures.ex_pixel_sim_${pixel_simulation_engine}
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_pixel_digi_${pixel_simulation_engine}
)

add_test(NAME ex_pixel_digi_to_bin_${pixel_simulation_engine}
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_digiToBin.sh 0 \"${pixel_simulation_engine}\")
set_tests_properties(ex_pixel_digi_to_bin_${pixel_simulation_engine} PROPERTIES
  FIXTURES_REQUIRED fixtures.ex_pixel_digi_${pixel_simulation_engine}
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_pixel_digi_to_bin_${pixel_simulation_engine}
)

install(FILES run_sim.C run_digi.C run_tracks.C run_reco.C run_digiToAscii.C run_digiToBin.C run_dAsciiSource.C run_dBinSource.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelDetector/macros/
)
