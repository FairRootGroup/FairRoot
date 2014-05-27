#!/bin/bash

if [ ! -d  $SIMPATH/generators/pythia8 ];
then 
  cd $SIMPATH/generators
  if [ ! -e $PYTHIA8VERSION.tgz ];
  then
    echo "*** Downloading pythia8 sources ***"
    download_file $PYTHIA8_LOCATION/$PYTHIA8VERSION.tgz
  fi
  untar pythia8 $PYTHIA8VERSION.tgz
  if [ -d $PYTHIA8VERSION ]; 
  then
    ln -s $PYTHIA8VERSION pythia8
  fi
fi 

install_prefix=$SIMPATH_INSTALL
checkfile=$install_prefix/lib/libpythia8.so

if [ ! -d $install_prefix/lib ];
then
  mkdir -p $install_prefix/lib
fi

if (not_there pythia8 $checkfile)
then

  cd $SIMPATH/generators/pythia8

  # needed to compile with Apple LLVM 5.1, shouldn't hurt on other systems
  patch -p0 < ../pythia8_friend.patch | tee -a $logfile
  
  USRLDFLAGSSHARED="$CXXFLAGS" ./configure  --enable-shared --with-hepmc=$HEPINSTALLDIR --with-hepmcversion=$HEPMCVERSION

  if [ "$compiler" = "PGI" ];
  then
    mysed "FC = gfortran" "FC = pgfortran" config.mk  
    mysed "CC = gcc" "CC = pgCC" config.mk  
    mysed "FFLAGS = -O2" "FFLAGS=${FFLAGS}" config.mk
    mysed "CFLAGS = -O2" "CFLAGS=${CFLAGS}" config.mk
    mysed "CXXFLAGS = -O2 -ansi -pedantic -W -Wall -Wshadow" "CXXFLAGS=${CXXFLAGS}" config.mk
    mysed "CXXFLAGSNO = -O2 -ansi -pedantic -W -Wall" "CXXFLAGSNO=${CXXFLAGS}" config.mk
    mysed "FLIBS = -lgfortran -lgfortranbegin" "" config.mk
    mysed "LDFLAGSSHARED = -O2 -ansi -pedantic -W -Wall -Wshadow -pthread -fPIC -shared" "LDFLAGSSHARED=${CXXFLAGS} -fPIC -shared " config.mk
  fi

  if [ "$system" = "64bit" ];
  then
   $MAKE_command -j$number_of_processes CFLAGS="$CFLAGS -m64" CXXFLAGS="$CXXFLAGS -m64"  
  else 
   $MAKE_command -j$number_of_processes CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS"    
  fi
  
  mkdir -p $install_prefix/include
  cp -r include/Pythia8 $install_prefix/include
 
  mkdir -p $install_prefix/share/pythia8
  cp -r xmldoc $install_prefix/share/pythia8
 
  if [ "$platform" = "macosx" ];
  then
    cp lib/libpythia8.dylib $install_prefix/lib
    cp lib/liblhapdfdummy.dylib $install_prefix/lib 
    cp lib/libpythia8tohepmc.dylib $install_prefix/lib
    cd $install_prefix/lib
    create_links dylib so
  else
    cp lib/libpythia8.so $install_prefix/lib
    cp lib/liblhapdfdummy.so $install_prefix/lib 
    cp lib/libpythia8tohepmc.so $install_prefix/lib
  fi

  check_all_libraries $install_prefix/lib

  check_success pythia8 $checkfile
  check=$?
fi

if [ "$platform" = "macosx" ];
then
  export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$install_prefix/lib
else
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$install_prefix/lib
fi

cd $SIMPATH

return 1
