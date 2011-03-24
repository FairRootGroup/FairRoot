// $Id: s_spe.h 478 2009-10-29 12:26:09Z linev $
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

#include "typedefs.h"
/* s_spe.h
 * =======
 *
 * Author   :     Ilya Kutznetsov, R. S. Mayer
 * Created  :     20-Sep-1994
 *
 * modified :     14-Oct-1994 Prepared for 2-dim histograms /RSM
 *                15-Nov-1994 Slot numbers for binary tree. /RSM
 *                02-Dec-1994 align structure. /RSM
 */

#define HIS__HISNAMLEN 32         /* max lenght of histogram name string     */

typedef struct {
  INTU4 ul_attr;                /*  flag                          */
  INTS4 l_version;              /* structure version mumber       */
  INTS4 i_slotlef;              /* next slot left (sort)          */
  INTS4 i_slotrig;              /* next slot right (sort)         */
  INTS4 l_protected;            /* clear histogram?               */
  INTS4 l_bins_1;               /* number of bins in dim=1        */
  INTS4 l_bins_2;               /* number of bins in dim=2        */
  INTS4 l_dim;                  /* dimension size                 */
  INTS4 l_data;                 /* relative pointer to data,      */
  INTU4 l_counts;               /* total sum of counts            */
  REAL8 d_contents;             /* total sum of counts            */
  INTU4 l_spare1;               /* spare                          */
  INTU4 l_spare2;               /* spare                          */
  INTU4 l_spare3;               /* spare                          */
  INTU4 l_spare4;               /* spare                          */
  INTU4 l_spare5;               /* spare                          */
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
  CHARS c_name[HIS__HISNAMLEN]; /* spect's name                   */
  CHARS c_dtype[4];             /* data flag                      */
  CHARS c_data_time_cre[28];    /* creation time                  */
  CHARS c_clear_date[28];       /* clearing time                  */
  CHARS c_lettering_res[64];    /* lettering data content         */
  CHARS c_lettering_1[64];      /* lettering 1st axis             */
  CHARS c_lettering_2[64];      /* lettering 2nd axis             */
} s_spe ;
