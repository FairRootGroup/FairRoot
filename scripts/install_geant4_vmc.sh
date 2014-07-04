#!/bin/bash


if [ ! -d  $SIMPATH/transport/geant4_vmc ]; then
  cd $SIMPATH/transport
  git clone $GEANT4VMC_LOCATION
fi

cd $SIMPATH/transport/geant4_vmc
git checkout $GEANT4VMCBRANCH
git reset $GEANT4VMCVERSION
    
install_prefix=$SIMPATH_INSTALL
checkfile=$install_prefix/lib/libgeant4vmc.so

if (not_there Geant4_VMC $checkfile);
then

  cd $SIMPATH/transport/geant4_vmc

  patch -p0 < ../Geant4_vmc_c++11.patch
  
  cd $SIMPATH/transport/geant4_vmc/g4root
  make -j$number_of_processes

  cd $SIMPATH/transport/geant4_vmc/source
  cp $SIMPATH/transport/Makefile_geant4vmc Makefile

  make -j$number_of_processes

  # fake make install
  architecture=$(root-config --arch)
  cd $SIMPATH/transport/geant4_vmc/lib/tgt_$architecture
  mkdir -p $install_prefix/lib
  cp * $install_prefix/lib 
  cd $SIMPATH/transport/geant4_vmc/include
  mkdir -p $install_prefix/include/geant4vmc
  cp g4root/* $install_prefix/include/geant4vmc
  cp geant4vmc/* $install_prefix/include/geant4vmc
  mkdir -p $install_prefix/share/geant4_vmc/macro
  cp $SIMPATH/transport/macro/* $install_prefix/share/geant4_vmc/macro

  if [ "$platform" = "macosx" ];
  then
    cd $install_prefix/lib
    create_links dylib so
  fi

  check_success Geant4_VMC $checkfile
  check=$?

  check_all_libraries $install_prefix/lib

fi

if [ "$platform" = "macosx" ];
then
  export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$SIMPATH/transport/geant4_vmc/lib/
else
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SIMPATH/transport/geant4_vmc/lib/
fi

cd $SIMPATH

return 1
