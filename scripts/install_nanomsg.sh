#!/bin/bash


if [ ! -d  $SIMPATH/basics/nanomsg ];
then
  cd $SIMPATH/basics
  if [ ! -e $NANOMSG_VERSION.tar.gz ];
  then
    echo "*** Downloading gtest sources ***"
    download_file $NANOMSG_LOCATION/$NANOMSG_VERSION.tar.gz
  fi
  untar nanomsg $NANOMSG_VERSION.tar.gz
  if [ -d $NANOMSG_VERSION ];
  then
    ln -s $NANOMSG_VERSION nanomsg
  fi
fi
 
install_prefix=$SIMPATH_INSTALL

checkfile=$install_prefix/bin/nanocat

if (not_there nanomsg $checkfile);
then
    cd $SIMPATH/basics/nanomsg
    
    ./configure --prefix=$install_prefix

    make -j$number_of_processes

    make install

    check_all_libraries  $install_prefix/lib

    check_success nanomsg $checkfile
    check=$?

fi

cd $SIMPATH

return 1
