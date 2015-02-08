#!/bin/bash


function num_proc() {
  N=`cat /proc/cpuinfo |grep 'processor\s*:\s*\d*'|wc -l`
  logN=`echo "l($N)" | bc -l`
  echo $logN/1+1| bc
}

CLEANUP=false
[ '$1' == 'cleanup' ] && CLEANUP=true

export SHIPSOFT=/opt/xocean
export FAIRROOTPATH=$SHIPSOFT/FairRootInst
export SIMPATH=$SHIPSOFT/FairSoftInst
mkdir build
pushd build
cmake .. -DCMAKE_INSTALL_PREFIX=$FAIRROOTPATH -DCMAKE_BUILD_TYPE=RELEASE

NP=`num_proc`
make -j $NP &&  make install 

# cleanup
popd
$CLEANUP && rm -rf build
exit 0
