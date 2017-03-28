################################################################################
#    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################
#
# Authors:
#
#   Dennis Klein
#
#
# ##########################
# # GTest helper functions #
# ##########################
#
# The helper functions allow concise cmake files for GTest based test submodules.
# Testsuites register themselves automatically as CTest test.
#
#
# Usage:
# 
#   add_testsuite(<name> SOURCES source1 [source2 ...]
#                        [DEPENDS dep1 [dep2 ...]]
#                        [LINKS linklib1 [linklib2 ...]
#                        [INCLUDES dir1 [dir2 ...])
#
#   -> created target: testsuite_<name>
#
#   add_testhelper(<name> SOURCES source1 [source2 ...]
#                         [DEPENDS dep1 [dep2 ...]]
#                         [LINKS linklib1 [linklib2 ...]
#                         [INCLUDES dir1 [dir2 ...])
#
#   -> created target: testhelper_<name>
#
#   The above add_* functions add all created targets to the cmake
#   variable ALL_TEST_TARGETS which can be used to create an aggregate
#   target, e.g.:
#
#   add_custom_target(AllTests DEPENDS ${ALL_TEST_TARGETS})
#
#

function(add_testsuite suitename)
    set(optional_args "")
    set(single_value_args TIMEOUT)
    set(multi_value_args SOURCES LINKS DEPENDS INCLUDES)
    cmake_parse_arguments(testsuite "${optional_args}" "${single_value_args}" "${multi_value_args}" ${ARGN})

    list(INSERT testsuite_LINKS 0 GTest::Main GTest::GTest)
    set(target "testsuite_${suitename}")

    add_executable(${target} ${testsuite_SOURCES})
    target_link_libraries(${target} ${testsuite_LINKS})
    if(testsuite_DEPENDS)
        add_dependencies(${target} ${testsuite_DEPENDS})
    endif()
    if(testsuite_INCLUDES)
        target_include_directories(${target} PUBLIC ${testsuite_INCLUDES})
    endif()

    add_test(NAME "${suitename}" COMMAND ${target})
    if(testsuite_TIMEOUT)
        set_tests_properties("${suitename}" PROPERTIES TIMEOUT ${testsuite_TIMEOUT})
    endif()

    list(APPEND ALL_TEST_TARGETS ${target})
    set(ALL_TEST_TARGETS ${ALL_TEST_TARGETS} PARENT_SCOPE)
endfunction()

function(add_testhelper helpername)
    set(optional_args "")
    set(multi_value_args SOURCES LINKS DEPENDS INCLUDES)
    cmake_parse_arguments(testhelper "${optional_args}" "" "${multi_value_args}" ${ARGN})

    set(target "testhelper_${helpername}")
    
    add_executable(${target} ${testhelper_SOURCES})
    if(testhelper_LINKS)
    target_link_libraries(${target} ${testhelper_LINKS})
    endif()
    if(testhelper_DEPENDS)
        add_dependencies(${target} ${testhelper_DEPENDS})
    endif()
    if(testhelper_INCLUDES)
        target_include_directories(${target} PUBLIC ${testhelper_INCLUDES})
    endif()

    list(APPEND ALL_TEST_TARGETS ${target})
    set(ALL_TEST_TARGETS ${ALL_TEST_TARGETS} PARENT_SCOPE)
endfunction()
