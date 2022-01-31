################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/test_tgeo_units.C)

set(maxTestTime 20)

add_test(NAME test_tgeo_units
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_tgeo_units.sh
        )
set_tests_properties(test_tgeo_units PROPERTIES
                     TIMEOUT ${maxTestTime}
                    )
