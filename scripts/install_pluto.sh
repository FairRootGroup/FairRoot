#!/bin/bash 

if [ ! -d  $SIMPATH/generators/pluto ];
then 
  cd $SIMPATH/generators
  if [ ! -e $PLUTOVERSION.tar.gz ];
  then
    echo "*** Downloading pluto sources ***"
    download_file $PLUTO_LOCATION/$PLUTOVERSION.tar.gz
  fi
  untar pluto $PLUTOVERSION.tar.gz 
  if [ -d $PLUTOVERSION ]; 
  then
    ln -s $PLUTOVERSION pluto  
  fi
fi 

if [ "$check" = "1" ];
then

  # special settings to compile pluto with gcc 4.0.X
  export FRIENDFLAG=""

  if [ "$compiler" = "gcc" ];
  then
    GCC_MAJOR=$(gcc -dumpversion | cut -c 1)
    GCC_MINOR=$(gcc -dumpversion | cut -c 3)
    if [ "$GCC_MAJOR" = "4" ]; 
    then
      if [ "$GCC_MINOR" != "0" ]; 
      then
        export FRIENDFLAG="-ffriend-injection"
      fi
    fi
  fi

  install_prefix=$SIMPATH_INSTALL
  checkfile=$install_prefix/lib/libPluto.so

  cd $SIMPATH/generators

  if (not_there pluto $checkfile);
  then
    cd pluto
    case $PLUTOVERSION in
	*412*)  echo Compiling Old Pluto Version
	    patch -p0 < ../pluto_v412.patch | tee -a $logfile
	    ;;
	*5.33*)  echo Compiling v5.33 Pluto Version
            cp ../Makefile_pluto5 Makefile
            cp ../newline.awk .
	    patch -p0 < ../pluto_v533.patch | tee -a $logfile
            ;;
	*5.36*)  echo Compiling v5.36 Pluto Version
            cp Makefile.fairsoft Makefile
            ;;
	*5.37*)  echo Compiling v5.37 Pluto Version
            cp Makefile.fairsoft Makefile
	    patch -p0 < ../pluto_v537.patch | tee -a $logfile
            # needed to compile with Apple LLVM 5.1, shouldn't hurt on other systems
            patch -p0 < ../pluto_friend.patch | tee -a $logfile
            ;;
	*5.4*)  echo Compiling v5.4x Pluto Version
            cp Makefile.fairsoft Makefile
            ;;
	*CVS*)  echo Compiling CVS Pluto Version
	    cp Makefile.fairsoft Makefile
	    ;; 
    esac

    if [ "$compiler" = "intel" ];
    then
      mysed 'g++' 'icpc' Makefile 
    fi
    if [ "$compiler" = "Clang" ];
    then
      mysed 'g++' 'clang++' Makefile 
      mysed '-rdynamic' '' Makefile 
    fi
    mysed "CXXFLAGS      = -Wall" "CXXFLAGS      = -Wall ${CXXFLAGS}"  Makefile
    mysed "SOFLAGS       =" "SOFLAGS       = ${CXXFLAGS}" Makefile
    if [ "$platform" = "macosx" ];
    then
      mysed  '-g -shared -Wl,-soname,$@' ' -dynamiclib -flat_namespace -single_module -undefined dynamic_lookup' Makefile
      mysed  'LIBSO         = libPluto.so' 'LIBSO         = libPluto.dylib' Makefile
    fi
    if [ "$system" = "64bit" ];
    then
      mysed 'SOFLAGS       =' 'SOFLAGS       = -m64' Makefile
      mysed 'CXXFLAGS      = -Wall' 'CXXFLAGS      = -Wall -m64' Makefile
    fi
  
    make
    
    # fake make install
    mkdir -p $install_prefix/lib
    cp libPluto.a $install_prefix/lib
    mkdir -p $install_prefix/include/pluto
    cp src/*.h $install_prefix/include/pluto
    find plugins -name "*.h" -exec cp "{}" $install_prefix/include/pluto ";" 
    if [ "$platform" = "macosx" ];
    then
      cp libPluto.dylib $install_prefix/lib
      cd $install_prefix/lib
      create_links dylib so
    else
      cp libPluto.so $install_prefix/lib
    fi

    check_all_libraries $install_prefix/lib

    check_success Pluto $checkfile
    check=$?

  fi
fi

cd $SIMPATH

return 1
