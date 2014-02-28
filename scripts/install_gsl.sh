#!/bin/bash

if [ "$system" = "64bit" ];
then
  CXXFLAGS_BAK=$CXXFLAGS
  CXXFLAGS="$CXXFLAGS -m64"
  export CXXFLAGS
  CFLAGS_BAK=$CFLAGS
  CFLAGS="$CFLAGS -m64"
  export CFLAGS
fi

if [ ! -d  $SIMPATH/basics/gsl ];
then 
  cd $SIMPATH/basics
  if [ ! -e $GSLVERSION.tar.gz ];
  then
    echo "*** Downloading gsl sources ***"
    download_file $GSL_LOCATION/$GSLVERSION.tar.gz
  fi
  untar gsl $GSLVERSION.tar.gz
  if [ -d  $GSLVERSION ]; 
  then
    ln -s $GSLVERSION gsl
  fi
fi 


install_prefix=$SIMPATH_INSTALL

checkfile=$install_prefix/lib/libgsl.a

if (not_there gsl $checkfile);
then
    cd $SIMPATH/basics

    cd gsl
    if [ "$arch" == "solarisCC5" ];then
      CFLAGS_BAK=$CFLAGS
      CFLAGS="$CFLAGS -DGSL_C99_INLINE"
      export CFLAGS
    fi 
    ./configure --prefix=$install_prefix  --with-pic --libdir=$install_prefix/lib
    if [ "$arch" == "solarisCC5" ];then
      CFLAGS=$CFLAGS_BAK
      export CFLAGS
    fi
    if [ "$compiler" == "PGI" ];then
      mysed "#define HAVE_INLINE 1" "#undef HAVE_INLINE" config.h
    fi
    $MAKE_command -j$number_of_processes
  #make check > log 2>&1
    $MAKE_command install -j$number_of_processes

    if [ "$platform" = "macosx" ];
    then
      cd  $install_prefix/lib
      create_links dylib so
    fi
    
    check_all_libraries  $install_prefix/lib

    check_success gsl $checkfile
    check=$?
    
fi

if [ "$system" = "64bit" ];
then
  CXXFLAGS=$CXXFLAGS_BAK
  CFLAGS=$CFLAGS_BAK
  export CXXFLAGS
  export CFLAGS
fi

cd $SIMPATH

return 1
