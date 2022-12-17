
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_project_root_containers.sh.in
               ${CMAKE_CURRENT_BINARY_DIR}/test_project_root_containers.sh
               @ONLY)
add_test(NAME project_root_containers
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_project_root_containers.sh)
set_tests_properties(project_root_containers PROPERTIES
  TIMEOUT "300"
  PASS_REGULAR_EXPRESSION "Test successful."
)
add_test(NAME project_root_containers_double
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_project_root_containers.sh --double-configure)
set_tests_properties(project_root_containers_double PROPERTIES
  TIMEOUT "300"
  PASS_REGULAR_EXPRESSION "Test successful."
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_project_stl_containers.sh.in
               ${CMAKE_CURRENT_BINARY_DIR}/test_project_stl_containers.sh
               @ONLY)
add_test(NAME project_stl_containers
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_project_stl_containers.sh)
set_tests_properties(project_stl_containers PROPERTIES
  TIMEOUT "300"
  PASS_REGULAR_EXPRESSION "Test successful."
)
add_test(NAME project_stl_containers_double
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_project_stl_containers.sh --double-configure)
set_tests_properties(project_stl_containers_double PROPERTIES
  TIMEOUT "300"
  PASS_REGULAR_EXPRESSION "Test successful."
)
