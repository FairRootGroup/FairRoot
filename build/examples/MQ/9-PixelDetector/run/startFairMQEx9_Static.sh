#!/bin/bash

# Setup the needed environment
export LD_LIBRARY_PATH=/Users/turany/development/FairRoot/build/lib:/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib
export DYLD_LIBRARY_PATH=/Users/turany/development/FairRoot/build/lib:/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib
export PATH=/Users/turany/development/install/RC_may16_R6//bin:$PATH:
export ROOTSYS=/Users/turany/development/install/RC_may16_R6
export ROOTEXE=/Users/turany/development/install/RC_may16_R6/bin/root.exe
export ROOT_INCLUDE_PATH=
export VMCWORKDIR=/Users/turany/development/FairRoot/examples
export GEANT4VMC_MACRO_DIR=/Users/turany/development/install/RC_may16_R6/share/geant4_vmc/macro
export USE_VGM=1
export BOOST=1
export G4LEDATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/G4EMLOW"
export G4LEVELGAMMADATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/PhotonEvaporation"
export G4NeutronHPCrossSections="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/G4NDL"
export G4NEUTRONHPDATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/G4NDL"
export G4NEUTRONXSDATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/G4NEUTRONXS"
export G4PIIDATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/G4PII"
export G4RADIOACTIVEDATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/RadioactiveDecay"
export G4REALSURFACEDATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/RealSurface"
export G4SAIDXSDATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/G4SAIDDATA"
export G4ENSDFSTATEDATA="/Users/turany/development/install/RC_may16_R6/share/Geant4/data/G4ENSDFSTATE"
export G3SYS="/Users/turany/development/install/RC_may16_R6/share/geant3"
export PYTHIA8DATA=""
if [ -e /env.sh ]; then
  . /env.sh
fi

cd /Users/turany/development/FairRoot/build/examples/MQ/9-PixelDetector/run

source  /Users/turany/development/FairRoot/build/bin/examples/MQ/9-PixelDetector/startFairMQEx9_Static.sh
