#!/bin/bash


function num_proc() {
  N=`cat /proc/cpuinfo |grep 'processor\s*:\s*\d*'|wc -l`
  logN=`echo "l($N)" | bc -l`
  echo $logN/1+1| bc
}

CLEANUP=false
[ '$1' == 'cleanup' ] && CLEANUP=true && shift

#export SHIPSOFT=/opt/xocean
[ -z "$SHIPSOFT" ] && echo "No SHIPSOFT env defined" && exit 1
#export FAIRROOTPATH=$SHIPSOFT/FairRootInst
#export SIMPATH=$SHIPSOFT/FairSoftInst
if [ -f $SIMPATH/bin/thisroot.sh ] ; then
  . $SIMPATH/bin/thisroot.sh
fi
mkdir build
pushd build
cmake .. -DCMAKE_INSTALL_PREFIX=$FAIRROOTPATH -DCMAKE_BUILD_TYPE=RELEASE -DUSE_DIFFERENT_COMPILER=TRUE

NP=`num_proc`
make -j $NP &&  make install 

# cleanup
popd
$CLEANUP && rm -rf build
exit 0
