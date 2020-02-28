################################################################################
# Copyright (C) 2014-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
set(ex "ex_tutorial3")
set(run "source ${CMAKE_BINARY_DIR}/config.sh && root -b -q -l ${CMAKE_CURRENT_SOURCE_DIR}/run")

foreach(mce IN ITEMS TGeant3 TGeant4)
  add_test(NAME ${ex}_sim_${mce} COMMAND bash -c "${run}_sim.C\\(100,\\\"${mce}\\\"\\)")

  add_test(NAME ${ex}_digi_${mce} COMMAND bash -c "${run}_digi.C\\(\\\"${mce}\\\"\\)")
  set_tests_properties(${ex}_digi_${mce} PROPERTIES DEPENDS ${ex}_sim_${mce})

  add_test(NAME ${ex}_reco_${mce} COMMAND bash -c "${run}_reco.C\\(\\\"${mce}\\\"\\)")
  set_tests_properties(${ex}_reco_${mce} PROPERTIES DEPENDS ${ex}_digi_${mce})

  add_test(NAME ${ex}_digi_timebased_${mce} COMMAND bash -c "${run}_digi_timebased.C\\(\\\"${mce}\\\"\\)")
  set_tests_properties(${ex}_digi_timebased_${mce} PROPERTIES DEPENDS ${ex}_sim_${mce})

  add_test(NAME ${ex}_reco_timebased_${mce} COMMAND bash -c "${run}_reco_timebased.C\\(\\\"${mce}\\\"\\)")
  set_tests_properties(${ex}_reco_timebased_${mce} PROPERTIES DEPENDS ${ex}_digi_timebased_${mce})

  add_test(NAME ${ex}_digi_reco_proof_${mce} COMMAND bash -c "${run}_digi_reco_proof.C\\(1,\\\"${mce}\\\"\\)")
  set_tests_properties(${ex}_digi_reco_proof_${mce} PROPERTIES DEPENDS ${ex}_sim_${mce})

  set_tests_properties(
    ${ex}_sim_${mce}
    ${ex}_digi_reco_proof_${mce}
    ${ex}_digi_timebased_${mce}
    ${ex}_reco_${mce}
    ${ex}_digi_${mce}

    PROPERTIES
    TIMEOUT 60
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )
  set_tests_properties(${ex}_sim_${mce} PROPERTIES TIMEOUT 180)
endforeach()

install(FILES
  run_sim.C run_digi.C run_reco.C eventDisplay.C run_digi_timebased.C run_reco_timebased.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/advanced/Tutorial3
)

install(FILES
  data/dummy.txt
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/advanced/Tutorial3/macro/data
)
