################################################################################
# Copyright (C) 2014-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
set(tut1 "ex_sim_tutorial1")
set(root "source ${CMAKE_BINARY_DIR}/config.sh && root -b -q -l ${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME load_all_libs COMMAND bash -c "${root}/load_all_libs.C\\(\\\"${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_LIBDIR}\\\"\\)")

foreach(mce IN ITEMS TGeant3 TGeant4)
  add_test(NAME ${tut1}_mesh_${mce} COMMAND bash -c "${root}/run_tutorial1_mesh.C\\(10,\\\"${mce}\\\"\\)")
  add_test(NAME ${tut1}_pythia6_${mce} COMMAND bash -c "${root}/run_tutorial1_pythia6.C\\(10,\\\"${mce}\\\"\\)")
  add_test(NAME ${tut1}_pythia8_${mce} COMMAND bash -c "${root}/run_tutorial1_pythia8.C\\(10,\\\"${mce}\\\"\\)")
  add_test(NAME ${tut1}_urqmd_${mce} COMMAND bash -c "${root}/run_tutorial1_urqmd.C\\(2,\\\"${mce}\\\"\\)")
  add_test(NAME ${tut1}_${mce} COMMAND bash -c "${root}/run_tutorial1.C\\(10,\\\"${mce}\\\"\\)")

  set_tests_properties(
    load_all_libs
    ${tut1}_mesh_${mce}
    ${tut1}_pythia6_${mce}
    ${tut1}_pythia8_${mce}
    ${tut1}_urqmd_${mce}
    ${tut1}_${mce}

    PROPERTIES
    TIMEOUT 60
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )
endforeach()

install(FILES run_tutorial1_mesh.C run_tutorial1_pythia6.C run_tutorial1_pythia8.C run_tutorial1_urqmd.C run_tutorial1.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial1
)
