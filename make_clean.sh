#!/bin/bash

# macro to emove all temporary files which are not needed after the
# installation of the external packages into a separate installation directory

export SIMPATH=$PWD

source scripts/package_versions.sh

# Geant4 - remove complete buid directory
cd $SIMPATH/transport
if [ -d geant4 ]; then
  rm -rf geant4
fi

# Geant3 - remove lib and temporary directory
cd $SIMPATH/transport
if [ -d geant3 ]; then
  rm -rf geant3
fi

# vgm - remove build directory
cd $SIMPATH/transport/vgm
if [ -d build_cmake ]; then
  rm -rf build_cmake
fi

# geant4_vmc - remove tmp, lib and include directories
# vgm - remove build directory
cd $SIMPATH/transport
if [ -d geant4_vmc ]; then
  rm -rf geant4_vmc
fi

# Pluto - remove all unneeded files
cd $SIMPATH/generators
if [ -d $PLUTOVERSION ]; then
  rm -rf $PLUTOVERSION
fi
if [ -h pluto ]; then
  rm -rf pluto
fi

# Pythia6 - remove build directory
cd $SIMPATH/generators
if [ -d pythia6 ]; then
  rm -rf pythia6
fi

# Pythia8 - remove all unneeded files
cd $SIMPATH/generators
if [ -d $PYTHIA8VERSION ]; then
  rm -rf $PYTHIA8VERSION
fi
if [ -h pythia8 ]; then
  rm -rf pythia8
fi

# HepMC - remove all unneeded files
cd $SIMPATH/generators
if [ -d HepMC-$HEPMCVERSION ]; then
  rm -rf HepMC-$HEPMCVERSION
fi
if [ -d build_HepMC ]; then
  rm -rf build_HepMC
fi
if [ -h HepMC ]; then
  rm -rf HepMC
fi

#  Boost remove all unneeded files
cd $SIMPATH/basics
if [ -d $BOOSTVERSION ]; then
  rm -rf $BOOSTVERSION
fi
if [ -h boost ]; then
  rm -rf boost
fi

#  CMake remove all unneeded files
cd $SIMPATH/basics
if [ -d $CMAKEVERSION ]; then
  rm -rf $CMAKEVERSION
fi
if [ -h cmake ]; then
  rm -rf  cmake
fi

#  GSL remove all unneeded files
cd $SIMPATH/basics
if [ -d $GSLVERSION ]; then
  rm -rf $GSLVERSION
fi
if [ -h gsl ]; then
  rm -rf gsl
fi

#  GTest remove all unneeded files
cd $SIMPATH/basics
if [ -d $GTESTVERSION ]; then
  rm -rf $GTESTVERSION
fi
if [ -h gtest ]; then
  rm -rf gtest
fi

#  ZeroMQ remove all unneeded files
cd $SIMPATH/basics
if [ -d zeromq-$ZEROMQVERSION ]; then
  rm -rf zeromq-$ZEROMQVERSION
fi
if [ -h zeromq ]; then
  rm -rf zeromq
fi

# millepede 
cd $SIMPATH/basics/MillepedeII
if [ -d  build ]; then
  rm -rf build
fi
rm  pede
rm *.mod
rm *.o  


# Root - remove all unneeded files
cd $SIMPATH/tools
if [ -d root ]; then
  rm -rf root
fi


set +xv
exit
