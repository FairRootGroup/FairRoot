/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef S_OPC1
#define S_OPC1

#include "typedefs.h"

#if MBS_ENDIAN == 1

struct s_opc1 {                         /* ++ byte1 (LSB) ++ */
  char          h_flt_len;          /* ++ byte4 (MSB) ++ length of filter*/
  char          h_next_fltblk;      /* ++ byte3 ++  next filter blk      */
  char          h_fltspec;          /* ++ byte2  filter specification */
  /* +++ 25-Jan-1994 reversed bit sequence +++ */
  unsigned      b1_lnkf2 :1;        /* lnk different flts blks   */
  unsigned      b1_lnkf1 :1;        /* lnk filters: and:1 or:0   */
  unsigned      b3_opc   :3;        /* opcode                    */
  unsigned      b1_selwrt:1;        /* select write of evt/sev          */
  unsigned      b1_selflt:1;        /* select event/subevent filter */
  unsigned      b1_evtsev :1;       /* 1:event/0:subevt active for sel */
  /* REM : h_next_fltblk and h_flt_len are ABSOLUTE adresses  !!! */
};


#else

/* struct for filter opcode                  */
struct s_opc1 {
  /* ++ byte1 (LSB) ++ */
  unsigned      b1_evtsev :1;       /* 1:event/0:subevt active for sel */
  unsigned      b1_selflt:1;        /* select event/subevent filter */
  unsigned      b1_selwrt:1;        /* select write of evt/sev          */
  unsigned      b3_opc   :3;        /* opcode                    */
  unsigned      b1_lnkf1 :1;        /* lnk filters: and:1 or:0   */
  unsigned      b1_lnkf2 :1;        /* lnk different flts blks   */
  char          h_fltspec;          /* ++ byte2  filter specification */
  char          h_next_fltblk;      /* ++ byte3 ++  next filter blk      */
  char          h_flt_len;          /* ++ byte4 (MSB) ++ length of filter*/
};

/* REM : h_next_fltblk and h_flt_len are ABSOLUTE adresses  !!! */

#endif

#endif
