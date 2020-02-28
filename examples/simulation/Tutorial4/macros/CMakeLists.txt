################################################################################
# Copyright (C) 2014-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
set(tut4 "ex_sim_tutorial4")
set(run "source ${CMAKE_BINARY_DIR}/config.sh && root -b -q -l ${CMAKE_CURRENT_SOURCE_DIR}/run")

foreach(mce IN ITEMS TGeant3 TGeant4)
  add_test(NAME ${tut4}_${mce} COMMAND bash -c "${run}_tutorial4.C\\(10,\\\"${mce}\\\"\\)")

  add_test(NAME ${tut4}_reco_${mce} COMMAND bash -c "${run}_reco.C\\(\\\"${mce}\\\"\\)")
  set_tests_properties(${tut4}_reco_${mce} PROPERTIES DEPENDS ${tut4}_${mce})

  set_tests_properties(${tut4}_${mce} ${tut4}_reco_${mce} PROPERTIES
    TIMEOUT 60
    PASS_REGULAR_EXPRESSION "Macro finished successfully"
  )
endforeach()

install(FILES
  eventDisplay.C run_reco.C Create_Tutorial4_Geometry.C run_tutorial4.C plots.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial4
)
