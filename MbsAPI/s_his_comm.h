/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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
