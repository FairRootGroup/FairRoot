// $Id: f_evcli.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef F_EVCLI
#define F_EVCLI

#include "f_evt.h"

int f_evcli_con(s_evt_channel* ps_chan, char* pc_node, int l_aport, int l_aevents, int l_asample);
int f_evcli_buf(s_evt_channel* ps_chan);
int f_evcli_evt(s_evt_channel* ps_chan);
int f_evcli_close(s_evt_channel* ps_chan);

#endif
