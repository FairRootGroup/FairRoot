
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_project_root_containers.sh.in ${CMAKE_CURRENT_BINARY_DIR}/test_project_root_containers.sh)
add_test(project_root_containers ${CMAKE_CURRENT_BINARY_DIR}/test_project_root_containers.sh PROPERTIES
  TIMEOUT "300"
  PASS_REGULAR_EXPRESSION "Test successful."
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_project_stl_containers.sh.in ${CMAKE_CURRENT_BINARY_DIR}/test_project_stl_containers.sh)
add_test(project_stl_containers ${CMAKE_CURRENT_BINARY_DIR}/test_project_stl_containers.sh PROPERTIES
  TIMEOUT "300"
  PASS_REGULAR_EXPRESSION "Test successful."
)
