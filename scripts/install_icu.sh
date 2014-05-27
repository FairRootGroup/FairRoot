#!/bin/bash


if [ ! -d  $SIMPATH/basics/icu ];
then
  cd $SIMPATH/basics
  if [ ! -e $ICUVERSION-src.tgz ];
  then
    echo "*** Downloading gtest sources ***"
    download_file $ICU_LOCATION/$ICUVERSION-src.tgz
  fi
  untar icu $ICUVERSION-src.tgz
fi

install_prefix=$SIMPATH_INSTALL

checkfile=$install_prefix/lib/libicuuc.so.53.1

if (not_there icu $checkfile);
then
    cd $SIMPATH/basics
    cd icu/source
    
    LDFLAGS_BAK=$LDFLAGS
    LDFLAGS=$CXXFLAGS

    ./configure --prefix=$install_prefix

    make -j$number_of_processes

    make install

    check_all_libraries  $install_prefix/lib

    check_success icu $checkfile
    check=$?

    LDFLAGS=$LDFLAGS_BAK
    
fi

cd $SIMPATH

return 1
