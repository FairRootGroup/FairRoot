#!/bin/bash

# Check if the source tar file is already available
# If not download it a from the geant4 web server and
# unpack it


if [ ! -d  $SIMPATH/transport/geant4 ];
then 
  cd $SIMPATH/transport
  if [ ! -e $GEANT4VERSION.tar.gz ];
  then
    echo "*** Downloading geant4 sources ***"
    download_file $GEANT4_LOCATION/$GEANT4VERSION.tar.gz
  fi
  untar geant4 $GEANT4VERSION.tar.gz 
  if [ -d $GEANT4VERSION ]; 
  then
    ln -s $GEANT4VERSION geant4  
  fi
fi 

# Full output during compilation and linking to check for the
# compile and link commands
#export CPPVERBOSE=1

install_prefix=$SIMPATH_INSTALL
clhep_exe=$SIMPATH_INSTALL/bin/clhep-config

checkfile=$install_prefix/lib/libG4physicslists.so

if (not_there Geant4-lib $checkfile);
then

  cd $SIMPATH/transport/geant4/
  
  if [ -f ../${GEANT4VERSION}_c++11.patch ]; then
    patch -p0 < ../${GEANT4VERSION}_c++11.patch | tee -a $logfile
  fi

  if [ "$platform" = "linux" -a "$compiler" = "Clang" ]; then
    patch -p0 < ../geant4.10.00_clang_linux.patch
  fi
  
  if (not_there Geant4-build  $G4WORKDIR/build);
  then 
    mkdir build
  fi 
  cd build
  
  if [ "$geant4_download_install_data_automatic" = "yes" ];
  then
    install_data="-DGEANT4_INSTALL_DATA=ON"
  else
    install_data=""
  fi

  if [ "$build_cpp11" = "yes" ];
  then
    geant4_cpp="-DGEANT4_BUILD_CXXSTD=c++11"
  else
    geant4_cpp=""
  fi

  if [ "$build_python" = "yes" ];
  then
    geant4_opengl="-DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_GDML=ON -DXERCESC_ROOT_DIR=$install_prefix" 
  else   
    geant4_opengl=""
  fi

  cmake -DCMAKE_INSTALL_PREFIX=$install_prefix \
        -DCMAKE_INSTALL_LIBDIR=$install_prefix/lib \
        -DGEANT4_USE_G3TOG4=ON \
        -DGEANT4_BUILD_STORE_TRAJECTORY=OFF \
        -DGEANT4_BUILD_VERBOSE_CODE=ON \
        $geant4_opengl \
        $install_data  $geant4_cpp ../

  $MAKE_command -j$number_of_processes  install

  # copy the env.sh script to the bin directorry
  mkdir -p $install_prefix/bin
 # cp $G4WORKDIR/env.sh $install_prefix/bin
  
  if [ "$platform" = "macosx" ];
  then
    cd $install_prefix/lib
    create_links dylib so
  fi

  if [ "$geant4_download_install_data_automatic" = "yes" ];
  then
    # create unique links which is independent of the Geant4 version  
    if [ ! -L $install_prefix/share/Geant4 ]; then
      ln -s $install_prefix/share/$GEANT4VERSIONp $install_prefix/share/Geant4
    fi
    # create unique links for the data directories which are
    # independent of the actual data versions
    if [ ! -L $install_prefix/share/Geant4/data/G4ABLA ]; then
      ln -s $install_prefix/share/Geant4/data/${G4ABLA_VERSION} $install_prefix/share/Geant4/data/G4ABLA
    fi
    if [ ! -L $install_prefix/share/Geant4/data/G4EMLOW ]; then
      ln -s $install_prefix/share/Geant4/data/${G4EMLOW_VERSION} $install_prefix/share/Geant4/data/G4EMLOW
    fi
    if [ ! -L $install_prefix/share/Geant4/data/G4ENSDFSTATE ]; then
      ln -s $install_prefix/share/Geant4/data/${G4ENSDFSTATE_VERSION} $install_prefix/share/Geant4/data/G4ENSDFSTATE
    fi
    if [ ! -L $install_prefix/share/Geant4/data/G4NDL ]; then
      ln -s $install_prefix/share/Geant4/data/${G4NDL_VERSION} $install_prefix/share/Geant4/data/G4NDL
    fi
    if [ ! -L $install_prefix/share/Geant4/data/G4NEUTRONXS ]; then
      ln -s $install_prefix/share/Geant4/data/${G4NEUTRONXS_VERSION} $install_prefix/share/Geant4/data/G4NEUTRONXS
    fi
    if [ ! -L $install_prefix/share/Geant4/data/G4PII ]; then
      ln -s $install_prefix/share/Geant4/data/${G4PII_VERSION} $install_prefix/share/Geant4/data/G4PII
    fi
    if [ ! -L $install_prefix/share/Geant4/data/G4SAIDDATA ]; then
      ln -s $install_prefix/share/Geant4/data/${G4SAIDDATA_VERSION} $install_prefix/share/Geant4/data/G4SAIDDATA
    fi
    if [ ! -L $install_prefix/share/Geant4/data/PhotonEvaporation ]; then
      ln -s $install_prefix/share/Geant4/data/${PhotonEvaporation_VERSION} $install_prefix/share/Geant4/data/PhotonEvaporation
    fi
    if [ ! -L $install_prefix/share/Geant4/data/RadioactiveDecay ]; then
      ln -s $install_prefix/share/Geant4/data/${RadioactiveDecay_VERSION} $install_prefix/share/Geant4/data/RadioactiveDecay
    fi
    if [ ! -L $install_prefix/share/Geant4/data/RealSurface ]; then
      ln -s $install_prefix/share/Geant4/data/${RealSurface_VERSION} $install_prefix/share/Geant4/data/RealSurface
    fi
    
  fi
              
  . $install_prefix/share/$GEANT4VERSIONp/geant4make/geant4make.sh
  
  check_success geant4 $checkfile
  check=$?

else
   
  . $install_prefix/share/$GEANT4VERSIONp/geant4make/geant4make.sh

fi
  
cd  $SIMPATH
return 1
