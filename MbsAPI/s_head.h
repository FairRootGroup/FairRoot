/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "typedefs.h"
/* s_head.h
 * ========
 * Purpose      : Histogram manager for SBS
 * Author       : Ilya Kuznetsov
 * Date         : 20-Sep-1994
 *
 * Modification : 11-Oct-1994 : Version number/RSM
 * Modification : 12-Oct-1994 : Text string/RSM
 * Modification : 10-Nov-1994 : flags for attach, detach etc. ??? /RSM
 * Modification : 15-Nov-1994 : Top-Slot-Index for name sort. /RSM
 * Modification : 22-Nov-1994 : Insertion of s_errstat with flag /RSM
 * Modification : 24-Jan-1995 : Identifier for histogram base /RSM
 * Modification : 24-Jul-1997 : Insert date /HE
 * Modification : 25-Aug-1999 : Insert counters /HE
 * Modification : 20-Jun-2001 : Insert autosave /HE
 */

#ifndef __S_ERRSTAT__
#include "s_errstat.h"
#endif

typedef struct {
  INTS4 l_endian;        /*  1 the length of the memory big piece     */
  INTS4 l_len;           /*  2 the length of the memory big piece     */
  INTS4 l_free;          /*  3 free room in that funny memory piece   */
  INTU4 ul_ofree;        /*  4 offset of the free room beginning      */
  INTS4 i_slot;          /*  5 no. of the funny slots requested       */
  INTS4 i_sfree;         /*  6 no. of the free funny slots            */
  INTS4 i_topslot;       /*  7 slot with first alphabetic name        */
  INTU4 ui_idbase;       /*  8 Identifier for a histogram base        */
  INTU4 l_version;       /*  9 version number for analysis check      */
  INTU4 l_segment;       /* 10 segment number                         */
  INTS4 bh_histogram;
  INTS4 bh_anal;
  INTS4 bh_lock;         /*    lock flag                     */
  INTS4 bh_free2;        /* 14                               */
  INTU4 l_events;        /* 15                               */
  INTU4 l_out_evts;      /* 16                               */
  INTU4 l_Lwords;        /* 17                               */
  INTU4 l_event_r;       /* 18                               */
  INTU4 l_kbyte_r;       /* 19                               */
  INTS4 l_running;       /* 20                               */
  REAL4 r_x1;            /* 21                               */
  REAL4 r_y1;            /* 22                               */
  REAL4 r_x2;            /* 23                               */
  REAL4 r_y2;            /* 24                               */
  struct s_errstat s_errstat_1;    /* 30 control block for f_error    */
  CHARS c_date[28];      /* 37 creation date                          */
  CHARS c_ident[32];     /* 45 process identification string          */
  CHARS c_shsegname[32]; /* 53 shared segment name string             */
  INTS4 l_points;        /* 54 number of polygon points                  */
  REAL4 r_x[32];         /* 86 x coordinates                             */
  REAL4 r_y[32];         /* 118 y coordinates                             */
  INTS4 l_cond_win;      /* 119 numer of window conditions */
  INTS4 l_cond_pol;      /* 120 numer of polygon conditions */
  INTS4 l_params;        /* 121 number of valid parameters in IDL exchange buffer */
  INTS4 l_param_type;    /* 122 meaning of parameters in IDL exchange buffer */
  INTS4 l_auto_sec;      /* 123 seconds till next autosave (0 is no autosave)          */
  INTS4 l_spare[5];      /* 5 spare                                  */
} s_head;
