#!/bin/bash

   echo $arch

   if [ "$debug" = "yes" ];
   then
     if [ "$compiler" = "Clang" -a "$arch" = "linux" ]; then
       debugstring=""
     else
       debugstring="--build=debug"
     fi
   else
     debugstring=""
   fi   
   ########### Xrootd has problems with gcc4.3.0 and 4.3.1 
   gcc_major_version=$(gcc -dumpversion | cut -c 1)
   gcc_minor_version=$(gcc -dumpversion | cut -c 3)
   if [ $gcc_major_version -ge 4 -a $gcc_minor_version -ge 3 ];
   then
      XROOTD="--disable-xrootd"
   else
      XROOTD=" "
    fi
   #######################################################

   OPENGL=" "
   if [ "$compiler" = "Clang" ]; then
     root_comp_flag="--with-clang"
     if [ $haslibcxx ]; then
       root_comp_flag="--with-clang --enable-cxx11 --enable-libcxx"
     fi
     if [ "$platform" = "linux" ]; then
       OPENGL="--with-opengl-incdir=$SIMPATH_INSTALL/include --with-opengl-libdir=$SIMPATH_INSTALL/lib"
     fi
   else
     root_comp_flag="--with-cc=$CC --with-cxx=$CXX --with-ld=$CXX"   
   fi

   ########### Roofit has problems with gcc3.3.5  
   gcc_major_version=$(gcc -dumpversion | cut -c 1)
   gcc_minor_version=$(gcc -dumpversion | cut -c 3)
   gcc_sub_version=$(gcc -dumpversion | cut -c 5)
   
   if [ $gcc_major_version -eq 3 -a $gcc_minor_version -eq 3 -a $gcc_sub_version -eq 5 ];
   then
      ROOFIT=" "
   else
      ROOFIT="--enable-roofit"
    fi

   if [ "$build_python" = "yes" ];
   then
      PYTHONBUILD="--enable-python"
   else   
      PYTHONBUILD=" "
   fi
   
   #######################################################
      
     pythia6_libdir=$SIMPATH_INSTALL/lib
     pythia8_libdir=$SIMPATH_INSTALL/lib
     pythia8_incdir=$SIMPATH_INSTALL/include
     gsl_dir=$SIMPATH_INSTALL
     etc_string="--etcdir=$SIMPATH_INSTALL/share/root/etc"
     prefix_string="--prefix=$install_prefix"
 
   ./configure $arch  --enable-soversion $PYTHONBUILD $XROOTD  $ROOFIT \
                    --enable-minuit2  --enable-gdml --enable-xml \
		    --enable-builtin-ftgl --enable-builtin-glew \
                    --enable-builtin-freetype $OPENGL \
		    --with-pythia6-libdir=$pythia6_libdir \
		    --with-pythia8-libdir=$pythia8_libdir \
		    --with-pythia8-incdir=$pythia8_incdir \
		    --enable-mysql --enable-pgsql \
                    --disable-globus \
                    --disable-reflex \
                    --disable-cintex \
                    --enable-vc --enable-http \
                    --with-gsl-incdir=$gsl_dir/include \
                    --with-gsl-libdir=$gsl_dir/lib \
                    --with-f77=$FC $root_comp_flag $prefix_string \
                    $etc_string $debugstring 
