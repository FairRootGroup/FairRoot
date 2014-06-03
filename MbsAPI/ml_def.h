/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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
