/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* filter structure for CLIENT */

struct s_clnt_filter {
  /* -------> Swapped <-------- */
  /* --------=========--------- */
  /* --- control byte ordering and machine type (2LW) ---- */
  unsigned long          l_testbit;       /* bit pattern               */
  unsigned long          l_endian;        /* endian of sender          */
  /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  long                   l_numb_of_evt;   /* numb of events to send    */
  long                   l_sample_rate;   /* flt match sample rate     */
  long                   l_flush_rate;    /* buffer flushing rate [sec]*/
  struct s_filter        filter[GPS__MAXFLT];/* 32 filter express (à 3LW) */
  struct s_flt_descr     flt_descr[GPS__MAXFLTDESCR]; /* Filter descriptor*/
  short unsigned         if_fltsev;      /* filter on subevent         */
  short unsigned         if_fltevt;      /* filter on event            */
  short unsigned         if_wrtsev;      /* write subevts (numb of sev)*/
  short unsigned         if_wrtevt;      /* write whole event          */
};
