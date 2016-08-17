#!/bin/bash

# This macro is used to generate the ROOT dictionaries
# To use the ctest launchers one needs some environment variables which
# are only present when running CMake. To have the same environment at
# the time the dictionary is build this script is used which is build
# at the time cmake runs.

# Setup the needed environment
export LD_LIBRARY_PATH=/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/FairRoot/build/lib:/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/install/RC_may16_R6/lib
export DYLD_LIBRARY_PATH=/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/FairRoot/build/lib:/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/install/RC_may16_R6/lib
export ROOTSYS=/Users/turany/development/install/RC_may16_R6

/Users/turany/development/install/RC_may16_R6/bin/rootcint -f /Users/turany/development/FairRoot/build/generators/G__GenDict.cxx -inlineInputHeader -rmf /Users/turany/development/FairRoot/build/lib/libGen.rootmap -rml Gen.dylib -c   -I/Users/turany/development/FairRoot/fairtools -I/Users/turany/development/FairRoot/geobase -I/Users/turany/development/FairRoot/field -I/Users/turany/development/FairRoot/base -I/Users/turany/development/FairRoot/base/steer -I/Users/turany/development/FairRoot/base/event -I/Users/turany/development/FairRoot/base/field -I/Users/turany/development/FairRoot/base/sim -I/Users/turany/development/FairRoot/generators -I/Users/turany/development/install/RC_may16_R6/include/root FairAsciiGenerator.h FairBoxGenerator.h FairIonGenerator.h FairParticleGenerator.h FairShieldGenerator.h FairUrqmdGenerator.h FairEvtGenGenerator.h GenLinkDef.h
