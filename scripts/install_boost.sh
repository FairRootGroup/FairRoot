#!/bin/bash

if [ ! -d  $SIMPATH/basics/boost ];
then 
  cd $SIMPATH/basics
  if [ ! -e $BOOSTVERSION.tar.bz2 ];
  then
    echo "*** Downloading boost sources ***"
    download_file $BOOST_LOCATION/$BOOSTVERSION.tar.bz2
  fi
  untar boost $BOOSTVERSION.tar.bz2
  if [ -d  $BOOSTVERSION ]; 
  then
    ln -s $BOOSTVERSION boost
  fi
fi 

if [ "$check" = "1" ];
then
  install_prefix=$SIMPATH_INSTALL

  checkfile=$install_prefix/lib/libboost_unit_test_framework.so
  if (not_there Boost $checkfile);
  then
    cd $SIMPATH/basics/boost

    # patch file toavoid problems with newer versions of glibc
    patch -p0 < ../boost_glibc.patch | tee -a $logfile
	
    # boost only support up to 64 parallel processes
    tmp_nop=$number_of_processes
    if [ $number_of_processes -gt 64 ];then
      number_of_processes=64
    fi
    
    _icu_path=""
    if [ "$compiler" = "intel" ];
    then
      toolset=intel
    elif [ "$compiler" = "PGI" ];
    then
      toolset=pgi 
    elif [ "$compiler" = "Clang" ];
    then
      toolset=clang
      if [ "$platform" = "linux" ]; then
        _icu_path="-sICU_PATH=$install_prefix"
      fi
    elif [ "$compiler" = "gcc" ];
    then
      if [ "$platform" = "macosx" ];
      then
        toolset=darwin
      else
        toolset=gcc
      fi  
    fi

    if [ $hascxx11 ];
    then
      cxxflags="-std=c++11"
      if [ $haslibcxx ];
      then
         cxxflags="$cxxflags -stdlib=libc++"
      fi   
      ./bootstrap.sh cxxflags="$cxxflags" linkflags="$cxxflags" --with-toolset=$toolset
      ./b2 ${_icu_path} cxxflags="$cxxflags" linkflags="$cxxflags"  --build-dir=$PWD/tmp --build-type=minimal --toolset=$toolset --prefix=$install_prefix  --layout=system -j $number_of_processes install
    else
      ./bootstrap.sh --with-toolset=$toolset
      ./b2 --build-dir=$PWD/tmp --build-type=minimal --toolset=$toolset --prefix=$install_prefix  --layout=system -j $number_of_processes install
    fi
     
    if [ "$platform" = "macosx" ];
    then
      cd  $install_prefix/lib
      create_links dylib so
    fi

    check_all_libraries $install_prefix/lib

    check_success Boost $checkfile
    check=$?

    number_of_processes=$tmp_nop
		
  fi
fi

cd $SIMPATH

return 1
