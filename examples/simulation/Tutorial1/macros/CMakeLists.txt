################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/load_all_libs.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1_mesh.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1_pythia6.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1_pythia8.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1_urqmd.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial1.C)

set(MaxTestTime 60)

add_test(load_all_libs ${CMAKE_CURRENT_BINARY_DIR}/load_all_libs.sh)
set_tests_properties(load_all_libs PROPERTIES TIMEOUT ${MaxTestTime})
set_tests_properties(load_all_libs PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

foreach(mcEngine IN ITEMS TGeant3 TGeant4)
  add_test(tutorial1_mesh_${mcEngine} ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1_mesh.sh 10 \"${mcEngine}\")
  set_tests_properties(tutorial1_mesh_${mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  set_tests_properties(tutorial1_mesh_${mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  add_test(tutorial1_pythia6_${mcEngine} ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1_pythia6.sh 10 \"${mcEngine}\")
  set_tests_properties(tutorial1_pythia6_${mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  set_tests_properties(tutorial1_pythia6_${mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  add_test(tutorial1_pythia8_${mcEngine} ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1_pythia8.sh 10 \"${mcEngine}\")
  set_tests_properties(tutorial1_pythia8_${mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  set_tests_properties(tutorial1_pythia8_${mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  add_test(tutorial1_urqmd_${mcEngine} ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1_urqmd.sh 2 \"${mcEngine}\")
  set_tests_properties(tutorial1_urqmd_${mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  set_tests_properties(tutorial1_urqmd_${mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

  add_test(tutorial1_${mcEngine} ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial1.sh 10 \"${mcEngine}\")
  set_tests_properties(tutorial1_${mcEngine} PROPERTIES TIMEOUT ${MaxTestTime})
  set_tests_properties(tutorial1_${mcEngine} PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")
endforeach()

install(FILES
  run_tutorial1_mesh.C
  run_tutorial1_pythia6.C
  run_tutorial1_pythia8.C
  run_tutorial1_urqmd.C
  run_tutorial1.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial1
)


