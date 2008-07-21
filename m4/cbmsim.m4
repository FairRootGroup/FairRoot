dnl
dnl $Id: cbmsim.m4,v 1.4 2006/08/31 13:55:44 turany Exp $
dnl $Author: turany $
dnl $Date: 2006/08/31 13:55:44 $
dnl
dnl Autoconf macro to check for existence or GEANT4 on the system
dnl Synopsis:
dnl
dnl  GSI_PATH([ACTION-IF-FOUND, [ACTION-IF-NOT-FOUND]])
dnl
dnl Some examples: 
dnl 
dnl    GSI_PATH(, AC_DEFUN([HAVEGEANT4VMC]))
dnl 
dnl The macro defines the following substitution variables
dnl
dnl    ROOTSIM         Where the root of the simulation installation is 
dnl    ROOTSIMSYSTEM   On which system you are
dnl
dnl The macro will if your are neither at gsi nor on florian laptop
dnl
dnl Florian Uhlig <f.uhlig@gsi.de>
dnl
AC_DEFUN([SIM_PATH],
[
#  AC_ARG_WITH(simpath,
#  [  --with-simpath          root of the simulation installation],
#    user_path=$withval,
#    user_path="none")

  no_gsi="no"
  ROOTSIMSYSTEM="gsi"

  dnl test for given path. if no path is given assume you're at GSI system
  
  if test x"$SIMPATH" = x ; then
    AC_MSG_ERROR(Please set the environment variable SIMPATH to the root of your Simulation installation (export SIMPATH=/path/to/Simulation))
#  else
#    if test x"$user_path" = xnone -o "$user_path" = "$SIMPATH"; then
#      simpath="$SIMPATH"
#    else
#      if test ! "$user_path" = "$SIMPATH"; then
#      AC_MSG_ERROR(The environment variable SIMPATH has to be the same directory you've given by the configure option  --with-simpath)
#      fi
#    fi
  fi

  simpath="$SIMPATH"

  dnl test if your're on a system with GSI layout of simulation subdirectory,
  dnl or if you're on a gentoo system layout

  AC_CHECK_FILE("$simpath", SIM=yes, SIM=no)

  dnl you're are on a system where the root of the simulation path exists 
  
  if test "$SIM" = "yes"; then
    AC_CHECK_FILE("$simpath/geant4/env.sh", SIMGENTOO=yes, SIMGENTOO=no)
    if test "$SIMGENTOO" = "yes"; then
      dnl you're on a gentoo system
      ROOTSIMSYSTEM="gentoo"
    else      
      ROOTSIMSYSTEM="gsi"
    fi  
  else
    no_gsi="yes"
  fi

  if test "$no_gsi" = "no"; then

    if test "$ROOTSIMSYSTEM" = "gsi"; then   

      ROOTSIM="$simpath"
      GEANT4LIBDIR="$ROOTSIM/transport/geant4/lib/Linux-g++:$ROOTSIM/transport/geant4/lib/plists/Linux-g++"
      GEANT4INC="-I$ROOTSIM/transport/geant4/include -I$ROOTSIM/transport/geant4/source/interfaces/common/include -I$ROOTSIM/transport/geant4/physics_lists/hadronic/Packaging/include -I$ROOTSIM/transport/geant4/physics_lists/hadronic/QGSP/include"
      PLUTOLIBDIR="$ROOTSIM/generators/pluto"
      PLUTOINC="-I$ROOTSIM/generators/pluto/src"
      GEANT4VMCLIBDIR="$ROOTSIM/transport/geant4_vmc/lib/tgt_linux:$ROOTSIM/transport/vgm/lib/Linux-g++"
      GEANT4VMCINC="-I$ROOTSIM/transport/geant4_vmc/source/global/include \
             -I$ROOTSIM/transport/geant4_vmc/source/geometry/include \
             -I$ROOTSIM/transport/geant4_vmc/source/digits+hits/include \
             -I$ROOTSIM/transport/geant4_vmc/source/physics/include \
             -I$ROOTSIM/transport/geant4_vmc/source/event/include \
             -I$ROOTSIM/transport/geant4_vmc/source/run/include \
             -I$ROOTSIM/transport/geant4_vmc/source/interfaces/include \
             -I$ROOTSIM/transport/geant4_vmc/source/visualization/include \
             -I$ROOTSIM/transport/vgm/packages/BaseVGM/include \
             -I$ROOTSIM/transport/vgm/packages/ClhepVGM/include \
             -I$ROOTSIM/transport/vgm/packages/Geant4GM/include \
             -I$ROOTSIM/transport/vgm/packages/RootGM/include \
             -I$ROOTSIM/transport/vgm/packages/VGM/include \
             -I$ROOTSIM/transport/vgm/packages/XmlVGM/include"
      CLHEPLIBDIR="$ROOTSIM/cern/clhep/lib"
      CLHEPINC="-I$ROOTSIM/cern/clhep/include"
      GEANT3LIBDIR="$ROOTSIM/transport/geant3/lib/tgt_linux"
      GEANT3INC="-I$ROOTSIM/transport/geant3/TGeant3"
      VGM_INSTALL="$ROOTSIM/transport/vgm"
      LD_LIBRARY_PATH="/usr/lib:/usr/X11R6/lib:$ROOTSIM/cern/clhep/lib:$ROOTSIM/generators/lib:$GEANT4LIBDIR:$GEANT3LIBDIR:$PLUTOLIBDIR:$GEANT4VMCLIBDIR:$LD_LIBRARY_PATH"

    else 
  
      ROOTSIM="/opt/hep_physics"
      GEANT4LIBDIR="$ROOTSIM/transport/geant4/lib"
      GEANT4INC="-I$ROOTSIM/transport/geant4/include"
      PLUTOLIBDIR="$ROOTSIM/generators/pluto/lib"
      PLUTOINC="-I$ROOTSIM/generators/pluto/include"
      GEANT4VMCLIBDIR="$ROOTSIM/transport/geant4_vmc/lib/tgt_linux"
      GEANT4VMCINC="-I$ROOTSIM/transport/geant4_vmc/include"
      CLHEPLIBDIR="$ROOTSIM/clhep/lib"
      CLHEPINC="-I$ROOTSIM/clhep/include"
      GEANT3LIBDIR="$ROOTSIM/transport/geant3/lib/tgt_Linux"
      GEANT3INC="-I$ROOTSIM/transport/geant3/TGeant3"

    fi
   
    AC_SUBST(ROOTSIMSYSTEM)
    AC_SUBST(ROOTSIM)
    AC_SUBST(GEANT4LIBDIR)
    AC_SUBST(GEANT4INC)
    AC_SUBST(PLUTOLIBDIR)
    AC_SUBST(PLUTOINC)
    AC_SUBST(GEANT4VMCLIBDIR)
    AC_SUBST(GEANT4VMCINC)
    AC_SUBST(CLHEPLIBDIR)
    AC_SUBST(CLHEPINC)
    AC_SUBST(GEANT3LIBDIR)
    AC_SUBST(GEANT3INC)
    AC_SUBST(VGM_INSTALL)
    
  fi

  if test "$no_gsi" = "no" ; then
     ifelse([$1], , :, [$1])
  else
     ifelse([$2], , :, [$2])
  fi
])


#
# EOF
#
