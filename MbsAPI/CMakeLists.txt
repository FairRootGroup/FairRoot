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

set(INCLUDE_DIRECTORIES
    ${ROOT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/MbsAPI
   )

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
   )

link_directories( ${LINK_DIRECTORIES})

# List of source files
set(MBSAPI_SRCS
    f_evcli.c
    f_evt.c
    fLmd.c
    f_radware.c
    f_ut_utime.c
    f_ut_wild.c
    f_his_hist.c
    f_his_swpbas.c
    f_his_toupper.c
    f_mbs_status.c
    f_stccomm.c
    f_swaplw.c
    f_ut_compress.c
    f_ut_seg_show.c
    f_ut_status.c
    f_ut_time.c

   )
# list of header files
set(MBSAPI_HEADERS
    clnt_buf_def.h
    fLmd.h
    gps_sc_def.h
    s_clntbuf.h
    s_evhe.h
    s_filter.h
    sMbs.h
    s_spe.h
    s_ves10_1_swap.h
    f_evcli.h
    f_radware.h
    mo_def.h
    s_clnt_filter.h
    s_evhe_swap.h
    s_flt_descr.h
    s_opc1.h
    s_ve10_1.h
    s_win_cond.h
    f_evt.h
    f_ut_utime.h
    s_bufhe.h
    s_clnt_filter_swap.h
    s_filhe.h
    s_flt_descr_swap.h
    s_pat.h
    s_ve10_1_swap.h
    f_ut_wild.h
    s_bufhe_swap.h
    s_errstat.h
    s_filhe_swap.h
    s_head.h
    s_pol_cond.h
    s_ves10_1.h
    err_mask_def.h
    f_his_hist.h
    f_his_toupper.h
    f_swaplw.h
    f_ut_status.h
    portnum_def.h
    s_daqst.h
    s_endian.h
    s_his_head.h
    s_set_mo.h
    s_stdint.h
    typedefs.h
    errnum_def.h
    f_his_swpbas.h
    f_stccomm.h
    f_ut_compress.h
    ml_def.h
    sbs_def.h
    s_daqst_v2.h
    s_his_comm.h
    s_set_ml.h
    s_setup.h
    sys_def.h
    typedefs_nt.h
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
