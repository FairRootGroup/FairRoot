#!/bin/bash


if [ ! -d  $SIMPATH/basics/$MESAVERSION ];
then
  cd $SIMPATH/basics
  if [ ! -e $MESAVERSION.tar.bz2 ];
  then
    echo "*** Downloading gtest sources ***"
    download_file $MESA_LOCATION/$MESAVERSION.tar.bz2
  fi
  untar mesa $MESAVERSION.tar.bz2
  if [ -d  Mesa-7.10.3 ]; 
  then
    ln -s Mesa-7.10.3 mesa 
  fi
fi
    
install_prefix=$SIMPATH_INSTALL

checkfile=$install_prefix/lib/libGLU.so

if (not_there mesa $checkfile);
then
    cd $SIMPATH/basics/mesa

    if [ "$platform" = "linux" -a "$compiler" = "Clang" ]; then
      patch -p0 < ../mesa_clang.patch
      LDFLAGS="-stdlib=libc++" ./configure --prefix=$install_prefix --with-driver=xlib --disable-gallium
    else
      ./configure --prefix=$install_prefix --with-driver=xlib --disable-gallium
    fi
        
    LDFLAGS="-stdlib=libc++" make -j$number_of_processes

    make install

    check_all_libraries  $install_prefix/lib

    check_success icu $checkfile
    check=$?
  
    unset LDFLAGS
fi

cd $SIMPATH

return 1
