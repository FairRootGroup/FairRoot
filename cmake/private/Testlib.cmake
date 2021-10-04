################################################################################
# Copyright (C) 2020-2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

function(fairroot_ctest_submit)
    cmake_parse_arguments(PARSE_ARGV 0 ARGS "FINAL" "" "")
    foreach(env_var IN ITEMS http_proxy HTTP_PROXY https_proxy HTTPS_PROXY)
        if("$ENV{${env_var}}" MATCHES ".*proxy.gsi[.]de.*")
            set(old_${env_var} "$ENV{${env_var}}")
            set(ENV{${env_var}})
            message(STATUS "safed ${env_var}: ${old_${env_var}}")
        endif()
    endforeach()
    if(ARGS_FINAL)
        ctest_submit(RETURN_VALUE _ctest_submit_ret_val
                     BUILD_ID cdash_build_id)
        set(cdash_build_id "${cdash_build_id}" PARENT_SCOPE)
    else()
        ctest_submit(RETURN_VALUE _ctest_submit_ret_val)
    endif()
    foreach(env_var IN ITEMS http_proxy HTTP_PROXY https_proxy HTTPS_PROXY)
        if(DEFINED old_${env_var})
            set(ENV{${env_var}} "${old_${env_var}}")
            message(STATUS "(restored ${env_var}: $ENV{${env_var}})")
        endif()
    endforeach()

    if(_ctest_submit_ret_val)
        message(WARNING " ctest_submit() failed. Continueing")
    endif()
endfunction()

function(fairroot_summary_cdash)
    if(cdash_build_id)
        message(STATUS " CDash Build Summary ..: "
                "${CTEST_DROP_METHOD}://${CTEST_DROP_SITE}/buildSummary.php?buildid=${cdash_build_id}")
        message(STATUS " CDash Test List ......: "
                "${CTEST_DROP_METHOD}://${CTEST_DROP_SITE}/viewTest.php?buildid=${cdash_build_id}")
    else()
        message(STATUS "  /!\\  CDash submit likely failed")
    endif()
    message(STATUS " ")
endfunction()
