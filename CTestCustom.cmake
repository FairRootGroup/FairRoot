 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# -*- mode: cmake -*-

#message(" -- Read CTestCustom.cmake --")

# -----------------------------------------------------------
# -- Number of warnings to display
# -----------------------------------------------------------

set(CTEST_CUSTOM_MAXIMUM_NUMBER_OF_WARNINGS "500" )

# -----------------------------------------------------------
# -- Number of errors to display
# -----------------------------------------------------------

set(CTEST_CUSTOM_MAXIMUM_NUMBER_OF_ERRORS   "50" )

# -----------------------------------------------------------
# -- Warning execptions
# -----------------------------------------------------------

set(CTEST_CUSTOM_WARNING_EXCEPTION
	${CTEST_CUSTOM_WARNING_EXCEPTION}


        # -- warnings from ubuntu systems which are a little to much
        # -- probably defined warn-unused-result. ignoring the result
        # -- of fgets is common practice. A work around would be to
        # -- store the return value in a dummy variable
        "ignoring return value of 'char* fgets(char*, int, FILE*)'"
        "ignoring return value of 'char* fscanf(char*, int, FILE*)'"

        # filter warnings from generated files
        "PayloadDigi_generated.h"
        "PayloadHit_generated.h"
        "Payload.pb"
        "MyPayload.pb"
        "G__.*Dict"

        # filter warnings from internal gtest headers
        "gtest/internal"
        "gtest/gtest-test-part.h"
        "gtest/gtest.h"
  )

# -----------------------------------------------------------
# -- Warning addon's
# -----------------------------------------------------------
set(CTEST_CUSTOM_WARNING_MATCH	${CTEST_CUSTOM_WARNING_MATCH}
	)

Set (CTEST_CUSTOM_COVERAGE_EXCLUDE
     ".*Dict.h"
     ".*Dict.cxx"
     "third_party"
     "_.*"
    )

# -----------------------------------------------------------
# -- Error execptions
# -- Get rid of boost warnings which are misinterpreted as errors
# -----------------------------------------------------------

Set(CTEST_CUSTOM_ERROR_EXCEPTION
	${CTEST_CUSTOM_ERROR_EXCEPTION}
        "/include/boost/"
)
