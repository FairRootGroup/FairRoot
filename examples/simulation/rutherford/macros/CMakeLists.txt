################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_rad.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_rutherford.C)

set(maxTestTime 60)

foreach(mcEngine IN LISTS mcEngine_list)
  add_test(NAME ex_sim_rutherford_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_rutherford.sh 10 \"${mcEngine}\" false)
  set_tests_properties(ex_sim_rutherford_${mcEngine} PROPERTIES
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )

  add_test(NAME ex_sim_run_rad_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_rad.sh 100 \"${mcEngine}\")
  set_tests_properties(ex_sim_run_rad_${mcEngine} PROPERTIES
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )
endforeach()

install(FILES
  run_rutherford.C
  run_rad.C
  eventDisplay.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/rutherford
)
