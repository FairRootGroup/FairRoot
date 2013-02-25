// $Id: s_clnt_filter_swap.h 478 2009-10-29 12:26:09Z linev $
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
