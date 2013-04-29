// $Id: s_ve10_1.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef S_VE10_1
#define S_VE10_1

#include "typedefs.h"
/*  ================= GSI VME Event header =======================  */

#if MBS_ENDIAN == 1

typedef struct {
  INTS4  l_dlen;   /*  Data length + 4 in words */
  INTS2 i_subtype;
  INTS2 i_type;
  INTS2 i_trigger;   /*  Trigger number */
  INTS2 i_dummy;   /*  Not used yet */
  INTS4  l_count;   /*  Current event number */
} s_ve10_1;
/* ------------------------------------------------------------------ */

#else

typedef struct {
  INTS4  l_dlen;   /*  Data length + 4 in words */
  INTS2 i_type;
  INTS2 i_subtype;
  INTS2 i_dummy;   /*  Not used yet */
  INTS2 i_trigger;   /*  Trigger number */
  INTS4  l_count;   /*  Current event number */
} s_ve10_1;

#endif

#endif
