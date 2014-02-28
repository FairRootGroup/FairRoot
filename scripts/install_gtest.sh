#!/bin/bash


if [ ! -d  $SIMPATH/basics/gtest ];
then 
  cd $SIMPATH/basics
  if [ ! -e $GTESTVERSION.zip ];
  then
    echo "*** Downloading gtest sources ***"
    download_file $GTEST_LOCATION/$GTESTVERSION.zip
  fi
  untar gtest $GTESTVERSION.zip
  if [ -d  $GTESTVERSION ]; 
  then
    ln -s $GTESTVERSION gtest
  fi
fi 


install_prefix=$SIMPATH_INSTALL

checkfile=$install_prefix/lib/libgtest.a

if (not_there gtest $checkfile);
then
    cd $SIMPATH/basics
    cd gtest
    mkdir build
    cd build
    cmake ..
    make
    # fake the installation process
    mkdir -p $install_prefix/lib
    cp libgtest.a libgtest_main.a $install_prefix/lib
    if [ ! -d $install_prefix/include/gtest ];then
      mkdir -p $install_prefix/include
      cp -r ../include/gtest $install_prefix/include 
    fi

    check_all_libraries  $install_prefix/lib

    check_success gtest $checkfile
    check=$?
    
fi

cd $SIMPATH

return 1
