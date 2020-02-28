################################################################################
# Copyright (C) 2014-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
set(ex "ex_sim")
set(run "source ${CMAKE_BINARY_DIR}/config.sh && root -b -q -l ${CMAKE_CURRENT_SOURCE_DIR}/run")

foreach(mce IN ITEMS TGeant3 TGeant4)
  add_test(NAME ${ex}_rutherford_${mce} COMMAND bash -c "${run}_rutherford.C\\(10,\\\"${mce}\\\"\\)")
  add_test(NAME ${ex}_run_rad_${mce} COMMAND bash -c "${run}_rad.C\\(100,\\\"${mce}\\\"\\)")

  set_tests_properties(${ex}_run_rad_${mce} ${ex}_rutherford_${mce} PROPERTIES
    TIMEOUT 60
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )
endforeach()

install(FILES
  run_rutherford.C
  run_rad.C
  eventDisplay.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/rutherford
)
