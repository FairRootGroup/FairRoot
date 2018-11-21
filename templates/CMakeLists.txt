
configure_file(${CMAKE_SOURCE_DIR}/templates/test_project_root_containers.sh.in ${CMAKE_BINARY_DIR}/templates/test_project_root_containers.sh)
add_test(project_root_containers ${CMAKE_BINARY_DIR}/templates/test_project_root_containers.sh)
SET_TESTS_PROPERTIES(project_root_containers PROPERTIES TIMEOUT "300")
SET_TESTS_PROPERTIES(project_root_containers PROPERTIES PASS_REGULAR_EXPRESSION "Test successful.")

configure_file(${CMAKE_SOURCE_DIR}/templates/test_project_stl_containers.sh.in ${CMAKE_BINARY_DIR}/templates/test_project_stl_containers.sh)
add_test(project_stl_containers ${CMAKE_BINARY_DIR}/templates/test_project_stl_containers.sh)
SET_TESTS_PROPERTIES(project_stl_containers PROPERTIES TIMEOUT "300")
SET_TESTS_PROPERTIES(project_stl_containers PROPERTIES PASS_REGULAR_EXPRESSION "Test successful.")

