// $Id: f_his_hist.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef F_HIS_HIST
#define F_HIS_HIST

#include "typedefs.h"
#include "s_his_comm.h"
#include "s_his_head.h"

/* node, port, base, password, histogram, [header, ] buffer, size */
INTS4 f_his_getbas(CHARS*, INTS4, CHARS*, CHARS*, INTS4**);
INTS4 f_his_getdir(CHARS*, INTS4, CHARS*, CHARS*, CHARS*, INTS4**, INTS4*);
INTS4 f_his_gethis(CHARS*, INTS4, CHARS*, CHARS*, CHARS*, s_his_head**, INTS4**, INTS4*);
INTS4 f_his_server(CHARS*, CHARS*, INTS4*);
INTS4 f_his_wait(INTS4*, CHARS*);
INTS4 f_his_senddir(s_his_head*, INTS4);
INTS4 f_his_sendhis(s_his_head*, INTS4, CHARS*, INTS4*);
INTS4 f_his_close();

#endif
