// $Id: s_bufhe.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef S_BUFHE
#define S_BUFHE

#include "typedefs.h"
/* Generated from SA$BUFHE.TXT  */
/* Swapping enabled           */
/*  ================= GSI Buffer header =======================  */
#define MAX__DLEN 16360

#if MBS_ENDIAN == 1

typedef struct {
  INTS4  l_dlen;   /*  Length of data field in words */
  INTS2 i_subtype;
  INTS2 i_type;
  CHARS  h_begin;   /*  Fragment at end of buffer */
  CHARS  h_end;   /*  Fragment at begin of buffer */
  INTS2 i_used;   /*  Used length of data field in words */
  INTS4  l_buf;   /*  Current buffer number */
  INTS4  l_evt;   /*  Number of fragments */
  INTS4  l_current_i;   /*  Index, temporarily used */
  INTS4  l_time[2];
  INTS4  l_free[4];
} s_bufhe;

#else

typedef struct {
  INTS4  l_dlen;   /*  Length of data field in words */
  INTS2 i_type;
  INTS2 i_subtype;
  INTS2 i_used;   /*  Used length of data field in words */
  CHARS  h_end;   /*  Fragment at begin of buffer */
  CHARS  h_begin;   /*  Fragment at end of buffer */
  INTS4  l_buf;         /*  Current buffer number */
  INTS4  l_evt;         /*  Number of fragments */
  INTS4  l_current_i;   /*  Index, temporarily used */
  INTS4  l_time[2];
  INTS4  l_free[4];
} s_bufhe;

#endif

#endif
