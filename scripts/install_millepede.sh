#!/bin/bash


if [ ! -d  $SIMPATH/basics/MillepedeII ];
then 
  cd $SIMPATH/basics
  if [ ! -d MillepedeII ];
  then
    echo "*** Downloading MillepedeII sources with subversion***"
    svn co $MILLEPEDE_LOCATION/$MILLEPEDE_VERSION MillepedeII
  fi
fi 

install_prefix=$SIMPATH_INSTALL
checkfile=$install_prefix/bin/pede

if (not_there Millepede $checkfile);
then

  cd $SIMPATH/basics/MillepedeII

  # patch needed since the gcc of Apple does not have gfortran
  # Also use the found fortran (FC) and c (CC) compiler
  patch -p0 < ../Makefile_millepede.patch | tee -a $logfile

  # add the correct library path for gfortran on Mac OS since 
  # gfortran is not installed in the system path 
  if [ "$platform" = "macosx" ];
  then 
    fortran_filepath=$(gfortran -print-file-name=libgfortran.dylib)
    fortran_libdir=$(dirname $fortran_filepath)
    mysed "-lgfortran " "-L${fortran_libdir} -lgfortran " Makefile has_slash
  fi

  make 

  # fake make install
  mkdir -p $install_prefix/bin
  cp $SIMPATH/basics/MillepedeII/pede $install_prefix/bin

  cp ../CMakeLists.txt_libMille CMakeLists.txt
  mkdir build
  cd build
  cmake .. -DCMAKE_INSTALL_PREFIX=$install_prefix
  make install

  if [ "$platform" = "macosx" ];
  then
    cd $install_prefix/lib
    create_links dylib so
  fi
              
  check_success Millepede $checkfile
  check=$?

fi

if [ "$platform" = "macosx" ];
then
  export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$install_prefix
else
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SIMPATH/install_prefix
fi

cd $SIMPATH

return 1
