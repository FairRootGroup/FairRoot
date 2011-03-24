// $Id: ml_def.h 478 2009-10-29 12:26:09Z linev $
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
/*
 * N. Kurz 11-Jan-1996
 * global definitions for multi-branch multi-layer system
 */
#define ML__N_RD_PIPE    16 /* maximal nr. of pipes a mb ml node can read */
#define ML__N_NODE       32 /* maximal nr. nodes in mb ml (without br master */

#define ML__SETUP_TAB    "ml_setup"
#define ML__WR_PIPE_NAME "ml_write_pipe"
#define ML__RD_PIPE_NAME "ml_read_pipe"
