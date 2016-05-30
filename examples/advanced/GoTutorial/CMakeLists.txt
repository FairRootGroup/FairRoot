## basically:

set(GOPATH $ENV{GOPATH})
set(GOPATH ${GOPATH}:${CMAKE_SOURCE_DIR}/examples/advanced/GoTutorial/src)
set(ENV{GOPATH} "${GOPATH}")
MESSAGE(" GOPATH: ${GOPATH}")

#GOBIN=$CMAKE_INSTALL_PATH/bin go get go-sink
#GOBIN=$CMAKE_INSTALL_PATH/bin go get go-processor
