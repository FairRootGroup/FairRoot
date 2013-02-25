// $Id: s_flt_descr.h 478 2009-10-29 12:26:09Z linev $
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

/* filter descriptor */
struct s_flt_descr {
  char                   hf_wrtdescr;   /* write descriptor          */
  char                   hf_fltdescr;       /* filter descriptor         */
  /* indices to filter[]  */
  char                   h_fltblkbeg;   /* begin filter block        */
  char                   h_fltblkend;       /* end filter block          */
  /* index to flt_descr[] */
  char                   h_nextdescr;       /* next descriptor           */
  char                   h_dummy;
  short                  i_descriptors;     /* number of descriptors     */
};

