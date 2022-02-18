################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial4_createMatrices.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial4_createGeometryFile.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial4_createParameterFile.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial4.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_reco.C)

set(maxTestTime 60)

foreach(mcEngine IN LISTS mcEngine_list)
  add_test(NAME ex_sim_tutorial4_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial4.sh 10 \"${mcEngine}\")
  set_tests_properties(ex_sim_tutorial4_${mcEngine} PROPERTIES
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )

  add_test(NAME ex_sim_tutorial4_reco_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_reco.sh \"${mcEngine}\")
  set_tests_properties(ex_sim_tutorial4_reco_${mcEngine} PROPERTIES
    DEPENDS ex_sim_tutorial4_${mcEngine}
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )
endforeach(mcEngine IN ITEMS TGeant3 TGeant4)

install(FILES
  eventDisplay.C
  run_reco.C
  Create_Tutorial4_Geometry.C
  run_tutorial4.C
  plots.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial4
)
