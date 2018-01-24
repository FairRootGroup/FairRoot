 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
set(INCLUDE_DIRECTORIES
 ${ROOT_INCLUDE_DIR}
 ${GTEST_INCLUDE_DIRS}
 ${CMAKE_SOURCE_DIR}/parbase
 ${CMAKE_SOURCE_DIR}/geobase
 ${CMAKE_SOURCE_DIR}/fairtools
 ${CMAKE_SOURCE_DIR}/base/sim
 ${CMAKE_SOURCE_DIR}/base/steer
 ${CMAKE_SOURCE_DIR}/test/testlib
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
 ${ROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})
############### build the test #####################

add_executable(_GTestFairModule _GTestFairModule.cxx)
target_link_libraries(_GTestFairModule ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} FairTools FairTest Base )

Generate_Exe_Script(${CMAKE_CURRENT_SOURCE_DIR} _GTestFairModule)
add_test(_GTestFairModule ${CMAKE_BINARY_DIR}/bin/_GTestFairModule)

File(COPY ${CMAKE_SOURCE_DIR}/examples/common/geometry/cave.geo
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
