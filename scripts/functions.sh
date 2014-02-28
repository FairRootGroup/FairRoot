#!/bin/bash
# define functions needed later on

#_____________________________________________________________________
# checks if one of the files is existing and print message
# updated to check a list of packages because some libraries
# have slightly different names on differnt platforms
function not_there {
    pack=$1
    shift
    files=$*
    retval=0
    for file in $files;do
      if [ -e $file ];     
      then 
        echo "*** Package $pack is OK ***" | tee -a $logfile
        return 1
      fi
    done

    echo "*** Compiling $pack ................ " | tee -a $logfile
    return 0
}

#_____________________________________________________________________
# check if package is already unpacked and do the unpacking if
# necessary
function untar {
    pack=$1
    tarf=$2
    if [ -d $pack ];
    then 
       echo "*** Package $pack already unpacked ***" | tee -a $logfile
    else
       echo "*** Unpacking $tarf .............." | tee -a $logfile
       if [ "$platform" != "solaris" ];
       then
         if [ "$(file $tarf | grep -c gzip)" = "1" ];
         then
           tar zxf $tarf
         elif [ "$(file $tarf | grep -c bzip2)" = "1" ];
         then
           tar xjf $tarf
         elif [ "$(file $tarf | grep -c Zip)" = "1" ];
         then
           unzip $tarf
         else
	   echo "--E-- Cannot unpack package $pack"
           exit 
         fi
       else
         if [ "$(file $tarf | grep -c gzip)" = "1" ];
         then
            /usr/sfw/bin/gtar xzf $tarf 
         elif [ "$(file $tarf | grep -c bzip2)" = "1" ];
         then
            /usr/sfw/bin/gtar xjf $tarf 
         else
	   echo "--E-- Cannot unpack package $pack"
           exit 
         fi
       fi
    fi
}

#_____________________________________________________________________
# check if file exists after the compilation process
# return error code
function check_success {
    pack=$1
    file=$2
    if [ -e $file ];
    then
      echo "*** $1 compiled successfully ***" | tee -a $logfile
      return 1
    else
      echo "*** ERROR: $1 could not be created." | tee -a $logfile
      return 0
    fi
}
#_____________________________________________________________________
# scripts perform sed command differently on linux and on Mac Os X
# return error code
# first parameter is the text to search for, the second is the
# replacement and the third one defines the filename
# with the fourth on defines if the the string 
# contains a /
function mysed {

    # Assert that we got enough arguments
    if [ $# -lt 3 ]; 
    then
      echo "mysed: 3 or 4 arguments needed"
      echo "Script was called only with $# arguments"
      echo "Searchstring: $1"
      echo "Replacement : $2"
      echo "Filename    : $3"
      if [ $# -eq 4 ];
      then
        echo "Option    : $4"       
      fi
      return 1
    fi

    old=$1
    new=$2
    change_file=$3
    if [ $# -eq 4 ];
    then
      has_slash=yes
    fi

 
   if [ "$platform" = "linux" ];
    then
      if [ "$has_slash" = "yes" ];
      then 
        sed -e "s#$old#$new#g" -i'' $change_file 
      else
        sed -e "s/$old/$new/g" -i'' $change_file
      fi
    elif [ "$platform" = "macosx" ];
    then
      if [ "$has_slash" = "yes" ];
      then 
        sed -e "s#$old#$new#g" -i '' $change_file
      else
        sed -e "s/$old/$new/g" -i '' $change_file
      fi
    elif [ "$platform" = "solaris" ];
    then
      mv $change_file tmpfile
      if [ "$has_slash" = "yes" ];
      then 
        sed -e "s#$old#$new#g" tmpfile > $change_file
      else
        sed -e "s/$old/$new/g" tmpfile > $change_file
      fi
      rm tmpfile     
    fi
}

#_____________________________________________________________________
function check_library {
    # The function is inspired by the ROOT configure script and adapted
    # to run on linux and Mac OS X
    #
    # This function will try to find out if a library [$1] contains 64 bit
    # or 32 bit code. Currently works only for linux and Mac OS X.
    # The result of the check is stored in lib_is, which should be 
    # immediately copied or used , since the variable
    # will be overwritten at next invocation of this function.

    chklibname=$1

    lib_is=0

    # Assert that we got enough arguments
    if [ $# -ne 1 ]; 
    then
      echo "check_library: not 1 argument"
      return 1
    fi

    
    if [ "x`basename $chklibname .a`" != "x`basename $chklibname`" ]; then
        # we have an archive .a file
        if [ "$platform" = "linux" ];
        then
          objdump -a $1 | grep 'x86-64' > /dev/null 2>& 1
	  ret=$?
        elif [ "$platform" = "macosx" ];
        then
          # 0xfeedfacf is the magic key for 64bit files
          otool -h $1 | grep '0xfeedfacf' > /dev/null 2>& 1
	  ret=$?
        elif [ "$platform" = "solaris" ];
        then
          # Since I don't have a 64bit machine in can only test for 32bit
          # because i don't now the result on a 64bit machine.
          /usr/sfw/bin/gobjdump -a $1 | grep 'elf32-i386' > /dev/null 2>& 1
	  ret1=$?
          if [ $ret1 -eq 0 ];
          then
            ret=1
          else
            ret=0
          fi        
        fi
    else
        if [ "$platform" = "solaris" ]; 
        then
           file $1 | grep '64-Bit' > /dev/null 2>& 1
   	   ret=$?
           if [ $ret -eq 1 ];then
             file $1 | grep '64-bit' > /dev/null 2>& 1
   	     ret=$?
           fi 
        else        
           file -L $1 | grep '64-bit' > /dev/null 2>& 1
	   ret=$?
        fi
    fi
    if [ $ret -eq 0 ]; 
    then
      lib_is=64bit
    else
      lib_is=32bit
    fi
}

#_____________________________________________________________________
function check_all_libraries {
    # This function loops over all libraries in the given path and
    # checks if the library contains code as given in $system.

    # Assert that we got enough arguments
    if [ $# -ne 1 ]; 
    then
      echo "check_all_libraries: not 1 argument"
      return 1
    fi

    chkdirname=$1
    echo "**** Checking libraries in $chkdirname ****" | tee -a $logfile_lib

    if [ "$platform" = "linux" -o "$platform" = "solaris" ];
     then
       shared_ext=so
     elif [ "$platform" = "macosx" ];
     then
       shared_ext=dylib
     fi   

    oldpwd=$(pwd)
    cd $chkdirname
    if [ "$(find . -name "lib*.$shared_ext" | wc -l)" != "0" ];
    then
	for file in $(ls *.$shared_ext);
	do
	  check_library $file
	  if [ "$lib_is" != "$system" ];
	      then
	      echo "Library $file is $lib_is, but system is $system" | tee -a $logfile_lib
#      else
#        echo "Library $file is ok" | tee -a $logfile_lib
	  fi
	done
    fi
    if [ "$(find . -name "lib*.a" | wc -l)" != "0" ];
    then
	for file in $(ls lib*.a);
	  do
	  check_library $file
	  if [ "$lib_is" != "$system" ];
	      then
	      echo "Library $file is $lib_is, but system is $system" | tee -a $logfile_lib
#      else
#        echo "Library $file is ok" | tee -a $logfile_lib
	  fi
	done
    fi
    cd $oldpwd
}

#_____________________________________________________________________
function is_in_path {
    # This function checks if a file exists in the $PATH.
    # To do so it uses which.
    # There are several versions of which available with different
    # return values. Either it is "" or "no searched program in PATH" or
    # "/usr/bin/which: no <searched file>".
    # To check for all differnt versions check if the return statement is 
    # not "".
    # If it is not "" check if the return value starts with no or have
    # the string "no <searched file> in the return string. If so set
    # return value to "". So all negative return statements go to "".
    # If program is found in Path return 1, else return 0.

    searched_program=$1
    answer=$(which $searched_program)
    if [ "$answer" != "" ];
    then
      no_program=$(which $searched_program | grep -c '^no' )
      no_program1=$(which $searched_program | grep -c "^no $searched_program")
      if [ "$no_program" != "0" -o "$no_program1" != "0" ];
      then
        answer=""
      fi
    fi

    if [ "$answer" != "" ];
    then
      return 1
    else
      return 0
    fi
}
#------------------------------------
function create_links {

     # create symbolic links from files with suffix $2 to $1

      ext1=$1
      ext2=$2

      for file in $(ls *.$ext1);
      do
         ln -s $file ${file%.*}.$ext2
      done

}
#_____________________________________________________________________
function download_file {
      # download the file from the given location using either wget or 
      # curl depending which one is available

      url=$1
      
      if [ "$install_curl" = "yes" ]; # no curl but wget
      then
        wget $url
      else 
        # -L follow redirections which is needed for boost
        curl -O -L $url    
      fi
}
#_____________________________________________________________________
check_lib() {

    # copied from ROOT configure
    # This function will try to locate a library [$1] in the specific
    # directory [$3] or in a default path [$*].  If the second argument
    # [$2] is not "no", then shared libraries are favoured.
    # The result of the search is stored in found_lib and found_dir,
    # which should be immediately copied, since the variables value will
    # be overwritten at next invocation of this function.

    # Assert that we got enough arguments
    if test $# -lt 4 ; then
        echo "check_library: Too few arguments"
        return 1
    fi

    # Save arguments in local names
    lib=$1       ; shift
    shared=$1    ; shift
    libdirl=$1   ; shift
    libdirs="$*"

    # Write a message
    checking_msg $lib

    # check if we got a specific argument as to where the library
    # is to be found
    if test ! "x$libdirl" = "x" ; then
        libdirs=$libdirl
    fi
    found_lib=no
    found_dir=no

    # Make list of libraries to search for. The .lib extension is for
    # Windoze - note $shared is always "no" on windoze, since we need
    # the .lib export library to link.
    libs=""
    for i in $lib ; do
        for ext in .a .lib "" ; do     # lib without extension for MacOS X
            libs="$libs $i$ext"
        done
    done
    slibs=""
    for i in $lib ; do
        for ext in .so .sl .dylib .dll.a ; do      # .dll.a for cygwin gcc
            slibs="$slibs $i$ext"
        done
    done
    if test ! "x$shared" = "xno" ; then
        libs="$slibs $libs"
    else
        libs="$libs $slibs"
    fi

    logmsg "libraries to check for: $libs"
    # Loop over the list of possible directories, and see if we can
    # find any of the library files as determind above.
    for i in $libdirs ; do
        # look first in the lib32 directories
        if test "x$checklib32" = "xyes" ; then
            i32=`echo $i | sed -e 's|lib$|lib32|' -e 's|lib/|lib32/|'`
            #i="$i32 $i"
            i="$i32"
        fi
        # look first in the lib64 directories
        if test "x$checklib64" = "xyes" ; then
            i64=`echo $i | sed -e 's|lib$|lib64|' -e 's|lib/|lib64/|'`
            i="$i64 $i"
        fi
        # look only in the lib64 directories
        if test "x$checkonlylib64" = "xyes" ; then
            i64=`echo $i | sed -e 's|lib$|lib64|' -e 's|lib/|lib64/|'`
            i="$i64"
        fi
        # look only in the hpux64 directories
        if test "x$checkhpux64" = "xyes" ; then
            i64=`echo $i | sed 's|\(lib\)|\1/hpux64|'`
            i="$i64"
        fi
        # look only in the amd64 directories
        if test "x$checksolaris64" = "xyes" ; then
            i64=`echo $i | sed 's|\(lib\)|\1/amd64|'`
            i="$i64"
        fi
        logmsg " Checking in directories $i for $libs"
        for l in $i ; do
            l=`echo $l | sed 's,^//,/,'`
            if test ! -d $l ; then
                continue
            fi
            for j in ${libs} ; do
                logmsg "  Checking for library $j in directory $i"
                # if we found the file (it's readable by user), we set the
                # logical variables and are on our way, otherwise we continue
                liblist=`echo $l/$j`    # expands wildcard in $l/$j
                for n in ${liblist} ; do
                    logmsg "   Checking $n"
                    if test -f $n ; then
                        logmsg "   Found file $n"
                        if test "x$checklib64" = "xyes" ; then
                            check_lib64 $n
                            if test $is_lib64 -eq 1 ; then
                                found_dir=$l
                                found_lib=$j
                                break 4
                            fi
                        else
                            found_dir=$l
                            found_lib=$j
                            if test "x$arch" = "linux"; then
                               check_lib64 $n
                            else
                               is_lib64=0
                            fi
                            if test $is_lib64 -eq 1 ; then
                                found_dir=no
                                found_lib=no
                            else
                                # skip cygwin libraries when in pure Win32 mode
                                if test "x$platform" = "xwin32"; then
                                    case $found_dir in
                                        /lib|/lib/*|/usr/*) found_dir=no ;;
                                        *) break 4;;
                                    esac
                                else
                                    break 4
                                fi
                            fi
                        fi
                    else
                        logmsg "  $j not found in $j"
                    fi
                done
            done
        done
    done

    echo $found_dir
    unset libs
    unset libdirs

    if test "x$found_dir" = "xno" || test "x$found_lib" = "xno" ; then
        found_dir=""
        found_lib=""
        found_raw_lib=""
        logmsg " library not found"
    else
        flib=""
        maclib=""
        for i in $lib ; do
            for ext in .a .lib "" ; do     # lib without extension for MacOS X
                if test "x$found_lib" = "x$i$ext" ; then
                    flib=$i$ext
                    if test "x$ext" = "x" ; then
                        maclib="yes"
                    fi
                    break 2
                fi
            done
        done

        if (test "x$found_lib" = "x$flib" && test "x$shared" = "xno") || \
           test "x$maclib" = "xyes" ; then
                found_raw_lib=${found_lib}
            found_lib=${found_dir}/${found_lib}
            found_raw_dir=${found_dir}
            found_dir=""
        else
            found_raw_lib=${found_lib}
            found_lib=`echo $found_lib | sed 's|^lib\(.*\)\..*|-l\1|'`
            found_raw_dir=${found_dir}
            found_dir=-L${found_dir}
            # Avoid inclusion of /usr/lib, which is always included anyway
            if test "x$found_dir" = "x-L/usr/lib"   || \
               test "x$found_dir" = "x-L/usr/lib32" || \
               test "x$found_dir" = "x-L/usr/lib64" ; then
                found_dir=""
            fi
        fi

        # Correct path for win32
        if test "x$platform" = "xwin32"; then
            if test ! "x$found_lib" = "x" ; then
                found_lib=`cygpath -m $found_lib`
            fi
            if test ! "x$found_dir" = "x" ; then
               found_dir=`cygpath -m $found_dir`
            fi
        fi
    fi
    unset shared
    unset slibs
    unset lib
    unset flib
    unset maclib
    unset libdirl
}

#_____________________________________________________________________
logmsg() {
    # copied from ROOT configure 
    # Write a simple message to std out
    if test $# -lt 1 ; then
        echo "logmsg: Too few arguments"
        return 1
    fi
    if test "x$1" = "x-n"; then
       shift
       echo -n "$*" >> $logfile
    else
       echo "$*" >> $logfile
    fi
}

#_____________________________________________________________________
checking_msg() {
    # Write a simple "checking" message to std out.
    if test $# -lt 1 ; then
        echo "checking_msg: Too few arguments"
        return 1
    fi
    echo $ac_n "Checking for$ac_c"
    logmsg $ac_n "Checking for$ac_c"
    while test $# -gt 1 ; do
        echo $ac_n " $1,$ac_c"
        logmsg $ac_n " $1,$ac_c"
        shift
        if test $# -eq 1 ; then
            echo $ac_n " or$ac_c"
            logmsg $ac_n " or$ac_c"
        fi
    done
    echo $ac_n " $1 ... $ac_c"
    logmsg " $1 ... "
}

#_____________________________________________________________________
result() {
    echo "$*"
    logmsg "Result: $*"
}
#_____________________________________________________________________
check_header()  {
    # copied from ROOT
    # This function will try to locate a header [$1] in the specific
    # directory [$2] or in a default path [$*].
    # The result of the search is stored in found_hdr and found_dir,
    # which should be immediately copied, since the variables value will
    # be overwritten at next invocation of this function.

    # Assert that we got enough arguments
    if test $# -lt 3 ; then
        echo "check_header: Too few arguments"
        return 1
    fi

    # Save arguments in logical names
    hdrs=$1     ; shift
    hdrdir=$1   ; shift
    hdrdirs="$*"

    # Write a message
    checking_msg $hdrs

    # Check if we got a specific argument as to where the library
    # is to be found
    if test ! "x$hdrdir" = "x" ; then
        hdrdirs=$hdrdir
    fi
    found_hdr=no
    found_dir=no

    # Loop over the list of possible directories, and see if we can
    # find any of the library files as determind above.

    for i in $hdrdirs; do
        logmsg " Checking in directory $i"
        for j in ${hdrs} ; do
            logmsg "  Checking for $j in directory $i"
            # if we found the file (it's readable by user), we set the
            # logical variables and are on our way, otherwise we continue
            if test -r $i/$j ; then
                logmsg "  $i/$j is read-able"
                found_dir=$i
                found_hdr=$j
                # skip cygwin headers when in pure Win32 mode
                if test "x$platform" = "xwin32"; then
                    case $found_dir in
                        /usr/*) found_dir="no" ;;
                        *) break 2;;
                    esac
                else
                    break 2
                fi
            fi
        done
    done

    echo $found_dir

    if test "x$found_hdr" = "xno" || test "x$found_dir" = "xno" ; then
        found_hdr=""
        found_dir=""
    fi

    # Avoid inclusion of /usr/include, which is always included anyway
    #if test "x$found_dir" = "x/usr/include" ; then
        # found_dir="include"
    #fi

    # Correct path for win32
    if test "x$platform" = "xwin32"; then
        if test ! "x$found_hdr" = "x" ; then
           found_hdr=`cygpath -m $found_hdr`
        fi
        if test ! "x$found_dir" = "x" ; then
           found_dir=`cygpath -m $found_dir`
        fi
    fi

    unset hdrs
    unset hdrdirs
    unset hdrdir
}

#_____________________________________________________________________
check_lib64() {
    # This function will try to find out if a library [$1] contains 64 bit
    # or 32 bit code. Currently works only for linux.
    # The result of the check is stored in is_lib64, 1 if true,
    # 0 otherwise, which should be immediately copied, since the variable
    # will be overwritten at next invocation of this function.

    is_lib64=0

    # Assert that we got enough arguments
    if test $# -ne 1 ; then
        echo "check_lib64: not 1 argument"
        return 1
    fi

    # Save arguments in logical names
    chklib64=$1
    logmsg "Checking if $chklib64 is a 64bit library"
    if [ "x`basename $chklib64 .a`" != "x`basename $chklib64`" ]; then
        # we have an archive .a file
        logmsg " objdump -a $chklib64 | grep 'x86-64'"
        objdump -a $chklib64 | grep 'x86-64' > /dev/null 2>& 1
        ret=$?
    else
        logmsg " file -L $chklib64 | grep '64-bit'"
        file -L $chklib64 | grep '64-bit' > /dev/null 2>& 1
        ret=$?
    fi
    logmsg " result: $ret"
    if test $ret -eq 0 ; then
        is_lib64=1
        logmsg " is a 64bit library"
    fi
}
