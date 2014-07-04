#!/bin/bash
# Uses the tool uname to check on which system
# the script is run 
# The script is inspired by the configure script
# from ROOT

#setting the default language (from Andery Sokolov)
default_lang=$(echo $LANG)
LANG=en_EN.utf-8

arch=`uname -s | tr '[A-Z]' '[a-z]'`
chip=`uname -m | tr '[A-Z]' '[a-z]'`

# get the number of processors
#work around for using icecc 
ncpu=`echo $NCPU`
if [ "$ncpu" != "" ];
then
  number_of_processors=$ncpu
  echo "Number of proccessors = $NCPU "
elif [ "$arch" = "linux" ];
then
  number_of_processors=$(cat /proc/cpuinfo | grep processor | wc -l)
elif [ "$arch" = "darwin" ];
then
  number_of_processors=$(sysctl -n hw.ncpu)
elif [ "$arch" = "sunos" ];
then
  number_of_processors=$(/usr/sbin/psrinfo | wc -l)
fi

number_of_processes=$number_of_processors

case "$arch:$chip:$compiler" in
    linux:ia64:gcc)          
        arch=linuxia64gcc    
        platform=linux
        PLATFORM=$platform
        system=64bit
        MAKE_command=make
	checklib64="yes" 
        ;;
    linux:ia64:intel) 
        echo "The Intel compiler is not supported for Itanium"
        exit 1         
        #arch=linuxia64gcc    
        #platform=linux
        #PLATFORM=$platform
        #system=64bit
        #MAKE_command=make
        ;;
    linux:x86_64:gcc)        
        arch=linuxx8664gcc   
        platform=linux
        PLATFORM=$platform
        system=64bit
        MAKE_command=make
	checklib64="yes" 
        ;;
    linux:x86_64:intel)        
        arch=linuxx8664icc   
        platform=linux
        PLATFORM=$platform
        system=64bit
        MAKE_command=make
	checklib64="yes" 
        ;;
    linux:i*86:gcc)          
        arch=linux           
        platform=linux
        PLATFORM=$platform
        system=32bit
        MAKE_command=make
        ;;
    linux:i*86:intel)          
        arch=linuxicc           
        platform=linux
        PLATFORM=$platform
        system=32bit
        MAKE_command=make
        ;;
    linux:x86_64:Clang)         
        arch=linuxx8664gcc      
        platform=linux
        PLATFORM=$platform
        system=64bit
        MAKE_command=make
	checklib64="yes" 
        ;;
    darwin:*86*:gcc)         
        arch=macosx          
        platform=macosx
        PLATFORM=$platform
        system=32bit
        MAKE_command=make
        ;;
    darwin:*86*:Clang)         
        arch=macosx          
        platform=macosx
        PLATFORM=$platform
        system=64bit
        MAKE_command=make
        ;;
     sunos:*86*:CC)
        arch=solarisCC5
        platform=solaris
        PLATFORM=$platform
        system=64bit
        MAKE_command=gmake
	checklib64="yes" 
        ;;      
    sunos:*86*:gcc)
        arch=solarisgcc
        platform=solaris
        PLATFORM=$platform
        system=64bit
        MAKE_command=gmake
	checklib64="yes"    
        ;;
    linux:x86_64:PGI)        
        arch=linuxx8664gcc   
        platform=linux
        PLATFORM=$platform
        system=64bit
        MAKE_command=make
	checklib64="yes" 
        ;;
    linux:i*86:PGI)          
        arch=linux           
        platform=linux
        PLATFORM=$platform
        system=32bit
        MAKE_command=make
        ;;
    *)
        echo "Architecture: $arch"
        echo "Hardware    : $chip"
        echo "Compiler    : $compiler"
        echo "Please check that all above variables are set."
        echo "This architecture, hardware or compiler is not supported up to now."
        echo "Please contact the FairRoot team at GSI"
        echo "http://fairroot.gsi.de"
        exit 1
        ;;
esac

if [ "$arch" = "macosx" ]; then
   if [ `sw_vers | sed -n 's/ProductVersion://p' | cut -d . -f 2` -ge 5 ]; then
      if `sysctl machdep.cpu.extfeatures | grep "64" > /dev/null  2>&1` ; then
         arch=macosx64
         platform=macosx
         PLATFORM=$platform
         system=64bit
         MAKE_command=make
	 checklib64="yes" 
      fi
   fi
fi


case "$platform:$compiler:$debug:$optimize" in
  linux:gcc:yes:no)
    export CXX=g++
    export CC=gcc
    export CFLAGS="-g -O0"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with debug information" | tee -a $logfile
    ;;
  linux:gcc:no:no)
    export CXX=g++
    export CC=gcc
    export CFLAGS="-O2"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with optimization" | tee -a $logfile
    ;;
  linux:gcc:no:yes)
    export CXX=g++
    export CC=gcc
    export CFLAGS="-O3" # -march=native"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with best optimization" | tee -a $logfile
    ;;
  linux:intel:yes:no)
    export CXX=icpc
    export CC=icc
    export CFLAGS="-g -O0"
    geant4_system=Linux-icc
    echo "*** Compiling the external packages with the Intel compiler" | tee -a $logfile
    echo "*** Building the libraries with debug information" | tee -a $logfile
    ;;
  linux:intel:no:no)  
    export CXX=icpc
    export CC=icc
    export CFLAGS="-O2"
    geant4_system=Linux-icc
    echo "*** Compiling the external packages with the Intel Compiler" | tee -a $logfile
    echo "*** Building the libraries with optimization" | tee -a $logfile
    ;;
  linux:intel:no:yes) 
    export CXX=icpc
    export CC=icc
    export CFLAGS="-O3 -mtune=pentium4 -xN -axN"
    geant4_system=Linux-icc
    echo "*** Compiling the external packages with the Intel Compiler" | tee -a $logfile
    echo "*** Building the libraries with best optimization" | tee -a $logfile
    ;;  
  linux:Clang:yes:no)
    export CXX=clang++
    export CC=clang
    export CFLAGS="-g -O0"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the Clang compiler" | tee -a $logfile
    echo "*** Building the libraries with debug information" | tee -a $logfile
    ;;
  linux:Clang:no:no)
    export CXX=clang++
    export CC=clang
    export CFLAGS="-O2"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the Clang compiler" | tee -a $logfile
    echo "*** Building the libraries with optimization" | tee -a $logfile
    ;;
  linux:Clang:no:yes)
    export CXX=clang++
    export CC=clang
    export CFLAGS="-O3"  #-march=pentium4"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the Clang compiler" | tee -a $logfile
    echo "*** Building the libraries with best optimization" | tee -a $logfile
    ;;
  macosx:gcc:yes:no)
    export CXX=g++
    export CC=gcc
    export CFLAGS="-g -O0"
    geant4_system=Darwin-g++
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with debug information" | tee -a $logfile
    ;;
  macosx:gcc:no:no)
    export CXX=g++
    export CC=gcc
    export CFLAGS="-O2"
    geant4_system=Darwin-g++
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with optimization" | tee -a $logfile
    ;;
  macosx:gcc:no:yes)
    export CXX=g++
    export CC=gcc
    export CFLAGS="-O3"  #-march=pentium4"
    geant4_system=Darwin-g++
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with best optimization" | tee -a $logfile
    ;;
  macosx:Clang:yes:no)
    export CXX=clang++
    export CC=clang
    export CFLAGS="-g -O0"
    geant4_system=Darwin-g++
    echo "*** Compiling the external packages with the Clang compiler" | tee -a $logfile
    echo "*** Building the libraries with debug information" | tee -a $logfile
    ;;
  macosx:Clang:no:no)
    export CXX=clang++
    export CC=clang
    export CFLAGS="-O2"
    geant4_system=Darwin-g++
    echo "*** Compiling the external packages with the Clang compiler" | tee -a $logfile
    echo "*** Building the libraries with optimization" | tee -a $logfile
    ;;
  macosx:Clang:no:yes)
    export CXX=clang++
    export CC=clang
    export CFLAGS="-O3"  #-march=pentium4"
    geant4_system=Darwin-g++
    echo "*** Compiling the external packages with the Clang compiler" | tee -a $logfile
    echo "*** Building the libraries with best optimization" | tee -a $logfile
    ;;
  macosx:intel:*:*)
    echo "The Intel compilers are not supported for Mac OS X up to now"
    echo "Please choose a different compiler"
    echo "Stop the script now"
    exit 
    ;;
  solaris:CC:yes:no)
    export CXX=CC
    export CC=cc
    export CFLAGS="-g -O0"
    geant4_system=SUN-CC
    echo "*** Compiling the external packages with the CC compiler" | tee -a $logfile
    echo "*** Building the libraries with debug information" | tee -a $logfile
    ;;
  solaris:CC:no:no)
    export CXX=CC
    export CC=cc
    export CFLAGS="-O2"
    geant4_system=SUN-CC
    echo "*** Compiling the external packages with the CC compiler" | tee -a $logfile
    echo "*** Building the libraries with optimization" | tee -a $logfile
    ;;
  solaris:CC:no:yes)
    export CXX=CC
    export CC=cc
    export CFLAGS="-O3 " #-march=pentium4"
    geant4_system=SUN-CC
    echo "*** Compiling the external packages with the CC compiler" | tee -a $logfile
    echo "*** Building the libraries with best optimization" | tee -a $logfile
    ;;  
  solaris:gcc:yes:no)
    export CXX=g++
    export CC=gcc
    export CFLAGS="-g -O0"
    geant4_system=SUN-gcc
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with debug information" | tee -a $logfile
    ;;
  solaris:gcc:no:no)
    export CXX=g++
    export CC=gcc
    export CFLAGS="-O2"
    geant4_system=SUN-gcc
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with optimization" | tee -a $logfile
    ;;
  solaris:gcc:no:yes)
    export CXX=gcc
    export CC=g++
    export CFLAGS="-O3 " #-march=pentium4"
    geant4_system=SUN-gcc
    echo "*** Compiling the external packages with the GCC compiler" | tee -a $logfile
    echo "*** Building the libraries with best optimization" | tee -a $logfile
    ;;    
  linux:PGI:yes:no)
    export CXX=pgCC
    export CC=pgcc
    export CFLAGS="-g -O0"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the PGI compiler" | tee -a $logfile
    echo "*** Building the libraries with debug information" | tee -a $logfile
    ;;
  linux:PGI:no:no)
    export CXX=pgCC
    export CC=pgcc
    export CFLAGS="-O2"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the PGI compiler" | tee -a $logfile
    echo "*** Building the libraries with optimization" | tee -a $logfile
    ;;
  linux:PGI:no:yes)
    export CXX=pgCC
    export CC=pgcc
    export CFLAGS="-O3" # -march=native"
    geant4_system=Linux-g++
    echo "*** Compiling the external packages with the PGI compiler" | tee -a $logfile
    echo "*** Building the libraries with best optimization" | tee -a $logfile
    ;;
  *)
    echo "This platform or the compiler are not supported"
    echo "Stop the script now"
    exit 
    ;;
esac

#------------------------------------------------------------------
# Check if the required programs are already installed on the system 
# Use CMake to do all the system checks
# Creates also the version info fill

mkdir -p $SIMPATH/test/build
cd $SIMPATH/test

cp $SIMPATH/scripts/FairVersion.h.* .
cp $SIMPATH/scripts/GenerateVersionInfo.cmake .
cp $SIMPATH/scripts/Test_CMakeLists.txt CMakeLists.txt
cp $SIMPATH/scripts/configure.in .

cd build
cmake ..
ret_val=$?

if [ $ret_val -ne 0 ]; 
then
  echo ""
  echo "There have been problems found. Please check the output above."
  echo ""
  cd $SIMPATH
  rm -rf test
  exit
fi  

hascxx11=$(grep HasCxx11 $SIMPATH/test/configure | cut -f2 -d:)
haslibcxx=$(grep HasLibCxx $SIMPATH/test/configure | cut -f2 -d:)
_hascurl=$(grep HasCurl $SIMPATH/test/configure | cut -f2 -d:)

if [ ${_hascurl} ];
then
  install_curl=no
else
  install_curl=yes
fi

export CXXFLAGS="${CFLAGS}"

if [ $hascxx11 ];
then
  export CXXFLAGS="${CXXFLAGS} -std=c++11"
  export build_cpp11=yes
fi

if [ $haslibcxx ];
then
  export CXXFLAGS="${CXXFLAGS} -stdlib=libc++"
fi

export FC=$(grep FortranCompiler $SIMPATH/test/configure | cut -f2 -d:)
# On Linux systems f95 in many cases is only a link to gfortran
# If there are many links 'readlink -f' returns the link to the final source 
if [ "$FC" = "f95" ]; then
  export FC=$(readlink -f `which f95`)
fi
export F77=$FC

# actualy one should check for mac os x 10.8 
if [ "$platform" = "macosx" -a "$compiler" = "Clang" ]; 
then
  # remove debug flag from list of flags if present
  FFLAGS=$(echo ${CFLAGS} | sed -e 's/-g//g')
  export FFLAGS
else  
  export FFLAGS=${CFLAGS}
fi

#restore the default langauge
export LANG=${default_lang}


cd $SIMPATH
rm -rf test

return 1

