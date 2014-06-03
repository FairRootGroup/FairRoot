/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef F_EVCLI
#define F_EVCLI

#include "f_evt.h"

int f_evcli_con(s_evt_channel* ps_chan, char* pc_node, int l_aport, int l_aevents, int l_asample);
int f_evcli_buf(s_evt_channel* ps_chan);
int f_evcli_evt(s_evt_channel* ps_chan);
int f_evcli_close(s_evt_channel* ps_chan);

#endif
