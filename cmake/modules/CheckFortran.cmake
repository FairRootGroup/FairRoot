 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# FFLAGS depend on the compiler
get_filename_component (Fortran_COMPILER_NAME ${CMAKE_Fortran_COMPILER} NAME)

  message ("CMAKE_Fortran_COMPILER full path: " ${CMAKE_Fortran_COMPILER})
  message ("Fortran compiler: " ${Fortran_COMPILER_NAME})

if (Fortran_COMPILER_NAME STREQUAL "gfortran")
  # gfortran
  set (Fortran_UseLib "gfortran")
elseif (Fortran_COMPILER_NAME STREQUAL "f95")
  # gfortran
  message("f95 found -> gfortran")
  set (Fortran_UseLib "gfortran")
elseif (Fortran_COMPILER_NAME STREQUAL "g77")
  # g77
  set (Fortran_UseLib "g2c")
elseif (Fortran_COMPILER_NAME STREQUAL "f77")
  # g77
  message("f77 found -> g77")
  set (Fortran_UseLib "g2c")
else (Fortran_COMPILER_NAME STREQUAL "gfortran")
  message ("Fortran compiler not known/tested")
endif (Fortran_COMPILER_NAME STREQUAL "gfortran")

