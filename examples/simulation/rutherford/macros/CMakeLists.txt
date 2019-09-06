################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_rutherford.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_rad.C)

set(maxTestTime 60)

foreach(mcEngine IN ITEMS TGeant3 TGeant4)
  add_test(run_rutherford_${mcEngine} ${CMAKE_CURRENT_BINARY_DIR}/run_rutherford.sh 10 \"${mcEngine}\")
  set_tests_properties(run_rutherford_${mcEngine} PROPERTIES TIMEOUT ${maxTestTime})
  set_tests_properties(run_rutherford_${mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  add_test(run_rad_${mcEngine} ${CMAKE_CURRENT_BINARY_DIR}/run_rad.sh 100 \"${mcEngine}\")
  set_tests_properties(run_rad_${mcEngine} PROPERTIES TIMEOUT ${maxTestTime})
  set_tests_properties(run_rad_${mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")
endforeach()

install(FILES
  run_rutherford.C
  run_rad.C
  eventDisplay.C
  DESTINATION
  ${PROJECT_INSTALL_DATADIR}/examples/simulation/rutherford
)
