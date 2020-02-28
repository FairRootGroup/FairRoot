################################################################################
# Copyright (C) 2014-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(ex "ex_pixel")
set(run "source ${CMAKE_BINARY_DIR}/config.sh && root -b -q -l ${CMAKE_CURRENT_SOURCE_DIR}/run")
set(maxTestTime 30)
math(EXPR testTime 4*${maxTestTime})

foreach(mce IN ITEMS TGeant3)
  add_test(NAME ${ex}_sim_${mce} COMMAND bash -c "${run}_sim.C\\(10000,\\\"${mce}\\\"\\)")
  set_tests_properties(${ex}_sim_${mce} PROPERTIES
    TIMEOUT ${testTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )

  add_test(NAME ${ex}_digi_${mce} COMMAND bash -c "${run}_digi.C\\(\\\"${mce}\\\"\\)")
  set_tests_properties(${ex}_digi_${mce} PROPERTIES
    DEPENDS ${ex}_sim_${mce}
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )

  add_test(NAME ${ex}_digi_to_bin_${mce} COMMAND bash -c "${run}_digiToBin.C\\(0,\\\"${mce}\\\"\\)")
  set_tests_properties(${ex}_digi_to_bin_${mce} PROPERTIES
    DEPENDS ${ex}_digi_${mce}
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )
endforeach()

install(FILES run_sim.C run_digi.C run_tracks.C run_reco.C run_digiToAscii.C run_digiToBin.C run_dAsciiSource.C run_dBinSource.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelDetector/macros/
)
