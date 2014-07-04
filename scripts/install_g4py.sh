#!/bin/bash

install_prefix=$SIMPATH_INSTALL

checkfile=$install_prefix/lib/g4py/__init__.pyc

if (not_there g4py $checkfile);
then

    if [ ! -e $SIMPATH_INSTALL/lib64 ]; then
      cd $SIMPATH_INSTALL
      ln -s lib lib64
    fi
      
    cd $SIMPATH/transport/geant4/environments/g4py
    patch -p0 < ../../../g4py.patch


    cd $SIMPATH/transport/geant4
    mkdir build_g4py
    cd build_g4py
    
    cmake ../environments/g4py \
          -DXERCESC_ROOT_DIR=${SIMPATH_INSTALL}  \
          -DBOOST_ROOT=${SIMPATH_INSTALL} \
          -DBoost_NO_SYSTEM_PATHS=TRUE \
          -DBoost_NO_BOOST_CMAKE=TRUE
      
    $MAKE_command -j$number_of_processes
    $MAKE_command install -j$number_of_processes

    if [ "$platform" = "macosx" ];
    then
      cd  $install_prefix/lib
      create_links dylib so
    fi
    
    check_all_libraries  $install_prefix/lib

    check_success g4py $checkfile
    check=$?
    
fi

cd $SIMPATH

return 1
