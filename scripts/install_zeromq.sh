#!/bin/bash

if [ ! -d  $SIMPATH/basics/zeromq ];
then 
  cd $SIMPATH/basics
  if [ ! -e zeromq-$ZEROMQVERSION.tar.gz ];
  then
    echo "*** Downloading zeromq sources ***"
    download_file $ZEROMQ_LOCATION/zeromq-$ZEROMQVERSION.tar.gz
  fi
  untar zeromq zeromq-$ZEROMQVERSION.tar.gz 
  if [ -d zeromq-$ZEROMQVERSION ]; 
  then
    ln -s zeromq-$ZEROMQVERSION zeromq  
  fi
fi 

install_prefix=$SIMPATH_INSTALL
checkfile=$install_prefix/lib/libzmq.a

if (not_there zeromq $checkfile);
then
    cd $SIMPATH/basics/zeromq

    patch -p0 < ../zeromq_clang_c++11.patch

    ./configure --prefix=$install_prefix --libdir=$install_prefix/lib --enable-static
    make
    make install

    check_all_libraries  $install_prefix/lib

    check_success zeromq $checkfile
    check=$?
    

    if [ "$platform" = "macosx" ];
    then
      cd $install_prefix/lib
      create_links dylib so
    fi
fi

cp $SIMPATH/basics/zmq.hpp  $install_prefix/include/zmq.hpp 
cd $SIMPATH

return 1
