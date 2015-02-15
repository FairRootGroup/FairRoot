#!/bin/bash


function num_proc() {
  N=`cat /proc/cpuinfo |grep 'processor\s*:\s*\d*'|wc -l`
  logN=`echo "l($N)" | bc -l`
  echo $logN/1+1| bc
}

function halt() {
  echo $1
  exit 1
}

CLEANUP=false
[ '$1' == 'cleanup' ] && CLEANUP=true && shift

[ -z "$SIMPATH" ] && halt "No SIMPATH env defined"
[ -z "$FAIRROOTPATH" ] && halt "No FAIRROOTPATH env defined"
[ -f $SIMPATH/bin/thisroot.sh ] && source $SIMPATH/bin/thisroot.sh
mkdir build
pushd build
cmake .. -DCMAKE_INSTALL_PREFIX=$FAIRROOTPATH -DCMAKE_BUILD_TYPE=RELEASE -DUSE_DIFFERENT_COMPILER=TRUE

NP=`num_proc`
echo NP: $NP
make -j $NP || halt "make failed"
make install || halt "make install failed"

# cleanup
popd
$CLEANUP && rm -rf build
exit 0
