
set(GOPATH $ENV{GOPATH})
set(GOPATH ${CMAKE_SOURCE_DIR}/examples/advanced/GoTutorial/)
set(ENV{GOPATH} "${GOPATH}")


execute_process(COMMAND ${GO_EXECUTABLE} get go-processor WORKING_DIRECTORY ${GOPATH}/src/go-processor)
execute_process(COMMAND ${GO_EXECUTABLE} build WORKING_DIRECTORY ${GOPATH}/src/go-processor)
execute_process(COMMAND ${GO_EXECUTABLE} get go-sink WORKING_DIRECTORY ${GOPATH}/src/go-sink)
execute_process(COMMAND ${GO_EXECUTABLE} build WORKING_DIRECTORY ${GOPATH}/src/go-sink)

Install(
  FILES ${GOPATH}/bin/go-sink ${GOPATH}/bin/go-processor
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
  DESTINATION bin
)
