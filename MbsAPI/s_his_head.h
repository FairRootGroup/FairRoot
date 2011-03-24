// $Id: s_his_head.h 478 2009-10-29 12:26:09Z linev $
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum für Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

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
