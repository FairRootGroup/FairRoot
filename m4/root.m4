dnl
dnl $Id: root.m4,v 1.2 2006/08/31 13:55:44 turany Exp $
dnl $Author: turany $
dnl $Date: 2006/08/31 13:55:44 $
dnl
dnl Autoconf macro to check for existence or ROOT on the system
dnl Synopsis:
dnl
dnl  ROOT_PATH([MINIMUM-VERSION, [ACTION-IF-FOUND, [ACTION-IF-NOT-FOUND]]])
dnl
dnl Some examples: 
dnl 
dnl    ROOT_PATH(3.03/05, , AC_MSG_ERROR(Your ROOT version is too old))
dnl    ROOT_PATH(, AC_DEFUN([HAVE_ROOT])
dnl 
dnl The macro defines the following substitution variables
dnl
dnl    ROOTCONF           full path to root-config
dnl    ROOTEXEC           full path to root
dnl    ROOTCINT           full path to rootcint
dnl    ROOTLIBDIR         Where the ROOT libraries are 
dnl    ROOTINCDIR         Where the ROOT headers are 
dnl    ROOTCFLAGS         Extra compiler flags
dnl    ROOTLIBS           ROOT basic libraries 
dnl    ROOTGLIBS          ROOT basic + GUI libraries
dnl    ROOTAUXLIBS        Auxilary libraries and linker flags for ROOT
dnl    ROOTAUXCFLAGS      Auxilary compiler flags 
dnl    ROOTRPATH          Same as ROOTLIBDIR
dnl
dnl The macro will fail if root-config and rootcint isn't found.
dnl
dnl Christian Holm Christensen <cholm@nbi.dk>
dnl

AC_DEFUN([ROOT_PATH],
[
  AC_ARG_WITH(rootsys,
  [  --with-rootsys          top of the ROOT installation directory],
    user_rootsys=$withval,
    user_rootsys="none")

dnl check for existence of environment variable ROOTSYS
  
  echo "ROOTSYS=$ROOTSYS" 
  if test x"$ROOTSYS" = x ; then
    AC_MSG_ERROR(Please set the environment variable ROOTSYS to the root of your ROOT installation (export ROOTSYS=/path/to/ROOT))
  else
    if test x"$user_rootsys" = xnone -o "$user_rootsys" = "$ROOTSYS"; then
      rootbin="$ROOTSYS/bin"
    else
      if test ! "$user_rootsys" = "$ROOTSYS"; then
      AC_MSG_ERROR(The environment variable ROOTSYS has to be the same directory you've given by the configure option  --with-rootsys)
      fi
    fi
  fi
  
  LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"
#  export "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"

  AC_PATH_PROG(ROOTCONF, root-config , no, $rootbin)
  AC_PATH_PROG(ROOTEXEC, root , no, $rootbin)
  AC_PATH_PROG(ROOTCINT, rootcint , no, $rootbin)
	
  if test ! x"$ROOTCONF" = "xno" && \
     test ! x"$ROOTCINT" = "xno" ; then 

    # define some variables 
    ROOTLIBDIR=`$ROOTCONF --libdir`
    ROOTINCDIR=`$ROOTCONF --incdir`
    ROOTCFLAGS=`$ROOTCONF --noauxcflags --cflags` 
    ROOTLIBS=`$ROOTCONF --noauxlibs --noldflags --libs`
    ROOTGLIBS=`$ROOTCONF --noauxlibs --noldflags --glibs`
    ROOTAUXCFLAGS=`$ROOTCONF --auxcflags`
    ROOTAUXLIBS=`$ROOTCONF --auxlibs`
    ROOTRPATH=$ROOTLIBDIR

	
    if test $1 ; then 
      AC_MSG_CHECKING(wether ROOT version >= [$1])
      vers=`$ROOTCONF --version | tr './' ' ' | awk 'BEGIN { FS = " "; } { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
      requ=`echo $1 | tr './' ' ' | awk 'BEGIN { FS = " "; } { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
      if test $vers -lt $requ ; then 
        AC_MSG_RESULT(no)
	no_root="yes"
      else 
        AC_MSG_RESULT(yes)
      fi
    fi
  else
    # otherwise, we say no_root
    no_root="yes"
  fi

  AC_SUBST(ROOTLIBDIR)
  AC_SUBST(ROOTINCDIR)
  AC_SUBST(ROOTCFLAGS)
  AC_SUBST(ROOTLIBS)
  AC_SUBST(ROOTGLIBS) 
  AC_SUBST(ROOTAUXLIBS)
  AC_SUBST(ROOTAUXCFLAGS)
  AC_SUBST(ROOTRPATH)
  AC_SUBST(ROOTSYS)  
  AC_SUBST(LD_LIBRARY_PATH)  

  if test "x$no_root" = "x" ; then 
    ifelse([$2], , :, [$2])     
  else 
    ifelse([$3], , :, [$3])     
  fi
])


#
# EOF
#
