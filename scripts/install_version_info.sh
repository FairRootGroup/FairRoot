#!/bin/bash

# script uses cmake to extract SVN information of the current source

mkdir -p $SIMPATH/test/build
cd $SIMPATH/test

cp $SIMPATH/scripts/FairVersion.h.* .
cp $SIMPATH/scripts/GenerateVersionInfo.cmake .
cp $SIMPATH/scripts/Test_CMakeLists.txt CMakeLists.txt

cd build
cmake .. 

#rm -rf $SIMPATH/build

cd $SIMPATH
