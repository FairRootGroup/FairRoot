/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* filter structure for CLIENT */

#ifndef S_CINT_FILTER
#define S_CINT_FILTER

struct s_clnt_filter {
  /* --- control byte ordering and machine type (2LW) ---- */
  unsigned int          l_testbit;       /* bit pattern               */
  unsigned int          l_endian;        /* endian of sender          */
  /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  int                   l_numb_of_evt;   /* numb of events to send    */
  int                   l_sample_rate;   /* flt match sample rate     */
  int                   l_flush_rate;    /* buffer flushing rate [sec]*/
  struct s_filter        filter[GPS__MAXFLT];/* 32 filter express (à 3LW) */
  struct s_flt_descr     flt_descr[GPS__MAXFLTDESCR]; /* Filter descriptor*/
  short unsigned         if_fltevt;      /* filter on event            */
  short unsigned         if_fltsev;      /* filter on subevent         */
  short unsigned         if_wrtevt;      /* write whole event          */
  short unsigned         if_wrtsev;      /* write subevts (numb of sev)*/
};

#endif
