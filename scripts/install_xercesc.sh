#!/bin/bash

# Check if the source tar file is already available
# If not download it a from the geant4 web server and
# unpack it


if [ ! -d  $SIMPATH/basics/xercesc ];
then
  cd $SIMPATH/basics
  if [ ! -e  xerces-c-$XERCESCVERSION.tar.gz ];
  then
    echo "*** Downloading xerces-c sources ***"
    download_file $XERCESC_LOCATION/xerces-c-$XERCESCVERSION.tar.gz
  fi
  untar xercesc xerces-c-$XERCESCVERSION.tar.gz
  if [ -d xerces-c-$XERCESCVERSION ];
  then
    ln -s xerces-c-$XERCESCVERSION xercesc
  fi
fi

install_prefix=$SIMPATH_INSTALL
checkfile=$install_prefix/lib/libxerces-c-3.1.so


if (not_there XercesC $checkfile);
then

  cd $SIMPATH/basics/xercesc

  patch -p0 < ../xerces-c-3.1.1_fixcast.patch
  
  LDFLAGS_BAK=$LDFLAGS
  if [ "$compiler" = "Clang" -a "$platform" = "linux" ]; then
    LDFLAGS=$CXXFLAGS
    LIBS=$CXXFLAGS

    ./configure --prefix=$install_prefix --with-icu=$install_prefix

    mysed "-lstdc++" "-lc++" libtool
  else
    ./configure --prefix=$install_prefix 
  fi
    
  $MAKE_command -j$number_of_processes  install



  if [ "$platform" = "macosx" ];
  then
    cd $install_prefix/lib
    create_links dylib so
  fi
              
  check_success XercesC $checkfile
  check=$?
      
  LDFLAGS=$LDFLAGS_BAK   
        
fi

cd  $SIMPATH
return 1
