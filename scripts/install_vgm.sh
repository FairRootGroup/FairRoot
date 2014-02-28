#!/bin/bash

if [ "$system" = "64bit" ];
then
  CXXFLAGS_BAK=$CXXFLAGS
  CXXFLAGS="$CXXFLAGS -m64"
  CFLAGS_BAK=$CFLAGS
  CFLAGS="$CFLAGS -m64"
  export CXXFLAGS
  export CFLAGS
fi

if [ ! -d  $SIMPATH/transport/vgm ];
then 
  cd $SIMPATH/transport
  if [ ! -d vgm ];
  then
    echo "*** Downloading vgm sources with subversion***"
    svn co $VGM_LOCATION/$VGMVERSION/vgm vgm
  fi
fi 


install_prefix=$SIMPATH_INSTALL
checkfile=$install_prefix/lib/libBaseVGM.so

if (not_there VGM $checkfile);
then
  cd $SIMPATH/transport/vgm

  mkdir build_cmake
  cd build_cmake

  cmake ../  -DCLHEP_DIR=$SIMPATH_INSTALL -DWITH_GEANT4=TRUE -DGEANT4_INCLUDE_DIR=$G4INCLUDE -DGEANT4_LIB_DIR=$SIMPATH_INSTALL/lib -DWITH_ROOT=TRUE -DROOT_DIR=$SIMPATH_INSTALL -DCMAKE_INSTALL_PREFIX=$install_prefix -DWITH_TEST=OFF

  make -j$number_of_processes
  make install -j$number_of_processes
 
  if [ "$platform" = "macosx" ];
  then 
      cd $install_prefix/lib
      create_links dylib so
  fi

  check_success VGM $checkfile
  check=$?

  check_all_libraries $install_prefix/lib

fi

if [ "$platform" = "macosx" ];
then
  export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$install_prefix/lib
else
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$install_prefix/lib
fi

export USE_VGM=1
export VGM_INSTALL=$install_prefix

if [ "$system" = "64bit" ];
then
  CXXFLAGS=$CXXFLAGS_BAK
  CFLAGS=$CFLAGS_BAK
  export CXXFLAGS
  export CFLAGS
fi

cd $SIMPATH

return 1
