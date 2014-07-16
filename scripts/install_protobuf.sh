#!/bin/bash


if [ ! -d  $SIMPATH/basics/protobuf ];
then
  cd $SIMPATH/basics
  if [ ! -e $PROTOBUF_VERSION.tar.gz ];
  then
    echo "*** Downloading gtest sources ***"
    download_file $PROTOBUF_LOCATION/$PROTOBUF_VERSION.tar.gz
  fi
  untar protobuf $PROTOBUF_VERSION.tar.gz
  if [ -d $PROTOBUF_VERSION ];
  then
    ln -s $PROTOBUF_VERSION protobuf
  fi
fi

install_prefix=$SIMPATH_INSTALL

checkfile=$install_prefix/bin/protoc

if (not_there protobuf $checkfile);
then
    cd $SIMPATH/basics/protobuf
    
    ./configure --prefix=$install_prefix

    make -j$number_of_processes

    make install

    check_all_libraries  $install_prefix/lib

    check_success protobuf $checkfile
    check=$?

fi

cd $SIMPATH

return 1
