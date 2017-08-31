################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(CMAKE_SYSTEM_NAME MATCHES Linux)
  add_definitions(-DLinux  -DSYSTEM64  -D_LARGEFILE64_SOURCE)
endif()

if(CMAKE_SYSTEM_NAME MATCHES Darwin)
  add_definitions(-DDarwin  -DSYSTEM64  -D_LARGEFILE64_SOURCE)
endif()

CHECK_SYMBOL_EXISTS(CLOCK_REALTIME "time.h" HAS_CLOCK_REALTIME)
if(HAS_CLOCK_REALTIME)
  add_definitions(-D_HAS_CLOCK_REALTIME)
endif()

add_fairroot_library(MbsAPI
  SOURCES
  f_evt.c
  fLmd.c
  f_ut_utime.c
  f_stccomm.c

  HEADERS
  fLmd.h
  s_evhe.h
  s_evhe_swap.h
  sMbs.h
  s_ves10_1.h
  s_ves10_1_swap.h
  s_ve10_1.h
  s_ve10_1_swap.h
  f_evt.h
  f_ut_utime.h
  s_bufhe.h
  s_bufhe_swap.h
  s_filhe.h
  s_filhe_swap.h
  portnum_def.h
  s_stdint.h
  typedefs.h
  f_stccomm.h

  INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/MbsAPI
)
