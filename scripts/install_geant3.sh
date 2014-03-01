#!/bin/bash
#export CXXVERBOSE=1

if [ ! -d  $SIMPATH/transport/geant3 ];
then 
  cd $SIMPATH/transport
  if [ ! -e $GEANT3VERSION.tar.gz ];
  then
    echo "*** Downloading geant3 sources ***"
    download_file $GEANT3_LOCATION/$GEANT3VERSION.tar.gz
  fi
  untar geant3 $GEANT3VERSION.tar.gz 
fi 

install_prefix=$SIMPATH_INSTALL
checkfile=$install_prefix/lib/libgeant321.so

if (not_there Geant3 $checkfile);
then
  cd $SIMPATH/transport
  cp gdecay.F geant3/gphys
  cp gdalet.F geant3/gphys
  cp gdalitzcbm.F geant3/gphys
  cd geant3 

  # patch to correctly install geant3 on linuxx8664icc 
  patch -p0 < ../Makefile_geant3.patch | tee -a $logfile
  patch -p0 < ../geant3_geane.patch | tee -a $logfile
  	
  if [ "$platform" = "macosx" ];
  then
    patch -p0 < ../Makefile_geant3_macos.patch | tee -a $logfile
  fi
          
            # install gcalor only on 32bit and 64bit machines
  # The probem is fixed in the new version of gcalor which comes with fairsoft
  mkdir gcalor
  cp ../gcalor.F gcalor
  if [ ! -f ../xsneut.dat ]; 
  then
    bunzip2 ../xsneut.dat.bz2          
  fi
  cp ../xsneut.dat data
  cp ../chetc.dat data
  mysed 'minicern gdraw' 'minicern gdraw gcalor' Makefile

  make 

  # fake make install
  mkdir -p $install_prefix/lib
  cp $SIMPATH/transport/geant3/lib/tgt_$arch/libgeant321.so $install_prefix/lib
  mkdir -p $install_prefix/include/TGeant3
  cp $SIMPATH/transport/geant3/TGeant3/*.h $install_prefix/include/TGeant3

  mkdir -p $install_prefix/share/geant3
  cp -r $SIMPATH/transport/geant3/data $install_prefix/share/geant3
                           
  check_all_libraries $install_prefix/lib

  check_success Geant3 $checkfile
  check=$?

fi

if [ "$platform" = "macosx" ];
then
  export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$install_prefix
else
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SIMPATH/install_prefix
fi

cd $SIMPATH

return 1
