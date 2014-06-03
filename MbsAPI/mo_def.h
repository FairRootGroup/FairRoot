/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* N.Kurz  8-Jun-1998 */
/* N.Kurz 30-May-2000 updated */

#include "typedefs.h"

#define MO__TCP_MSG_DAQSTAT 0x101
#define MO__TCP_MSG_DATREQ  0x102
#define MO__TCP_MSG_ACKREQ1 0x103
#define MO__TCP_MSG_ACKREQ2 0x104

#define MO__DATREQ_SIZE      12
#define MO__ACKN1_SIZE       32

#define MO__N_NODE           16
/* maximal nr. of ds and dr nodes each in a system */

#define MO__SETUP_TAB        "mo_setup"

#define MO__RD_PIPE_NAME     "mo_read_pipe"
/* generic name, will be expanded by the ds node id */

#define MO__EVT_BUF_NAME     "evt_buf"
/* intermediate event buffer                        */

#define RIO2__SLAVE_VME_PIPE_OFF  0x200000
#define RIO2__SLAVE_VME_WIN_SIZE  0x1000000
#define RIO2__PCI_OFFSET          0x80000000


#define DLEB__TCP_INFO      0x201
#define DLEB__INFO_SIZE       12
#define DLEB__CONNECT_RETRY   5
