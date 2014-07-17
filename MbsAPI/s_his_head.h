/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef S_HIS_HEAD
#define S_HIS_HEAD

#include "typedefs.h"

/* histogram header sent by histogram server */
typedef struct {
  INTS4 l_bins_1;               /* number of bins in dim=1        */
  INTS4 l_bins_2;               /* number of bins in dim=2 (>=1)  */
  /* + + +  dim = 1  + + + */
  INTS4 l_outlim_up_counts;     /* no of counts that are          */
  INTS4 l_outlim_low_counts;    /* out of range                   */
  REAL4 r_limits_low;           /* upper limit                    */
  REAL4 r_limits_up;            /* lower limit                    */
  REAL4 r_binsize;              /* bin size                       */
  REAL4 r_factor;               /* linear trans.                  */
  REAL4 r_offset;               /* offset                         */
  /* + + +  dim = 2  + + + */
  INTS4 l_outlim_up_counts_2;   /* no of counts that are          */
  INTS4 l_outlim_low_counts_2;  /* out of range                   */
  REAL4 r_limits_low_2;         /* energy limits dim = 2          */
  REAL4 r_limits_up_2;          /* energy limits dim = 2          */
  REAL4 r_binsize_2;            /* bin size                       */
  REAL4 r_factor_2;             /* linear trans.                  */
  REAL4 r_offset_2;
  /* +++ character strings +++ */
  CHARS c_name[64];             /* histogram name                 */
  CHARS c_dtype[4];             /* data flag                      */
  CHARS c_data_time_cre[28];    /* creation time                  */
  CHARS c_clear_date[28];       /* clearing time                  */
  CHARS c_lettering_res[64];    /* lettering data content         */
  CHARS c_lettering_1[64];      /* lettering 1st axis             */
  CHARS c_lettering_2[64];      /* lettering 2nd axis             */
} s_his_head ;

#endif
