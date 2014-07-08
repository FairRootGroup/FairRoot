#!/bin/bash

# check if the root source directory is already available
# If it is not there get the source tar file from the 
# root web server and unpack it

if [ "$build_cpp11" = "yes" ];
then
  CXXFLAGS_BAK=$CXXFLAGS
  CXXFLAGS="$CFLAGS"
  export CXXFLAGS
fi

if [ ! -d  $SIMPATH/tools/root ];
then
  cd $SIMPATH/tools
  git clone $ROOT_LOCATION
fi
cd $SIMPATH/tools/root
git checkout $ROOTBRANCH
git reset $ROOTVERSION
                    
#if [ ! -d  $SIMPATH/tools/root ];
#then 
#  cd $SIMPATH/tools
#  if [ ! -e root_$ROOTVERSION.source.tar.gz ];
#  then
#    echo "*** Downloading root sources ***"
#    download_file $ROOT_LOCATION/root_$ROOTVERSION.source.tar.gz
#  fi
#  untar root root_$ROOTVERSION.source.tar.gz
#fi 


install_prefix=$SIMPATH_INSTALL
libdir=$install_prefix/lib/root

checkfile=$install_prefix/bin/root.exe

if [ "$platform" = "macosx" ];
then
  export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}
else
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}
fi


if (not_there root $checkfile);
then          
  cd $SIMPATH/tools/root

  # special patch for Fedora 16 on 32bit
  # This should go into root
  cat /etc/issue | grep "Fedora release 16 (Verne)"
  result=$?
  if [ "$result" = "0" ];then
    if [ "$system" = "32bit" ]; then
      echo "*** Applying patch needed for Fedora 16 32bit " | tee -a $logfile
      patch -p0 < ../root_fedora16_32bit.patch  
    fi
  fi
  if [ "$debug" = "yes" ];
  then
    echo "*** Building ROOT with debug information"  | tee -a $logfile
    export ROOTBUILD=debug
  fi

  if [ "$compiler" = "intel" -a "$icc_version" = "10" ];
  then
    echo "*** Patching Makfiles.linuxicc " | tee -a $logfile
    cp ../Makefile.linuxicc config
  fi

  if [ "$build_for_grid" = "yes" ]
  then
    cp ../rootconfig_grid.sh  rootconfig.sh
    echo "Copied rootconfig_grid.sh ......................" | tee -a $logfile
  else
    cp ../rootconfig.sh  .
    echo "Copied rootconfig.sh ......................" | tee -a $logfile
  fi
  echo "Configure Root .........................................." | tee -a $logfile
  if [ "$platform" = "solaris" ];
  then 
    mysed "awk" "gawk" configure
    chmod a+x configure
    cp ../makelib.sh build/unix
    if [ "$compiler" = "gcc" ];
    then
      cp ../Makefile.solarisgcc config 
      if [ "$system" = "64bit" ];
      then
        mysed '-fPIC' '-fPIC -m64' config/Makefile.solarisgcc	  
        mysed '$(EXTRA_LDFLAGS)' '$(EXTRA_LDFLAGS) -m64' config/Makefile.solarisgcc
     fi    
    else
      cp ../Makefile.solarisCC5 config 
      if [ "$system" = "64bit" ];
      then
        mysed '-KPIC' '-KPIC -m64' config/Makefile.solarisCC5	  	  
        mysed '$(EXTRA_LDFLAGS)' '$(EXTRA_LDFLAGS) -m64' config/Makefile.solarisCC5
      fi    
    fi
  fi
  # actualy one should check for mac os x 10.8 
  if [ "$platform" = "macosx" -a "$compiler" = "Clang" ];
  then
    mysed 'DEBUGFLAGS    = -g$(DWARF2)' 'DEBUGFLAGS    =' config/Makefile.macosx64	  	  
    mysed 'LDFLAGS       = $(OPT) -m64 -mmacosx-version-min=$(MACOSXVERS)' 'LDFLAGS       = -m64 -mmacosx-version-min=$(MACOSXVERS)' config/Makefile.macosx64	  	  
  fi

  # needed to compile with Apple LLVM 5.1, shouldn't hurt on other systems
#  patch -p0 < ../root5_34_17_LLVM51.patch | tee -a $logfile 
  patch -p0 < ../root5_34_17_linux_libc++.patch | tee -a $logfile 

  # needed to solve problem with the TGeoManger for some CBM and Panda geometries
  patch -p0 < ../root_TGeoShape.patch
    
  . rootconfig.sh

  #This workaround  to run make in a loop is
  #needed because of problems with the intel compiler.
  #Due to some internal problems of icc (my interpretation)
  #there are crashes of the compilation process. After 
  #restarting the make process the compilation passes the 
  #problematic file and may crash at a differnt point. 
  #If there are more than 10 crashes the script is stoped
  
  if [ "$compiler" = "intel" ];
  then
    counter=0
    until [ -e $checkfile ];
    do
      counter=$[$counter+1]
      touch run_$counter   
      if [ $counter -gt 10 ];
      then
        echo "There is a problem compiling root"  | tee -a $logfile
        echo "This is the " $counter " try to compile"  | tee -a $logfile
        echo "Stop the script now"  | tee -a $logfile
        exit 1
      fi
      $MAKE_command -j$number_of_processes
    done
  else
    $MAKE_command -j$number_of_processes
  fi

  cd $SIMPATH/tools/root/etc/vmc

  if [ "$arch" = "linuxx8664icc" ];
  then
    cp Makefile.linuxx8664gcc Makefile.linuxx8664icc
    mysed 'g++' 'icpc' Makefile.linuxx8664icc
    mysed 'g77' 'ifort' Makefile.linuxx8664icc
    mysed 'gcc' 'icc' Makefile.linuxx8664icc 
    mysed 'SHLIB         = -lg2c' '' Makefile.linuxx8664icc
    mysed '-fno-f2c -fPIC' '-fPIC' Makefile.linuxx8664icc
    mysed '-fno-second-underscore' '' Makefile.linuxx8664icc
  fi
  if [[ $FC =~ .*gfortran.* ]];
  then
    if [ "$arch" = "linuxx8664gcc" ];
    then     
      mysed "OPT   = -O2 -g" "OPT   = ${CXXFLAGS}" Makefile.$arch
      mysed 'LDFLAGS       = $(OPT)' "LDFLAGS       = ${CXXFLAGS_BAK}" Makefile.$arch
      if [ "$compiler" = "Clang" ]; then
        mysed 'CXXOPTS       = $(OPT)' "CXXOPTS       = ${CXXFLAGS_BAK}" Makefile.$arch
        cd $SIMPATH/tools/root
        patch -p0 < ../root_vmc_MakeMacros.diff
      fi   
    elif [ "$arch" = "linuxia64gcc" ];
    then 
      cp Makefile.linux Makefile.linuxia64gcc
#      mysed "OPT   = -O2" "OPT   =" Makefile.linuxia64gcc
      mysed "-Woverloaded-virtual" "" Makefile.linuxia64gcc
      mysed "-DCERNLIB_LINUX" "-DCERNLIB_LXIA64" Makefile.linuxia64gcc
      mysed "OPT   = -O2" "OPT   =" Makefile.$arch
      mysed "OPT   = -g" "OPT   = ${CXXFLAGS} -fPIC" Makefile.$arch
    fi
  fi

  cd $SIMPATH/tools/root

  $MAKE_command install

  check_all_libraries $install_prefix/lib

  check_success root $checkfile
  check=$?

  export PATH=${install_prefix}/bin:${PATH}
  
  if [ "$platform" = "macosx" ];
  then
    export DYLD_LIBRARY_PATH=${libdir}:${DYLD_LIBRARY_PATH}
  else
    export LD_LIBRARY_PATH=${libdir}:${LD_LIBRARY_PATH}
  fi
else
  export PATH=${install_prefix}/bin:${PATH}
  if [ "$platform" = "macosx" ];
  then
    export DYLD_LIBRARY_PATH=${libdir}:${DYLD_LIBRARY_PATH}
  else
    export LD_LIBRARY_PATH=${libdir}:${LD_LIBRARY_PATH}
  fi
fi

if [ "$build_cpp11" = "yes" ];
then
  CXXFLAGS=$CXXFLAGS_BAK
  export CXXFLAGS
fi

cd $SIMPATH

return 1
