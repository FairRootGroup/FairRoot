
#set(GOPATH $ENV{GOPATH})
set(GOPATH ${CMAKE_CURRENT_SOURCE_DIR})
set(ENV{GOPATH} "${GOPATH}")

build_go_package(go-processor "${GOPATH}")
build_go_package(go-sink "${GOPATH}")

install(
  FILES ${GOPATH}/bin/go-processor ${GOPATH}/bin/go-sink
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
  DESTINATION bin
)
