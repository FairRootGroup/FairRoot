// $Id: s_his_comm.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef S_HIS_COMM
#define S_HIS_COMM

#include "typedefs.h"

#define COMM__PORT     6009
#define COMM__GETDIR   1
#define COMM__GETHIST  2
#define COMM__PUTDIR   3
#define COMM__PUTHIST  4
#define COMM__EXIT     5
#define COMM__GETBASE  6
#define COMM__PUTBASE  7
#define COMM__SUCCESS  0
#define COMM__ERROR    -1
#define COMM__NOACCESS -2
#define COMM__NOBASE   -3
#define COMM__NOSERVER -4
#define COMM__NOHIST   -5

/* structure for communication between histogram server and client */
typedef struct {
  INTU4 lu_endian;    /* set = 1 by sender, checked by receiver */
  INTU4 lu_action;    /* what to do, defined by COM__xxx        */
  INTU4 lu_histos;    /* returned number of histograms                   */
  INTU4 lu_size;      /* returned number of bytes of following buffer    */
  INTS4 l_status;     /* completion status, COMM_xxx        */
  CHARS c_access[32]; /* password depending on server       */
  CHARS c_base[32];   /* base name depending on server      */
  CHARS c_histo[64];  /* histogram name                     */
} s_his_comm;

#endif
