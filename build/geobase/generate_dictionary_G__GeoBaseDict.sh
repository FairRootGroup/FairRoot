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

/Users/turany/development/install/RC_may16_R6/bin/rootcint -f /Users/turany/development/FairRoot/build/geobase/G__GeoBaseDict.cxx -inlineInputHeader -rmf /Users/turany/development/FairRoot/build/lib/libGeoBase.rootmap -rml GeoBase.dylib -c   -I/Users/turany/development/FairRoot/fairtools -I/Users/turany/development/FairRoot/geobase -I/Users/turany/development/install/RC_may16_R6/include/root FairGeoAssembly.h FairGeoCone.h FairGeoCons.h FairGeoEltu.h FairGeoBuilder.h FairGeoInterface.h FairGeoIo.h FairGeoLoader.h FairGeoMatrix.h FairGeoMedia.h FairGeoMedium.h FairGeoNode.h FairGeoOldAsciiIo.h FairGeoPcon.h FairGeoPgon.h FairGeoRootBuilder.h FairGeoRotation.h FairGeoSet.h FairGeoShapes.h FairGeoSphe.h FairGeoTransform.h FairGeoTrap.h FairGeoTrd1.h FairGeoTube.h FairGeoTubs.h FairGeoTorus.h FairGeoVector.h FairGeoVolume.h FairGeoCompositeVolume.h FairGeoAsciiIo.h FairGeoBrik.h FairGeoBasicShape.h GeoBaseLinkDef.h
