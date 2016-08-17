#!/bin/bash

# This macro is needed to start the Root macros used for automatic testing
# from inside CMake using the add_test functionality. Since the tests 
# starts with a fresh environment on has to set first the correct environment
# needed to run FairRoot.
# Also parameters defined in add_test will be converted in the correct format
# to be passed to root.

# Setup the needed environment
export LD_LIBRARY_PATH=/Users/turany/development/FairRoot/build/lib:/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib
export DYLD_LIBRARY_PATH=/Users/turany/development/FairRoot/build/lib:/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib:/Users/turany/development/install/RC_may16_R6/lib
export PATH=/Users/turany/development/install/RC_may16_R6//bin:$PATH:
export ROOTSYS=/Users/turany/development/install/RC_may16_R6
export ROOTEXE=/Users/turany/development/install/RC_may16_R6/bin/root.exe
export ROOT_INCLUDE_PATH=/Users/turany/development/FairRoot/fairtools:/Users/turany/development/FairRoot/geobase:/Users/turany/development/FairRoot/parbase:/Users/turany/development/FairRoot/base:/Users/turany/development/FairRoot/base/steer:/Users/turany/development/FairRoot/base/event:/Users/turany/development/FairRoot/base/field:/Users/turany/development/FairRoot/base/sim:/Users/turany/development/FairRoot/base/source:/Users/turany/development/FairRoot/dbase:/Users/turany/development/FairRoot/dbase/dbInterface:/Users/turany/development/FairRoot/dbase/dbValidation:/Users/turany/development/FairRoot/dbase/dbUtils:/Users/turany/development/FairRoot/input/db:/Users/turany/development/FairRoot/dbase/dbInput:/Users/turany/development/FairRoot/dbase/dbIO
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

# Concatenate all parameters given on the command line to one 
# comma separated string 
parameters=""
for i in $*; do 
  if [ -z $parameters ]; then
    parameters=$i
  else
    parameters=$(echo "$parameters,$i")
  fi 
done

cd /Users/turany/development/FairRoot/build/examples/simulation/rutherford/macros

# execute root with the defined macro and the command line parameters
$ROOTEXE -q -b /Users/turany/development/FairRoot/examples/simulation/rutherford/macros/run_rad.C\($parameters\)
