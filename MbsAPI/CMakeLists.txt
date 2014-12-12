 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.
if (CMAKE_SYSTEM_NAME MATCHES Linux)
   ADD_DEFINITIONS(-DLinux  -DSYSTEM64  -D_LARGEFILE64_SOURCE)
endif (CMAKE_SYSTEM_NAME MATCHES Linux)

if (CMAKE_SYSTEM_NAME MATCHES Darwin)
   ADD_DEFINITIONS(-DDarwin  -DSYSTEM64  -D_LARGEFILE64_SOURCE)
endif (CMAKE_SYSTEM_NAME MATCHES Darwin)

Set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/MbsAPI
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

# List of source files
Set(MBSAPI_SRCS
  f_evt.c
  fLmd.c
  f_ut_utime.c
  f_stccomm.c
)

# list of header files
Set(MBSAPI_HEADERS
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
)

############### build the library #####################
add_library(MbsAPI SHARED ${MBSAPI_SRCS})
target_link_libraries(MbsAPI ${ROOT_LIBRARIES})
set_target_properties(MbsAPI PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})

############### install the library ###################

install(FILES ${MBSAPI_HEADERS}
        DESTINATION include
       )

install(TARGETS MbsAPI DESTINATION lib)
