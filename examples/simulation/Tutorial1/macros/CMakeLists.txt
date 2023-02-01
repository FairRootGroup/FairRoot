################################################################################
# Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1_mesh.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1_pythia6.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1_pythia8.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1_urqmd.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1.C)

set(maxTestTime 60)

foreach(mcEngine IN LISTS mcEngine_list)
  add_test(NAME ex_sim_tutorial1_mesh_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1_mesh.sh 10 \"${mcEngine}\")
  set_tests_properties(ex_sim_tutorial1_mesh_${mcEngine} PROPERTIES
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )

  add_test(NAME ex_sim_tutorial1_pythia6_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1_pythia6.sh 10 \"${mcEngine}\")
  set_tests_properties(ex_sim_tutorial1_pythia6_${mcEngine} PROPERTIES
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )

  add_test(NAME ex_sim_tutorial1_pythia8_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1_pythia8.sh 10 \"${mcEngine}\")
  set_tests_properties(ex_sim_tutorial1_pythia8_${mcEngine} PROPERTIES
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )

  add_test(NAME ex_sim_tutorial1_urqmd_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1_urqmd.sh 2 \"${mcEngine}\")
  set_tests_properties(ex_sim_tutorial1_urqmd_${mcEngine} PROPERTIES
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )

  add_test(NAME ex_sim_tutorial1_${mcEngine}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1.sh 10 \"${mcEngine}\")
  set_tests_properties(ex_sim_tutorial1_${mcEngine} PROPERTIES
    TIMEOUT ${maxTestTime}
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )
endforeach()

add_test(NAME ex_tutorial1_Geant4MT
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1.sh 20 \"TGeant4\" true false)
set_tests_properties(ex_tutorial1_Geant4MT PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Simulation successful."
)

add_test(NAME ex_tutorial1_PostInitConfig
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1.sh 1 \"TGeant4\" false true)
set_tests_properties(ex_tutorial1_PostInitConfig PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Loading Geant4 PostInit Config."
)

install(FILES run_tutorial1_mesh.C run_tutorial1_pythia6.C run_tutorial1_pythia8.C run_tutorial1_urqmd.C run_tutorial1.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial1
)
