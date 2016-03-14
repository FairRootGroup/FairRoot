## basically:
export GOPATH=`pwd`:$GOPATH
GOBIN=$CMAKE_INSTALL_PATH/bin go get go-sink
GOBIN=$CMAKE_INSTALL_PATH/bin go get go-processor

