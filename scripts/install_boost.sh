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
	
    cxxflags=""
    if [ $hascxx11 ];
    then
       cxxflags="$cxxflags -std=c++11"
    fi   

    if [ $haslibcxx ];
    then
       cxxflags="$cxxflags -stdlib=libc++"
    fi   

	if [ "$compiler" = "intel" ];
	then
            ./bootstrap.sh --with-toolset=intel-linux
           ./b2 --build-dir=$PWD/tmp --build-type=minimal --toolset=intel --prefix=$install_prefix  --layout=system -j $number_of_processes install
	elif [ "$compiler" = "PGI" ];
	then
            ./bootstrap.sh --with-toolset=pgi
           ./b2 --build-dir=$PWD/tmp --build-type=minimal --toolset=pgi --prefix=$install_prefix --layout=system -j $number_of_processes install
	elif [ "$compiler" = "Clang" ];
	then
            ./bootstrap.sh --with-toolset=clang
           if [ $hascxx11 ];
           then
             ./b2 cxxflags="$cxxflags" linkflags="$cxxflags" --build-dir=$PWD/tmp --build-type=minimal --toolset=clang --prefix=$install_prefix --layout=system -j $number_of_processes install
           else
             ./b2 --build-dir=$PWD/tmp --build-type=minimal --toolset=clang --prefix=$install_prefix --layout=system -j $number_of_processes install
           fi
	elif [ "$arch" = "macosx64" ];
        then
            ./bootstrap.sh --with-toolset=darwin
           ./b2 --build-dir=$PWD/tmp --build-type=minimal --toolset=darwin --prefix=$install_prefix --layout=system -j $number_of_processes install
	elif [ "$arch" = "macosx" ];
        then
            ./bootstrap.sh --with-toolset=darwin
           ./b2 --build-dir=$PWD/tmp --build-type=minimal --toolset=darwin --prefix=$install_prefix --layout=system -j $number_of_processes install
	else
            ./bootstrap.sh --with-toolset=gcc
           ./b2 --build-dir=$PWD/tmp --build-type=minimal --toolset=gcc --prefix=$install_prefix  --layout=system -j $number_of_processes install
	fi
	
        if [ "$platform" = "macosx" ];
        then
            cd  $install_prefix/lib
	    create_links dylib so
	fi

	check_all_libraries $install_prefix/lib

	check_success Boost $checkfile
	check=$?
		
    fi
fi

cd $SIMPATH

return 1
