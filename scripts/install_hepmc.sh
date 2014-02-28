#!/bin/bash

if [ ! -d  $SIMPATH/generators/HepMC ];
then 
  cd $SIMPATH/generators
  if [ ! -e HepMC-$HEPMCVERSION.tar.gz ];
  then
    echo "*** Downloading hepmc sources ***"
    download_file $HEPMC_LOCATION/HepMC-$HEPMCVERSION.tar.gz
  fi
  untar hepmc HepMC-$HEPMCVERSION.tar.gz
  if [ -d HepMC-$HEPMCVERSION ]; 
  then
    ln -s HepMC-$HEPMCVERSION HepMC
  fi
fi 

install_prefix=$SIMPATH_INSTALL
checkfile=$install_prefix/lib/libHepMC.a

if [ ! -d $install_prefix/lib ];
then
  mkdir -p $install_prefix/lib
fi
  
if (not_there hepmc $checkfile)
then
  
  cd $SIMPATH/generators

  mkdir build_HepMC
  cd build_HepMC
        
  cmake -DCMAKE_INSTALL_PREFIX=$install_prefix -Dmomentum:STRING=GEV -Dlength:STRING=CM ../HepMC

  make install -j$number_of_processes
 
  if [ "$platform" = "macosx" ];
  then 
      cd $install_prefix/lib
      create_links dylib so
  fi

  check_success hepmc $checkfile
  check=$?

  check_all_libraries $install_prefix/lib

fi

export HEPINSTALLDIR=$install_prefix 

if [ "$platform" = "macosx" ];
then
  export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$install_prefix/lib
else
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$install_prefix/lib
fi

cd $SIMPATH

return 1
