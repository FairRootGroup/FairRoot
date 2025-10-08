
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_project.sh.in
               ${CMAKE_CURRENT_BINARY_DIR}/test_project.sh
               @ONLY)

foreach(container_type IN ITEMS root stl)
  add_test(NAME project_${container_type}_containers
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_project.sh ${container_type})
  set_tests_properties(project_${container_type}_containers PROPERTIES
    TIMEOUT "300"
    PASS_REGULAR_EXPRESSION "Test successful."
  )

  add_test(NAME project_${container_type}_containers_double
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_project.sh ${container_type} --double-configure)
  set_tests_properties(project_${container_type}_containers_double PROPERTIES
    TIMEOUT "300"
    PASS_REGULAR_EXPRESSION "Test successful."
  )
endforeach()
