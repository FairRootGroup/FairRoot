// $Id: s_evhe.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef S_EVHE
#define S_EVHE

#include "typedefs.h"

#if MBS_ENDIAN == 1

/*  ================= GSI VME General event header ===============  */
typedef struct {
  INTS4  l_dlen;   /*  Length of data in words */
  INTS2 i_subtype;
  INTS2 i_type;
} s_evhe;
/* ------------------------------------------------------------------ */

#else

typedef struct {
  INTS4  l_dlen;   /*  Length of data in words */
  INTS2 i_type;
  INTS2 i_subtype;
} s_evhe;

#endif

#endif
