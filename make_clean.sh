#!/bin/bash

# macro to emove all temporary files which are not needed after the
# installation of the external packages into a separate installation directory

export SIMPATH=$PWD
export PATH=$PATH:$SIMPATH/tools/root/bin

# Geant4 - remove complete buid directory
cd $SIMPATH/transport/geant4
if [ -d build ]; then
  rm -rf build
fi

# Geant3 - remove lib and temporary directory
cd $SIMPATH/transport/geant3
if [ -d lib ]; then
  rm -rf lib
fi
rm -rf tgt_*

# vgm - remove build directory
cd $SIMPATH/transport/vgm
if [ -d build_cmake ]; then
  rm -rf build_cmake
fi

# geant4_vmc - remove tmp, lib and include directories
cd $SIMPATH/transport/geant4_vmc
if [ -d tmp ]; then
  rm -rf tmp
fi
if [ -d lib ]; then
  rm -rf lib
fi
if [ -d include ]; then
  rm -rf include
fi

# Pluto - remove all unneeded files
cd $SIMPATH/generators/Pluto.5.37
make clean
make pluginclean

# Pythia6 - remove build directory
cd $SIMPATH/generators/pythia6
if [ -d build ]; then
  rm -rf build
fi

# Pythia8 - remove all unneeded files
cd $SIMPATH/generators/pythia8
make distclean

# Root - remove all unneeded files
cd $SIMPATH/tools/root
make distclean
